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
#include"CCamera.h"

CCockpit::CCockpit()
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Num		(NULL					),
	_Tank		(NULL					),
	_SpriteTh	(NULL					),
	_SpriteCircle	(NULL					),
	_SpriteStatus	(NULL					),
	_spriteMiniMap	(NULL					),
	_spriteDot		(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteCircleMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteStatusMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteMiniMapMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteDotMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
}

CCockpit::~CCockpit()
{
	disableTask();
	SAFE_DELETE(_Num);
	SAFE_DELETE(_SpriteTh);
	SAFE_DELETE(_SpriteCircle);
	SAFE_DELETE(_SpriteStatus);
	SAFE_DELETE(_spriteMiniMap);
	SAFE_DELETE(_spriteDot);
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
	_spriteMiniMap	(NULL					),
	_spriteDot		(NULL					),
	_spriteThMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteCircleMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteStatusMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteMiniMapMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	_spriteDotMatrix(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
	const D3DXIMAGE_INFO *info;
	D3DXMatrixIdentity(&_spriteThMatrix);
	D3DXMatrixIdentity(&_spriteCircleMatrix);
	D3DXMatrixIdentity(&_spriteStatusMatrix);
	D3DXMatrixIdentity(&_spriteMiniMapMatrix);
	D3DXMatrixIdentity(&_spriteDotMatrix);

	_Num = OBJFACTORY->create<CNum>(OBJKEY::NUM());
	_Num->setDrawMode(POINT_RIGHT);
	_Num->setPos(D3DXVECTOR3(720,400,0));
	_SpriteTh = SPRITEFACTORY->create(TEXKEY::NUM_TH());
	_SpriteTh->setCenter(0,0,0);
	
	_SpriteCircle = SPRITEFACTORY->create(TEXKEY::CIRCLE());
	info = _SpriteCircle->getTextureInfo();

	_SpriteStatus = SPRITEFACTORY->create(TEXKEY::TANK());
	info = _SpriteStatus->getTextureInfo();
	_SpriteStatus->createAnimeParam(ANIMEPATH::TANK());
	_SpriteStatus->setCatAnime(0);
	_SpriteStatus->updateAnime();

	_spriteMiniMap = SPRITEFACTORY->create(TEXKEY::MINIMAP());
	_spriteDot	   = SPRITEFACTORY->create(TEXKEY::MINIDOT());

	_spriteThMatrix._41 = 720;
	_spriteThMatrix._42 = 400;
	_spriteCircleMatrix._41 = 100.0f;
	_spriteCircleMatrix._42 = 510.0f;
	_spriteCircleMatrix._43 = 0.001f;
	_spriteStatusMatrix._41 = 355.0f;
	_spriteStatusMatrix._42 = 510.0f;
	_spriteMiniMapMatrix._41 = 126.0f;
	_spriteMiniMapMatrix._42 = 126.0f;

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
	_spriteMiniMap->draw(0,&_spriteMiniMapMatrix);
	_spriteDot->draw(0,&_spriteDotMatrix);
}

void CCockpit::update()
{
	float life;
	float maxlife;
	float rag;
	float maxrag;

	life = static_cast<float>(_Tank->getlife());
	maxlife = static_cast<float>(_Tank->getmaxlife());
	rag = static_cast<float>(_Tank->getradiate());
	maxrag = static_cast<float>(_Tank->getMaxradiateTime());
	
	if(rag > 0.0f)
	{
//		_SpriteCircle->setColorRevision(D3DXCOLOR(1.0f - (rag / maxrag), 0.0f, 0.0f, 1.0f));
	}
	else
	{
		_SpriteCircle->setColorRevision(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	_Num->setNum(_Tank->getRank()+1);
	if(life < 0)
	{
		life = 0;
	}
	_SpriteStatus->setCatAnime(5 - int(5 * (life / maxlife)));
	_SpriteStatus->updateAnime();



	updateMiniMap();
}

#include"CInputCommon.h"

void CCockpit::updateMiniMap()
{
	//	プレイヤー座標 - 中心点 = ベクトル
	//	ミニマップ中心点 + ベクトル = ミニマップ座標

	static float a = 1.25f;
	static float b = 1.25f;
	

	const float vx = (_Tank->getMatBottom()->_41) * 0.5f * a;
	const float vy = -(_Tank->getMatBottom()->_43) * 0.5f * b;
	_spriteDotMatrix._41 = vx + _spriteMiniMapMatrix._41;
	_spriteDotMatrix._42 = vy + _spriteMiniMapMatrix._42;

	if(_Tank->getDestroyed() == TRUE)
	{
		CTaskMng::erase(&_TaskUpdate);
	}

}
