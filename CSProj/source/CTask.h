/***********************************************************************/
/*! @file  CTask.h
 *  @brief �^�X�N�N���X
 *  
 *  @author �쌴�@�C��
 *  @date
 */
/***********************************************************************/
#ifndef ___CTASK___
#define ___CTASK___	///<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CTaskBase.h"

/***********************************************************************/
/*! @class  CTask
 *  @brief �^�X�N�N���X
 */
/***********************************************************************/
template<class T>
class CTask:public CTaskBase
{
public:
	CTask(
		const uint unTaskID,
		T* pInst,
		void (T::*func)()
		);					///<	�R���X�g���N�^
	~CTask();				///<	�f�X�g���N�^
	void run();				///<	�����֐����s

private:
	T*				_pInst;			///<	�C���X�^���X
	void			(T::*_func)();	///<	�����o�֐��|�C���^
};



/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] unTaskID �^�X�N�ԍ�
 *  @param[in] pInst 	�����֐������C���X�^���X
 *  @param[in] func 	�����o�֐��|�C���^
 */
/***********************************************************************/
template<class T>
CTask<T>::CTask(
		const	uint	unTaskID,
				T*		pInst,
				void	(T::*func)()
	):CTaskBase(unTaskID),
	_pInst(pInst),
	_func(func)
{
}



/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
template<class T>
CTask<T>::~CTask()
{
}



/***********************************************************************/
/*! @brief �����֐�
 * 
 *  @retval void
 */
/***********************************************************************/
template<class T>
void CTask<T>::run()
{
	(_pInst->*_func)();
}

#endif