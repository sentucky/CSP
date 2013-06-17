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

	void init();				//!<	初期化処理
	void release();				//!<	解放処理
	void update();				//!<	更新処理
	void draw();				//!<	描画処理
	CSceneBase* nextScene();	//!<	シーン切り替え
private:
};

#endif 