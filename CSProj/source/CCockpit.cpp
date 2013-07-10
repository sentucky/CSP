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

#include"CSystemparam.h"
#include"CInputCommon.h"


CCockpit::CCockpit()
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Tank		(NULL					)
{
	for(int n = 0; n < S_SUM; n++)
	{
		*(_sprite + n) = NULL;
		D3DXMatrixIdentity(_spriteMat + n);
	}

	for(int n = 0; n < N_SUM; n++)
	{
		*(_Num + n) = NULL;
	}
}

CCockpit::~CCockpit()
{
	disableTask();

	for(int n = 0; n < N_SUM; n++)
	{
		SAFE_DELETE(_Num[n]);
	}
	for(int n = 0; n < S_SUM; n++)
	{
		SAFE_DELETE(_sprite[n]);
	}
}

CCockpit::CCockpit(const CCockpit& src)
	:CObjBase	(OBJGROUPKEY::COCKPIT()	),
	_TaskDraw	(NULL					),
	_TaskUpdate	(NULL					),
	_Tank		(NULL					)
{
	const D3DXIMAGE_INFO *info;

	for(int n = 0; n < S_SUM; n++)
	{
		*(_sprite + n) = NULL;
		D3DXMatrixIdentity(_spriteMat + n);
	}

	CSpriteFactory* SpriteFactory = SPRITEFACTORY;

	//	ラップ
	//......ラップ情報
	_sprite[S_LAP] = SpriteFactory->create(TEXKEY::LAP());
	_sprite[S_LAP]->setCenter(0,0,0);
	_spriteMat[S_LAP]._41 = 400.0f;
	_spriteMat[S_LAP]._42 = 0.0f;
	_spriteMat[S_LAP]._43 = 0;
	//....../
	_sprite[S_LAPDIV] = SpriteFactory->create(TEXKEY::LAPDIV());
	_sprite[S_LAPDIV]->setCenter(0,0,0);
	_spriteMat[S_LAPDIV]._41 = _spriteMat[S_LAP]._41 + 160.0f;
	_spriteMat[S_LAPDIV]._42 = _spriteMat[S_LAP]._42;
	_spriteMat[S_LAPDIV]._43 = 0;

	//	順位
	//......順位の数値
	_Num[N_RANK] = OBJFACTORY->create<CNum>(OBJKEY::NUM());
	_Num[N_RANK]->setDrawMode(POINT_RIGHT);
	_Num[N_RANK]->setPos(D3DXVECTOR3(720,500,0));
	//......順位の尾
	_sprite[S_TH] = SpriteFactory->create(TEXKEY::NUM_TH());
	_sprite[S_TH]->setCenter(0,0,0);
	_spriteMat[S_TH]._41 = 720;
	_spriteMat[S_TH]._42 = 500;
	
	//	サークル
	_sprite[S_CIRCLE] = SpriteFactory->create(TEXKEY::CIRCLE());
	info = _sprite[S_CIRCLE]->getTextureInfo();
	_spriteMat[S_CIRCLE]._41 = 100.0f;
	_spriteMat[S_CIRCLE]._42 = 510.0f;
	_spriteMat[S_CIRCLE]._43 = 0.1f;

	//	ステータス
	_sprite[S_STATUS] = SpriteFactory->create(TEXKEY::TANK());
	info = _sprite[S_STATUS]->getTextureInfo();
	_sprite[S_STATUS]->createAnimeParam(ANIMEPATH::TANK());
	_sprite[S_STATUS]->setCatAnime(0);
	_sprite[S_STATUS]->calcCenter();
	_sprite[S_STATUS]->updateAnime();
	_spriteMat[S_STATUS]._41 = 100.0f;
	_spriteMat[S_STATUS]._42 = 510.0f;
	_spriteMat[S_STATUS]._43 = 0.01f;

	//	ミニマップ
	_sprite[S_MINIMAP] = SpriteFactory->create(TEXKEY::MINIMAP());
	_spriteMat[S_MINIMAP]._41 = 800.0f - 70.0f;
	_spriteMat[S_MINIMAP]._42 = 70.0f;

	//	点
	_sprite[S_DOT]	   = SpriteFactory->create(TEXKEY::MINIDOT());


	for(int n = 0; n < N_SUM; n++)
	{
		*(_Num + n) = static_cast<CNum*>(OBJFACTORY->create(OBJKEY::NUM()));
		_NumPos[n] = D3DXVECTOR3(0,0,0);
	}

	_NumPos[N_RANK] = D3DXVECTOR3(_spriteMat[S_TH]._41 - 64.0f,_spriteMat[S_TH]._42,0);

	_Num[N_LAP]->setDrawMode(POINT_LEFT);
	_NumPos[N_LAP] = D3DXVECTOR3(_spriteMat[S_LAP]._41+128.0f,_spriteMat[S_LAP]._42,0);

	_Num[N_LAPMAX]->setDrawMode(POINT_LEFT);
	_NumPos[N_LAPMAX] = D3DXVECTOR3(_spriteMat[S_LAPDIV]._41+32.0f,_spriteMat[S_LAPDIV]._42,0);


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
//	_Num[N_RANK]->draw();

	for(int n = 0; n < S_SUM; ++n)
	{
		if(*(_sprite + n) == NULL)
			continue;

		_sprite[n]->draw(0 ,&_spriteMat[n]);
	}

	for(int n = 0; n < N_SUM; ++n)
	{
		if(*(_Num + n) == NULL)
			continue;

		(*(_Num + n))->draw();
	}
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
//		_sprite[S_CIRCLE]->setColorRevision(D3DXCOLOR(1.0f - (rag / maxrag), 0.0f, 0.0f, 1.0f));
	}
	else
	{
		_sprite[S_CIRCLE]->setColorRevision(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	_Num[N_RANK]->setNum(_Tank->getRank()+1);
	if(life < 0)
	{
		life = 0;
	}
	_sprite[S_STATUS]->setCatAnime(5 - int(5 * (life / maxlife)));
	_sprite[S_STATUS]->calcCenter();
	_sprite[S_STATUS]->updateAnime();


	for(int n = 0; n < N_SUM; ++n)
	{
		if(_Num[n] == NULL)
			continue;

		_Num[n]->setPos(_NumPos[n]);
	}


	updateMiniMap();
	updateLap();
}


void CCockpit::updateMiniMap()
{
	//	プレイヤー座標 - 中心点 = ベクトル
	//	ミニマップ中心点 + ベクトル = ミニマップ座標
	static float a = 1.25f;
	static float b = 1.25f;
	
	const float vx = (_Tank->getMatBottom()->_41) * 0.25f * a;
	const float vy = -(_Tank->getMatBottom()->_43) * 0.25f * b;
	_spriteMat[S_DOT]._41 = vx + _spriteMat[S_MINIMAP]._41;
	_spriteMat[S_DOT]._42 = vy + _spriteMat[S_MINIMAP]._42;

	
	if(_Tank->getDestroyed() == TRUE)
	{
		CTaskMng::erase(&_TaskUpdate);
	}
}

void CCockpit::updateLap()
{
	int PlayerTankLap = _Tank->getlap();

	PlayerTankLap = PlayerTankLap <= 0 ? 0 : PlayerTankLap;
	PlayerTankLap = PlayerTankLap + 1 >  CSystemparam::getMaxLap() - 1 ?  CSystemparam::getMaxLap() :  PlayerTankLap;
	
	_Num[N_LAP]->setNum(PlayerTankLap + 1);
	_Num[N_LAPMAX]->setNum(CSystemparam::getMaxLap());
}