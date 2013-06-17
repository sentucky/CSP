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

	void init();				//!<	初期化処理
	void release();				//!<	解放処理
	void update();				//!<	更新処理
	void draw();				//!<	描画処理
	CSceneBase* nextScene();	//!<	シーン切り替え
private:
};

#endif