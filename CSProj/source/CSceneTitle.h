/***********************************************************************/
/*! @file  CSceneTitle.h
 *  @brief �^�C�g�������̏���
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSCENETITLE___
#define ___CSCENETITLE___

#include"CSceneBase.h"

/***********************************************************************/
/*!
 *	@class CSceneTitle
 *	@brift �^�C�g�������̏���
 */
/***********************************************************************/
class CSceneTitle:public CSceneBase
{
public:
	CSceneTitle();
	~CSceneTitle();
private:
	void init();
	void update();
	void draw();
	void release();
	CSceneBase* nextScene();	//!<	�V�[���؂�ւ�

};

#endif