/***********************************************************************/
/*! @file  CSprite.h
 *  @brief スプライトクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルードガード
/***********************************************************************/
#pragma once

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include <d3d9.h>
#include <d3dx9.h>
#include"CDevice.h"	//デバイスヘッダ
#include"CTexture.h"
#include"common.h"
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


const DWORD kdwColorRevisionMax = 0xffffffff;
/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CSprite
{
	//	フレンド登録
	friend class CSpriteFactory;	///<スプライトファクトリ

public:
	explicit CSprite(CTexture* pTexture);
	CSprite(const CSprite& copy);
	virtual~CSprite();

public:
	//---初期化処理
	void init();

	//---描画処理
	void draw(
		DWORD SpriteType,
		const D3DXVECTOR3* vec3Pos,
		const D3DXVECTOR3* vec3Rot,
		const D3DXVECTOR3* vec3Scale);		///<	描画処理
	void draw(
		DWORD SpriteType,
		const D3DXMATRIXA16* pMatWorld,
		const D3DXMATRIXA16* pMatView);		///<	描画
	void draw(
		DWORD SpriteType,
		const D3DXMATRIXA16* pmatWorld);	///<	2D描画

	//---テクスチャスプライトの作成
	HRESULT create();							///<	スプライトを作る

	//...中心座標計算
	void calcCenter();							///<	中心座標を計算して設定

	//---値の設定
	//....テクスチャの設定
	void setTexture(CTexture* pTexture);		///<	テクスチャ設定

	void setCenter(float x, float y, float z);	///<	中心座標設定
	void setCenter(D3DXVECTOR3* pos);			///<	中心座標設定

	//....矩形領域
	void setUV(long lLeft,long lTop,long lRight,long lBottom);	///<	UV値の設定
	void setUV(RECT& );											///<	UV値の設定

	//...色補正値
	void setColorRevision(D3DXCOLOR&);			///<	色補正の設定
	void setColorRevision(						//	色補正の設定
		const float fR,
		const float fG,
		const float fB,
		const float fA
		);
	void setColorRevisionR(const float fR);		///<	色補正個別設定R
	void setColorRevisionG(const float fG);		///<	色補正個別設定G
	void setColorRevisionB(const float fB);		///<	色補正個別設定B
	void setColorRevisionA(const float fA);		///<	色補正個別設定A


	//....色補正
	D3DCOLOR CSprite::getColorRevision();	///<	色補正の取得

	//...テクスチャ情報の取得
	const D3DXIMAGE_INFO* getTextureInfo();	///<	テクスチャ情報取得


protected:
	CTexture*			_pTexture;		//!<	テクスチャ
	LPD3DXSPRITE		_pD3DSprite;	//!<	スプライト
	D3DXVECTOR3			_vecCenter;		//!<	スプライト中心点
	RECTEX				_UV;			//!<	Rectの値
	D3DCOLOR			_colorRevision;	//!<	色補正の値
	BOOL				_bDrawFlg;		//!<	描画フラグ
};
//EOF