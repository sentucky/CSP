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
#include"CStartCamWork.h"

#include"CTask.h"
#include"CTaskMng.h"
#include"CTaskList.h"

#include"CFactory.h"
#include"CMeshFactory.h"
#include"CObjMng.h"

#include"CSoundKey.h"

//OBJ
#include"CTank.h"
#include"CStage.h"
#include"CFollowCamera.h"
#include"CCockpit.h"
#include"CSystemparam.h"

#include"CTankIntPlayer.h"
#include"CHItTestTAndT.h"
#include"CHitTestTankToShell.h"
#include"CHitTestTankToWall.h"

#include"ObjKey.h"

#ifdef _DEBUG
#include"CPin.h"
#include"CTankIntDummy.h"

#include"CInputCommon.h"
#include"CFont.h"
#include"CScreen.h"
#include"CListGroup.h"
#endif
#include"CTime.h"

#include"CLight.h"
#include"StageData.h"
#include"CListItem.h"
#include"CObjBase.h"
#include "CTankIntDummy.h"
#include"CSound.h"

CLight* GLight;

enum SCENEGAMEPHASE
{
	GP_START,
	GP_MAIN,
	GP_END,
};


#include"CListMng.h"
#include"CListItem.h"



/***********************************************************************/
/*! @brief コンストラクタ
*/
/***********************************************************************/
CSceneGame::CSceneGame()
	:_pCamera(NULL),
	Phase(NULL),
	_FollowCamera(NULL),
	_CamStart(NULL)
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
	OUTPUT t[16][16];
	pStage->getStageData()->getTile(t);
//	CPin* pin = NULL;
	int n2 = 0;
//*	
	for(int n = 0; n < 1; n++)
	{
		OBJMNG->push(OBJGROUPKEY::TANK(),pTank2 = (CTank*)OBJFACTORY->create(OBJKEY::TANKDUMMY()),NULL);
		pTank2->setPos(
			pTank->getMatBottom()->_41 + n * 0.1f, 
			pTank->getMatBottom()->_43 + n2 * 0.1f
			);
	}
	//*/
#endif

	//...追跡カメラ
	OBJMNG->push(OBJGROUPKEY::CAMERA(),_FollowCamera = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOWCAMERA())),NULL);
	_FollowCamera->disableTask();
	_FollowCamera->setTank(pTank);

	CStartCamWork* pSTCam = NULL;
	OBJMNG->push(OBJGROUPKEY::CAMERA(),pSTCam = static_cast<CStartCamWork*>(OBJFACTORY->create(OBJKEY::STARTCAMERA())),&_CamStart);
	pSTCam->reset();
	pSTCam->camMove();


	//...ピン
	OBJMNG->push(OBJGROUPKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);
#ifdef _DEBUG

#endif
	CSystemparam* SysParam;
	OBJMNG->push(OBJGROUPKEY::COCKPIT(),SysParam = OBJFACTORY->create<CSystemparam>(OBJKEY::SYSTEMPARAM()),NULL);
	SysParam->setCamera(_FollowCamera);
	SysParam->setPlayerTank(pTank);

	CCockpit* Cockpit;
	OBJMNG->push(OBJGROUPKEY::COCKPIT(),Cockpit = OBJFACTORY->create<CCockpit>(OBJKEY::COCKPIT()),NULL);
	Cockpit->setTank(pTank);



	//	あたり判定
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOT())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOW())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOS())),NULL);


	CTankIntInter::setStageData(pStage->getStageData());
	CTank::setStageData(pStage->getStageData());
	CHitTestTankToWall::setStageData(pStage->getStageData());
	CHitTestTankToWall::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));
	CHitTestTankToShell::setShellList(OBJMNG->getList(OBJGROUPKEY::SHELL()));
	CHitTestTankToShell::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));

	//	スタート位置に配置
	standby(pStage);
	_DrawFlg = TRUE;

	pSTCam->lastPoint(
		pTank->getMatBottom()->_41 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->x,
		pTank->getMatBottom()->_42 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->y,
		pTank->getMatBottom()->_43 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->z
		);
	LPDIRECTSOUNDBUFFER bgm = CSOUND->GetSound(SOUNDKEY::BGM1());


	

//	bgm->Play(0,0,1);
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

	if(_CamStart != 0)
	{
		if(_CamStart->getInst()->getDeleteFlg() == TRUE)
		{
			switchGMain();
		}
	}


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

	//	CTankIntDummy::Debug();

	static RECTEX fpspos(0,0,0,0);
	FONT->DrawInt("FPS:",CTIMER->getFPS(),fpspos);
