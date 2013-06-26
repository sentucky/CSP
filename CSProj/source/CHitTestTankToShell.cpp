/***********************************************************************/
/*! @file  CHitTestTankToShell.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CHitTestTankToShell.h"

#include"CListMng.h"
#include"CListItem.h"
#include"CTaskList.h"
#include"CTaskMng.h"
#include"CShell.h"
#include"CTank.h"
#include"ObjKey.h"

CListMng<CObjBase*>* CHitTestTankToShell::_pTankList	= NULL;
CListMng<CObjBase*>* CHitTestTankToShell::_pShellList	= NULL;

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CHitTestTankToShell::CHitTestTankToShell()
	:CObjBase(OBJGROUPKEY::HITTEST()),
	_HitTestTToS(NULL)
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CHitTestTankToShell::~CHitTestTankToShell()
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
CHitTestTankToShell::CHitTestTankToShell(const CHitTestTankToShell& src)
	:CObjBase			(src._GroupID						),
_HitTestTToS(NULL)
{
	enableTask();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTankToShell::enableTask()
{
	CTaskMng::push<CHitTestTankToShell>(
		TASKKEY::HITTEST_TANKTOSHELL(),
		this,
		&CHitTestTankToShell::hitTest,
		&_HitTestTToS
		);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTankToShell::disableTask()
{
	CTaskMng::erase(&_HitTestTToS);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTankToShell::hitTest()
{
	CListItem<CObjBase*>* pRunTank = _pTankList->begin();
	const CListItem<CObjBase*>* pEndTank = _pTankList->end();
	CListItem<CObjBase*>* pRunShell = NULL;
	const CListItem<CObjBase*>* pEndShell = _pShellList->end();


	
	float shellRad;


	CShell* pShell;
	CTank* pTank;

	while(pRunTank != pEndTank)
	{
		pTank = static_cast<CTank*>(pRunTank->getInst());
		if(pTank->getDestroyed() == TRUE)
		{
			pRunTank = pRunTank->next();
			continue;
		}
		pRunShell = (_pShellList->begin());

		while(pRunShell != pEndShell)
		{
			pShell = static_cast<CShell*>(pRunShell->getInst());
			const CTank* pShellOwner = pShell->getOwner();
			if(pShell->getOwner() != pTank)
			{
				shellRad = pShell->getRad();
				const D3DXMATRIXA16* shellmatW = pShell->getMatW();
				const D3DXMATRIXA16* Bottom = pTank->getMatBottom();
				if(bindCircle(
					&D3DXVECTOR2(shellmatW->_41,shellmatW->_43),shellRad,
					&D3DXVECTOR2(Bottom->_41,Bottom->_43),pTank->getRadius())
					)
				{
					pTank->hitTestShell(pShell);
					pShell->hitTestTank(pTank);
				}
			}
			pRunShell = pRunShell->next();
		}
		pRunTank = pRunTank->next();
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTankList 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTankToShell::setTankList(CListMng<CObjBase*>* pTankList)
{
	_pTankList = pTankList;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pShellList 
 *  @retval void
 */
/***********************************************************************/
void CHitTestTankToShell::setShellList(CListMng<CObjBase*>* pShellList)
{
	_pShellList = pShellList;
}











