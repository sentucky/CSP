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

#include"CSceneTitle.h"

#include"CCamera.h"
#include"CStartCamWork.h"

#include"CTask.h"
#include"CTaskMng.h"
#include"CTaskList.h"

#include"CFactory.h"
#include"CMeshFactory.h"
#include"CObjMng.h"

#include"CSoundKey.h"

#include<algorithm>

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
	_CamStart(NULL),
	_SysPara(NULL)
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
	CTaskMng::resize(TASKKEY::SUM());


	//	オブジェクト作成
	//...ステージ
	CStage* pStage;
	OBJMNG->push(OBJGROUPKEY::STAGE(),pStage = static_cast<CStage*>(OBJFACTORY->create(OBJKEY::STAGE01())),NULL);

	//...戦車
	CTank*			pTank = NULL;
	OBJMNG->push(OBJGROUPKEY::TANK(),pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())),NULL);
	CTank::setTankPlayer(pTank);

	CTank*			pTank2 = NULL;
	int n2 = 0;
	CTankIntInter::setPlayerTank(pTank);

	for(int n = 0; n < 50; n++){
		OBJMNG->push(OBJGROUPKEY::TANK(),pTank2 = (CTank*)OBJFACTORY->create(OBJKEY::TANKDUMMY()),NULL);
	}
	for(int n = 0; n < 49; n++){
		OBJMNG->push(OBJGROUPKEY::TANK(),OBJFACTORY->create(OBJKEY::TANK02()),NULL);
	}

	//...追跡カメラ
	OBJMNG->push(OBJGROUPKEY::CAMERA(),_FollowCamera = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOWCAMERA())),NULL);
	_FollowCamera->disableTask();
	_FollowCamera->setTank(pTank);

	CStartCamWork* pSTCam = NULL;
	OBJMNG->push(OBJGROUPKEY::CAMERA(),pSTCam = static_cast<CStartCamWork*>(OBJFACTORY->create(OBJKEY::STARTCAMERA())),NULL);
	pSTCam->reset();


	CSystemparam* SysParam;
	OBJMNG->push(OBJGROUPKEY::COCKPIT(),SysParam = OBJFACTORY->create<CSystemparam>(OBJKEY::SYSTEMPARAM()),NULL);
	_SysPara = SysParam;
	SysParam->setFollowCamera(_FollowCamera);
	SysParam->setPlayerTank(pTank);

	CCockpit* Cockpit;
	OBJMNG->push(OBJGROUPKEY::COCKPIT(),Cockpit = OBJFACTORY->create<CCockpit>(OBJKEY::COCKPIT()),NULL);
	Cockpit->setTank(pTank);




	//	あたり判定
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOT())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOW())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOS())),NULL);


	CTankIntInter::setStageData(pStage->getStageData());
	SysParam->Rankcpy(	CTankIntInter::_Ranking);
	CTank::setStageData(pStage->getStageData());
	

	CHitTestTankToWall::setStageData(pStage->getStageData());
	CHitTestTankToWall::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));
	CHitTestTankToShell::setShellList(OBJMNG->getList(OBJGROUPKEY::SHELL()));
	CHitTestTankToShell::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));

	//	スタート位置に配置
	standby(pStage);
	_DrawFlg = TRUE;

#ifdef _0
	pSTCam->count(0,30);
	pSTCam->count(1,30);
#else
	pSTCam->count(0,215);
	pSTCam->count(1,30);
