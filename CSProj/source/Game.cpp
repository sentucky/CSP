/***********************************************************************/
/*! @file  Loop.cpp
 *  @brief ゲームループ
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"Game.h"

#include"CInputCommon.h"
#include"CTextureFactory.h"
#include"CSpriteFactory.h"
#include"CSceneBase.h"
#include"CSceneGame.h"
#include"CSceneTitle.h"


#include"CSceneTestSpace.h"
#include"CScreen.h"
#include"CFadeInOut.h"
#include"CMeshFactory.h"
#include"CDevice.h"			//デバイスクラスヘッダ
#include"CTaskMng.h"
#include"CFactory.h"

#include"CCamera.h"
#include"CStartCamWork.h"

#include"CTank.h"
#include"CStage.h"
#include"CFollowCamera.h"
#include"CPin.h"
#include"CShell.h"
#include"CCockpit.h"
#include"CSystemparam.h"


#include"CSprite.h"
#include"CSound.h"

#include"CNum.h"

#include"const.h"
#include"TextureKey.h"
#include"CSoundKey.h"
#include"ObjKey.h"

#include"CHItTestTAndT.h"
#include"CHitTestTankToWall.h"
#include"CHitTestTankToShell.h"
/***********************************************************************/
//	グローバル変数宣言
/***********************************************************************/
CSceneBase* pScene		= NULL;
CSceneBase* pLastScene	= NULL;	//	最後に扱ったシーン
uint		Phase		= 0;

CSprite* spriteSight;
D3DXMATRIXA16 matSight;

/***********************************************************************/
//	先行宣言
/***********************************************************************/
BOOL drawBegin();	//	描画開始
void drawEnd();		//	描画終了


/***********************************************************************/
//	フェーズ
/***********************************************************************/
enum{
	P_INIT,
	P_FADEIN,
	P_UPDATE,
	P_FADEOUT,
	P_SCENE_SWITCH,
};

/***********************************************************************/
/*! @brief 初期化処理
 * 
 *  @retval void
 */
