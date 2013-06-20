/***********************************************************************/
/*! @file  CListGroup.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CLISTGROUP___
#define ___CLISTGROUP___

#include<vector>
#include"CListMng.h"
#include"CListItem.h"
#include"CSingleton.h"

template<class T>
class CListItem;


/*!
 *	@class CListGroup
 *	@brift ���X�g�O���[�v
 *
 */
template<class T>
class CListGroup
{
public:
	//	�폜
	void erase(
		const uint unID,
		CListItem<T>** deletedItem
		);						

	//	�ǉ�
	void push(
		const uint unID,
		T pInst,
		CListItem<T>** pListItem
		);						

	//	�J������
	void release();	

	//	�e�ʊm��
	void resize(const uint);				

	//	���X�g�擾
	CListMng<T>* getList(const uint unID);

	//	�T�C�Y�擾
	const uint size();						
protected:
	std::vector<CListMng<T>> _ListGroup;	///<	�O���[�v�̒ǉ�
};



template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unID 
 *  @param[in,out] deletedItem 
 *  @retval template<class T>
void CListGroup<T> 
 */
/***********************************************************************/
void CListGroup<T>::erase(
	const uint unID,
	CListItem<T>** deletedItem
	)
{
	if( *deletedItem == NULL)
	{
		return;
	}
	const uint unTaskID = (*deletedItem)->getInst()->getID();

	if( _ListGroup.size() == 0)
		return;

	delete ((*deletedItem)->getInst());
	_ListGroup[unTaskID].erase(*deletedItem);
	*deletedItem = NULL;
}



template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unID 
 *  @param[in,out] pInst 
 *  @param[in,out] pListItem 
 *  @retval template<class T>
void CListGroup<T> 
 */
/***********************************************************************/
void CListGroup<T>::push(
	const uint unID,
	T pInst,
	CListItem<T>** pListItem
	)
{
	CListItem<T>* pItem = NULL;
	pItem = static_cast<CListItem<T>*>(_ListGroup[unID].push_back(pInst));
	if(pListItem != NULL)
	{
		*pListItem = pItem;
	}
}



template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @retval template<class T>
void CListGroup<T> 
 */
/***********************************************************************/
void CListGroup<T>::release()
{
	const uint unVectorSize = _ListGroup.size();	///<	�x�N�^�T�C�Y

	for(uint unVCnt = 0; unVCnt < unVectorSize; ++unVCnt)
	{
		_ListGroup[unVCnt].release();
	}
	_ListGroup.clear();
}



template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unSize 
 *  @retval template<class T>
void CListGroup<T> 
 */
/***********************************************************************/
void CListGroup<T>::resize(const uint unSize)
{
	_ListGroup.resize(unSize);
	_ListGroup.reserve(unSize);
}


//	���X�g�擾
template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unID 
 *  @retval template<class T>
CListMng<T>* CListGroup<T> 
 */
/***********************************************************************/
CListMng<T>* CListGroup<T>::getList(const uint unID)
{
	return &(_ListGroup[unID]);
}


//	�T�C�Y�擾
template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @retval template<class T>
const uint CListGroup<T> 
 */
/***********************************************************************/
const uint CListGroup<T>::size()
{
	return _ListGroup.size();
}


#endif