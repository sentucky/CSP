/***********************************************************************/
/*! @file  CSceneGame.cpp
 *  @brief �Q�[�������̏���
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
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
#include"CHitTestTankToShell.h"
#include"CHitTestTankToWall.h"

#ifdef _DEBUG
#include"CPin.h"
#include"CTankIntDummy.h"

#include"CInputCommon.h"
#include"CFont.h"
#include"CScreen.h"
#include"CListGroup.h"
#include"CTime.h"
#endif

#include"CLight.h"
#include"StageData.h"

#include "CTankIntDummy.h"

	CLight* GLight;

/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CSceneGame::CSceneGame()
	:_pCamera(NULL)
{
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CSceneGame::~CSceneGame()
{
	release();
	TASKMNG::release();
	delete GLight;
}

/***********************************************************************/
/*! @brief ����������
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::init()
{
	//	�������
	release();

	_DrawFlg = FALSE;


	GLight  = new CLight;
	GLight->lightON();
	GLight->setDirectionalLight(
		COLORVALUE(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR3(0.0,-1.0f,5.0f)
		);


	//	�J�����쐬
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	���X�g�T�C�Y�ݒ�
	OBJMNG->resize(OBJGROUPKEY::SUM());

	//	�I�u�W�F�N�g�쐬
	//...�X�e�[�W
	CStage* pStage;
	OBJMNG->push(OBJGROUPKEY::STAGE(),pStage = static_cast<CStage*>(OBJFACTORY->create(OBJKEY::STAGE01())),NULL);

	//...���
	CTank*			pTank = NULL;
	OBJMNG->push(OBJGROUPKEY::TANK(),pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())),NULL);

#ifdef _DEBUG
	CTank*			pTank2 = NULL;
//*
	OUTPUT t[16][16];
	pStage->getStageData()->getTile(t);
	CPin* pin = NULL;
	int n2 = 0;
	/*
	for(int n = 0; n < 8; n++)
	{
	//	for( = 0; n2 < 8; n2++)
		{
			OBJMNG->push(OBJGROUPKEY::TANK(),pTank2 = (CTank*)OBJFACTORY->create(OBJKEY::TANKDUMMY()),NULL);
			pTank2->setPos(
				pTank->getMatBottom()->_41 + n * 0.1, 
				pTank->getMatBottom()->_43 + n2 * 0.1);
		}
	}
//*/
#endif

	//...�ǐՃJ����
	CFollowCamera*	pFCam = NULL;
	OBJMNG->push(OBJGROUPKEY::FOLLOW(),pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())),NULL);
	pFCam->setTank(pTank);

	//...�s��
	OBJMNG->push(OBJGROUPKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);
#ifdef _DEBUG

#endif

	//	�����蔻��
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOT())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOW())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),(OBJFACTORY->create(OBJKEY::HITTESTTTOS())),NULL);

	
	CTankIntInter::setStageData(pStage->getStageData());
	CTank::setStageData(pStage->getStageData());
	CHitTestTankToWall::setStageData(pStage->getStageData());
	CHitTestTankToWall::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));
	CHitTestTankToShell::setShellList(OBJMNG->getList(OBJGROUPKEY::SHELL()));
	CHitTestTankToShell::setTankList(OBJMNG->getList(OBJGROUPKEY::TANK()));

	//	�X�^�[�g�ʒu�ɔz�u
	standby(pStage);
	pFCam->update();
	_DrawFlg = TRUE;
}

/***********************************************************************/
/*! @brief �X�V����
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::update()
{
	CHECK_UPDATE;


	CTaskMng::run();

	//	�I�u�W�F�N�g�̍X�V
	_pCamera->update();

	//	�s�v�I�u�W�F�N�g�̍폜
	OBJMNG->checkDelete();
}

/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneGame::draw()
{
	CHECK_DRAW;
	CTaskMng::draw();

//	CTankIntDummy::Debug();
	
#ifdef _DEBUG
	static RECTEX fpspos(0,0,0,0);
	FONT->DrawInt("FPS:",CTIMER->getFPS(),fpspos);
	static RECTEX ps(0,16,0,0);
	static D3DXVECTOR3 Mouse3DPos;
	MOUSE.mousePoint3D(&Mouse3DPos,0);
	FONT->DrawFloat("MOUSEX:",Mouse3DPos.x,RECTEX(0,16,0,0));
	ps.left = 50;		   
	FONT->DrawFloat("MOUSEZ:",Mouse3DPos.z,RECTEX(150,16,0,0));
   
#endif
}

/***********************************************************************/
/*! @brief �������
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
/*! @brief �V�[���؂�ւ�
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
	//	�v�f���o
	CListMng<CObjBase*>* pTankMng = OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>*pListTank	= pTankMng->begin();
	const CListItem<CObjBase*>*pEnd = pTankMng->end();



	//	�J�n�ʒu�̃^�C�����擾������
	//....�X�^�[�g�ʒu�^�C���擾
	const OUTPUT* pStTile= pStage->getStageData()->getStartTile();

	
	const float moveX = 1.0f;
	const float moveY = 1.0f;

	//....��_�擾
	const float& pointX = pStTile->posX;
	const float& pointY = pStTile->posY;

	uint cnt = 0;
	CTank* pTank = NULL;

	while(pListTank !=  pEnd)
	{
	//	�{���̌^�Ń|�C���^�擾
		
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
