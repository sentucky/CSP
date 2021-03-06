/***********************************************************************/
/*! @file  CTaskBase.cpp
 *  @brief タスクベースクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"CTaskBase.h"

/***********************************************************************/
/*! @brief コンストラクタ
 * 
 *  @param[in] unTaskID タスク番号
 */
/***********************************************************************/
CTaskBase::CTaskBase(const uint unTaskID)
	:_unTaskID(unTaskID)
{
}

CTaskBase::~CTaskBase(){}

/***********************************************************************/
/*! @brief コピーコンストラクタ(コピー禁止)
 * 
 *  @param[in] src コピーするオブジェクト
 *  @retval  
 */
/***********************************************************************/
CTaskBase::CTaskBase(const CTaskBase& src):_unTaskID(0)
{
}

/***********************************************************************/
/*! @brief 代入オーバーロード(代入禁止)
 * 
 *  @param[in] srcコピーするオブジェクト
 *  @retval void
 */
/***********************************************************************/
void CTaskBase::operator =(const CTaskBase& src)
{
}

/***********************************************************************/
/*! @brief タスクID取得
 * 
 *  @retval const uint タスクID
 */
/***********************************************************************/
const uint CTaskBase::getTaskID()
{
	return _unTaskID;
}
