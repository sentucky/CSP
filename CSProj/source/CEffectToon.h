/***********************************************************************/
/*! @file  CEffectToon.h
 *  @brief トゥーンシェーディング
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CEFFECTLIGHT___
#define ___CEFFECTLIGHT___	//!<	インクルードガード


/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CEffectBase.h"

/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CEffectToon:public CEffectBase
{
public:
	CEffectToon();		///<	コンストラクタ
	~CEffectToon();		///<	デストラクタ
private:
	CEffectToon(const CEffectToon& copy);	///<	コピー禁止
	void create();							///<	エフェクト作成

public:
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);	///<	描画処理
	void setlightDir(D3DXVECTOR4* lightDir);

private:
	char		_ToonTexPath[MAX_PATH];	//!< トゥーンテクスチャファイルパス
	D3DXHANDLE _techTechHandle;			//!< テクニック名
	D3DXHANDLE _paramWVP;				//!< ワールドビュープロジェクションマトリクス
	D3DXHANDLE _paramLight;				//!< ライト方向
	D3DXHANDLE _paramColor;				//!< メッシュカラーハンドル
	D3DXHANDLE _paramDecalTex;			//!< 通常テクスチャ
	D3DXHANDLE _paramToonTex;			//!< 陰テクスチャ
	LPDIRECT3DTEXTURE9 _pToonTex;		//!< トゥーンテクスチャ
	D3DXVECTOR4* _lightDir;				//!<　ライト方向
};

#endif