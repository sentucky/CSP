/***********************************************************************/
/*! @file  CSceneResult.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSCENERESULT___
#define ___CSCENERESULT___

#include"CSceneBase.h"

class CSceneResult:public CSceneBase
{
public:
	CSceneResult();
	~CSceneResult();

	void init();				//!<	����������
	void release();				//!<	�������
	void update();				//!<	�X�V����
	void draw();				//!<	�`�揈��
	CSceneBase* nextScene();	//!<	�V�[���؂�ւ�
private:
};

#endif