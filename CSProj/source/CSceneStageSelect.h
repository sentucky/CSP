/***********************************************************************/
/*! @file  CSceneStageSelect.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSCENESTAGESELECT___
#define ___CSCENESTAGESELECT___

#include"CSceneBase.h"

class CSceneStageSelect:public CSceneBase
{
public:
	CSceneStageSelect();
	~CSceneStageSelect();

	void init();				//!<	����������
	void release();				//!<	�������
	void update();				//!<	�X�V����
	void draw();				//!<	�`�揈��
	CSceneBase* nextScene();	//!<	�V�[���؂�ւ�
private:
};

#endif 