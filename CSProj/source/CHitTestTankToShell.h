#ifndef ___CHITTESTANKTOSHELL___
#define ___CHITTESTANKTOSHELL___

#include"CObjBase.h"

class CTaskList;

template<class T>
class CListMng;

class CHitTestTankToShell:public CObjBase
{
public:
	CHitTestTankToShell();
	~CHitTestTankToShell();
	CHitTestTankToShell(const CHitTestTankToShell& src);


public:
	void enableTask();
	void disableTask();
	void hitTest();

	static void setTankList(CListMng<CObjBase*>* pTankList);
	static void setShellList(CListMng<CObjBase*>* pTankList);

private:
	CTaskList* _HitTestTToS;

	static CListMng<CObjBase*>* _pTankList;
	static CListMng<CObjBase*>* _pShellList;
};

#endif