#ifdef _DEBUG
	static RECTEX ps(0,16,0,0);
	static D3DXVECTOR3 Mouse3DPos;
	MOUSE.mousePoint3D(&Mouse3DPos,0);
	FONT->DrawFloat("MOUSEX:",Mouse3DPos.x,RECTEX(0,16,0,0));
	ps.left = 50;		   
	FONT->DrawFloat("MOUSEZ:",Mouse3DPos.z,RECTEX(200,16,0,0));
	FONT->DrawFloat("CAMX:",CCamera::getEye().x,RECTEX(0,400,0,0));
	FONT->DrawFloat("CAMY:",CCamera::getEye().y,RECTEX(0,416,0,0));
	FONT->DrawFloat("CAMZ:",CCamera::getEye().z,RECTEX(0,432,0,0));

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

/***********************************************************************/
/*! @brief 
* 
*  @param[in,out] pStage 
*  @retval void
*/
/***********************************************************************/
void CSceneGame::standby(CStage* pStage)
{
	//	要素抽出
	CListMng<CObjBase*>* pTankMng = OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>*pListTank	= pTankMng->begin();
	const CListItem<CObjBase*>*pEnd = pTankMng->end();


	//	開始位置のタイルを取得したい
	//....スタート位置タイル取得
	const OUTPUT* pStTile= pStage->getStageData()->getLastTile();

	const float rotStartTile = pStTile->rot;

	float moveX = 2.0f;
	float moveY = 2.0f;


	float pointX = pStTile->posX;
	float pointY = pStTile->posY;

	//....基点取得
	if(rotStartTile >= 1.5f * D3DX_PI){
		pointX -= 15;
		pointY -= 15;
	}
	else 	if(rotStartTile >= 1.0f * D3DX_PI){
		pointX += 15;
		pointY -= 15;
	}
	else 	if(rotStartTile >= 0.5f * D3DX_PI){ 
		pointX += 15;
		pointY += 15;
	}
	else{
		pointX -= 15;
		pointY += 15;
	}
	float setPointX;
	float setPointY;

	uint cnt = 0;
	CTank* pTank = NULL;


	const int div = 10;

	while(pListTank !=  pEnd)
	{
		//	本来の型でポインタ取得

		pTank = static_cast<CTank*>(pListTank->getInst());


		if(rotStartTile >= 1.5f * D3DX_PI)
		{//+X-Y
			setPointX = pointX + moveX * static_cast<float>(cnt / div);
			setPointY = pointY + moveY * static_cast<float>(cnt % div);

		}
		else 	if(rotStartTile >= 1.0f * D3DX_PI)
		{
			setPointX = pointX + moveX * static_cast<float>(cnt % div) * -1;
			setPointY = pointY + moveY * static_cast<float>(cnt / div);
		}
		else 	if(rotStartTile >= 0.5f * D3DX_PI)
		{ 
			setPointX = pointX + moveX * static_cast<float>(cnt / div) * -1;
			setPointY = pointY + moveY * static_cast<float>(cnt % div) * -1;
		}
		else
		{
			setPointX = pointX + moveX * static_cast<float>(cnt % div);
			setPointY = pointY + moveY * static_cast<float>(cnt / div) * -1;
		}

		pTank->setPos(
			setPointX, 
			setPointY
			);
		pListTank = pListTank->next();
		++cnt;
	}
	CCamera::update();
}


/***********************************************************************/
/*! @brief 
* 
*  @retval void
*/
/***********************************************************************/
void CSceneGame::switchGMain()
{
	//	CAMERA切り替え
	OBJMNG->erase(
		OBJGROUPKEY::CAMERA(),
		&_CamStart
		);
	_FollowCamera->enableTask();
	_FollowCamera->update();

	//	戦車を動かせるようにする
	CListMng<CObjBase*>*TankList =  OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>* pItem = TankList->begin();
	CListItem<CObjBase*>* pEnd = TankList->end();
	CTank* pTank;

	while(1)
	{
		pTank = static_cast<CTank*>(pItem->getInst());
		pTank->enableTask();
		pItem = pItem->next();
		if(pItem == pEnd)
		{
			break;
		}
	}
}

/***********************************************************************/
/*! @brief 
* 
*  @retval void
*/
/***********************************************************************/
void CSceneGame::switchGEnd()
{


	
}