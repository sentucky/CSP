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
#include"ObjKey.h"

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
	):CObjBase(OBJGROUPKEY::STAGE()),
	_pTaskDraw(NULL),
	_StageDataPath(StageFilePath),
	_StageData(new CStageData(_StageDataPath)),
	_Mesh(pMesh),
	_InstCnt(new int(0))
{
	++(*_InstCnt);
	D3DXMatrixIdentity(&_WMat);
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
	:CObjBase		(src._GroupID			),
	_pTaskDraw		(NULL					),
	_StageDataPath	(src._StageDataPath		),
	_StageData		(src._StageData			),
	_Mesh			(new CMesh(*src._Mesh)	),
	_InstCnt		(src._InstCnt			)
{
	++(*_InstCnt);
	D3DXMatrixIdentity(&_WMat);
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
	--*_InstCnt;

	if(*_InstCnt <= 0)
	{
		SAFE_DELETE(_StageData);
		SAFE_DELETE(_InstCnt);
	}
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
	_Mesh->draw(&_WMat);
	_StageData->Draw();
}



/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @retval void
 */
/***********************************************************************/
const CStageData* CStage::getStageData()
{
	return _StageData;
}


