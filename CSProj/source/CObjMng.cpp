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
	
	const uint size = _ListGroup.size();
	for(uint Cnt = 0; Cnt < size; Cnt++)
	{
		CListItem<CObjBase*>* pRun = _ListGroup[Cnt].begin();
		CListItem<CObjBase*>* pEnd = _ListGroup[Cnt].end();
		CObjBase* pInst;

		while(pRun != pEnd)
		{
			pInst = pRun->getInst();
			if(pInst->getDeleteFlg() == TRUE)
			{
				CListItem<CObjBase*>* pNext = pRun->next();
				delete pRun->getInst();
				_ListGroup[Cnt].erase(pRun);
				pRun = pNext;
			}
			else
			{
				pRun = pRun->next();
			}
		}
	}
};