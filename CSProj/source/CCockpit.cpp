#include"CCockpit.h"


#include"CFactory.h"

#include"CTaskMng.h"
#include"CTaskList.h"

#include"CNum.h"
#include"CTank.h"

#include"ObjKey.h"

CCockpit::CCockpit()
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					)
{
}

CCockpit::~CCockpit()
{
	disableTask();
	SAFE_DELETE(_Num);
}

CCockpit::CCockpit(const CCockpit& src)
	:CObjBase	(OBJGROUPKEY::COCKPIT()),
	_TaskDraw	(NULL),
	_TaskUpdate	(NULL),
	_Num		(NULL),
	_Tank		(NULL)
{
	_Num = OBJFACTORY->create<CNum>(OBJKEY::NUM());
	_Num->setDrawMode(POINT_RIGHT);
	_Num->setPos(D3DXVECTOR3(780,400,0));
	enableTask();
}

void CCockpit::enableTask()
{
	CTaskMng::push<CCockpit>(
		TASKKEY::DRAW(),
		this,
		&CCockpit::draw,
		&_TaskDraw);
	CTaskMng::push<CCockpit>(
		TASKKEY::COCKPIT(),
		this,
		&CCockpit::update,
		&_TaskUpdate);
}

void CCockpit::disableTask()
{
	CTaskMng::erase(&_TaskDraw);
	CTaskMng::erase(&_TaskUpdate);
}


void CCockpit::draw()
{
	_Num->draw();
}

void CCockpit::update()
{
	_Num->setNum(_Tank->getRank());
}
