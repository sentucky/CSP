/***********************************************************************/
/*! @file  CEffectBase.h
 *  @brief エフェクトベース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CEFFECTBASE___
#define ___CEFFECTBASE___	//!<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"common.h"
#include<WinDef.h>

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CMesh;


/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CEffectBase
{
public:
	CEffectBase(const char FXFilePath[MAX_PATH]);	///<	コンストラクタ
	virtual ~CEffectBase();							///<	デストラクタ
private:
	CEffectBase(const CEffectBase&);				///<	コピー禁止
	virtual void create() = 0;						///<	エフェクト作成

protected:
	void createVtxDecl(D3DVERTEXELEMENT9*);

public:
	virtual void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld) = 0;

	LPD3DXEFFECT				 getEffect();				///<	エフェクト取得
	LPDIRECT3DVERTEXDECLARATION9 getDecl();					///<
	void setTechniqueHandle( const D3DXHANDLE TechHandle);	///<	technicハンドル取得


protected:
	char						 _FXFilePath[MAX_PATH];	//!<	fxファイルパス
	LPD3DXEFFECT				 _Effect;				//!<	エフェクト
	LPDIRECT3DVERTEXDECLARATION9 _Decl;					//!<	
};
#endif