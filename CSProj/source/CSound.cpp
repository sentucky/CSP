//================================================================================
// CSound.cpp
//
// サウンドクラス											
//--------------------------------------------------------------------------------
// 更新履歴
//	2011/1/4
//		作成開始
//================================================================================
//================================================================================
// マクロ定義
//================================================================================

//================================================================================
// インクルード
//================================================================================
#include <sstream>
#include "CSound.h"
#include "CWindow.h"
#include "CDevice.h"


//================================================================================
// クラス関数宣言
//================================================================================
//コンストラクタ
CSound::CSound() : _pDSound(NULL),_pDSoundPrimary(NULL)
{}

//デストラクタ
CSound::~CSound()
{}

//初期化
HRESULT CSound::Init()
{
	HRESULT hr;

	//サウンドデバイスが作成されていなければ
	if(!_pDSound)
	{
		// DirectSoundオブジェクトの作成
		hr = DirectSoundCreate8(NULL,&_pDSound,NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL,"DirectSoundオブジェクトの作成に失敗しました。","エラー",MB_OK | MB_ICONWARNING);
			return S_FALSE;
		}
	}

	//協調モード設定
	hr = _pDSound->SetCooperativeLevel(WINDOW->getWnd(),DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSound協調レベル設定に失敗しました。","エラー",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	//プライマリバッファの作成
	//複数のセカンダリバッファからのサウンドをミキサーしてまとめるバッファ
	//同時再生とかに必要
	DSBUFFERDESC dsdesc;						//サウンドバッファ作成のための構造体
	ZeroMemory(&dsdesc,sizeof(DSBUFFERDESC));	
	dsdesc.dwSize = sizeof(DSBUFFERDESC);		
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER		//プライマリバッファであることを定義
		| DSBCAPS_CTRLVOLUME					//ボリューム変更を有効に
		| DSBCAPS_CTRLPAN;						//パンを有効にする
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	hr = _pDSound->CreateSoundBuffer(&dsdesc,&_pDSoundPrimary,NULL);	//プライマリバッファを作成
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSoundプライマリバッファの作成に失敗しました。","エラー",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	//プライマリバッファの設定
	//CD音源レベルに設定
	WAVEFORMATEX wf;
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	wf.cbSize = sizeof(WAVEFORMAT);
	wf.wFormatTag = WAVE_FORMAT_PCM;	//形式(PCM)
	wf.nChannels = 2;					//チャンネル(2chステレオ)
	wf.nSamplesPerSec = 44100;			//サンプリンググレード
	wf.wBitsPerSample = 16;				//量子化ビット(16bit)
	wf.nBlockAlign = 4;					//1サンプリングあたりのバイト数(16bit * 2ch)
	wf.nAvgBytesPerSec = 176400;		//1秒あたりのバイト数(16bit * 2ch * 4410Hz)
	hr = _pDSoundPrimary->SetFormat(&wf);
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSoundプライマリバッファの設定に失敗しました。","エラー",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	return S_OK;
}

//終了
void CSound::Uninit()
{
	//マップの解放(セカンダリバッファ)
	const uint size = _soundVector.size();

	for( uint i = 0; i < size; ++i)
	{
		SAFE_RELEASE(_soundVector[i]);
	}
	_soundVector.clear();

	//プライマリバッファの解放
	SAFE_RELEASE(_pDSoundPrimary);

	//サウンドデバイスの解放
	SAFE_RELEASE(_pDSound);
}

