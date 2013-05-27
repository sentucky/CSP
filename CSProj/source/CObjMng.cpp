/***********************************************************************/

/*! @file  CObjMng.cpp
 *  @brief オブジェクト管理リスト
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CObjBase.h"
#include"CObjMng.h"

/***********************************************************************/
/*! @brief 削除チェック
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