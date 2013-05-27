/***********************************************************************/

/*! @file  CObjMng.cpp
 *  @brief �I�u�W�F�N�g�Ǘ����X�g
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CObjBase.h"
#include"CObjMng.h"

/***********************************************************************/
/*! @brief �폜�`�F�b�N
 * 
 *  @retval void
 */
/***********************************************************************/
void CObjMng::checkDelete()
{
	CListItem<CObjBase*>* pRun = _Begin.next();
	CObjBase* pInst;

	for(;pRun != &_End; pRun = pRun->next())
	{
		pInst = pRun->getInst();
		if(pInst->getDeleteFlg() == TRUE)
		{
			CListItem<CObjBase*>* pNext = pRun->next();
			erase(pRun);
			pRun = pNext;
		}
		else
		{
			pRun = pRun->next();
		}
	}
};