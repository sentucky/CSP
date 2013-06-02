/***********************************************************************/
/*! @file  CHItTestTAndT.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CHITTEST___
#define ___CHITTEST___

#include"CObjBase.h"

class CTaskList;

template<class T>
class CListMng;

class CHitTestTAndT:public CObjBase
{
public:
	CHitTestTAndT();
	~CHitTestTAndT();
	CHitTestTAndT(const CHitTestTAndT& src);

public:
	void enableTask();
	void disableTask();
	void hitTest();

	static void setTankList(CListMng<CObjBase*>* pTankList);

private:
	CTaskList* _HitTestTask;

	static CListMng<CObjBase*>* _pTankList;
};

#endif