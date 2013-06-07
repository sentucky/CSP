/***********************************************************************/
/*! @file  CTankIntDummy.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CTankIntDummy.h"

#include"CTank.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(CTank* pTank)
	:CTankIntInter(pTank)
{
	_pMyTank = pTank;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::~CTankIntDummy()
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(const CTankIntDummy& src)
	:CTankIntInter(src._pMyTank)
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::update()
{
	/*
	switch(getRand(2))
	{
	case 0:
		_MoveDir = 1;
		break;
	case 1:
		_MoveDir = 8;
		break;
	}*/
}