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