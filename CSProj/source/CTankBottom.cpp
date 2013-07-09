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

#include"CObjMng.h"

#include"ObjKey.h"

#include"CEffectBase.h"


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
	CMesh* pMesh2,
	const float fSpeedMove,
	const float fSpeedTurn
	)
	:_pMesh(pMesh),
	_pMesh2(pMesh2),
	_pDrawMesh(NULL),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,0.0f),
	_MoveDir(0,0,0),
	_fSpeedMove(fSpeedMove),
	_fSpeedTurn(fSpeedTurn),
	_CaterpillarRoll(FALSE),
	_pEffect(NULL)
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
	SAFE_DELETE(_pMesh2);
	_pEffect = NULL;
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
	_pMesh2(new CMesh(*src._pMesh2)),
	_pDrawMesh(_pMesh),
	_pIntelligence(NULL),
	_Dir(0,0.0f,1.0f),
	_MoveVec(0,0,0.0f),
	_MoveDir(0,0,0),
	_fSpeedMove(src._fSpeedMove),
	_fSpeedTurn(src._fSpeedTurn),
	_CaterpillarRoll(FALSE),
	_pEffect(NULL)
{
	D3DXMatrixIdentity(&_WMat);
//	_pEffect = CEffectToon::getInst();
	_pMesh->setEffect(_pEffect);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::draw()
{
	_pDrawMesh->draw(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::move()
{
	//	épê®Ç©ÇÁÉxÉNÉgÉãÇåvéZ
	_MoveVec *= _fDeceleration;
	_WMat._41 += _MoveVec.x;
	_WMat._42 += _MoveVec.y;
	_WMat._43 += _MoveVec.z;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::clacMove(const uint rank)
{
	CListMng<CObjBase*>* pTankList = OBJMNG->getList(OBJGROUPKEY::TANK());

	const uint size = pTankList->size();
	const float rankPar = static_cast<float>(rank) / static_cast<float>(size) - 0.5f;

	const D3DXVECTOR2* pMoveVec = _pIntelligence->getModeDir();


	if(abs(pMoveVec->x) + abs(pMoveVec->y) > 0)
	{
		D3DXVec3Normalize(&_Dir,&_Dir);
		_MoveVec += _Dir *( _fSpeedMove/*  + _fSpeedMove * rankPar*/);
		_CaterpillarRoll++;
		if(_CaterpillarRoll > 5)
		{
			_pDrawMesh = _pDrawMesh != _pMesh ? _pMesh : _pMesh2;
			_CaterpillarRoll = 0;
		}
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

void CTankBottom::rotationsetY(const float fY)
{
	_Dir.x = _Dir.y = _Dir.z = 0;

	if( fY >= 1.5f)
	{
		_Dir.x = 1;
	}
	else if(fY >= 1.0f)
	{
		_Dir.y = -1;
	}
	else if(fY >= 0.5f)
	{
		_Dir.x = -1;
	}
	else
	{
		_Dir.y = 1;
	}

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
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::turn()
{
	_MoveVec.y = 0;

	const D3DXVECTOR2* pMoveDir = _pIntelligence->getModeDir();

	if(abs(pMoveDir->x) + abs(pMoveDir->y) == 0)
	{
		return;
	}

	//	à⁄ìÆï˚å¸ÇÃç∂âEämîF
	static D3DXVECTOR2 v1;

	D3DXVec3Normalize(&_MoveDir,&_MoveDir);
	v1.x = _Dir.x;
	v1.y = _Dir.z;
	_MoveDir.x = pMoveDir->x;
	_MoveDir.z = pMoveDir->y;
	float fCross = D3DXVec2CCW(&v1,pMoveDir);	//	äOêœ

	float fDot	 = D3DXVec3Dot(&_Dir,&_MoveDir);

	//	ç∂âEîªíË
	//	ïΩçsÇ©Ç¬âsäp
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
	//	âsäp


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
const D3DXVECTOR3  CTankBottom::getPos()
{
	return D3DXVECTOR3(_WMat._41,_WMat._42,_WMat._43);
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



/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] x 
 *  @param[in,out] z 
 *  @retval void
 */
/***********************************************************************/
void CTankBottom::setPos(const float x,const float z)
{
	_WMat._41 = x;
	_WMat._43 = z;
}