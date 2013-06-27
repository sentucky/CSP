#include"CStartCamWork.h"

#include"CTaskList.h"
#include"CTaskMng.h"
#include"StageData.h"
#include"CCamera.h"


#include"ObjKey.h"

CStartCamWork::CStartCamWork(
	const CStageData* StageData
	)
	:CObjBase(OBJGROUPKEY::CAMERA()),
	_StageData(StageData),
	_TaskCamMove(NULL),
	_CurPhase(0),
	_t(0),
	_Count(0)
{
}

CStartCamWork::~CStartCamWork()
{
	disableTask();
}

CStartCamWork::CStartCamWork(const CStartCamWork& src)
	:CObjBase			(src._GroupID						),
	_StageData(src._StageData),
	_TaskCamMove(NULL),
	_CurPhase(0),
	_t(0),
	_Count(0)
{
	//******************************************************
	//	以下
	//	_SumPhase	ヘッダで定義	パターン数
	//	_CamWorkParam[i].Count	再生時間
	//	_CamWorkParam[i].Pos	頂点数
	//	_CamWorkParam[i].At		注視点
	//	※最後の枠にはあとから、追尾カメラが入るので、値が反映されない
	//
	//	ここで移動量を決定

	//	ここで移動時間を決定
	for(int i = 0; i < _SumPhase; ++i)
	{
		_CamWorkParam[i].Count = 60;
	}
	//													以上
	//******************************************************


	enableTask();
}

void CStartCamWork::enableTask()
{
	CTaskMng::push<CStartCamWork>(
		TASKKEY::STARTCAMMOVE(),
		this,
		&CStartCamWork::camMove,
		&_TaskCamMove);
}

void CStartCamWork::disableTask()
{
	CTaskMng::erase(&_TaskCamMove);
}

void CStartCamWork::camMove()
{
	if(_CurPhase >= _SumPhase - 1)
	{
		//	再生終了
		_DeleteFlg = TRUE;
		return;
	}

	//	rename
	Param& CurParam = _CamWorkParam[_CurPhase];
	Param& NextParam = _CamWorkParam[_CurPhase + 1];

	//	変位値取得
	const float T = static_cast<float>(_Count) / static_cast<float>(CurParam.Count);

	//	座標計算
	const OUTPUT* startTile = _StageData->getStartTile();
	const float Eyex = CurParam.Pos.x + (NextParam.Pos.x - CurParam.Pos.x) * T;
	const float Eyey = CurParam.Pos.y + (NextParam.Pos.y - CurParam.Pos.y) * T;
	const float Eyez = CurParam.Pos.z + (NextParam.Pos.z - CurParam.Pos.z) * T;
	const float Atx = CurParam.At.x + (NextParam.At.x - CurParam.At.x) * T;
	const float Aty = CurParam.At.y + (NextParam.At.y - CurParam.At.y) * T;
	const float Atz = CurParam.At.z + (NextParam.At.z - CurParam.At.z) * T;

	CCamera::setAt(D3DXVECTOR3(startTile->posX,0,startTile->posY));
	CCamera::setEye(D3DXVECTOR3(Eyex,Eyey,Eyez));
	CCamera::setAt(D3DXVECTOR3(Atx,Aty,Atz));
	++_Count;
	CCamera::update();
	if(_Count > CurParam.Count)
	{
		_Count = 0;
		++_CurPhase;
	}
}

void CStartCamWork::reset()
{
	D3DXMATRIXA16 RotMat;
	D3DXMatrixIdentity(&RotMat);

	const OUTPUT* startTile = _StageData->getStartTile();

	const float Rot = startTile->rot;

	D3DXMatrixRotationY(&RotMat,Rot * D3DX_PI);

	for(int i = 0; i < _SumPhase; ++i)
	{
		D3DXVec3TransformCoord(&_CamWorkParam[i].Pos,&_CamWorkParam[i].Pos,&RotMat);
	}

}

void CStartCamWork::count(const int n, const uint count)
{
	if(n >= _SumPhase)
		return;
	_CamWorkParam[n].Count = count;
}

void CStartCamWork::point(const int n,const float x,const float y,const float z)
{
	if(n >= _SumPhase)
		return;

	_CamWorkParam[n].Pos.x = x;
	_CamWorkParam[n].Pos.y = y;
	_CamWorkParam[n].Pos.z = z;
}



void CStartCamWork::lastPoint(const float x,const float y,const float z)
{
	_CamWorkParam[_SumPhase - 1].Pos.x = x;
	_CamWorkParam[_SumPhase - 1].Pos.y = y;
	_CamWorkParam[_SumPhase - 1].Pos.z = z;
}


void CStartCamWork::At(const int n,const float x,const float y,const float z)
{
	if(n >= _SumPhase)
		return;
	_CamWorkParam[n].At.x = x;
	_CamWorkParam[n].At.y = y;
	_CamWorkParam[n].At.z = z;
}

void CStartCamWork::lastAt(const float x,const float y,const float z)
{
	_CamWorkParam[_SumPhase - 1].At.x = x;
	_CamWorkParam[_SumPhase - 1].At.y = y;
	_CamWorkParam[_SumPhase - 1].At.z = z;
}
