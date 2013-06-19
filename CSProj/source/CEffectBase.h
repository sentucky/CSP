/***********************************************************************/
/*! @file  CEffectBase.h
 *  @brief �G�t�F�N�g�x�[�X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___CEFFECTBASE___
#define ___CEFFECTBASE___	//!<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"common.h"
#include<WinDef.h>

/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CMesh;


/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CEffectBase
{
public:
	CEffectBase(const char FXFilePath[MAX_PATH]);	///<	�R���X�g���N�^
	virtual ~CEffectBase();							///<	�f�X�g���N�^
private:
	CEffectBase(const CEffectBase&);				///<	�R�s�[�֎~
	virtual void create() = 0;						///<	�G�t�F�N�g�쐬

protected:
	void createVtxDecl(D3DVERTEXELEMENT9*);

public:
	virtual void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld) = 0;

	LPD3DXEFFECT				 getEffect();				///<	�G�t�F�N�g�擾
	LPDIRECT3DVERTEXDECLARATION9 getDecl();					///<
	void setTechniqueHandle( const D3DXHANDLE TechHandle);	///<	technic�n���h���擾


protected:
	char						 _FXFilePath[MAX_PATH];	//!<	fx�t�@�C���p�X
	LPD3DXEFFECT				 _Effect;				//!<	�G�t�F�N�g
	LPDIRECT3DVERTEXDECLARATION9 _Decl;					//!<	
};
#endif