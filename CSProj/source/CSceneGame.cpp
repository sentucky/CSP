/***********************************************************************/
/*! @file  CSceneGame.cpp
 *  @brief ゲーム部分の処理
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CSceneGame.h"
#include"CCamera.h"

#include"CTask.h"
#include"CTaskMng.h"
#include"CTaskList.h"

#include"CFactory.h"
#include"CMeshFactory.h"
#include"CObjMng.h"

//OBJ
#include"CTank.h"
#include"CStage.h"
#include"CFollowCamera.h"

#include"CTankIntPlayer.h"

#ifdef _DEBUG
#include"CInputCommon.h"
#include"CFont.h"
#include"CScreen.h"
#include"CListGroup.h"
#endif

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CSceneGame::CSceneGame()
	:_pCamera(NULL)
{
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CSceneGame::~CSceneGame()
{
	release();
	TASKMNG::release();
}

/***********************************************************************/
/*! @brief 初期化処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::init()
{
	//	解放処理
	release();

	//	カメラ作成
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	リストサイズ設定
	OBJMNG->resize(OBJKEY::SUM());

	//	オブジェクト作成
	//...ステージ
	OBJMNG->push(OBJKEY::STAGE01(),OBJFACTORY->create(OBJKEY::STAGE01()),NULL);

	//...戦車
	CTank*			pTank = NULL;
	OBJMNG->push(OBJKEY::TANK01(),pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())),NULL);

	//...追跡カメラ
	CFollowCamera*	pFCam = NULL;
	OBJMNG->push(OBJKEY::FOLLOW(),pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())),NULL);
	pFCam->setTank(pTank);

	//...ピン
	OBJMNG->push(OBJKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);

	//	追跡カメラの追跡対象設定
}

/***********************************************************************/
/*! @brief 更新処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::update()
{
	CHECK_UPDATE;

	
	CTaskMng::run();

	//	オブジェクトの更新
	_pCamera->update();

	//	不要オブジェクトの削除
	OBJMNG->checkDelete();
}

/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::draw()
{
	CHECK_DRAW;
	CTaskMng::draw();

#ifdef _DEBUG
   
   
#endif
}

/***********************************************************************/
/*! @brief 解放処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::release()
{
	SAFE_DELETE(_pCamera);
	OBJMNG->release();


}

/***********************************************************************/
/*! @brief シーン切り替え
 * 
 *  @retval CSceneBase * 
 */
/***********************************************************************/
CSceneBase * CSceneGame::nextScene()
{
	return this;
}