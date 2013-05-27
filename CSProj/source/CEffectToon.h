/***********************************************************************/
/*! @file  CEffectToon.h
 *  @brief �g�D�[���V�F�[�f�B���O
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CEFFECTLIGHT___
#define ___CEFFECTLIGHT___	//!<	�C���N���[�h�K�[�h


/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CEffectBase.h"

/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CEffectToon:public CEffectBase
{
public:
	CEffectToon();		///<	�R���X�g���N�^
	~CEffectToon();		///<	�f�X�g���N�^
private:
	CEffectToon(const CEffectToon& copy);	///<	�R�s�[�֎~
	void create();							///<	�G�t�F�N�g�쐬

public:
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);	///<	�`�揈��
	void setlightDir(D3DXVECTOR4* lightDir);

private:
	char		_ToonTexPath[MAX_PATH];	//!< �g�D�[���e�N�X�`���t�@�C���p�X
	D3DXHANDLE _techTechHandle;			//!< �e�N�j�b�N��
	D3DXHANDLE _paramWVP;				//!< ���[���h�r���[�v���W�F�N�V�����}�g���N�X
	D3DXHANDLE _paramLight;				//!< ���C�g����
	D3DXHANDLE _paramColor;				//!< ���b�V���J���[�n���h��
	D3DXHANDLE _paramDecalTex;			//!< �ʏ�e�N�X�`��
	D3DXHANDLE _paramToonTex;			//!< �A�e�N�X�`��
	LPDIRECT3DTEXTURE9 _pToonTex;		//!< �g�D�[���e�N�X�`��
	D3DXVECTOR4* _lightDir;				//!<�@���C�g����
};

#endif