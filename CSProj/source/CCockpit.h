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
	CCockpit();
	~CCockpit();
	CCockpit::CCockpit(const CCockpit& src);

	void enableTask();
	void disableTask();

	void draw();
	void update();
	void setTank(CTank* Tank){ _Tank = Tank;}

private:
	CTaskList*	_TaskDraw;
	CTaskList*	_TaskUpdate;
	CTank*		_Tank;
	CNum*		_Num;
	CSprite*	_SpriteTh;
	CSprite*	_SpriteCircle;
	CSprite*	_SpriteStatus;

	D3DXMATRIXA16 _spriteThMatrix;
	D3DXMATRIXA16 _spriteCircleMatrix;
	D3DXMATRIXA16 _spriteStatusMatrix;
};

#endif