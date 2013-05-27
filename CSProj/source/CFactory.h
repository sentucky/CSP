/***********************************************************************/
/*! @file  CFactory.h
 *  @brief ファクトリーテンプレート
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___FACTORY___
#define ___FACTORY___	//!<インクルードガード


/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"common.h"
#include"CSingleton.h"
#include"CCreator.h"
#include<vector>

#define OBJFACTORY CFactory<CObjBase>::getInst()

/***********************************************************************/
//	クラス定義
/***********************************************************************/
template<class T>
class CFactory:public CSingleton<CFactory<T>>
{
	friend class CSingleton<CFactory<T>>;
private:
	CFactory();					///<	コンストラクタ
	CFactory(const CFactory<T>&);	///<	コピーコンストラクタ
	~CFactory();				///<	デストラクタ
public:
	template<class InheriT>
	void registPrototype(const uint unKey,InheriT* pPrototype);	///<	原型登録
	void reserve(const uint unSumKey);						///<	容量予約
	T* create(const uint unKey);							///<	原型から複製を作る
	void release();											///<	原型をすべて手放す
private:
	std::vector<CCreatorInter<T>*> _prototypes;	///<	Prototype格納ベクタ
};

template<class T>
/***********************************************************************/
/*! @brief コンストラクタ
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
/*! @brief コピーコンストラクタ
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
/*! @brief デストラクタ
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
/*! @brief 原型登録
 * 
 *  @param[in] unKey		原型キー
 *  @param[in] pPrototype	原型
 *  @retval template<class T>
			CFactory<T> 
 */
/***********************************************************************/
void CFactory<T>::registPrototype(const uint unKey,InheriT* pPrototype)
{
//#ifdef _DEBUG
	if(_prototypes.size() < unKey)
	{
		MessageAlert("サイズが足りません","error from CFactory<T>::reserve");
		return;
	}
	if(_prototypes[unKey] != NULL)
	{
		MessageAlert("既に登録されています","error from CFactory<T>::reserve");
		return;
	}
//#endif
	_prototypes[unKey] = new CCreator<T,InheriT>(pPrototype);
}

template<class T>
/***********************************************************************/
/*! @brief 容量予約
 * 
 *  @param[in,out] unSumKey 確保容量
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