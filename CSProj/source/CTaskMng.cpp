/***********************************************************************/
/*! @file  CTaskMng.cpp
 *  @brief タスク管理リスト
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CTaskMng.h"
#include"CTask.h"
#include"CListItem.h"
#include"CListMng.h"
#include"CTaskList.h"

/***********************************************************************/
//	静的メンバ定義
/***********************************************************************/
TASKLIST	CTaskMng::_DrawTaskList;
TASKVEC		CTaskMng::_TaskList;

/***********************************************************************/
/*! @brief デフォルトコンストラクタ
 */
/***********************************************************************/
CTaskMng::CTaskMng()
{
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CTaskMng::~CTaskMng()
{
	release();
}

/***********************************************************************/
/*! @brief 処理関数
 */
/***********************************************************************/
void CTaskMng::run()
{

	const uint unVectorSize = _TaskList.size();	//	ベクタサイズ

	CListItem<CTaskBase*>* run;	//	リスト走査用ポインタ
	CListItem<CTaskBase*>* end;	//	終端リストポインタ

	//	処理
	for(uint unVCnt = 0; unVCnt < unVectorSize; unVCnt++)
	{
		run = _TaskList[unVCnt].begin();	//	先頭取得
		end = _TaskList[unVCnt].end();		//	終端取得

		//	処理実行
		/***********************************************************************/
		/*! @brief 
		 * 
		 *  @retval run = run-> 
		 */
		/***********************************************************************/
		/***********************************************************************/
		/*! @brief 
		 * 
		 *  @retval run = run-> 
		 */
		/***********************************************************************/
		for(; run != end; run = run->next())
		{
			run->getInst()->run();
		}
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::draw()
{
	CListItem<CTaskBase*>* run = _DrawTaskList.begin();
	CListItem<CTaskBase*>* end = _DrawTaskList.end();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval run = run-> 
	 */
	/***********************************************************************/
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval run = run-> 
	 */
	/***********************************************************************/
	for(; run != end; run = run->next())
	{
		run->getInst()->run();
	}
}


/***********************************************************************/
/*! @brief サイズを広げる
 * 
 *  @param[in] unSize 設定するサイズ
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::resize(uint unSize)
{
	_TaskList.resize(unSize);
	_TaskList.reserve(unSize);
}


/***********************************************************************/
/*! @brief 削除処理
 * 
 *  @param[in] deleledList　被削除
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::erase(CTaskList** deletedList)
{
	if( *deletedList == NULL)
	{
		return;
	}


	const uint unTaskID = (*deletedList)->getInst()->getID();

	if(unTaskID == TASKKEY::DRAW())
	{
		delete ((*deletedList)->getInst());
		_DrawTaskList.erase(*deletedList);
		*deletedList = NULL;
		return;
	}

	if( _TaskList.size() == 0)
		return;

	delete ((*deletedList)->getInst());
	_TaskList[unTaskID].erase(*deletedList);
	*deletedList = NULL;
}
/***********************************************************************/
/*! @brief 解放処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::release()
{
	const uint unVectorSize = _TaskList.size();	//	ベクタサイズ

	for(uint unVCnt = 0; unVCnt < unVectorSize; ++unVCnt)
	{
		_TaskList[unVCnt].clear();
	}
	_TaskList.clear();
}
