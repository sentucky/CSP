#include"CCockpit.h"


#include"CFactory.h"

#include"CTaskMng.h"
#include"CTaskList.h"

#include"CNum.h"
#include"CTank.h"

#include"ObjKey.h"

#include"CSprite.h"
#include"CSpriteFactory.h"
#include"TextureKey.h"

CCockpit::CCockpit()
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					),
	_SpriteTh	(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
}

CCockpit::~CCockpit()
{
	disableTask();
	SAFE_DELETE(_Num);
	SAFE_DELETE(_SpriteTh);
}

CCockpit::CCockpit(const CCockpit& src)
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					),
	_SpriteTh	(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
	D3DXMatrixIdentity(&_spriteThMatrix);

	_Num = OBJFACTORY->create<CNum>(OBJKEY::NUM());
	_Num->setDrawMode(POINT_RIGHT);
	_Num->setPos(D3DXVECTOR3(720,400,0));
	_SpriteTh = SPRITEFACTORY->create(TEXKEY::NUM_TH());
	_SpriteTh->setCenter(0,0,0);
	_spriteThMatrix._41 = 720;
	_spriteThMatrix._42 = 400;
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
	_SpriteTh->draw(0,&_spriteThMatrix);
}

void CCockpit::update()
{
	_Num->setNum(_Tank->getRank()+1);
}
