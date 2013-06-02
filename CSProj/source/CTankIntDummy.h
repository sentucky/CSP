/***********************************************************************/
/*! @file  CTankIntDummy.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANKINTENEMY___
#define ___CTANKINTENEMY___

#include"CTankIntInter.h"

class CTankIntDummy:public CTankIntInter
{
public:
	CTankIntDummy(CTank* pTank);
	~CTankIntDummy();

private:
	CTankIntDummy(const CTankIntDummy& src);
	void update();

private:
};

#endif