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


private:
	CTankIntDummy(const CTankIntDummy& src);
	void update();
	void root();
	void shot();

private:
	static const int SHOT_PROB = ( 1024  );
	static const int POINT_ERROR_NUM = ( 20 );

	int _point;		///< 現在目的としてるナビポイント
	int _pointError;	// ナビポイント誤差


};


#endif