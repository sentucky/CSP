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

#include "CFont.h"
#include"CTankIntInter.h"

class CTankIntDummy:public CTankIntInter
{
public:
	CTankIntDummy(CTank* pTank);
	~CTankIntDummy();

	static void Debug();
private:
	CTankIntDummy(const CTankIntDummy& src);
	void update();
	void root();

private:
	int _point;		///< ���ݖړI�Ƃ��Ă�i�r�|�C���g


};


#endif