/***********************************************************************/
void gameInit()
{
	CDEVICE->init();				//デバイスの初期化
	INPUTCOMMON->createKeyboard();
	INPUTCOMMON->createMouse();
	CSceneBase* ps;
	ps = new CSceneGame;
//	ps = new CSceneTitle;
//	ps = new CSceneTestSpace;
	pScene = ps;

	D3DXMatrixIdentity(&matSight);

	TEXTUREFACTORY->reserve(TEXKEY::SUM());
	SPRITEFACTORY->registTexture(TEXKEY::SIGHT(),			TEXPATH::SIGHT()			);
	SPRITEFACTORY->registTexture(TEXKEY::MINIMAP(),			TEXPATH::MINIMAP());
	SPRITEFACTORY->registTexture(TEXKEY::MINIDOT(),			TEXPATH::MINIDOT()			);
	SPRITEFACTORY->registTexture(TEXKEY::TANK_EXPLOAD(),	TEXPATH::TANK_EXPLOAD()		);
	SPRITEFACTORY->registTexture(TEXKEY::GAME_BG(),			TEXPATH::GAME_BG()			);
	SPRITEFACTORY->registTexture(TEXKEY::CIRCLE(),			TEXPATH::CIRCLE()			);
	SPRITEFACTORY->registTexture(TEXKEY::TANK(),			TEXPATH::TANK()				);
	SPRITEFACTORY->registTexture(TEXKEY::LOSE(),			TEXPATH::LOSE()				);
	SPRITEFACTORY->registTexture(TEXKEY::FADEMASK(),		TEXPATH::FADEMASK()			);
	SPRITEFACTORY->registTexture(TEXKEY::BACK_BUTTON(),		TEXPATH::BACK_BUTTON()		);
	SPRITEFACTORY->registTexture(TEXKEY::TITLE_BG(),		TEXPATH::TITLE_BG()			);
	SPRITEFACTORY->registTexture(TEXKEY::TITLE_STR(),		TEXPATH::TITLE_STR()		);
	SPRITEFACTORY->registTexture(TEXKEY::TITLE_BUTTON01(),	TEXPATH::TITLE_BUTTON01()	);
	SPRITEFACTORY->registTexture(TEXKEY::TITLE_BUTTON02(),	TEXPATH::TITLE_BUTTON02()	);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_BUTTON01(),	TEXPATH::SELECT_BUTTON01()	);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_BUTTON02(),	TEXPATH::SELECT_BUTTON02()	);
	SPRITEFACTORY->registTexture(TEXKEY::END_BUTTON01(),	TEXPATH::END_BUTTON01()		);
	SPRITEFACTORY->registTexture(TEXKEY::END_BUTTON02(),	TEXPATH::END_BUTTON02()		);
	SPRITEFACTORY->registTexture(TEXKEY::RETRY_BUTTON01(),	TEXPATH::RETRY_BUTTON01()	);
	SPRITEFACTORY->registTexture(TEXKEY::RETRY_BUTTON02(),	TEXPATH::RETRY_BUTTON02()	);
	SPRITEFACTORY->registTexture(TEXKEY::START_BUTTON01(),	TEXPATH::START_BUTTON01()	);
	SPRITEFACTORY->registTexture(TEXKEY::START_BUTTON02(),	TEXPATH::START_BUTTON02()	);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_BG(),		TEXPATH::SELECT_BG()		);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_COURSE1(),	TEXPATH::SELECT_COURSE1()	);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_COURSE2(),	TEXPATH::SELECT_COURSE2()	);
	SPRITEFACTORY->registTexture(TEXKEY::SELECT_COURSE3(),	TEXPATH::SELECT_COURSE3()	);
	SPRITEFACTORY->registTexture(TEXKEY::RESULT_BG(),		TEXPATH::RESULT_BG()		);
	SPRITEFACTORY->registTexture(TEXKEY::RESULT_RANK(),		TEXPATH::RESULT_RANK()		);
	SPRITEFACTORY->registTexture(TEXKEY::RESULT_LOSE(),		TEXPATH::RESULT_LOSE()		);
	SPRITEFACTORY->registTexture(TEXKEY::TILE01(),			TEXPATH::TILE01()			);
	SPRITEFACTORY->registTexture(TEXKEY::TILE02(),			TEXPATH::TILE02()			);
	SPRITEFACTORY->registTexture(TEXKEY::TILE03(),			TEXPATH::TILE03()			);
	SPRITEFACTORY->registTexture(TEXKEY::TILE04(),			TEXPATH::TILE04()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B0(),			TEXPATH::NUM_B0()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B1(),			TEXPATH::NUM_B1()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B2(),			TEXPATH::NUM_B2()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B3(),			TEXPATH::NUM_B3()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B4(),			TEXPATH::NUM_B4()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B5(),			TEXPATH::NUM_B5()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B6(),			TEXPATH::NUM_B6()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B7(),			TEXPATH::NUM_B7()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B8(),			TEXPATH::NUM_B8()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_B9(),			TEXPATH::NUM_B9()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W0(),			TEXPATH::NUM_W0()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W1(),			TEXPATH::NUM_W1()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W2(),			TEXPATH::NUM_W2()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W3(),			TEXPATH::NUM_W3()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W4(),			TEXPATH::NUM_W4()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W5(),			TEXPATH::NUM_W5()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W6(),			TEXPATH::NUM_W6()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W7(),			TEXPATH::NUM_W7()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W8(),			TEXPATH::NUM_W8()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_W9(),			TEXPATH::NUM_W9()			);
	SPRITEFACTORY->registTexture(TEXKEY::NUM_TH(),			TEXPATH::NUM_TH()			);

	SPRITEFACTORY->registTexture(TEXKEY::START(),			TEXPATH::START()			);
	SPRITEFACTORY->registTexture(TEXKEY::STAGESELECT(),		TEXPATH::STAGESELECT()		);
	SPRITEFACTORY->registTexture(TEXKEY::EXIT(),			TEXPATH::EXIT()				);
	SPRITEFACTORY->registTexture(TEXKEY::READY(),			TEXPATH::READY()			);
	SPRITEFACTORY->registTexture(TEXKEY::GO(),				TEXPATH::GO()				);


	SPRITEFACTORY->registTexture(TEXKEY::ANIMETEST(),		TEXPATH::ANIMETEST()		);


	//	メッシュ初期化
	MESHFACTORY->reserve(MESHKEY::SUM());