#endif
	pSTCam->point(
		0,
		pStage->getStageData()->getStartTile()->posX + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->x,
		_FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->y,
		pStage->getStageData()->getStartTile()->posY + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->z
		);
	pSTCam->point(
		1,
		pTank->getMatBottom()->_41 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->x,
		pTank->getMatBottom()->_42 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->y,
		pTank->getMatBottom()->_43 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->z
		);
	pSTCam->lastPoint(
		pTank->getMatBottom()->_41 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->x,
		pTank->getMatBottom()->_42 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->y,
		pTank->getMatBottom()->_43 + _FollowCamera->getDistance() * _FollowCamera->getNAtToEye()->z
		);
	pSTCam->At(
		0,
		pStage->getStageData()->getStartTile()->posX,
		0,
		pStage->getStageData()->getStartTile()->posY);
	pSTCam->At(
		1,
		pTank->getMatBottom()->_41,
		pTank->getMatBottom()->_42,
		pTank->getMatBottom()->_43
		);
	pSTCam->lastAt(
		pTank->getMatBottom()->_41,
		pTank->getMatBottom()->_42,
		pTank->getMatBottom()->_43
		);
	pSTCam->camMove();
	//*
	LPDIRECTSOUNDBUFFER bgm = CSOUND->GetSound(SOUNDKEY::GAMEBGM());
	//*/
	SysParam->setCamStart(pSTCam);
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

	if(_SysPara->getFlgEnd())
	{
		_EndFlg = TRUE;
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
	static RECTEX fpspos(0,0,0,0);
	FONT->DrawInt("FPS:",CTIMER->getFPS(),fpspos);
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
	CSOUND->GetSound(SOUNDKEY::LOSEBGM())->Stop();
	switch(_SysPara->getgotoscene())
	{
	case 1:
//		return new CSceneGame;
		delete this;
		return new CSceneGame;
		break;
	case 2:
		return new CSceneTitle;
		break;
	}

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
	CListItem<CObjBase*>*pEnd = pTankMng->end();


	//	開始位置のタイルを取得したい
	//....スタート位置タイル取得
	const OUTPUT* pStTile= pStage->getStageData()->getLastTile();

	const float rotStartTile = pStTile->rot;

	float moveX = 5.0f;
	float moveY = 5.0f;


	float pointX = pStTile->posX;
	float pointY = pStTile->posY;

	const int div = 4;


	//....基点取得
	if(rotStartTile >= 1.5f * D3DX_PI){
		pointX -= (15 - (7));
		pointY += (15 - (7));
	}
	else 	if(rotStartTile >= 1.0f * D3DX_PI){
		pointX += (15 - (7));
		pointY -= (15 - (7));
	}
	else 	if(rotStartTile >= 0.5f * D3DX_PI){ 
		pointX += (15 - (7));
		pointY += (15 - (7));
	}
	else{
		pointX -= (15 - (7));
		pointY += (15 - (7));
	}

	float setPointX;
	float setPointY;
	
	uint cnt = 0;
	uint maxcnt = 0;
	CTank* pTank = NULL;

	CTank* Player;

	CTank* tank[1024];

	

	while(pListTank !=  pEnd)
	{	
		tank[cnt] = static_cast<CTank*>(pListTank->getInst());
		pListTank = pListTank->next();
		cnt++;
	}

	maxcnt = cnt;

	pListTank = pTankMng->begin();

	cnt = 0;

	while(pListTank !=  pEnd)
	{
		//	本来の型でポインタ取得

		pTank = static_cast<CTank*>(pListTank->getInst());
		pTank->rotationY(rotStartTile);
		if(pTank->getThisType() == CTank::TYPE_PLAYER)
		{
			Player = pTank;
		}
		else
		{
		}

		if(rotStartTile >= 1.5f * D3DX_PI)
		{//+X-Y
			setPointX = pointX + moveX * static_cast<float>(cnt / div)*-1;
			setPointY = pointY + moveY * static_cast<float>(cnt % div)*-1;

		}
		else 	if(rotStartTile >= 1.0f * D3DX_PI)
		{
			setPointX = pointX + moveX * static_cast<float>(cnt % div) * -1;
			setPointY = pointY + moveY * static_cast<float>(cnt / div);
		}
		else 	if(rotStartTile >= 0.5f * D3DX_PI)
		{ 
			setPointX = pointX + moveX * static_cast<float>(cnt % div) * +1;
			setPointY = pointY + moveY * static_cast<float>(cnt / div) * +1;
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


	//	最後尾とプレイヤーの位置交換
	pTank = static_cast<CTank*>(pEnd->prev()->getInst());
	if( Player != pTank)
	{
		const float tmpx = pTank->getMatBottom()->_41;
		const float tmpz = pTank->getMatBottom()->_43;
		pTank->setPos(Player->getMatBottom()->_41, Player->getMatBottom()->_43);
		Player->setPos(tmpx, tmpz);
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