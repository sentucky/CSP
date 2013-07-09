#ifndef ___CCOCKPIT___
#define ___CCOCKPIT___

#include"common.h"
#include"CObjBase.h"

class CTaskList;
class CNum;
class CTank;
class CSprite;

class CCockpit:public CObjBase
{
public:
	enum eCOCKPIT_SPRITE
	{
		S_LAP,
		S_LAPDIV,
		S_TH,
		S_CIRCLE,
		S_STATUS,
		S_MINIMAP,
		S_DOT,
		S_SUM,
	};

	enum eCOCKPIT_NUM
	{
		N_RANK,
		N_LAP,
		N_LAPMAX,
		N_SUM,
	};

	CCockpit();
	~CCockpit();
	CCockpit::CCockpit(const CCockpit& src);

	void enableTask();
	void disableTask();

	void draw();
	void update();
	void setTank(CTank* Tank){ _Tank = Tank;}

	void updateMiniMap();
	void updateLap();
private:
	CTaskList*	_TaskDraw;
	CTaskList*	_TaskUpdate;
	CTank*		_Tank;
	CNum*		_Num[N_SUM];
	D3DXVECTOR3 _NumPos[N_SUM];
	CSprite*	  _sprite[S_SUM];
	D3DXMATRIXA16 _spriteMat[S_SUM];

};

#endif