#ifdef _DEBUG
	MESHFACTORY->registMesh(MESHKEY::RING(),	MESHPATH::RING()	);
#endif
	MESHFACTORY->registMesh(MESHKEY::DOME(),			MESHPATH::DOME()			);
	MESHFACTORY->registMesh(MESHKEY::TANK01_BOTTOM(),	MESHPATH::TANK01_BOTTOM()	);
	MESHFACTORY->registMesh(MESHKEY::TANK02_BOTTOM(),	MESHPATH::TANK02_BOTTOM()	);
	MESHFACTORY->registMesh(MESHKEY::TANK03_BOTTOM(),	MESHPATH::TANK03_BOTTOM()	);
	MESHFACTORY->registMesh(MESHKEY::TANK04_BOTTOM(),	MESHPATH::TANK04_BOTTOM()	);
	MESHFACTORY->registMesh(MESHKEY::TANK01_TOP(),		MESHPATH::TANK01_TOP()		);
	MESHFACTORY->registMesh(MESHKEY::TANK02_TOP(),		MESHPATH::TANK02_TOP()		);
	MESHFACTORY->registMesh(MESHKEY::TANK03_TOP(),		MESHPATH::TANK03_TOP()		);
	MESHFACTORY->registMesh(MESHKEY::TANK04_TOP(),		MESHPATH::TANK04_TOP()		);
	MESHFACTORY->registMesh(MESHKEY::STAGE01(),			MESHPATH::STAGE01()			);
	MESHFACTORY->registMesh(MESHKEY::PIN(),				MESHPATH::PIN()				);
	MESHFACTORY->registMesh(MESHKEY::SHELL01(),			MESHPATH::SHELL01()			);


	
	TASKMNG::resize(TASKKEY::SUM());

	//	オブジェクト登録
	CTank* pObj = new CTank(
		MESHFACTORY->create(MESHKEY::TANK01_TOP()),
		MESHFACTORY->create(MESHKEY::TANK01_BOTTOM()),
		MESHFACTORY->create(MESHKEY::TANK01_BOTTOM()),
		0,
		new CShell(60,0.5f,MESHFACTORY->create(MESHKEY::SHELL01()),1),
		0.05f,
		0.05f,
		10
		);
	CTank* pObj3 = new CTank(
		MESHFACTORY->create(MESHKEY::TANK02_TOP()),
		MESHFACTORY->create(MESHKEY::TANK02_BOTTOM()),
		MESHFACTORY->create(MESHKEY::TANK02_BOTTOM()),
		-1,
		new CShell(60,0.5f,MESHFACTORY->create(MESHKEY::SHELL01()),1),
		0.03f,
		0.05f,
		10
		);
	CStage* pStage = new CStage(STAGEPATH::NO_01(),MESHFACTORY->create(MESHKEY::DOME()));

	CTank* pObj2 = new CTank(
		MESHFACTORY->create(MESHKEY::TANK02_TOP()),
		MESHFACTORY->create(MESHKEY::TANK02_BOTTOM()),
		MESHFACTORY->create(MESHKEY::TANK02_BOTTOM()),
		-1,
		new CShell(60,0.5,MESHFACTORY->create(MESHKEY::SHELL01()),1),
		0.04f,
		0.05f,
		5);

	OBJFACTORY->reserve(OBJKEY::SUM());
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANK01(),pObj);
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANKDUMMY(),pObj2);
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANK02(),pObj3);
	OBJFACTORY->registPrototype(OBJKEY::STAGE01(),pStage);
	OBJFACTORY->registPrototype(OBJKEY::NUM(),			new CNum);
	OBJFACTORY->registPrototype(OBJKEY::FOLLOWCAMERA(),	new CFollowCamera								);
	OBJFACTORY->registPrototype(OBJKEY::PIN(),			new CPin(MESHFACTORY->create(MESHKEY::PIN()))	);
	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOW(),	new CHitTestTankToWall							);
	OBJFACTORY->registPrototype(OBJKEY::STARTCAMERA(),	new CStartCamWork(pStage->getStageData())		);
	OBJFACTORY->registPrototype(OBJKEY::COCKPIT(),		new CCockpit);
	OBJFACTORY->registPrototype(OBJKEY::SYSTEMPARAM(),	new CSystemparam);
	CHitTestTAndT* pHTTAT;
	pHTTAT = new CHitTestTAndT;

	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOT(),pHTTAT);
	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOS(),new CHitTestTankToShell);

	//*
	CSound* pSound = CSOUND;
	pSound->reserve(SOUNDKEY::SUM());
	pSound->Init();
	pSound->LoadSoundFile(SOUNDKEY::COLLISION(),	SOUNDPATH::COLLISION()	);
	pSound->LoadSoundFile(SOUNDKEY::FANFARE(),		SOUNDPATH::FANFARE()	);
	pSound->LoadSoundFile(SOUNDKEY::MOVE(),			SOUNDPATH::MOVE()		);
	pSound->LoadSoundFile(SOUNDKEY::FIRE(),			SOUNDPATH::FIRE()		);
	pSound->LoadSoundFile(SOUNDKEY::GAMEBGM(),		SOUNDPATH::GAMEBGM()	);
	pSound->LoadSoundFile(SOUNDKEY::LOSEBGM(),		SOUNDPATH::LOSEBGM()	);
	pSound->LoadSoundFile(SOUNDKEY::TITLEBGM(),		SOUNDPATH::TITLEBGM()	);
	CTank::setSoundFire(pSound->GetSound(SOUNDKEY::FIRE()));