//WAVサウンドデータの読み込み
HRESULT CSound::LoadSoundFile(const uint keyName,char* fileName)
{
	HRESULT hr;


	/*CSOUNDMAPITR itr =*/
	_soundVector[keyName];
	if (_soundVector[keyName] != NULL)
	{
		//失敗の報告
		std::ostringstream oss;
		oss << "同じインスタンス名でサウンドをロードしようとしました。\nインスタンス名：" << keyName << "\n";
		MessageBox(NULL,oss.str().c_str(),"エラー",MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	LPDIRECTSOUNDBUFFER pDSoundSecondry;	//セカンダリバッファ
    MMCKINFO mSrcWaveFile;
    MMCKINFO mSrcWaveFmt;
    MMCKINFO mSrcWaveData;
    LPWAVEFORMATEX wf;

	//WinApiによるWAVファイルの抽出
    // WAVファイルをロード
    HMMIO hSrc;
    hSrc = mmioOpen(fileName,NULL,MMIO_ALLOCBUF|MMIO_READ|MMIO_COMPAT);
    if( !hSrc ) {
        MessageBox(NULL,"DirectSound WAVファイルロードエラー\n","エラー",MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // 'WAVE'チャンクチェック
    ZeroMemory( &mSrcWaveFile,sizeof(mSrcWaveFile) );
    hr = mmioDescend( hSrc,&mSrcWaveFile,NULL,MMIO_FINDRIFF );
    if( mSrcWaveFile.fccType!=mmioFOURCC('W','A','V','E') ) {
        MessageBox(NULL,"DirectSound WAVチャンクチェックエラー\n","エラー",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // 'fmt 'チャンクチェック
    ZeroMemory( &mSrcWaveFmt,sizeof(mSrcWaveFmt) );
    hr = mmioDescend( hSrc,&mSrcWaveFmt,&mSrcWaveFile,MMIO_FINDCHUNK );
    if( mSrcWaveFmt.ckid!=mmioFOURCC('f','m','t',' ') ) {
        MessageBox(NULL,"DirectSound fmt チャンクチェックエラー\n","エラー",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // ヘッダサイズの計算
    int iSrcHeaderSize = mSrcWaveFmt.cksize;
    if( iSrcHeaderSize<sizeof(WAVEFORMATEX) )
	{
        iSrcHeaderSize=sizeof(WAVEFORMATEX);
	}

    // ヘッダメモリ確保
    wf = (LPWAVEFORMATEX)malloc( iSrcHeaderSize );
    if( !wf ) {
        MessageBox(NULL,"DirectSound メモリ確保エラー\n","エラー",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }
    ZeroMemory( wf,iSrcHeaderSize );

    // WAVEフォーマットのロード
    hr = mmioRead( hSrc,(char*)wf,mSrcWaveFmt.cksize );
    if( FAILED(hr) ) {
        MessageBox(NULL,"DirectSound WAVEフォーマットロードエラー\n","エラー",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // fmtチャンクに戻る
    mmioAscend( hSrc,&mSrcWaveFmt,0 );

    // dataチャンクを探す
    while(1) {
        // 検索
        hr = mmioDescend( hSrc,&mSrcWaveData,&mSrcWaveFile,0 );
        if( FAILED(hr) ) {
			MessageBox(NULL,"DirectSound dataチャンクが見つからない\n","エラー",MB_OK | MB_ICONERROR);
            free( wf );
            mmioClose( hSrc,0 );
            return E_FAIL;
        }
        if( mSrcWaveData.ckid==mmioStringToFOURCC("data",0) )
            break;
        // 次のチャンクへ
        hr = mmioAscend( hSrc,&mSrcWaveData,0 );
    }

    // サウンドバッファの作成
    DSBUFFERDESC dsdesc;
    ZeroMemory( &dsdesc,sizeof(DSBUFFERDESC) );
    dsdesc.dwSize = sizeof( DSBUFFERDESC );
    dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2	//再生位置の取得を可能に
		| DSBCAPS_STATIC 
		| DSBCAPS_LOCDEFER 
		| DSBCAPS_GLOBALFOCUS;						//非アクティブ再生
    dsdesc.dwBufferBytes = mSrcWaveData.cksize;
    dsdesc.lpwfxFormat = wf;
    dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
    hr = _pDSound->CreateSoundBuffer( &dsdesc,&pDSoundSecondry,NULL );
    if( FAILED(hr) ) {
		MessageBox(NULL,"DirectSound サウンドバッファの作成エラー\n","エラー",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // ロック開始
    LPVOID pMem1,pMem2;
    DWORD dwSize1,dwSize2;
    hr = pDSoundSecondry->Lock( 0,mSrcWaveData.cksize,&pMem1,&dwSize1,&pMem2,&dwSize2,0 );
    if( FAILED(hr) ) {
		MessageBox(NULL,"ロック失敗\n","エラー",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // データ書き込み
    mmioRead( hSrc,(char*)pMem1,dwSize1 );
    mmioRead( hSrc,(char*)pMem2,dwSize2 );

    // ロック解除
    pDSoundSecondry->Unlock( pMem1,dwSize1,pMem2,dwSize2 );

    // ヘッダ用メモリを開放
    free( wf );

    // WAVを閉じる
    mmioClose( hSrc,0 );

	//成功したらマップ登録
	if (pDSoundSecondry != NULL)
	{
		//オブジェクトをインサート
		_soundVector[keyName] = pDSoundSecondry;
//		_soundMap.insert(CSOUNDPAIR(keyName,pDSoundSecondry));
	}

	return S_OK;
}

//サウンドデータの取得
LPDIRECTSOUNDBUFFER CSound::GetSound(const uint KeyName)
{

	//その名前があればポインタを返す
	if ( _soundVector.size() > 0)
	{
		return _soundVector[KeyName];
	}

	//無ければNULLを返す
	return NULL;
}


void CSound::reserve(const uint size)
{
	_soundVector.reserve(size);
	_soundVector.resize(size);
}
