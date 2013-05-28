/***********************************************************************/
/*! @file  Loop.cpp
 *  @brief �Q�[�����[�v
 *  
 *  @author �쌴�@�C��
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
#include"CDevice.h"			//�f�o�C�X�N���X�w�b�_
#include"CTaskMng.h"
#include"CFactory.h"

#include"CCamera.h"

#include"CTank.h"
#include"CStage.h"
#include"CFollowCamera.h"
#include"CPin.h"
#include"CShell.h"
/***********************************************************************/
//	�O���[�o���ϐ��錾
/***********************************************************************/
CSceneBase* pScene		= NULL;
CSceneBase* pLastScene	= NULL;	//	�Ō�Ɉ������V�[��
uint		Phase		= 0;


/***********************************************************************/
//	��s�錾
/***********************************************************************/
BOOL drawBegin();	//	�`��J�n
void drawEnd();		//	�`��I��


/***********************************************************************/
//	�t�F�[�Y
/***********************************************************************/
enum{
	P_INIT,
	P_FADEIN,
	P_UPDATE,
	P_FADEOUT,
	P_SCENE_SWITCH,
};

/***********************************************************************/
/*! @brief ����������
 * 
 *  @retval void
 */
/***********************************************************************/
void gameInit()
{
	CDEVICE->init();				//�f�o�C�X�̏�����
	INPUTCOMMON->createKeyboard();
	INPUTCOMMON->createMouse();
	CSceneBase* ps;
	ps = new CSceneGame;
	pScene = ps;


	TEXTUREFACTORY->reserve(TEXKEY::SUM());
	SPRITEFACTORY->registTexture(TEXKEY::FADEMASK(),TEXPATH::FADEMASK());


	//	���b�V��������
	MESHFACTORY->reserve(MESHKEY::SUM());
	MESHFACTORY->registMesh(MESHKEY::TANK01_BOTTOM(),	MESHPATH::TANK01_BOTTOM()	);
	MESHFACTORY->registMesh(MESHKEY::TANK01_TOP(),		MESHPATH::TANK01_TOP()		);
	MESHFACTORY->registMesh(MESHKEY::STAGE01(),			MESHPATH::STAGE01()			);
	MESHFACTORY->registMesh(MESHKEY::PIN(),				MESHPATH::PIN()				);


	
	TASKMNG::resize(TASKID::SUM());

	//	�I�u�W�F�N�g�o�^
	CTank* pObj = new CTank(
		MESHFACTORY->create(MESHKEY::TANK01_TOP()),
		MESHFACTORY->create(MESHKEY::TANK01_BOTTOM()),
		0,
		new CShell(60,0.5f,MESHFACTORY->create(MESHKEY::PIN())),
		0.05f,
		0.05f);

	CStage* pStage = new CStage(MESHFACTORY->create(MESHKEY::STAGE01()));
	
	OBJFACTORY->reserve(OBJKEY::SUM());
	OBJFACTORY->registPrototype<CTank>(OBJKEY::TANK01(),pObj);
	OBJFACTORY->registPrototype<CStage>(OBJKEY::STAGE01(),pStage);
	OBJFACTORY->registPrototype<CFollowCamera>(OBJKEY::FOLLOW(),new CFollowCamera);
	OBJFACTORY->registPrototype<CPin>(OBJKEY::PIN(),new CPin(MESHFACTORY->create(MESHKEY::PIN())));

}


/***********************************************************************/
/*! @brief ���[�v
 * 
 *  @retval void
 */
/***********************************************************************/
void gameLoop()
{

	//...���͏��̍X�V
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
/*! @brief �`��J�n
 * 
 *  @retval BOOL ���s
 */
/***********************************************************************/
BOOL drawBegin()
{
	//---�`�揈��---//
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
/*! @brief �`��I��
 * 
 *  @retval void
 */
/***********************************************************************/
void drawEnd()
{
	D3DDEVICE->EndScene();
}

/***********************************************************************/
/*! @brief �������
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