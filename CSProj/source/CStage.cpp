/***********************************************************************/
/*! @file  CStage.cpp
 *  @brief �X�e�[�W�I�u�W�F�N�g
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#include"CStage.h"
#include"CMesh.h"
#include"CTaskMng.h"
#include"CTaskList.h"
#include"const.h"

/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] pMesh
 */
/***********************************************************************/
CStage::CStage(
	const char* StageFilePath,
	CMesh* pMesh
	):_pTaskDraw(NULL),
	_StageFilePath(StageFilePath),
	_Mesh(pMesh)
{
	D3DXMatrixIdentity(&_matW);
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CStage::~CStage()
{
	disableTask();
	release();
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] src �R�s�[����I�u�W�F�N�g
 *  @retval  
 */
/***********************************************************************/
CStage::CStage(const CStage& src)
	:_pTaskDraw(NULL),
	_StageFilePath(src._StageFilePath),
	_Mesh(new CMesh(*src._Mesh))
{
	D3DXMatrixIdentity(&_matW);

	enableTask();
}

/***********************************************************************/
/*! @brief �������
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::release()
{
	SAFE_DELETE(_Mesh);
}

/***********************************************************************/
/*! @brief �^�X�N�̗L����
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::enableTask()
{
	CTaskMng::push<CStage>(	TASKKEY::DRAW(),	this,&CStage::draw, &_pTaskDraw);
}

/***********************************************************************/
/*! @brief �^�X�N�̖�����
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::disableTask()
{
	CTaskMng::erase(&_pTaskDraw);
}

/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::draw()
{
	_Mesh->draw(&_matW);
}