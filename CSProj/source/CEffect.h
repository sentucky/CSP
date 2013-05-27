/***********************************************************************/
/*! @file  CEffect.h
 *  @brief エフェクトクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___EFFECT___
#define ___EFFECT___	//!<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"common.h"
#include"CEffectBase.h"

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CMesh;


/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CEffect:public CEffectBase
{
public:
	CEffect(
		const char FXFilePath[MAX_PATH],
		const char TechnicHandle[MAX_PATH],
		const char TextureHandle[MAX_PATH],
		const char WVPHandle[MAX_PATH]
	);			///<	コンストラクタ
	~CEffect();	///<	デストラクタ

private:
	CEffect(const CEffect& copy);	///<	コピー禁止

public:

	void create();	///<	エフェクト作成
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);	///<	描画処理
	void setTechniqueHandle( const D3DXHANDLE TechHandle);	///<	テクニック指定
	void setTextureHandle( const D3DXHANDLE TexHandle);		///<	
	void setWVPHandle( const D3DXHANDLE WVPHandle);			///<

private:
	D3DXHANDLE	 _TechniqueHandle;	///<	technicハンドル
	D3DXHANDLE	 _TextureHandle;	///<	テクスチャハンドル
	D3DXHANDLE	 _WVPHandle;		///<	WVPハンドル
};



#endif