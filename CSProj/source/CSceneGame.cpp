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
	release();
	_pCamera = new CCamera;
	_pCamera->setEyeY(50);
	_pCamera->update();
	
	CTank* pTank = NULL;
	CFollowCamera* pFCam;
	CObjBase* ObjPtr;

	OBJMNG->push_back(OBJFACTORY->create(OBJKEY::STAGE01()));
	OBJMNG->push_back(pTank = static_cast<CTank*>(OBJFACTORY->create(OBJKEY::TANK01())));
	OBJMNG->push_back(pFCam = static_cast<CFollowCamera*>(OBJFACTORY->create(OBJKEY::FOLLOW())));
	OBJMNG->push_back(ObjPtr = OBJFACTORY->create(OBJKEY::PIN()));
	pFCam->setTank(pTank);
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
	_pCamera->update();

	CListItem<CObjBase*>* run = OBJMNG->begin();
	CListItem<CObjBase*>* next = NULL;
	CListItem<CObjBase*>* end = OBJMNG->end();
	while(run != end)
	{
		if(run->getInst()->getDeleteFlg() == TRUE)
		{
			next = run->next();
			OBJMNG->erase(run);
			run = next;
			continue;
		}
		run = run->next();
	}
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