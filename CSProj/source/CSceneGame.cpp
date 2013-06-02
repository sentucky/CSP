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
#include"CHItTestTAndT.h"

#ifdef _DEBUG
#include"CTankIntDummy.h"

#include"CInputCommon.h"
#include"CFont.h"
#include"CScreen.h"
#include"CListGroup.h"
#include"CTime.h"
#endif

#include"CLight.h"
#include"StageData.h"

	CLight* aaaaaaaaaaaaa;

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
	delete aaaaaaaaaaaaa;
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


	aaaaaaaaaaaaa  = new CLight;
	aaaaaaaaaaaaa->lightON();
	aaaaaaaaaaaaa->setDirectionalLight(
		COLORVALUE(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR3(1.0,-1.0f,0)
		);

	//CStageData::getInst()->Load();

	//	カメラ作成
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	リストサイズ設定
	OBJMNG->resize(OBJGROUPKEY::SUM());

	//	オブジェクト作成
	//...ステージ
	OBJMNG->push(OBJGROUPKEY::STAGE(),OBJFACTORY->create(OBJKEY::STAGE01()),NULL);

	//...戦車
	CTank*			pTank = NULL;
	OBJMNG->push(OBJGROUPKEY::TANK(),pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())),NULL);
#ifdef _DEBUG
	CTank*			pTank2 = NULL;
//*
	for(int n = 0; n < 10; n++)
	{
		for(int n2 = 0; n2 < 10; n2++)
		{
			OBJMNG->push(OBJGROUPKEY::TANK(),pTank2 = (CTank*)OBJFACTORY->create(OBJKEY::TANKDUMMY()),NULL);
			const_cast<D3DXMATRIXA16*>(pTank2->getMatBottom())->_41 += 5.0f * n + 0.5f;
			const_cast<D3DXMATRIXA16*>(pTank2->getMatBottom())->_43 += 5.0f * n2 + 0.5f;
		}
	}
//*/
#endif

	//...追跡カメラ
	CFollowCamera*	pFCam = NULL;
	OBJMNG->push(OBJGROUPKEY::FOLLOW(),pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())),NULL);
	pFCam->setTank(pTank);

	//...ピン
	OBJMNG->push(OBJGROUPKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);

	//	追跡カメラの追跡対象設定

	//	あたり判定
//	OBJMNG->push(OBJGROUPKEY::HITTEST(),static_cast<CHitTestTAndT*>(OBJFACTORY->create(OBJKEY::HITTEST())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),static_cast<CHitTestTAndT*>(OBJFACTORY->create(OBJKEY::HITTEST())),NULL);
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
	static RECTEX fpspos(0,0,0,0);
	FONT->DrawInt("FPS:",CTIMER->getFPS(),fpspos);
   
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