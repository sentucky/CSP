/***********************************************************************/
/*! @file  CTaskMng.h
 *  @brief �^�X�N�Ǘ��N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___TASKMNG___
#define ___TASKMNG___	///<	�C���N���[�h�K�[�h


/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include<list>
#include<vector>
#include"common.h"
#include"CTask.h"
#include"CListMng.h"
#include"const.h"
/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CTaskBase;	///<	�^�X�N�x�[�X
template<class T>
class CListMng;		///<	���X�g�Ǘ�
class CTaskList;	///<	�^�X�N���X�g


/***********************************************************************/
//	�^��`
/***********************************************************************/
typedef CListMng<CTaskBase*>				TASKLIST;
typedef std::vector<CListMng<CTaskBase*>>	TASKVEC;

#define TASKMNG CTaskMng

/***********************************************************************/
/*!	@class CTaskMng
 *	@brift �^�X�N�Ǘ��N���X
 */
/***********************************************************************/
class CTaskMng
{
public:
	CTaskMng();										///<	�R���X�g���N�^
	~CTaskMng();									///<	�f�X�g���N�^
	static void run();								///<	�^�X�N���s
	static void draw();								///<		�`�揈��
	static void resize(uint unSize);				///<	�T�C�Y�g��

	static void erase(CTaskList** deletedList);		///<	�폜

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
		);	///<	�^�X�N�o�^

	static void release();							///<	�������
private:
	static 	TASKVEC		_TaskList;		//!<	�^�X�N���X�g�̃x�N�^
	static	TASKLIST	_DrawTaskList;	///<	�`��^�X�N���X�g
};



/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] unTaskID �^�X�N�ԍ�
 *  @param[in] pInst	�C���X�^���X
 *  @param[in] func		�֐��|�C���^
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