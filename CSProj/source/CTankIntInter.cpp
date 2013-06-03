/***********************************************************************/
/*! @file  CTaskIntInter.cpp
 *  @brief タンク思考インターフェース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"CTankIntInter.h"
#include"CTank.h"
#include"StageData.h"

CTank*			CTankIntInter::_pPlayerTank = NULL;	//	プレイヤータンクのポインタ
CStageData*		CTankIntInter::_StageData	= NULL;	//	ステージデータ

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CTankIntInter::CTankIntInter(CTank* pMyTank)
	:_FireFlg(FALSE),
	_MoveDir(TMV_5),
	_pMyTank(pMyTank),
	_TargetPoint(0,0,0)
{

}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CTankIntInter::~CTankIntInter()
{
}

/***********************************************************************/
/*! @brief FireFlgの取得
 * 
 *  @retval const BOOL 
 */
/***********************************************************************/
const BOOL CTankIntInter::getFireFlg(){return _FireFlg;}

/***********************************************************************/
/*! @brief MoveDirの取得
 * 
 *  @retval const uint 
 */
/***********************************************************************/
const uint CTankIntInter::getMoveFlg(){return _MoveDir;}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3* CTankIntInter::getTargetPoint()
{
	return &_TargetPoint;
}

void CTankIntInter::setStageData(CStageData* StageData)
{
	_StageData = StageData;
}
