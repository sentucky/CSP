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
#include"CAnimeParam.h"
#include"AnimeKey.h"

CCockpit::CCockpit()
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					),
	_SpriteTh	(NULL					),
	_SpriteCircle	(NULL					),
	_SpriteStatus	(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteCircleMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteStatusMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
}

CCockpit::~CCockpit()
{
	disableTask();
	SAFE_DELETE(_Num);
	SAFE_DELETE(_SpriteTh);
	SAFE_DELETE(_SpriteCircle);
	SAFE_DELETE(_SpriteStatus);
}

CCockpit::CCockpit(const CCockpit& src)
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					),
	_SpriteTh	(NULL					),
	_SpriteCircle	(NULL					),
	_SpriteStatus	(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteCircleMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteStatusMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
	const D3DXIMAGE_INFO *info;
	D3DXMatrixIdentity(&_spriteThMatrix);
	D3DXMatrixIdentity(&_spriteCircleMatrix);
	D3DXMatrixIdentity(&_spriteStatusMatrix);

	_Num = OBJFACTORY->create<CNum>(OBJKEY::NUM());
	_Num->setDrawMode(POINT_RIGHT);
	_Num->setPos(D3DXVECTOR3(720,400,0));
	_SpriteTh = SPRITEFACTORY->create(TEXKEY::NUM_TH());
	_SpriteTh->setCenter(0,0,0);
	
	_SpriteCircle = SPRITEFACTORY->create(TEXKEY::CIRCLE());
	info = _SpriteCircle->getTextureInfo();
//	_SpriteCircle->setCenter(info->Width / 2, info->Height / 2, 0);

	_SpriteStatus = SPRITEFACTORY->create(TEXKEY::TANK());
	info = _SpriteStatus->getTextureInfo();
//	_SpriteStatus->setCenter(info->Width / 2, info->Height / 2, 0);
	_SpriteStatus->createAnimeParam(ANIMEPATH::TANK());
	_SpriteStatus->setCatAnime(0);
	_SpriteStatus->updateAnime();

	_spriteThMatrix._41 = 720;
	_spriteThMatrix._42 = 400;
	_spriteCircleMatrix._41 = 100;
	_spriteCircleMatrix._42 = 510;
	_spriteCircleMatrix._43 = 0.001;
	_spriteStatusMatrix._41 = 355;
	_spriteStatusMatrix._42 = 510;

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
	_SpriteCircle->draw(0,&_spriteCircleMatrix);
	_SpriteStatus->draw(0,&_spriteStatusMatrix);

}

void CCockpit::update()
{
	float life;
	float maxlife;

	life = _Tank->getlife();
	maxlife = _Tank->getmaxlife();

	//_SpriteCircle->setColorRevision(D3DXCOLOR();

	_Num->setNum(_Tank->getRank()+1);
	_SpriteStatus->setCatAnime(5 - int(5 * (life / maxlife)));
	_SpriteStatus->updateAnime();
	
}
