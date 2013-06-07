#include"CHitTestTankToWall.h"

#include"CTank.h"

#include"CTaskList.h"
#include"CTaskMng.h"
#include"CObjMng.h"
#include"CObjBase.h"
#include"CListMng.h"
#include"CListItem.h"

CListMng<CObjBase*>* CHitTestTankToWall::_pTankList = NULL;

CHitTestTankToWall::CHitTestTankToWall()
	:_pHitTestTask(NULL)
{
}

CHitTestTankToWall::~CHitTestTankToWall()
{
	disableTask();
}

CHitTestTankToWall::CHitTestTankToWall(const CHitTestTankToWall& src)
	:_pHitTestTask(NULL)
{
	enableTask();
}

void CHitTestTankToWall::enableTask()
{
	CTaskMng::push<CHitTestTankToWall>(
		TASKKEY::HITTEST_TANKTOWALL(),
		this,
		&CHitTestTankToWall::hitTest,
		&_pHitTestTask);
}

void CHitTestTankToWall::disableTask()
{
	CTaskMng::erase(&_pHitTestTask);
}

void CHitTestTankToWall::hitTest()
{
	CListItem<CObjBase*>* run = _pTankList->begin();	
	const CListItem<CObjBase*>* end = _pTankList->end();
	CTank* pTank = NULL;

	while(run != end)
	{
		pTank = static_cast<CTank*>(run->getInst());

		pTank->hitTestWall();

		run = run->next();
	}
}
