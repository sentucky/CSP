/***********************************************************************/
/*! @file  CHitTestTAndT.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CHitTestTAndT.h"

#include"CTaskMng.h"

#include"CObjBase.h"
#include"CListMng.h"
#include"CTank.h"

#include"CTaskList.h"
#include"CObjMng.h"

CListMng<CObjBase*>* CHitTestTAndT::_pTankList = NULL;

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CHitTestTAndT::CHitTestTAndT()
	:_HitTestTask(NULL)
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CHitTestTAndT::~CHitTestTAndT()
{
	disableTask();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CHitTestTAndT::CHitTestTAndT(const CHitTestTAndT& src)
	:_HitTestTask(NULL)
{
	if(_pTankList == NULL)
	{
		_pTankList = OBJMNG->getList(OBJGROUPKEY::TANK());
	}
	enableTask();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTAndT::enableTask()
{
	CTaskMng::push<CHitTestTAndT>(
		TASKKEY::HITTEST_TANKADNTANK(),
		this,
		&CHitTestTAndT::hitTest,
		&_HitTestTask);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTAndT::disableTask()
{
	CTaskMng::erase(&_HitTestTask);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTAndT::hitTest()
{
	CListItem<CObjBase*>* pRunA = _pTankList->begin();
	CListItem<CObjBase*>* pRunB = NULL;
	CListItem<CObjBase*>* pEnd = _pTankList->end();
	CTank* pTankA = NULL;
	CTank* pTankB = NULL;


	//	あたり判定計算用ポインタ
	const D3DXMATRIXA16* pMatA = NULL;
	const D3DXMATRIXA16* pMatB = NULL;
	float fRadA = 0;
	float fRadB = 0;


	while(pRunA != pEnd)
	{
		//	判定オブジェクトAを設定
		pTankA = static_cast<CTank*>(pRunA->getInst());

		//	
		pRunB = pRunA->next();

		//	
		while(pRunB != pEnd)
		{
			pTankB = static_cast<CTank*>(pRunB->getInst());

			pMatA = pTankA->getMatBottom();
			pMatB = pTankB->getMatBottom();
			fRadA = pTankA->getRadius();
			fRadB = pTankB->getRadius();

			////////////////////////////
			//	二つのオブジェクトの距離を計算
			const float fX = (pMatB->_41 - pMatA->_41) * (pMatB->_41 - pMatA->_41);
			const float fZ = (pMatB->_43 - pMatA->_43) * (pMatB->_43 - pMatA->_43);
			const float fSumRad = (fRadA + fRadB) * (fRadA + fRadB);
			//球とプレイヤーのあたり判定
			if(	fX + fZ <=  fSumRad)
			{
				pTankA->hitTank(pTankB);
			}
			pRunB = pRunB->next();
		}
		pRunA = pRunA->next();
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTankList 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTAndT::setTankList(CListMng<CObjBase*>* pTankList)
{
	_pTankList = pTankList;
}