#include"CPin.h"

#include"CInputCommon.h"
#include"CMesh.h"
#include"CTaskList.h"
#include"CTaskMng.h"

#include"const.h"
#ifdef _DEBUG
#include"CFont.h"
#endif

CPin::CPin(CMesh* pMesh)
	:_pTaskDraw(NULL),
	_pTaskUpdate(NULL),
	_pMesh(pMesh)
{
}

CPin::~CPin()
{
	SAFE_DELETE(_pMesh);
	disableTask();
}


CPin::CPin(const CPin& src)
	:_pTaskDraw(NULL),
	_pTaskUpdate(NULL),
	_pMesh(new CMesh(*src._pMesh))
{
	D3DXMatrixIdentity(&_matW);
	enableTask();
}


void CPin::enableTask()
{
	CTaskMng::push<CPin>(TASKID::DRAW(), this, &CPin::draw,&_pTaskDraw);
	CTaskMng::push<CPin>(TASKID::MOVE(), this, &CPin::move,&_pTaskUpdate);

}

void CPin::disableTask()
{
	CTaskMng::erase(&_pTaskDraw);
	CTaskMng::erase(&_pTaskUpdate);
}



void CPin::draw()
{
	_pMesh->draw(&_matW);
#ifdef _DEBUG
	FONT->DrawFloat("",_matW._41,RECTEX(0,0,0,0));
	FONT->DrawFloat("",_matW._42,RECTEX(0,16,0,0));
	FONT->DrawFloat("",_matW._43,RECTEX(0,32,0,0));
#endif
}

void CPin::move()
{
	D3DXVECTOR3 Target;

	MOUSE.mousePoint3D(&Target,0);

	_matW._41 = Target.x;
	_matW._42 = Target.y;
	_matW._43 = Target.z;
}

