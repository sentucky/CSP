//================================================================================
// CSound.cpp
//
// �T�E���h�N���X											
//--------------------------------------------------------------------------------
// �X�V����
//	2011/1/4
//		�쐬�J�n
//================================================================================
//================================================================================
// �}�N����`
//================================================================================

//================================================================================
// �C���N���[�h
//================================================================================
#include <sstream>
#include "CSound.h"
#include "CWindow.h"
#include "CDevice.h"


//================================================================================
// �N���X�֐��錾
//================================================================================
//�R���X�g���N�^
CSound::CSound() : _pDSound(NULL),_pDSoundPrimary(NULL)
{}

//�f�X�g���N�^
CSound::~CSound()
{}

//������
HRESULT CSound::Init()
{
	HRESULT hr;

	//�T�E���h�f�o�C�X���쐬����Ă��Ȃ����
	if(!_pDSound)
	{
		// DirectSound�I�u�W�F�N�g�̍쐬
		hr = DirectSoundCreate8(NULL,&_pDSound,NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL,"DirectSound�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B","�G���[",MB_OK | MB_ICONWARNING);
			return S_FALSE;
		}
	}

	//�������[�h�ݒ�
	hr = _pDSound->SetCooperativeLevel(WINDOW->getWnd(),DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSound�������x���ݒ�Ɏ��s���܂����B","�G���[",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	//�v���C�}���o�b�t�@�̍쐬
	//�����̃Z�J���_���o�b�t�@����̃T�E���h���~�L�T�[���Ă܂Ƃ߂�o�b�t�@
	//�����Đ��Ƃ��ɕK�v
	DSBUFFERDESC dsdesc;						//�T�E���h�o�b�t�@�쐬�̂��߂̍\����
	ZeroMemory(&dsdesc,sizeof(DSBUFFERDESC));	
	dsdesc.dwSize = sizeof(DSBUFFERDESC);		
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER		//�v���C�}���o�b�t�@�ł��邱�Ƃ��`
		| DSBCAPS_CTRLVOLUME					//�{�����[���ύX��L����
		| DSBCAPS_CTRLPAN;						//�p����L���ɂ���
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;

	hr = _pDSound->CreateSoundBuffer(&dsdesc,&_pDSoundPrimary,NULL);	//�v���C�}���o�b�t�@���쐬
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSound�v���C�}���o�b�t�@�̍쐬�Ɏ��s���܂����B","�G���[",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	//�v���C�}���o�b�t�@�̐ݒ�
	//CD�������x���ɐݒ�
	WAVEFORMATEX wf;
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	wf.cbSize = sizeof(WAVEFORMAT);
	wf.wFormatTag = WAVE_FORMAT_PCM;	//�`��(PCM)
	wf.nChannels = 2;					//�`�����l��(2ch�X�e���I)
	wf.nSamplesPerSec = 44100;			//�T���v�����O�O���[�h
	wf.wBitsPerSample = 16;				//�ʎq���r�b�g(16bit)
	wf.nBlockAlign = 4;					//1�T���v�����O������̃o�C�g��(16bit * 2ch)
	wf.nAvgBytesPerSec = 176400;		//1�b������̃o�C�g��(16bit * 2ch * 4410Hz)
	hr = _pDSoundPrimary->SetFormat(&wf);
	if (FAILED(hr))
	{
		MessageBox(NULL,"DirectSound�v���C�}���o�b�t�@�̐ݒ�Ɏ��s���܂����B","�G���[",MB_OK | MB_ICONWARNING);
		return S_FALSE;
	}

	return S_OK;
}

//�I��
void CSound::Uninit()
{
	//�}�b�v�̉��(�Z�J���_���o�b�t�@)
	const uint size = _soundVector.size();

	for( uint i = 0; i < size; ++i)
	{
		SAFE_RELEASE(_soundVector[i]);
	}
	_soundVector.clear();

	//�v���C�}���o�b�t�@�̉��
	SAFE_RELEASE(_pDSoundPrimary);

	//�T�E���h�f�o�C�X�̉��
	SAFE_RELEASE(_pDSound);
}

//WAV�T�E���h�f�[�^�̓ǂݍ���
HRESULT CSound::LoadSoundFile(const uint keyName,char* fileName)
{
	HRESULT hr;


	/*CSOUNDMAPITR itr =*/
	_soundVector[keyName];
	if (_soundVector[keyName] != NULL)
	{
		//���s�̕�
		std::ostringstream oss;
		oss << "�����C���X�^���X���ŃT�E���h�����[�h���悤�Ƃ��܂����B\n�C���X�^���X���F" << keyName << "\n";
		MessageBox(NULL,oss.str().c_str(),"�G���[",MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	LPDIRECTSOUNDBUFFER pDSoundSecondry;	//�Z�J���_���o�b�t�@
    MMCKINFO mSrcWaveFile;
    MMCKINFO mSrcWaveFmt;
    MMCKINFO mSrcWaveData;
    LPWAVEFORMATEX wf;

	//WinApi�ɂ��WAV�t�@�C���̒��o
    // WAV�t�@�C�������[�h
    HMMIO hSrc;
    hSrc = mmioOpen(fileName,NULL,MMIO_ALLOCBUF|MMIO_READ|MMIO_COMPAT);
    if( !hSrc ) {
        MessageBox(NULL,"DirectSound WAV�t�@�C�����[�h�G���[\n","�G���[",MB_OK | MB_ICONERROR);
        return E_FAIL;
    }

    // 'WAVE'�`�����N�`�F�b�N
    ZeroMemory( &mSrcWaveFile,sizeof(mSrcWaveFile) );
    hr = mmioDescend( hSrc,&mSrcWaveFile,NULL,MMIO_FINDRIFF );
    if( mSrcWaveFile.fccType!=mmioFOURCC('W','A','V','E') ) {
        MessageBox(NULL,"DirectSound WAV�`�����N�`�F�b�N�G���[\n","�G���[",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // 'fmt '�`�����N�`�F�b�N
    ZeroMemory( &mSrcWaveFmt,sizeof(mSrcWaveFmt) );
    hr = mmioDescend( hSrc,&mSrcWaveFmt,&mSrcWaveFile,MMIO_FINDCHUNK );
    if( mSrcWaveFmt.ckid!=mmioFOURCC('f','m','t',' ') ) {
        MessageBox(NULL,"DirectSound fmt �`�����N�`�F�b�N�G���[\n","�G���[",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // �w�b�_�T�C�Y�̌v�Z
    int iSrcHeaderSize = mSrcWaveFmt.cksize;
    if( iSrcHeaderSize<sizeof(WAVEFORMATEX) )
	{
        iSrcHeaderSize=sizeof(WAVEFORMATEX);
	}

    // �w�b�_�������m��
    wf = (LPWAVEFORMATEX)malloc( iSrcHeaderSize );
    if( !wf ) {
        MessageBox(NULL,"DirectSound �������m�ۃG���[\n","�G���[",MB_OK | MB_ICONERROR);
        mmioClose( hSrc,0 );
        return E_FAIL;
    }
    ZeroMemory( wf,iSrcHeaderSize );

    // WAVE�t�H�[�}�b�g�̃��[�h
    hr = mmioRead( hSrc,(char*)wf,mSrcWaveFmt.cksize );
    if( FAILED(hr) ) {
        MessageBox(NULL,"DirectSound WAVE�t�H�[�}�b�g���[�h�G���[\n","�G���[",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // fmt�`�����N�ɖ߂�
    mmioAscend( hSrc,&mSrcWaveFmt,0 );

    // data�`�����N��T��
    while(1) {
        // ����
        hr = mmioDescend( hSrc,&mSrcWaveData,&mSrcWaveFile,0 );
        if( FAILED(hr) ) {
			MessageBox(NULL,"DirectSound data�`�����N��������Ȃ�\n","�G���[",MB_OK | MB_ICONERROR);
            free( wf );
            mmioClose( hSrc,0 );
            return E_FAIL;
        }
        if( mSrcWaveData.ckid==mmioStringToFOURCC("data",0) )
            break;
        // ���̃`�����N��
        hr = mmioAscend( hSrc,&mSrcWaveData,0 );
    }

    // �T�E���h�o�b�t�@�̍쐬
    DSBUFFERDESC dsdesc;
    ZeroMemory( &dsdesc,sizeof(DSBUFFERDESC) );
    dsdesc.dwSize = sizeof( DSBUFFERDESC );
    dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2	//�Đ��ʒu�̎擾���\��
		| DSBCAPS_STATIC 
		| DSBCAPS_LOCDEFER 
		| DSBCAPS_GLOBALFOCUS;						//��A�N�e�B�u�Đ�
    dsdesc.dwBufferBytes = mSrcWaveData.cksize;
    dsdesc.lpwfxFormat = wf;
    dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
    hr = _pDSound->CreateSoundBuffer( &dsdesc,&pDSoundSecondry,NULL );
    if( FAILED(hr) ) {
		MessageBox(NULL,"DirectSound �T�E���h�o�b�t�@�̍쐬�G���[\n","�G���[",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // ���b�N�J�n
    LPVOID pMem1,pMem2;
    DWORD dwSize1,dwSize2;
    hr = pDSoundSecondry->Lock( 0,mSrcWaveData.cksize,&pMem1,&dwSize1,&pMem2,&dwSize2,0 );
    if( FAILED(hr) ) {
		MessageBox(NULL,"���b�N���s\n","�G���[",MB_OK | MB_ICONERROR);
        free( wf );
        mmioClose( hSrc,0 );
        return E_FAIL;
    }

    // �f�[�^��������
    mmioRead( hSrc,(char*)pMem1,dwSize1 );
    mmioRead( hSrc,(char*)pMem2,dwSize2 );

    // ���b�N����
    pDSoundSecondry->Unlock( pMem1,dwSize1,pMem2,dwSize2 );

    // �w�b�_�p���������J��
    free( wf );

    // WAV�����
    mmioClose( hSrc,0 );

	//����������}�b�v�o�^
	if (pDSoundSecondry != NULL)
	{
		//�I�u�W�F�N�g���C���T�[�g
		_soundVector[keyName] = pDSoundSecondry;
//		_soundMap.insert(CSOUNDPAIR(keyName,pDSoundSecondry));
	}

	return S_OK;
}

//�T�E���h�f�[�^�̎擾
LPDIRECTSOUNDBUFFER CSound::GetSound(const uint KeyName)
{

	//���̖��O������΃|�C���^��Ԃ�
	if ( _soundVector.size() > 0)
	{
		return _soundVector[KeyName];
	}

	//�������NULL��Ԃ�
	return NULL;
}


void CSound::reserve(const uint size)
{
	_soundVector.reserve(size);
	_soundVector.resize(size);
}
