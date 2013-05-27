#include"CTankBottom.h"

#include"CMesh.h"
#include"CTankIntInter.h"


CTankBottom::CTankBottom(
	CMesh* pMesh,
	const float fSpeedMove,
	const float fSpeedTurn
	)
	:_pMesh(pMesh),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,1.0f),
	_fSpeedMove(fSpeedMove),
	_fSpeedTurn(fSpeedTurn)
{
	D3DXMatrixIdentity(&_WMat);
}


CTankBottom::~CTankBottom()
{
	SAFE_DELETE(_pMesh);
}

CTankBottom::CTankBottom(const CTankBottom& src)
	:_pMesh(new CMesh(*src._pMesh)),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,1.0f),
	_fSpeedMove(src._fSpeedMove),
	_fSpeedTurn(src._fSpeedTurn)
{
	D3DXMatrixIdentity(&_WMat);
}

void CTankBottom::draw()
{
	_pMesh->draw(&_WMat);
}

void CTankBottom::move()
{

	//	姿勢からベクトルを計算
	if(_pIntelligence->getMoveFlg() != TMV_5)
	{
		_MoveVec = _Dir;
	}
	else
	{
		_MoveVec.x = _MoveVec.y = _MoveVec.z = 0;
	}
	_MoveVec *= _fSpeedMove;

	_WMat._41 += _MoveVec.x;
	_WMat._42 += _MoveVec.y;
	_WMat._43 += _MoveVec.z;
}

void CTankBottom::rotateMatrix(float fTurnSpeed)
{
	const float x = _Dir.x * cosf(fTurnSpeed) + (-_Dir.z * sin(fTurnSpeed));
	const float z = _Dir.z * cosf(fTurnSpeed) + _Dir.x * sin(fTurnSpeed);
	_Dir.x = x;
	_Dir.z = z;
}

void CTankBottom::turn()
{
	uint unMoveDir = _pIntelligence->getMoveFlg();
	_MoveVec.y = 0;
	switch(unMoveDir % 3)
	{
	case 1:_MoveVec.x = -1.0f;	break;
	case 2:_MoveVec.x = 0.0f;	break;
	case 0:_MoveVec.x = 1.0f;	break;
	}
	switch((unMoveDir -1 ) / 3)
	{
	case 0:_MoveVec.z = -1.0f;	break;
	case 1:_MoveVec.z = 0.0f;	break;
	case 2:_MoveVec.z = 1.0f;	break;
	}
		//	移動方向の左右確認
	static D3DXVECTOR2 v1,v2;

	v1.x = _Dir.x;
	v1.y = _Dir.z;
	v2.x = _MoveVec.x;
	v2.y = _MoveVec.z;

	float fCross = D3DXVec2CCW(&v1,&v2);	//	外積
	float fDot;

	//	左右判定
	if(fCross > 0)
	{
		rotateMatrix(_fSpeedTurn);
	}
	else if(fCross < 0)
	{
		rotateMatrix(-_fSpeedTurn);
	}
	else
	{
		fDot = D3DXVec3Dot(&_Dir,&_MoveVec);
		
		if(fDot < 0)
		{
			rotateMatrix(_fSpeedTurn);
		}
	}

	float x,y,z;

	x = _WMat._41;
	y = _WMat._42;
	z = _WMat._43;

	static const D3DXVECTOR3 XV(0.0f,0.0f,1.0f);
	
	D3DXVec3Normalize(&_Dir,&_Dir);

	_WMat._41 = _WMat._42 = _WMat._43 = 0;

	D3DXMatrixRotationY(&_WMat,-atan2f(_Dir.z,_Dir.x) + 0.5F*3.1415f);

	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;
}

const D3DXMATRIXA16* CTankBottom::getWMat()
{
	return &_WMat;
}

void CTankBottom::setIntelligence(CTankIntInter* pIntelligence)
{
	_pIntelligence = pIntelligence;
}