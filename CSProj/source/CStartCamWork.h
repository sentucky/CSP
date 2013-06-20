#ifndef ___CSTARTCAMWORK___
#define ___CSTARTCAMWORK___

#include"common.h"
#include"CObjBase.h"

class CCamera;

class CTaskList;
class CStageData;

struct Param
{
	uint		Count;
	D3DXVECTOR3 At;
	D3DXVECTOR3 Pos;
};


class CStartCamWork:public CObjBase
{
public:
	CStartCamWork(
		const CStageData* stagedata
		);
	~CStartCamWork();
	CStartCamWork(const CStartCamWork&);

	void enableTask();
	void disableTask();

	void camMove();

	void reset();
	void lastPoint(const float x,const float y,const float z);

private:
	const CStageData* _StageData;
	CTaskList*	_TaskCamMove;
	uint		_CurPhase;	//	現在フェーズ
	static const uint _SumPhase = 5;	//	総フェーズ数

	float _t;	//	変位
	uint _Count;

	Param _CamWorkParam[_SumPhase];
};

#endif