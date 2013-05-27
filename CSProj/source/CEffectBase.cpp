/***********************************************************************/
/*! @file  CEffectBase.cpp
 *  @brief �G�t�F�N�g�x�[�X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CEffectBase.h"
#include"CDevice.h"



/***********************************************************************/
/*! @brief �R���X�g���N�^
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
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CEffectBase::~CEffectBase()
{
	SAFE_RELEASE(_Effect);
	SAFE_RELEASE(_Decl);
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^\n�R�s�[�֎~
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

	// ���_�錾�쐬
	if(FAILED(hr = D3DDEVICE->CreateVertexDeclaration(
									DECL, 
									&_Decl
									)))
	{
		MessageAlert("���_�錾�ԈႢ�I","error from CEffectBase::createVtxDecl");
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
/*! @brief �G�t�F�N�g���擾
 * 
 *  @retval LPD3DXEFFECT 
 */
/***********************************************************************/
LPD3DXEFFECT	CEffectBase::getEffect()
{
	return _Effect;
}


