/***********************************************************************/
/*! @file  CSceneGame.h
 *  @brief ゲーム部分の処理
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSCENEGAME___
#define ___CSCENEGAME___	///<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CSceneBase.h"

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CCamera;
class CStage;
class CObjMng;
class CFollowCamera;
template<class T>
class CListItem;
class CObjBase;
/***********************************************************************/
/*!	@class CSceneGame
 *	@brift ゲーム部分の処理
 */
/***********************************************************************/
class CSceneGame:public CSceneBase
{
public:
	CSceneGame();				///<	コンストラクタ
	~CSceneGame();				///<	デストラクタ

private:
	void init();				///<	初期化処理
	void update();				///<	更新処理
	void draw();				///<	描画処理
	void release();				///<	解放処理
	CSceneBase* nextScene();	///<	シーン切り替え

	void standby(CStage* pStage);	///<	整列

	void switchGStart();
	void switchGMain();
	void switchGEnd();


	uint Phase;
private:
	CCamera* _pCamera;	///<	カメラクラスポインタ
	CFollowCamera* _FollowCamera;
	CListItem<CObjBase*>* _CamStart;
};

#endif