#include"CShell.h"

#include"CTaskList.h"
#include"CMesh.h"
#include"CTaskMng.h"

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
	_nLife(-1)
{
	D3DXMatrixIdentity(&_matW);
}

CShell::~CShell()
{
	SAFE_DELETE(_pMesh);
	disableTask();
}

CShell::CShell(
	const CShell& src
	)
	:_OldPos(0,0,0),
	_Trajectory(0,0,0),
	_MoveVector(0,0,0),
	_pMesh(new CMesh(*src._pMesh)),
	_MoveSpeed(src._MoveSpeed),
	_TaskListDraw(NULL),
	_TaskListMove(NULL),
	_TaskListCheckAlive(NULL),
	_TaskListExplosion(NULL),
	_nMaxLife(src._nMaxLife),
	_nLife(-1)
{
	D3DXMatrixIdentity(&_matW);
	enableTask();
}

void CShell::enableTask()
{
	CTaskMng::push(TASKID::DRAW(),this,&CShell::draw,&_TaskListDraw);
	CTaskMng::push(TASKID::MOVE(),this,&CShell::move,&_TaskListMove);
	CTaskMng::push(TASKID::CHECKALIVE(),this,&CShell::checkAlive,&_TaskListCheckAlive);
	CTaskMng::push(TASKID::EXPLOSION(),this,&CShell::explosion,&_TaskListExplosion);
}

void CShell::disableTask()
{
	CTaskMng::erase(&_TaskListDraw);
	CTaskMng::erase(&_TaskListMove);
	CTaskMng::erase(&_TaskListCheckAlive);
	CTaskMng::erase(&_TaskListExplosion);
}

void CShell::draw()
{
	_pMesh->draw(&_matW);
}

void CShell::move()
{
	_OldPos.x = _matW._41;
	_OldPos.y = _matW._42;
	_OldPos.z = _matW._43;
	_matW._41 += _MoveVector.x;
	_matW._42 += _MoveVector.y;
	_matW._43 += _MoveVector.z;
}

void CShell::checkAlive()
{
	_nLife -= 1;
	if(_nLife < 0)
	{
		_DeleteFlg = TRUE;
	}
}

void CShell::explosion()
{
}

D3DXVECTOR3& CShell::getTrajectory()
{
	return _Trajectory;
}

void CShell::setMoveVector(const D3DXVECTOR3* MoveVec)
{
	_MoveVector = *MoveVec;
	D3DXVec3Normalize(&_MoveVector,&_MoveVector);
	_MoveVector *= _MoveSpeed;
}

void CShell::setPos(const D3DXMATRIXA16*	pos)
{
	_matW._41 = pos->_41;
	_matW._42 = pos->_42;
	_matW._43 = pos->_43;
}

void CShell::setPos(const D3DXVECTOR3*		pos)
{
	_matW._41 = pos->x;
	_matW._42 = pos->y;
	_matW._43 = pos->z;
}