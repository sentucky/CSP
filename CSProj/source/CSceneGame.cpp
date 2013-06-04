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

	CLight* GLight;

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
	delete GLight;
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

	_DrawFlg = FALSE;


	GLight  = new CLight;
	GLight->lightON();
	GLight->setDirectionalLight(
		COLORVALUE(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR3(0.0,-1.0f,5.0f)
		);


	//	カメラ作成
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	リストサイズ設定
	OBJMNG->resize(OBJGROUPKEY::SUM());

	//	オブジェクト作成
	//...ステージ
	CStage* pStage;
	OBJMNG->push(OBJGROUPKEY::STAGE(),pStage = static_cast<CStage*>(OBJFACTORY->create(OBJKEY::STAGE01())),NULL);

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

	//	あたり判定
	OBJMNG->push(OBJGROUPKEY::HITTEST(),static_cast<CHitTestTAndT*>(OBJFACTORY->create(OBJKEY::HITTEST())),NULL);

//	CTankIntInter::setStageData(CStageData::getInst());

	//	スタート位置に配置
	standby(pStage);
	pFCam->update();
	_DrawFlg = TRUE;
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









void CSceneGame::standby(CStage* pStage)
{
	//	要素抽出
	CListMng<CObjBase*>* pTankMng = OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>*pListTank	= pTankMng->begin();
	const CListItem<CObjBase*>*pEnd = pTankMng->end();



	//	開始位置のタイルを取得したい
	//....スタート位置タイル取得
	const TILE* pStTile= pStage->getStageData()->startTile();

	
	const float moveX = 1.0f;
	const float moveY = 1.0f;

	//....基点取得
	const float& pointX = pStTile->posX;
	const float& pointY = pStTile->posY;

	uint cnt = 0;
	CTank* pTank = NULL;
	while(pListTank !=  pEnd)
	{
	//	本来の型でポインタ取得
		
		pTank = static_cast<CTank*>(pListTank->getInst());
		pTank->setPos(
			pointX + moveX * static_cast<float>(cnt % 10),
			pointY + moveY * static_cast<float>(cnt / 10)
			);
		pListTank = pListTank->next();
		++cnt;
	}
	CCamera::update();
}
