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
 *	@brift	�N���G�[�^�C���^�[�t�F�[�X
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
 *	@brift	�N���G�[�^
 */
/***********************************************************************/
template<class BaseT,class InheriT>
class CCreator:public CCreatorInter<BaseT>
{
public:
	/***********************************************************************/
	/*! @brief �R���X�g���N�^
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
	/*! @brief �f�X�g���N�^
	 * 
	 *  @retval  
	 */
	/***********************************************************************/
	~CCreator(){SAFE_DELETE(_pPrototype);}
	/***********************************************************************/
	/*! @brief �쐬����
	 * 
	 *  @retval BaseT* ��쐬�I�u�W�F�N�g
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


