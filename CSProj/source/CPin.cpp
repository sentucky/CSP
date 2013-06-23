/***********************************************************************/
/*! @file  CPin.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CPin.h"

#include"CInputCommon.h"
#include"CMesh.h"
#include"CTaskList.h"
#include"CTaskMng.h"


#include"const.h"
#include"ObjKey.h"

#ifdef DEBUG
#include"CFont.h"
#endif

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pMesh 
 *  @retval  
 */
/***********************************************************************/
CPin::CPin(CMesh* pMesh)
	:CObjBase(OBJGROUPKEY::PIN()),
	_pTaskDraw(NULL),
	_pTaskUpdate(NULL),
	_pMesh(pMesh)
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CPin::~CPin()
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
CPin::CPin(const CPin& src)
	:CObjBase			(src._GroupID						),
_pTaskDraw(NULL),
	_pTaskUpdate(NULL),
	_pMesh(new CMesh(*src._pMesh))
{
	D3DXMatrixIdentity(&_matW);
	enableTask();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CPin::enableTask()
{
	CTaskMng::push<CPin>(TASKKEY::DRAW(), this, &CPin::draw,&_pTaskDraw);
	CTaskMng::push<CPin>(TASKKEY::MOVE(), this, &CPin::move,&_pTaskUpdate);

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CPin::disableTask()
{
	CTaskMng::erase(&_pTaskDraw);
	CTaskMng::erase(&_pTaskUpdate);
}



/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CPin::draw()
{
	_pMesh->draw(&_matW);
#ifdef DEBUG
#endif
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CPin::move()
{
	D3DXVECTOR3 Target;

	MOUSE.mousePoint3D(&Target,0);

	_matW._41 = Target.x;
	_matW._42 = Target.y;
	_matW._43 = Target.z;
}

