#ifndef ___CRANK___
#define ___CRANK___

#include"CObjBase.h"

template<class T>
class CListMng;
template<class T>
class CListItem;
class CTank;
class CTaskList;
class CFollowCamera;
class CSprite;

class CStartCamWork;

class CSystemparam:public CObjBase
{
public:
	CSystemparam();
	~CSystemparam();
	CSystemparam(const CSystemparam& src);
private:
	void enableTask();
	void disableTask();

	void drawResult();
	void drawStart();
	void drawReady();

	void endCount();
	void endcheck();
	void startcheck();
public:
	void Ranking();
private:
	

	BOOL endcheckGoal(CTank** GoalTank,CListItem<CObjBase*>* begin,const CListItem<CObjBase*>* end);
	BOOL endcheckDestroy(CTank** DestroyerTank,CListItem<CObjBase*>* begin,const uint sumTanks);
public:
	void setFollowCamera(CFollowCamera* FollowCamera)	{	_FollowCamera		= FollowCamera;	}
	void setPlayerTank(CTank* tank)			{	_playerTank	= tank;		}

	void setCamStart(CStartCamWork* camstart)		{_CamStart		= camstart;		}

	void Rankcpy(CTank** cpy[1024]){
		for(int n = 0; n < 1024; n++)
		{
			cpy[n] = &_Ranking[n];
		}
	}

	void switchGame();

	const uint getFlgResult(){return _flgRaceResult;}
	const BOOL getFlgEnd(){return _flgEnd;}
	const int getgotoscene(){return _gotoscene;}
	static const int getMaxLap(){return _MaxLap;}
private:
	CTaskList* _TaskList;
	CTaskList* _TaskEndCount;
	CTaskList* _TaskEndCheck;
	CTaskList* _TaskStartCheck;
	CTaskList* _TaskDrawResult;
	CTaskList* _TaskDrawStart;

	uint _flgRaceResult;	//	0:レース中	1:プレイヤー勝利 2:プレイヤー負け
	BOOL _flgEnd;
	int  _gotoscene;

	CSprite* _Sprite;
	CSprite* _retrySpriteA;
	CSprite* _retrySpriteB;
	CSprite* _titleSpriteA;
	CSprite* _titleSpriteB;

	int _startCount;
	static const int MaxStartCount = 60;
	static const int _MaxLap = 3;

	int _goalCount;
	static int _MaxGoalCount;

	CTank* _playerTank;
	CTank* _Ranking[1024];
	CListMng<CObjBase*>* TankList;

	CStartCamWork*	_CamStart;
	CFollowCamera*  _FollowCamera;
	D3DXMATRIXA16	_spriteMatrix;
};

#endif