/***********************************************************************/
/*! @file  CTaskMng.h
 *  @brief タスク管理クラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___TASKMNG___
#define ___TASKMNG___	///<	インクルードガード


/***********************************************************************/
//	インクルード
/***********************************************************************/
#include<list>
#include<vector>
#include"common.h"
#include"CTask.h"
#include"CListMng.h"
#include"const.h"
/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CTaskBase;	///<	タスクベース
template<class T>
class CListMng;		///<	リスト管理
class CTaskList;	///<	タスクリスト


/***********************************************************************/
//	型定義
/***********************************************************************/
typedef CListMng<CTaskBase*>				TASKLIST;
typedef std::vector<CListMng<CTaskBase*>>	TASKVEC;

#define TASKMNG CTaskMng

/***********************************************************************/
/*!	@class CTaskMng
 *	@brift タスク管理クラス
 */
/***********************************************************************/
class CTaskMng
{
public:
	CTaskMng();										///<	コンストラクタ
	~CTaskMng();									///<	デストラクタ
	static void run();								///<	タスク実行
	static void draw();								///<		描画処理
	static void resize(uint unSize);				///<	サイズ拡張

	static void erase(CTaskList** deletedList);		///<	削除

	static void push(
		const uint unTaskID,
		CTaskBase*  task,
		CTaskList** pRef
		);
	template<class T>
	static void push(
		const uint unTaskID,
		T* pInst,
		void (T::*func)(),
		CTaskList** pList
		);	///<	タスク登録

	static void release();							///<	解放処理
private:
	static 	TASKVEC		_TaskList;		//!<	タスクリストのベクタ
	static	TASKLIST	_DrawTaskList;	///<	描画タスクリスト
};



/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] unTaskID タスク番号
 *  @param[in] pInst	インスタンス
 *  @param[in] func		関数ポインタ
 *  @retval void 
 */
/***********************************************************************/
template<class T>
void CTaskMng::push(	
		const uint unTaskID,
		T* pInst,
		void (T::*func)(),
		CTaskList** pRef
		)
{
	if(*pRef != NULL)
	{
		return;
	}

	CTask<T>* pTask = new CTask<T>(unTaskID, pInst, func);
	if(TASKKEY::DRAW() == unTaskID)
	{
		*pRef = static_cast<CTaskList*>(_DrawTaskList.push_back(pTask));
	}
	else
	{
		*pRef = static_cast<CTaskList*>(_TaskList[unTaskID].push_back(pTask));
	}
}
#endif