/***********************************************************************/
/*! @file  CEffectBase.cpp
 *  @brief エフェクトベース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CEffectBase.h"
#include"CDevice.h"



/***********************************************************************/
/*! @brief コンストラクタ
 * 
 *  @param[in] FXFilePath 
 */
/***********************************************************************/
CEffectBase::CEffectBase(const char* FXFilePath)
	:_Effect(0),
	_Decl(0)
{
	strcpy(_FXFilePath,FXFilePath);
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CEffectBase::~CEffectBase()
{
	SAFE_RELEASE(_Effect);
	SAFE_RELEASE(_Decl);
}

/***********************************************************************/
/*! @brief コピーコンストラクタ\nコピー禁止
 * 
 *  @param[in] copy 
 */
/***********************************************************************/
CEffectBase::CEffectBase(const CEffectBase& copy)
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] DECL 
 *  @retval void
 */
/***********************************************************************/
void CEffectBase::createVtxDecl(D3DVERTEXELEMENT9* DECL)
{
	HRESULT hr;

	// 頂点宣言作成
	if(FAILED(hr = D3DDEVICE->CreateVertexDeclaration(
									DECL, 
									&_Decl
									)))
	{
		MessageAlert("頂点宣言間違い！","error from CEffectBase::createVtxDecl");
	}
}

/***********************************************************************/
/*! @brief 
* 
*  @retval LPDIRECT3DVERTEXDECLARATION9 
*/
/***********************************************************************/
LPDIRECT3DVERTEXDECLARATION9 CEffectBase::getDecl()
{
	return _Decl;
}


/***********************************************************************/
/*! @brief エフェクト情報取得
 * 
 *  @retval LPD3DXEFFECT 
 */
/***********************************************************************/
LPD3DXEFFECT	CEffectBase::getEffect()
{
	return _Effect;
}


