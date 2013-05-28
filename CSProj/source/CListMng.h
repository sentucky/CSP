/***********************************************************************/
/*! @file  CListMng.h
 *  @brief リスト管理クラス
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CLISTMNG___
#define ___CLISTMNG___	///<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CListItem.h"

template<class T>
class CListMng
{
public:
	CListMng();
	virtual ~CListMng();
public:
	CListMng(const CListMng&);
	void operator =(const CListMng&);

	CListItem<T>* push_top(T pInst);
	CListItem<T>* push_back(T pInst);
	
	CListItem<T>* begin();
	CListItem<T>* end();

	void remove(CListItem<T>* pList);
	void erase(CListItem<T>* pList);
	void clear();
	void release();
	void connect_back(CListItem<T>* pPrev,CListItem<T>* pList);	//	後ろにつなぐ
	const uint size();									//	サイズ取得
protected:
	CListItem<T> _Begin;	///<	先頭タスク
	CListItem<T> _End;		///<	終端タスク
	uint	 _size;		///<	サイズ
};


template<class T>
/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CListMng<T>::CListMng()
	:_Begin(NULL),
	_End(NULL),
	_size(0)
{
	_Begin.setNext(&_End);
	_End.setPrev(&_Begin);
}

template<class T>
/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CListMng<T>::~CListMng()
{
	clear();
}


template<class T>
/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] constCListMng& 
 */
/***********************************************************************/
CListMng<T>::CListMng(const CListMng&)
	:_Begin(NULL),
	_End(NULL),
	_size(0)
{
	_Begin.setNext(&_End);
	_End.setPrev(&_Begin);
}

template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] constCListMng& 
 *  void
 */
/***********************************************************************/
void CListMng<T>::operator =(const CListMng&)
{
}


template<class T>
/***********************************************************************/
/*! @brief 先頭に追加
 * 
 *  @param[in] pInst 	追加するインスタンス
 *  @retval CListItem<T>*	追加されたインスタンスを持つ要素
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::push_top(T Inst)
{
	CListItem<T> pList = new CListItem<T>(Inst);
	connect_back(&Begin,pList);

	++_size;
	return pList;
}


template<class T>
/***********************************************************************/
/*! @brief 終端に追加
 * 
 *  @param[in] pInst	追加するインスタンス
 *  @retval CListItem<T>*	追加されたインスタンスを持つ要素
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::push_back(T Inst)
{
	CListItem<T>* pList = new CListItem<T>(Inst);
	connect_back(_End.prev(),pList);
	++_size;

	return pList;
}

template<class T>
/***********************************************************************/
/*! @brief 先頭の取得
 * 
 *  @retval CListItem<T>*	リストの先頭の要素
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::begin()
{
	return _Begin.next();
}

template<class T>
/***********************************************************************/
/*! @brief 終端の取得
 * 
 *  @retval CListItem<T>*	リストの終端の要素
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::end()
{
	return &_End;
}


template<class T>
/***********************************************************************/
/*! @brief 除外処理
 * 
 *  @param[in] pList 除外する要素
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::remove(CListItem<T>* pList)
{
	CListItem<T>* pPrev = pList->prev();
	CListItem<T>* pNext = pList->next();

	//	連結
	pPrev->setNext(pNext);
	pNext->setPrev(pPrev);

	//	自己参照で孤立
	pList->setNext(pList);
	pList->setPrev(pList);

	--_size;
}

template<class T>
/***********************************************************************/
/*! @brief 削除処理
 * 
 *  @param[in] pList 削除する要素
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::erase(CListItem<T>* pList)
{
	remove(pList);
	SAFE_DELETE( pList);
}

template<class T>
/***********************************************************************/
/*! @brief 解放処理
 * 
 *  @retval	void
 */
/***********************************************************************/
void CListMng<T>::release()
{
	for(;_Begin.next() != &_End;)
	{
		delete _Begin.next()->getInst();
		erase(_Begin.next());
	}
}

template<class T>
/***********************************************************************/
/*! @brief 後ろにつなぐ
 * 
 *  @param[in] pPrev 繋がれる要素
 *  @param[in] pList 繋ぐ要素
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::connect_back(CListItem<T>* pPrev, CListItem<T>* pList)
{
	CListItem<T>* pNext = pPrev->next();

	//	前の要素と連結
	pPrev->setNext(pList);
	pList->setPrev(pPrev);

	//	次の要素と連結
	pNext->setPrev(pList);
//	pNext->setNext(pList->next());
	pList->setNext(pNext);
}


template<class T>
/***********************************************************************/
/*! @brief クリア
 * 
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::clear()
{
	for(;_Begin.next() != &_End;)
	{
		erase(_Begin.next());
	}
}

template<class T>
/***********************************************************************/
/*! @brief サイズの取得
 * 
 *  @retval const uint サイズ
 */
/***********************************************************************/
const uint CListMng<T>::size()
{
	return _size;
}

#endif