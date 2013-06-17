/***********************************************************************/
/*! @file  CSound.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//================================================================================
// CSound.h
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
#ifndef __CSOUND_H__
#define __CSOUND_H__

#define CSOUNDMAP		std::map<std::string,LPDIRECTSOUNDBUFFER>
#define CSOUNDMAPITR	std::map<std::string,LPDIRECTSOUNDBUFFER>::iterator
#define CSOUNDPAIR		std::pair<std::string,LPDIRECTSOUNDBUFFER>

#define CSOUND CSound::getInst()

//================================================================================
// インクルード
//================================================================================
//#include <map>
//#include <string>
//#include "main.h"
#include "CSingleton.h"
#include <dsound.h>
#include<vector>

typedef std::vector<LPDIRECTSOUNDBUFFER> CSOUNDVECTOR;
typedef std::vector<LPDIRECTSOUNDBUFFER>::iterator CSOUNDVECYORITR;

#pragma comment ( lib, "dsound.lib" )
//================================================================================
// クラス定義
//================================================================================
class CSound : public CSingleton<CSound>
{
	friend class CSingleton<CSound>;

public:
	//===========================
	// メンバ関数 - 公開
	//===========================
	//デストラクタ
	~CSound();

	//初期化
	HRESULT Init();
	//終了
	void Uninit();

	//WAVサウンドデータの読み込み
	HRESULT LoadSoundFile(const uint keyName, char* fileName);

	//サウンドデータの取得
	LPDIRECTSOUNDBUFFER GetSound(const uint Key);

	void reserve(const uint size);

private:
	//===========================
	// メンバ関数 - 非公開
	//===========================
	//コンストラクタ
	CSound();
	//===========================
	// メンバ変数 - 非公開
	//===========================
	LPDIRECTSOUND8		_pDSound;			///<サウンドデバイス
	LPDIRECTSOUNDBUFFER _pDSoundPrimary;	///<プライマリバッファ
	CSOUNDVECTOR		_soundVector;			///<セカンダリバッファのベクタ
};

#endif		//__CSOUND_H