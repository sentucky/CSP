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
	uint		_CurPhase;	//	���݃t�F�[�Y
	static const uint _SumPhase = 5;	//	���t�F�[�Y��

	float _t;	//	�ψ�
	uint _Count;

	Param _CamWorkParam[_SumPhase];
};

#endif