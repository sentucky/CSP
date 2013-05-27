/***********************************************************************/
/*! @file  CEffect.h
 *  @brief �G�t�F�N�g�N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___EFFECT___
#define ___EFFECT___	//!<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"common.h"
#include"CEffectBase.h"

/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CMesh;


/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CEffect:public CEffectBase
{
public:
	CEffect(
		const char FXFilePath[MAX_PATH],
		const char TechnicHandle[MAX_PATH],
		const char TextureHandle[MAX_PATH],
		const char WVPHandle[MAX_PATH]
	);			///<	�R���X�g���N�^
	~CEffect();	///<	�f�X�g���N�^

private:
	CEffect(const CEffect& copy);	///<	�R�s�[�֎~

public:

	void create();	///<	�G�t�F�N�g�쐬
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);	///<	�`�揈��
	void setTechniqueHandle( const D3DXHANDLE TechHandle);	///<	�e�N�j�b�N�w��
	void setTextureHandle( const D3DXHANDLE TexHandle);		///<	
	void setWVPHandle( const D3DXHANDLE WVPHandle);			///<

private:
	D3DXHANDLE	 _TechniqueHandle;	///<	technic�n���h��
	D3DXHANDLE	 _TextureHandle;	///<	�e�N�X�`���n���h��
	D3DXHANDLE	 _WVPHandle;		///<	WVP�n���h��
};



#endif