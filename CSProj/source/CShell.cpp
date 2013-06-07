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

#include"StageData.h"

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
			CMesh*	pMesh
	)
	:_OldPos(0,0,0),
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
	_Owner(NULL)
{
	D3DXMatrixIdentity(&_matW);
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
	:_Owner(src._Owner),
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
	_nLife(30){
	D3DXMatrixIdentity(&_matW);
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
	_pMesh->draw(&_matW);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CShell::move()
{
	_OldPos.x = _matW._41;
	_OldPos.y = _matW._42;
	_OldPos.z = _matW._43;
	_matW._41 += _MoveVector.x;
	_matW._42 += _MoveVector.y;
	_matW._43 += _MoveVector.z;
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

void CShell::hitTestTank(CTank* pTank)
{
	_DeleteFlg = TRUE;
}

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
void CShell::setMoveVector(const D3DXVECTOR3* MoveVec)
{
	_MoveVector = *MoveVec;
//	D3DXVec3Normalize(&_MoveVector,&_MoveVector);
	_MoveVector *= _MoveSpeed;
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
	_matW._41 = pos->_41;
	_matW._42 = pos->_42;
	_matW._43 = pos->_43;
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
	_matW._41 = pos->x;
	_matW._42 = pos->y;
	_matW._43 = pos->z;
}