//*/
	spriteSight = SPRITEFACTORY->create(TEXKEY::SIGHT());

	while(!(ShowCursor(FALSE) < 0));
}


/***********************************************************************/
/*! @brief ループ
 * 
 *  @retval void
 */
/***********************************************************************/
bool gameLoop()
{

	//...入力情報の更新
	INPUTCOMMON->update();

	if(	pLastScene != pScene)
	{
		SAFE_DELETE(pLastScene);
	}
	pLastScene = pScene;
	matSight._41 = MOUSE.getPointWindow().x;
	matSight._42 = MOUSE.getPointWindow().y;

	switch(Phase)
	{
	case P_INIT:
		if(pLastScene != NULL)
		{
			pLastScene->release();
		}
		pScene->release();
		pScene->init();
		FADEINOUT->fadeInStart(60);
		Phase = P_FADEIN;
		break;
	case P_FADEIN:
		FADEINOUT->update();
		if(FADEINOUT->getState() == FADE_NONE)
		{
			Phase = P_UPDATE;
		}
		break;

	case P_UPDATE:
		pScene->update();
		if(pScene->getEndFlg() == TRUE)
		{
			FADEINOUT->fadeOutStart(60);
			Phase = P_FADEOUT;
		}
		break;

	case P_FADEOUT:
		FADEINOUT->update();
		if(FADEINOUT->getState() == FADE_NONE)
		{
			Phase = P_SCENE_SWITCH;
		}
		break;

	case P_SCENE_SWITCH:
		pScene = pScene->nextScene();
		if(!pScene) 
		{
			return false;
		}
		Phase = P_INIT;
		break;
	}
	if(drawBegin())
	{
		pLastScene->draw();
//		FADEINOUT->draw();
		spriteSight->draw(0,&matSight);
		drawEnd();
		D3DDEVICE->Present(0,0,0,0);
	}

	return true;
}

/***********************************************************************/
/*! @brief 描画開始
 * 
 *  @retval BOOL 失敗
 */
/***********************************************************************/
BOOL drawBegin()
{
	//---描画処理---//
	D3DDEVICE->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ),
		D3DCOLOR_RGBA(100, 100, 100, 255),
		1.0f,
		0
		);

	if(FAILED(D3DDEVICE->BeginScene()))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/***********************************************************************/
/*! @brief 描画終了
 * 
 *  @retval void
 */
/***********************************************************************/
void drawEnd()
{
	D3DDEVICE->EndScene();
}

/***********************************************************************/
/*! @brief 解放処理
 * 
 *  @retval void
 */
/***********************************************************************/
void gameRelease()
{
	delete pScene;
	SAFE_DELETE(spriteSight);

	OBJFACTORY->release();
	MESHFACTORY->release();
}
