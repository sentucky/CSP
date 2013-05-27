/***********************************************************************/
/*! @file  CSceneTestSpace.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___TEST_SPACE___
#define ___TEST_SPACE___

#include"CSceneBase.h"

class CSceneTestSpace:public CSceneBase
{
public:
	CSceneTestSpace();
	~CSceneTestSpace();
private:
	void init();
	void update();
	void draw();
	void release();
	CSceneBase* nextScene();	//!<	ƒV[ƒ“Ø‚è‘Ö‚¦

};

#endif