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
	delete aaaaaaaaaaaaa;
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


	aaaaaaaaaaaaa  = new CLight;
	aaaaaaaaaaaaa->lightON();
	aaaaaaaaaaaaa->setDirectionalLight(
		COLORVALUE(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR3(1.0,-1.0f,0)
		);

	//CStageData::getInst()->Load();

	//	�J�����쐬
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	���X�g�T�C�Y�ݒ�
	OBJMNG->resize(OBJGROUPKEY::SUM());

	//	�I�u�W�F�N�g�쐬
	//...�X�e�[�W
	OBJMNG->push(OBJGROUPKEY::STAGE(),OBJFACTORY->create(OBJKEY::STAGE01()),NULL);

	//...���
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

	//...�ǐՃJ����
	CFollowCamera*	pFCam = NULL;
	OBJMNG->push(OBJGROUPKEY::FOLLOW(),pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())),NULL);
	pFCam->setTank(pTank);

	//...�s��
	OBJMNG->push(OBJGROUPKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);

	//	�ǐՃJ�����̒ǐՑΏېݒ�

	//	�����蔻��
//	OBJMNG->push(OBJGROUPKEY::HITTEST(),static_cast<CHitTestTAndT*>(OBJFACTORY->create(OBJKEY::HITTEST())),NULL);
	OBJMNG->push(OBJGROUPKEY::HITTEST(),static_cast<CHitTestTAndT*>(OBJFACTORY->create(OBJKEY::HITTEST())),NULL);
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
	
#ifdef _DEBUG
	static RECTEX fpspos(0,0,0,0);
	FONT->DrawInt("FPS:",CTIMER->getFPS(),fpspos);
   
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