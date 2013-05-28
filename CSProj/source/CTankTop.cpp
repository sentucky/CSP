#include"CTankTop.h"




#include"CMesh.h"
#include"CMeshFactory.h"

#include"CShell.h"
#include"CObjMng.h"
#include"CTankIntInter.h"


#include"CInputCommon.h"
#include"const.h"


CTankTop::CTankTop(
	CMesh*			pMesh,
	CTankIntInter*	pTankIntInter,
	CShell*			pProtoShell
	)
	:_pTankIntelligence(_pTankIntelligence),
	_pMesh(pMesh),
	_pProtoShell(pProtoShell),
	_TopDir(0,0,0)
{
	D3DXMatrixIdentity(&_WMat);
}

CTankTop::~CTankTop()
{
	SAFE_DELETE(_pMesh);
	SAFE_DELETE(_pProtoShell);
}


CTankTop::CTankTop(
	const CTankTop& src
	)
	:_pTankIntelligence(_pTankIntelligence),
	_pMesh(new CMesh( *src._pMesh)),
	_pProtoShell(new CShell(*src._pProtoShell)),
	_TopDir(0,0,1.0f)
{
	D3DXMatrixIdentity(&_WMat);

	//	’e‚Ì–³Œø‰»
	_pProtoShell->disableTask();
}


void CTankTop::fire()
{
	/*
	if(_CntCool > 0)
		return;

	_CntCool = 60;
	*/

	if(!_pTankIntelligence->getFireFlg())
		return;

	CShell* pShell = NULL;
	OBJMNG->push(OBJKEY::SHELL01(),pShell = new CShell(*_pProtoShell),NULL);
	pShell->setMoveVector(&_TopDir);
	pShell->setPos(&_WMat);
}

/***********************************************************************/
/*! @brief ˆÚ“®ƒxƒNƒgƒ‹‚ðŒvŽZ
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::turn()
{
	D3DXVECTOR3 p1;
	D3DXVECTOR2 cr;
	MOUSE.mousePoint3D(&p1,0);

	_TopDir.x = cr.x = p1.x - _WMat._41;
	_TopDir.z = cr.y = p1.z - _WMat._43;

	D3DXVec2Normalize(&cr,&cr);
	float x,y,z;
	x = _WMat._41;
	y = _WMat._42;
	z = _WMat._43;
	D3DXMatrixRotationY(&_WMat,-atan2f(cr.y,cr.x) + 0.5F*3.1415f);
	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;
}

void CTankTop::draw()
{
	_pMesh->draw(&_WMat);
}

void CTankTop::cooldown()
{
	_CntCool = _CntCool > 0 ? _CntCool - 1 : 0;
}

void CTankTop::setPos(const float x, const float y,const float z)
{
	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;
}


void CTankTop::setIntelligence(CTankIntInter* pIntelligence)
{
	_pTankIntelligence = pIntelligence;
}
