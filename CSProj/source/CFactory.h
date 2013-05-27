/***********************************************************************/
/*! @file  CFactory.h
 *  @brief �t�@�N�g���[�e���v���[�g
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___FACTORY___
#define ___FACTORY___	//!<�C���N���[�h�K�[�h


/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"common.h"
#include"CSingleton.h"
#include"CCreator.h"
#include<vector>

#define OBJFACTORY CFactory<CObjBase>::getInst()

/***********************************************************************/
//	�N���X��`
/***********************************************************************/
template<class T>
class CFactory:public CSingleton<CFactory<T>>
{
	friend class CSingleton<CFactory<T>>;
private:
	CFactory();					///<	�R���X�g���N�^
	CFactory(const CFactory<T>&);	///<	�R�s�[�R���X�g���N�^
	~CFactory();				///<	�f�X�g���N�^
public:
	template<class InheriT>
	void registPrototype(const uint unKey,InheriT* pPrototype);	///<	���^�o�^
	void reserve(const uint unSumKey);						///<	�e�ʗ\��
	T* create(const uint unKey);							///<	���^���畡�������
	void release();											///<	���^�����ׂĎ����
private:
	std::vector<CCreatorInter<T>*> _prototypes;	///<	Prototype�i�[�x�N�^
};

template<class T>
/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @retval template<class T>
CFactory<T> 
 */
/***********************************************************************/
CFactory<T>::CFactory()
{
}

template<class T>
/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] constCFactory& 
 *  @retval template<class T>
CFactory<T> 
 */
/***********************************************************************/
CFactory<T>::CFactory(const CFactory&)
{
}

template<class T>
/***********************************************************************/
/*! @brief �f�X�g���N�^
 * 
 *  @retval template<class T>
CFactory<T> 
 */
/***********************************************************************/
CFactory<T>::~CFactory()
{
}

template<class T>
template<class InheriT>
/***********************************************************************/
/*! @brief ���^�o�^
 * 
 *  @param[in] unKey		���^�L�[
 *  @param[in] pPrototype	���^
 *  @retval template<class T>
			CFactory<T> 
 */
/***********************************************************************/
void CFactory<T>::registPrototype(const uint unKey,InheriT* pPrototype)
{
//#ifdef _DEBUG
	if(_prototypes.size() < unKey)
	{
		MessageAlert("�T�C�Y������܂���","error from CFactory<T>::reserve");
		return;
	}
	if(_prototypes[unKey] != NULL)
	{
		MessageAlert("���ɓo�^����Ă��܂�","error from CFactory<T>::reserve");
		return;
	}
//#endif
	_prototypes[unKey] = new CCreator<T,InheriT>(pPrototype);
}

template<class T>
/***********************************************************************/
/*! @brief �e�ʗ\��
 * 
 *  @param[in,out] unSumKey �m�ۗe��
 *  @retval void
			CFactory<T> 
 */
/***********************************************************************/
void CFactory<T>::reserve(const uint unSumKey)
{
	_prototypes.reserve(unSumKey);
	_prototypes.resize(unSumKey);
}

template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unKey 
 *  @retval template<class T>
			CFactory<T> 
 */
/***********************************************************************/
T* CFactory<T>::create(const uint unKey)
{
	return _prototypes[unKey]->create();
}


template<class T>
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unKey 
 *  @retval template<class T>
			CFactory<T> 
 */
/***********************************************************************/
void CFactory<T>::release()
{
	const uint unSumKey = _prototypes.size();
	for(uint unCnt = 0; unCnt < unSumKey; ++unCnt)
	{
		SAFE_DELETE(_prototypes[unCnt]);
	}
}

#endif