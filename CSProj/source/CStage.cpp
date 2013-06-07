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

#include"StageData.h"

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
	_StageDataPath(StageFilePath),
	_StageData(NULL),
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
	_StageDataPath(src._StageDataPath),
	_StageData(NULL),
	_Mesh(new CMesh(*src._Mesh))
{
	D3DXMatrixIdentity(&_matW);
	_StageData = new CStageData(_StageDataPath);
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
	SAFE_DELETE(_StageData);
}

/***********************************************************************/
/*! @brief タスクの有効化
 * 
 *  @retval void
 */
/***********************************************************************/
void CStage::enableTask()
{
	CTaskMng::push<CStage>(
		TASKKEY::DRAW(),
		this,
		&CStage::draw,
		&_pTaskDraw
		);
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
	_StageData->Draw();
}



const CStageData* CStage::getStageData()
{
	return _StageData;
}


