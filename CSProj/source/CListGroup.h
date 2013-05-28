#ifndef ___CLISTGROUP___
#define ___CLISTGROUP___

#include<vector>
#include"CListMng.h"
#include"CListItem.h"
#include"CSingleton.h"

template<class T>
class CListItem;

template<class T>
class CListGroup:public CSingleton<CListGroup<T>>
{
	friend class CSingleton<CListGroup<T>>;
public:
	void erase(
		const uint unID,
		CListItem<T>** deletedItem
		);	//	削除


	void push(
		const uint unID,
		T* pInst,
		CListItem<T>** pListItem
		);	//	追加

	void release();				//	開放

	void resize(const uint);	//	容量確保
protected:
	std::vector<CListMng<T>> _ListGroup;	//	グループの追加
};



template<class T>
void CListGroup<T>::erase(
	const uint unID,
	CListItem<T>** deletedItem
	)
{
	if( *deletedItem == NULL)
	{
		return;
	}
	const uint unTaskID = (*deletedItem)->getInst()->getTaskID();

	if( _ListGroup.size() == 0)
		return;

	delete ((*deletedItem)->getInst());
	_ListGroup[unTaskID].erase(*deletedItem);
	*deletedList = NULL;
}



template<class T>
void CListGroup<T>::push(
	const uint unID,
	T* pInst,
	CListItem<T>** pListItem
	)
{
	*pLIstItem = static_cast<CListItem<T>*>(_ListGroup[unID].push(pInst));
}



template<class T>
void CListGroup<T>::release()
{
	const uint unVectorSize = _ListGroup.size();	//	ベクタサイズ

	for(uint unVCnt = 0; unVCnt < unVectorSize; ++unVCnt)
	{
		_ListGroup[unVCnt].clear();
	}
	_ListGroup.clear();
}



template<class T>
void CListGroup<T>::resize(const uint unSize)
{
	_ListGroup.resize(unSize);
	_ListGroup.reserve(unSize);
}

#endif