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

#ifdef _DEBUG
#include"CInputCommon.h"
#include"CFont.h"
#include"CScreen.h"
#include"CListGroup.h"
#endif

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

	//	�J�����쐬
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	//	���X�g�T�C�Y�ݒ�
	OBJMNG->resize(OBJKEY::SUM());

	//	�I�u�W�F�N�g�쐬
	//...�X�e�[�W
	OBJMNG->push(OBJKEY::STAGE01(),OBJFACTORY->create(OBJKEY::STAGE01()),NULL);

	//...���
	CTank*			pTank = NULL;
	OBJMNG->push(OBJKEY::TANK01(),pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())),NULL);

	//...�ǐՃJ����
	CFollowCamera*	pFCam = NULL;
	OBJMNG->push(OBJKEY::FOLLOW(),pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())),NULL);
	pFCam->setTank(pTank);

	//...�s��
	OBJMNG->push(OBJKEY::PIN(),OBJFACTORY->create(OBJKEY::PIN()),NULL);

	//	�ǐՃJ�����̒ǐՑΏېݒ�
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