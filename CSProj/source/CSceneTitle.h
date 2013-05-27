/***********************************************************************/
/*! @file  CSceneTitle.h
 *  @brief タイトル部分の処理
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
 *	@brift タイトル部分の処理
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
	CSceneBase* nextScene();	//!<	シーン切り替え

};

#endif