/***********************************************************************/
/*! @file  CTextureFactory.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	
//	概要			
//	制作者		
//	更新履歴		
/***********************************************************************/
//===================================================================
//	インクルードガード
//===================================================================
#pragma once
//===================================================================
//	インクルード
//===================================================================
#include<vector>
#include"CDevice.h"
#include"CTexture.h"
#include"CSingleton.h"

using namespace std;

//===================================================================
//	マクロ定義
//===================================================================
#define TEXTUREFACTORY CTextureFactory::getInst()
//===================================================================
//	クラス定義
//=================================================================== 
class CTextureFactory:public CSingleton<CTextureFactory>
{
	/////////////////////////
	//	変数型定義
	typedef vector<CTexture*>vec_texture;				///<テクスチャのマップコンテナ

	/////////////////////////
	//	フレンド登録
	friend class CSingleton< CTextureFactory>;
	//===========================================
	//	コンストラクタ	
	//===========================================
private:
	CTextureFactory();

	//===========================================
	//	デストラクタ		
	//===========================================
	~CTextureFactory();

	//===========================================
	//	メンバ関数		
	//===========================================
public:
	void reserve(const uint uReserveSize);
	BOOL registTexture(const int nId,const char* pszTextureFilePath);
	BOOL releaseTexture(const int nId);
	CTexture* getTexture(const int nId);


	//===========================================
	//	メンバ変数		
	//===========================================
private:
	vec_texture		_vecTexture;		///<テクスチャのコピー元
};
//EOF