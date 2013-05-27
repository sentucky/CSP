/***********************************************************************/
/*! @file  CCreator.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CCREATOR___
#define ___CCREATOR___


#include"common.h"


/***********************************************************************/
/*! @class	CCreatorInter
 *	@brift	クリエータインターフェース
 */
/***********************************************************************/
template<class T>
class CCreatorInter
{
public:
	CCreatorInter(){};
	virtual ~CCreatorInter(){};

	virtual T* create() = 0;

};

/***********************************************************************/
/*! @class	CCreator
 *	@brift	クリエータ
 */
/***********************************************************************/
template<class BaseT,class InheriT>
class CCreator:public CCreatorInter<BaseT>
{
public:
	/***********************************************************************/
	/*! @brief コンストラクタ
	 * 
	 *  @param[in,out] pPrototype 
	 *  @retval  
	 */
	/***********************************************************************/
	CCreator(InheriT* pPrototype)
	{
		_pPrototype = pPrototype;
	}

	/***********************************************************************/
	/*! @brief デストラクタ
	 * 
	 *  @retval  
	 */
	/***********************************************************************/
	~CCreator(){SAFE_DELETE(_pPrototype);}
	/***********************************************************************/
	/*! @brief 作成処理
	 * 
	 *  @retval BaseT* 被作成オブジェクト
	 */
	/***********************************************************************/
	BaseT* create()
	{
		return new InheriT(*_pPrototype);
	}
private:
	InheriT* _pPrototype;
};
#endif


