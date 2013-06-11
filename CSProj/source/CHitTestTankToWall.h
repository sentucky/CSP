#ifndef ___CHITTESTTANKANDWALL___
#define ___CHITTESTTANKANDWALL___

class CStageData;
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
	static void setStageData(const CStageData* pStageData){_StageData = pStageData;}
private:

	CTaskList* _pHitTestTask;
	static CListMng<CObjBase*>* _pTankList;
	static const CStageData*	_StageData;
};

#endif