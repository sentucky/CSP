#ifndef ___CHITTESTTANKANDWALL___
#define ___CHITTESTTANKANDWALL___

class CTaskList;
template<class T>
class CListMng;

#include"CObjBase.h"

class CHitTestTankToWall:public CObjBase
{
public:
	CHitTestTankToWall();
	~CHitTestTankToWall();
	CHitTestTankToWall(const CHitTestTankToWall& src);
	void enableTask();
	void disableTask();
	void hitTest();

	static void setTankList(CListMng<CObjBase*>* pTankList){_pTankList = pTankList;}
private:
	CTaskList* _pHitTestTask;
	static CListMng<CObjBase*>* _pTankList;
};

#endif