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
#include"ObjKey.h"

#ifdef _DEBUG
#include"CInputCommon.h"
#endif

/***********************************************************************/
/*! @brief コンストラクタ
* 
*  @retval  void
*/
/***********************************************************************/
CFollowCamera::CFollowCamera(
	)
	:CObjBase(OBJGROUPKEY::CAMERA()),
	_fDistance(	40.0f),	
	_NAtToEye	(	D3DXVECTOR3(0,1.0f,-0.25)),
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
	)
	:CObjBase	(src._GroupID		),
	_fDistance	(	src._fDistance	),	
	_NAtToEye	(	src._NAtToEye	),
	_pTank		(	NULL			),
	_pUpdate	(	NULL			)
{
	D3DXVec3Normalize(&_NAtToEye,&_NAtToEye);
	enableTask();
}


/***********************************************************************/
/*! @brief タスク有効化
* 
*  @retval void
*/
/***********************************************************************/
void CFollowCamera::enableTask()
{
	CTaskMng::push<CFollowCamera>(TASKKEY::UPDATECAMERA(),this,&CFollowCamera::update,&_pUpdate);
}


/***********************************************************************/
/*! @brief タスク無効化
* 
*  @retval void
*/
/***********************************************************************/
void CFollowCamera::disableTask()
{
	CTaskMng::erase(&_pUpdate);
}


/***********************************************************************/
/*! @brief 更新処理
* 
*  @retval void
*/
/***********************************************************************/
void CFollowCamera::update()
{
	if(_pTank == NULL)
		return;

	const float x = _pTank->getMatBottom()->_41;
	const float y = _pTank->getMatBottom()->_42;
	const float z = _pTank->getMatBottom()->_43;

#ifdef _DEBUG
	if(KEYBOARD.getPrsKey(DIK_P))
	{
		_fDistance+=1;
	}
	else if(KEYBOARD.getPrsKey(DIK_O))
	{
		_fDistance-=1;
	}
#endif

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