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
#include"CSceneTestSpace.h"
#include"CScreen.h"
#include"CFadeInOut.h"
#include"const.h"
#include"CMeshFactory.h"
#include"CDevice.h"			//デバイスクラスヘッダ
#include"CTaskMng.h"
#include"CFactory.h"

#include"CCamera.h"

#include"CTank.h"
#include"CStage.h"
#include"CFollowCamera.h"
#include"CPin.h"
#include"CShell.h"

#include"CHItTestTAndT.h"
#include"CHitTestTankToWall.h"
#include"CHitTestTankToShell.h"
/***********************************************************************/
//	グローバル変数宣言
/***********************************************************************/
CSceneBase* pScene		= NULL;
CSceneBase* pLastScene	= NULL;	//	最後に扱ったシーン
uint		Phase		= 0;


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
	pScene = ps;


	TEXTUREFACTORY->reserve(TEXKEY::SUM());
	SPRITEFACTORY->registTexture(TEXKEY::FADEMASK(),TEXPATH::FADEMASK());
	SPRITEFACTORY->registTexture(TEXKEY::TILE01(),TEXPATH::TILE01());
	SPRITEFACTORY->registTexture(TEXKEY::TILE02(),TEXPATH::TILE02());
	SPRITEFACTORY->registTexture(TEXKEY::TILE03(),TEXPATH::TILE03());
	SPRITEFACTORY->registTexture(TEXKEY::TILE04(),TEXPATH::TILE04());
	SPRITEFACTORY->registTexture(TEXKEY::TILE05(),TEXPATH::TILE05());
	SPRITEFACTORY->registTexture(TEXKEY::TILE06(),TEXPATH::TILE06());


	//	メッシュ初期化
	MESHFACTORY->reserve(MESHKEY::SUM());
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


	
	TASKMNG::resize(TASKKEY::SUM());

	//	オブジェクト登録
	CTank* pObj = new CTank(
		MESHFACTORY->create(MESHKEY::TANK01_TOP()),
		MESHFACTORY->create(MESHKEY::TANK01_BOTTOM()),
		0,
		new CShell(60,0.5f,MESHFACTORY->create(MESHKEY::PIN())),
		0.05f,
		0.05f);
	CStage* pStage = new CStage(STAGEPATH::NO_01(),MESHFACTORY->create(MESHKEY::STAGE01()));

#ifdef _DEBUG
	CTank* pObj2 = new CTank(
		MESHFACTORY->create(MESHKEY::TANK04_TOP()),
		MESHFACTORY->create(MESHKEY::TANK04_BOTTOM()),
		-1,
		new CShell(60,0.5f,MESHFACTORY->create(MESHKEY::PIN())),
		0.05f,
		0.05f);
#endif

	OBJFACTORY->reserve(OBJKEY::SUM());
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANK01(),pObj);
#ifdef _DEBUG
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANKDUMMY(),pObj2);
#endif
	OBJFACTORY->registPrototype(OBJKEY::STAGE01(),pStage);
	OBJFACTORY->registPrototype(OBJKEY::FOLLOW(),new CFollowCamera);
	OBJFACTORY->registPrototype(OBJKEY::PIN(),new CPin(MESHFACTORY->create(MESHKEY::PIN())));
	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOW(),new CHitTestTankToWall);

	CHitTestTAndT* pHTTAT;
	pHTTAT = new CHitTestTAndT;

	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOT(),pHTTAT);
	OBJFACTORY->registPrototype(OBJKEY::HITTESTTTOS(),new CHitTestTankToShell);

}


/***********************************************************************/
/*! @brief ループ
 * 
 *  @retval void
 */
/***********************************************************************/
void gameLoop()
{

	//...入力情報の更新
	INPUTCOMMON->update();
	pLastScene = pScene;

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
		Phase = P_INIT;
		break;
	}
	if(drawBegin())
	{
		pScene->draw();
		FADEINOUT->draw();
		drawEnd();
		D3DDEVICE->Present(0,0,0,0);
	}
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

	OBJFACTORY->release();
	MESHFACTORY->release();
}
