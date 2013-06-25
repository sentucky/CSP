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

	void endcheck();
	void run();


	BOOL endcheckGoal(CTank** GoalTank,CListItem<CObjBase*>* begin,const CListItem<CObjBase*>* end);
	BOOL endcheckDestroy(CTank** DestroyerTank,CListItem<CObjBase*>* begin,const uint sumTanks);
public:
	void setCamera(CFollowCamera* camera){_Camera = camera;}
	void setPlayerTank(CTank* tank){_playerTank = tank;}
	const uint getFlgResult(){return _flgRaceResult;}
	const uint getFlgGameEnd(){return _flgGameEnd;}
private:
	CTaskList* _TaskList;
	CTaskList* _TaskEndCheck;
	CTaskList* _TaskDrawResult;

	uint _flgRaceResult;	//	0:レース中	1:プレイヤー勝利 2:プレイヤー負け
	BOOL _flgGameEnd;

	CFollowCamera* _Camera;

	CSprite* _Sprite;

	CTank* _playerTank;

	CListMng<CObjBase*>* TankList;
};

#endif