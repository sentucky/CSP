/***********************************************************************/
/*! @file  CStage.cpp
 *  @brief ステージオブジェクト
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"CStage.h"
#include"CMesh.h"
#include"CTaskMng.h"
#include"CTaskList.h"
#include"const.h"

/***********************************************************************/
/*! @brief コンストラクタ
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
/*! @brief デストラクタ
 */
/***********************************************************************/
CStage::~CStage()
{
	disableTask();
	release();
}

/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] src コピーするオブジェクト
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
/*! @brief 解放処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::release()
{
	SAFE_DELETE(_Mesh);
}

/***********************************************************************/
/*! @brief タスクの有効化
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::enableTask()
{
	CTaskMng::push<CStage>(	TASKKEY::DRAW(),	this,&CStage::draw, &_pTaskDraw);
}

/***********************************************************************/
/*! @brief タスクの無効化
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::disableTask()
{
	CTaskMng::erase(&_pTaskDraw);
}

/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::draw()
{
	_Mesh->draw(&_matW);
}