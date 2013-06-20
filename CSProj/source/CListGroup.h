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
 *	@brift リストグループ
 *
 */
template<class T>
class CListGroup
{
public:
	//	削除
	void erase(
		const uint unID,
		CListItem<T>** deletedItem
		);						

	//	追加
	void push(
		const uint unID,
		T pInst,
		CListItem<T>** pListItem
		);						

	//	開放処理
	void release();	

	//	容量確保
	void resize(const uint);				

	//	リスト取得
	CListMng<T>* getList(const uint unID);

	//	サイズ取得
	const uint size();						
protected:
	std::vector<CListMng<T>> _ListGroup;	///<	グループの追加
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
	const uint unVectorSize = _ListGroup.size();	///<	ベクタサイズ

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


//	リスト取得
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


//	サイズ取得
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