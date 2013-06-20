/***********************************************************************/
/*! @file  CTaskMng.cpp
 *  @brief �^�X�N�Ǘ����X�g
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CTaskMng.h"
#include"CTask.h"
#include"CListItem.h"
#include"CListMng.h"
#include"CTaskList.h"

/***********************************************************************/
//	�ÓI�����o��`
/***********************************************************************/
TASKLIST	CTaskMng::_DrawTaskList;
TASKVEC		CTaskMng::_TaskList;

/***********************************************************************/
/*! @brief �f�t�H���g�R���X�g���N�^
 */
/***********************************************************************/
CTaskMng::CTaskMng()
{
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTaskMng::~CTaskMng()
{
	release();
}

/***********************************************************************/
/*! @brief �����֐�
 */
/***********************************************************************/
void CTaskMng::run()
{

	const uint unVectorSize = _TaskList.size();	//	�x�N�^�T�C�Y

	CListItem<CTaskBase*>* run;	//	���X�g�����p�|�C���^
	CListItem<CTaskBase*>* end;	//	�I�[���X�g�|�C���^

	//	����
	for(uint unVCnt = 0; unVCnt < unVectorSize; unVCnt++)
	{
		run = _TaskList[unVCnt].begin();	//	�擪�擾
		end = _TaskList[unVCnt].end();		//	�I�[�擾

		//	�������s
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
/*! @brief �T�C�Y���L����
 * 
 *  @param[in] unSize �ݒ肷��T�C�Y
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::resize(uint unSize)
{
	_TaskList.resize(unSize);
	_TaskList.reserve(unSize);
}


/***********************************************************************/
/*! @brief �폜����
 * 
 *  @param[in] deleledList�@��폜
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
/*! @brief �������
 * 
 *  @retval void
 */
/***********************************************************************/
void CTaskMng::release()
{
	const uint unVectorSize = _TaskList.size();	//	�x�N�^�T�C�Y

	for(uint unVCnt = 0; unVCnt < unVectorSize; ++unVCnt)
	{
		_TaskList[unVCnt].clear();
	}
	_TaskList.clear();
}
