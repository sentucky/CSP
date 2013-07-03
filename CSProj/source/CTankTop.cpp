/***********************************************************************/
/*! @file  CTankTop.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CTankTop.h"

#include"CEffectBase.h"
#include"CEffectToon.h"


#include"CMesh.h"
#include"CMeshFactory.h"

#include"CShell.h"
#include"CObjMng.h"
#include"CTankIntInter.h"
#include"CTankBottom.h"


#include"CInputCommon.h"
#include"const.h"
#include"ObjKey.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pMesh 
 *  @param[in,out] pTankIntInter 
 *  @param[in,out] pProtoShell 
 *  @retval  
 */
/***********************************************************************/
CTankTop::CTankTop(
	CTank*			pOwner,
	CMesh*			pMesh,
	CTankIntInter*	pTankIntInter,
	CShell*			pProtoShell
	)
	:_Owner(pOwner),
	_pTankIntelligence(_pTankIntelligence),
	_pMesh(pMesh),
	_pProtoShell(pProtoShell),
	_TopDir(0,0,0),
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
CTankTop::~CTankTop()
{
	SAFE_DELETE(_pMesh);
	_pEffect = NULL;
	SAFE_DELETE(_pProtoShell);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CTankTop::CTankTop(
	const CTankTop& src
	)
	:_Owner				(src._Owner),
	_pTankIntelligence	(_pTankIntelligence),
	_pMesh				(new CMesh( *src._pMesh)),
	_pProtoShell		(new CShell(*src._pProtoShell)),
	_TopDir				(0,0,1.0f),
	_pEffect			(NULL)
{
	D3DXMatrixIdentity(&_WMat);

//	_pEffect = CEffectToon::getInst();
	_pMesh->setEffect(_pEffect);

	//	’e‚Ì–³Œø‰»
	_pProtoShell->disableTask();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::fire()
{

	CShell* pShell = NULL;
	OBJMNG->push(OBJGROUPKEY::SHELL(),pShell = new CShell(*_pProtoShell),NULL);
	D3DXVECTOR3 ShellVec;;
	D3DXVec3Normalize(&ShellVec,&_TopDir);
	ShellVec += *_Bottom->getMoveVec();
	pShell->moveVector(&ShellVec);
	pShell->setPos(&_WMat);
	pShell->setOwner(_Owner);
}

/***********************************************************************/
/*! @brief ˆÚ“®ƒxƒNƒgƒ‹‚ðŒvŽZ
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::turn()
{
	const D3DXVECTOR3* 	p1 = _pTankIntelligence->getTargetPoint();
	D3DXVECTOR2 cr;

	_TopDir.x = cr.x = p1->x - _WMat._41;
	_TopDir.z = cr.y = p1->z - _WMat._43;

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

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::draw()
{
	_pMesh->draw(&_WMat);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::cooldown()
{
	_CntCool = _CntCool > 0 ? _CntCool - 1 : 0;
}


void CTankTop::rotationy(const float fY)
{
	_TopDir.x = _TopDir.y = _TopDir.z = 0;

	if( fY >= 1.5f)
	{
		_TopDir.x = 1;
	}
	else if(fY >= 1.0f)
	{
		_TopDir.y = -1;
	}
	else if(fY >= 0.5f)
	{
		_TopDir.x = -1;
	}
	else
	{
		_TopDir.y = 1;
	}

	const float x = _WMat._41;
	const float y = _WMat._42;
	const float z = _WMat._43;



	_WMat._41 = _WMat._42 = _WMat._43 = 0;

	float rot = -atan2f(_TopDir.z,_TopDir.x);

	D3DXMatrixRotationY(&_WMat,rot + 0.5f * D3DX_PI);

	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;

}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] x 
 *  @param[in,out] y 
 *  @param[in,out] z 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::setPos(const float x, const float y,const float z)
{
	_WMat._41 = x;
	_WMat._42 = y;
	_WMat._43 = z;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pIntelligence 
 *  @retval void
 */
/***********************************************************************/
void CTankTop::setIntelligence(CTankIntInter* pIntelligence)
{
	_pTankIntelligence = pIntelligence;
}
