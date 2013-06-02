/***********************************************************************/
/*! @file  CFollowCamera.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CFollowCamera.h"
#include"CCamera.h"
#include"CTaskList.h"
#include"CTank.h"
#include"CTaskMng.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out]  
 *  @retval  
 */
/***********************************************************************/
CFollowCamera::CFollowCamera(
	):_fDistance(	50.0f),	
	  _NAtToEye	(	D3DXVECTOR3(0,1.0f,0)),
	  _pTank	(	NULL),
	  _pUpdate	(	NULL)
{
	D3DXVec3Normalize(&_NAtToEye,&_NAtToEye);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CFollowCamera::~CFollowCamera()
{
	disableTask();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CFollowCamera::CFollowCamera(
	const CFollowCamera& src
	):_fDistance(	50.0f					),	
	  _NAtToEye	(	D3DXVECTOR3(0,0.8f,-0.2f)	),
	  _pTank	(	NULL),
	  _pUpdate	(	NULL					)
{
	D3DXVec3Normalize(&_NAtToEye,&_NAtToEye);
	enableTask();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CFollowCamera::enableTask()
{
	CTaskMng::push<CFollowCamera>(TASKKEY::UPDATECAMERA(),this,&CFollowCamera::update,&_pUpdate);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CFollowCamera::disableTask()
{
	CTaskMng::erase(&_pUpdate);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CFollowCamera::update()
{
	const float x = _pTank->getMatBottom()->_41;
	const float y = _pTank->getMatBottom()->_42;
	const float z = _pTank->getMatBottom()->_43;

	D3DXVECTOR3 eye;
	eye.x = x + _NAtToEye.x * _fDistance;
	eye.y = y + _NAtToEye.y * _fDistance;
	eye.z = z + _NAtToEye.z * _fDistance;


	CCamera::setAt(D3DXVECTOR3(x,y,z));
	CCamera::setEye(eye);

	CCamera::update();

	_DeleteFlg = _pTank->getDeleteFlg();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval void
 */
/***********************************************************************/
void CFollowCamera::setTank(CTank* pTank)
{
	_pTank = pTank;
}