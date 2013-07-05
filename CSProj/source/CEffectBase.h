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
	CEffectBase(char FXFilePath[MAX_PATH]);	///<	�R���X�g���N�^
	virtual ~CEffectBase();							///<	�f�X�g���N�^
	CEffectBase(const CEffectBase& src);
private:
public:
	void release();
	virtual BOOL create()		= 0;	//	����������
	virtual BOOL cloneCreate()	= 0;	//	��R�s�[���̏�����


	uint begin(uint Technique);
	void end();					//	�`��㏈��
	BOOL beginPass(uint Pass);	//
	void endPass();				//
	void commitChanges();

	virtual void setHandles(uint HandleID,D3DXHANDLE) = 0;

protected:
	char*						 _FxPath;	//!<	fx�t�@�C���p�X
	LPD3DXEFFECT				 _Effect;	//!<	�G�t�F�N�g
};
#endif