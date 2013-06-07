/***********************************************************************/
/*! @file  CTankBottom.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CTankBottom.h"

#include"CMesh.h"
#include"CTankIntInter.h"

const	float	CTankBottom::_fDeceleration = 0.900f;

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pMesh 
 *  @param[in,out] fSpeedMove 
 *  @param[in,out] fSpeedTurn 
 *  @retval  
 */
/***********************************************************************/
CTankBottom::CTankBottom(
	CMesh* pMesh,
	const float fSpeedMove,
	const float fSpeedTurn
	)
	:_pMesh(pMesh),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,0.0f),
	_MoveDir(0,0,0),
	_fSpeedMove(fSpeedMove),
	_fSpeedTurn(fSpeedTurn)
{
	D3DXMatrixIdentity(&_WMat);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTankBottom::~CTankBottom()
{
	SAFE_DELETE(_pMesh);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CTankBottom::CTankBottom(const CTankBottom& src)
	:_pMesh(new CMesh(*src._pMesh)),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,0.0f),
	_MoveDir(0,0,0),
	_fSpeedMove(src._fSpeedMove),
	_fSpeedTurn(src._fSpeedTurn)
{
	D3DXMatrixIdentity(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::draw()
{
	_pMesh->draw(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::move()
{

	//	Žp¨‚©‚çƒxƒNƒgƒ‹‚ðŒvŽZ
	_MoveVec *= _fDeceleration;
	_WMat._41 += _MoveVec.x;
	_WMat._42 += _MoveVec.y;
	_WMat._43 += _MoveVec.z;
}

void CTankBottom::clacMove()
{
	const D3DXVECTOR2* pMoveVec = _pIntelligence->getModeDir();
	if(abs(pMoveVec->x) + abs(pMoveVec->y) != 0)
	{
		D3DXVec3Normalize(&_Dir,&_Dir);
		_MoveVec += _Dir * _fSpeedMove;
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] fTurnSpeed 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::rotateMatrix(float fTurnSpeed)
{
	const float x = _Dir.x * cosf(fTurnSpeed) + (-_Dir.z * sin(fTurnSpeed));
	const float z = _Dir.z * cosf(fTurnSpeed) + _Dir.x * sin(fTurnSpeed);
	_Dir.x = x;
	_Dir.z = z;
	D3DXVec3Normalize(&_Dir,&_Dir);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::turn()
{
//	uint unMoveDir = _pIntelligence->getMoveDir();
	_MoveVec.y = 0;

//	if(unMoveDir == 5)
//		return;
	const D3DXVECTOR2* pMoveDir = _pIntelligence->getModeDir();

	if(abs(pMoveDir->x) + abs(pMoveDir->y) == 0)
	{
		return;
	}

	/*
	switch(unMoveDir % 3)
	{
	case 1:_MoveDir.x = -1.0f;	break;
	case 2:_MoveDir.x = 0.0f;	break;
	case 0:_MoveDir.x = 1.0f;	break;
	}
	switch((unMoveDir -1 ) / 3)
	{
	case 0:_MoveDir.z = -1.0f;	break;
	case 1:_MoveDir.z = 0.0f;	break;
	case 2:_MoveDir.z = 1.0f;	break;
	}
	*/

	//	ˆÚ“®•ûŒü‚Ì¶‰EŠm”F
	static D3DXVECTOR2 v1;


	D3DXVec3Normalize(&_MoveDir,&_MoveDir);
	v1.x = _Dir.x;
	v1.y = _Dir.z;
	_MoveDir.x = pMoveDir->x;
	_MoveDir.z = pMoveDir->y;

	float fCross = D3DXVec2CCW(&v1,pMoveDir);	//	ŠOÏ

	float fDot	 = D3DXVec3Dot(&_Dir,&_MoveDir);



	//	¶‰E”»’è
	//	•½s‚©‚Â‰sŠp
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
		if(fDot < 0)
			rotateMatrix(-_fSpeedTurn);
	}
	

	if(fDot > 0.999f)
	{
		_Dir = _MoveDir;
	}
	//	‰sŠp


	const float x = _WMat._41;
	const float y = _WMat._42;
	const float z = _WMat._43;


	_WMat._41 = _WMat._42 = _WMat._43 = 0;

	float rot = -atan2f(_Dir.z,_Dir.x);

	D3DXMatrixRotationY(&_WMat,rot + 0.5f * 3.1415f);

	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXMATRIXA16* 
 */
/***********************************************************************/
const D3DXMATRIXA16* CTankBottom::getWMat()
{
	return &_WMat;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3* CTankBottom::getMoveVec()
{
	return &_MoveVec;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pIntelligence 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::setIntelligence(CTankIntInter* pIntelligence)
{
	_pIntelligence = pIntelligence;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] MoveVec 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::setMoveVec( D3DXVECTOR3& MoveVec )
{
	_MoveVec.x  = MoveVec.x;
	_MoveVec.y  = MoveVec.y;
	_MoveVec.z  = MoveVec.z;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] MoveVec 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::setMoveVec( const D3DXVECTOR3 *MoveVec )
{
	_MoveVec.x  = MoveVec->x;
	_MoveVec.y  = MoveVec->y;
	_MoveVec.z  = MoveVec->z;
}



void CTankBottom::setPos(const float x,const float z)
{
	_WMat._41 = x;
	_WMat._43 = z;
}