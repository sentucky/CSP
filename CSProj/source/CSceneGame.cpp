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
	release();
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	CTank* pTank = NULL;
	CFollowCamera* pFCam;
	CObjBase* ObjPtr;

	OBJMNG->push_back(OBJFACTORY->create(OBJKEY::STAGE01()));
	OBJMNG->push_back(pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())));
	OBJMNG->push_back(pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())));
	OBJMNG->push_back(ObjPtr = OBJFACTORY->create(OBJKEY::PIN()));
	pFCam->setTank(pTank);
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
	_pCamera->update();

	CListItem<CObjBase*>* run = OBJMNG->begin();
	CListItem<CObjBase*>* next = NULL;
	CListItem<CObjBase*>* end = OBJMNG->end();
	while(run != end)
	{
		if(run->getInst()->getDeleteFlg() == TRUE)
		{
			next = run->next();
			OBJMNG->erase(run);
			run = next;
			continue;
		}
		run = run->next();
	}
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