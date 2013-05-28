/***********************************************************************/
/*! @file  CListMng.h
 *  @brief ���X�g�Ǘ��N���X
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CLISTMNG___
#define ___CLISTMNG___	///<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
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
	void connect_back(CListItem<T>* pPrev,CListItem<T>* pList);	//	���ɂȂ�
	const uint size();									//	�T�C�Y�擾
protected:
	CListItem<T> _Begin;	///<	�擪�^�X�N
	CListItem<T> _End;		///<	�I�[�^�X�N
	uint	 _size;		///<	�T�C�Y
};


template<class T>
/***********************************************************************/
/*! @brief �R���X�g���N�^
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
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CListMng<T>::~CListMng()
{
	clear();
}


template<class T>
/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
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
/*! @brief �擪�ɒǉ�
 * 
 *  @param[in] pInst 	�ǉ�����C���X�^���X
 *  @retval CListItem<T>*	�ǉ����ꂽ�C���X�^���X�����v�f
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
/*! @brief �I�[�ɒǉ�
 * 
 *  @param[in] pInst	�ǉ�����C���X�^���X
 *  @retval CListItem<T>*	�ǉ����ꂽ�C���X�^���X�����v�f
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
/*! @brief �擪�̎擾
 * 
 *  @retval CListItem<T>*	���X�g�̐擪�̗v�f
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::begin()
{
	return _Begin.next();
}

template<class T>
/***********************************************************************/
/*! @brief �I�[�̎擾
 * 
 *  @retval CListItem<T>*	���X�g�̏I�[�̗v�f
 */
/***********************************************************************/
CListItem<T>* CListMng<T>::end()
{
	return &_End;
}


template<class T>
/***********************************************************************/
/*! @brief ���O����
 * 
 *  @param[in] pList ���O����v�f
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::remove(CListItem<T>* pList)
{
	CListItem<T>* pPrev = pList->prev();
	CListItem<T>* pNext = pList->next();

	//	�A��
	pPrev->setNext(pNext);
	pNext->setPrev(pPrev);

	//	���ȎQ�ƂŌǗ�
	pList->setNext(pList);
	pList->setPrev(pList);

	--_size;
}

template<class T>
/***********************************************************************/
/*! @brief �폜����
 * 
 *  @param[in] pList �폜����v�f
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
/*! @brief �������
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
/*! @brief ���ɂȂ�
 * 
 *  @param[in] pPrev �q�����v�f
 *  @param[in] pList �q���v�f
 *  @retval void
 */
/***********************************************************************/
void CListMng<T>::connect_back(CListItem<T>* pPrev, CListItem<T>* pList)
{
	CListItem<T>* pNext = pPrev->next();

	//	�O�̗v�f�ƘA��
	pPrev->setNext(pList);
	pList->setPrev(pPrev);

	//	���̗v�f�ƘA��
	pNext->setPrev(pList);
//	pNext->setNext(pList->next());
	pList->setNext(pNext);
}


template<class T>
/***********************************************************************/
/*! @brief �N���A
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
/*! @brief �T�C�Y�̎擾
 * 
 *  @retval const uint �T�C�Y
 */
/***********************************************************************/
const uint CListMng<T>::size()
{
	return _size;
}

#endif