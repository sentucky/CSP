/***********************************************************************/
/*! @file  CShell.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CShell.h"

#include"CTaskList.h"
#include"CMesh.h"
#include"CTaskMng.h"
#include"CTank.h"
#include"ObjKey.h"


#include"StageData.h"
#include"CCamera.h"

CStageData* CShell::_StageData = 0;

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nMaxLife 
 *  @param[in,out] MoveSpeed 
 *  @param[in,out] pMesh 
 *  @retval  
 */
/***********************************************************************/
CShell::CShell(
	const	int		nMaxLife,
			float	MoveSpeed,
			CMesh*	pMesh,
			const int power
	)
	:CObjBase(OBJGROUPKEY::SHELL()),
	_OldPos(0,0,0),
	_Trajectory(0,0,0),
	_MoveVector(0,0,0),
	_pMesh(pMesh),
	_MoveSpeed(MoveSpeed),
	_TaskListDraw(NULL),
	_TaskListMove(NULL),
	_TaskListCheckAlive(NULL),
	_TaskListExplosion(NULL),
	_nMaxLife(nMaxLife),
	_nLife(-1),
	_Owner(NULL),
	_Power(power),
	_fRad(1.0f)
{
	D3DXMatrixIdentity(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CShell::~CShell()
{
	SAFE_DELETE(_pMesh);
	disableTask();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CShell::CShell(
	const CShell& src
	)
	:CObjBase(src._GroupID						),
	_Owner(src._Owner),
	_OldPos(0,0,0),
	_Trajectory(0,0,0),
	_MoveVector(0,0,0),
	_pMesh(new CMesh(*src._pMesh)),
	_MoveSpeed(src._MoveSpeed),
	_TaskListDraw(NULL),
	_TaskListMove(NULL),
	_TaskListCheckAlive(NULL),
	_TaskListExplosion(NULL),
	_nMaxLife(src._nMaxLife),
	_nLife(src._nMaxLife),
	_Power(src._Power),
	_fRad(src._fRad)

{
	D3DXMatrixIdentity(&_WMat);
	enableTask();
#ifdef _DEBUG
	_fRad = 1.0f;
#endif

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::enableTask()
{
	CTaskMng::push(TASKKEY::DRAW(),this,&CShell::draw,&_TaskListDraw);
	CTaskMng::push(TASKKEY::MOVE(),this,&CShell::move,&_TaskListMove);
	CTaskMng::push(TASKKEY::CHECKALIVE(),this,&CShell::checkAlive,&_TaskListCheckAlive);
	CTaskMng::push(TASKKEY::EXPLOSION(),this,&CShell::explosion,&_TaskListExplosion);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::disableTask()
{
	CTaskMng::erase(&_TaskListDraw);
	CTaskMng::erase(&_TaskListMove);
	CTaskMng::erase(&_TaskListCheckAlive);
	CTaskMng::erase(&_TaskListExplosion);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::draw()
{


	const int camx = YOUSO(CCamera::getAt().x);
	const int camy = YOUSO(CCamera::getAt().z);

	const int x = YOUSO(_WMat._41);
	const int y = YOUSO(_WMat._43);

	if(abs(x - camx) > 1 || abs(y - camy) > 1)
	{
		return;
	}
	_pMesh->draw(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::move()
{
	_OldPos.x = _WMat._41;
	_OldPos.y = _WMat._42;
	_OldPos.z = _WMat._43;
	_WMat._41 += _MoveVector.x;
	_WMat._42 += _MoveVector.y;
	_WMat._43 += _MoveVector.z;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::checkAlive()
{
	_nLife -= 1;
	if(_nLife < 0)
	{
		_DeleteFlg = TRUE;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::explosion()
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval void
 */
/***********************************************************************/
void CShell::hitTestTank(CTank* pTank)
{
	_DeleteFlg = TRUE;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::hitTestWall()
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval D3DXVECTOR3& 
 */
/***********************************************************************/
D3DXVECTOR3& CShell::getTrajectory()
{
	return _Trajectory;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] MoveVec 
 *  @retval void
 */
/***********************************************************************/
void CShell::moveVector(const D3DXVECTOR3* MoveVec)
{
	D3DXVec3Normalize(&_MoveVector,&_MoveVector);
	D3DXMATRIXA16 matbak = _WMat;

	D3DXMATRIXA16 rotmat;
	D3DXMatrixIdentity(&rotmat);

	float rotY = -atan2f(MoveVec->z,MoveVec->x) + 0.5f * D3DX_PI;

	D3DXMatrixRotationY(&rotmat,rotY);

	_WMat._41 = _WMat._42 = _WMat._43 = 0;

	_WMat *= rotmat;

	_WMat._41 = matbak._41;
	_WMat._42 = matbak._42;
	_WMat._43 = matbak._43;

	_MoveVector *= _MoveSpeed;
	_MoveVector += *MoveVec;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pos 
 *  @retval void
 */
/***********************************************************************/
void CShell::setPos(const D3DXMATRIXA16*	pos)
{
	_WMat._41 = pos->_41;
	_WMat._42 = pos->_42;
	_WMat._43 = pos->_43;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pos 
 *  @retval void
 */
/***********************************************************************/
void CShell::setPos(const D3DXVECTOR3*		pos)
{
	_WMat._41 = pos->x;
	_WMat._42 = pos->y;
	_WMat._43 = pos->z;
}