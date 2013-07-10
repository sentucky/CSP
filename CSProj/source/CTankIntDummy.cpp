/***********************************************************************/
/*! @file  CTankIntDummy.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CTankIntDummy.h"

#include"CTank.h"
#include"StageData.h"
#include"CObjMng.h"
#include"ObjKey.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(CTank* pTank)
	:CTankIntInter(pTank)
{
	_pMyTank = pTank;
	_point = 1;
	_MoveDir = D3DXVECTOR2(0,1);
	_pointError = (rand()%POINT_ERROR_NUM) - POINT_ERROR_NUM / 2;	// 誤差設定

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::~CTankIntDummy()
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(const CTankIntDummy& src)
	:CTankIntInter(src._pMyTank)
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::update()
{
	
	root();
	shot();
	
}
/***********************************************************************/
/*! @brief ルートに従う関数
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::root(){
	
	static D3DXVECTOR2 TanktoNaviPoint;			// 現在位置から目的ナビポイントまでのベクトル
	static D3DXVECTOR2 NaviToNavi;				// 前ナビポイントから目的ナビポイントまでのベクトル
	static D3DXVECTOR2 TtoNUnitVec;				// 現在位置から目的ナビポイントまでの単位ベクトル
	static D3DXVECTOR2 NtoNUnitVec;				// 前ナビポイントから目的ナビポイントまでの単位ベクトル
	static float dot;
	// 現在位置から目的ナビポイントまで
	
	TanktoNaviPoint.x = (CTankIntDummy::_StageData->getRoot()[_point].x + _pointError) - CTankIntDummy::_pMyTank->getMatBottom()->_41;
	TanktoNaviPoint.y = (CTankIntDummy::_StageData->getRoot()[_point].y + _pointError) - CTankIntDummy::_pMyTank->getMatBottom()->_43;
	//前ナビポイントから目的ナビポイントまで
	NaviToNavi.x = (CTankIntDummy::_StageData->getRoot()[_point].x + _pointError) - (CTankIntDummy::_StageData->getRoot()[_point-1].x + _pointError);
	NaviToNavi.y = (CTankIntDummy::_StageData->getRoot()[_point].y + _pointError) - (CTankIntDummy::_StageData->getRoot()[_point-1].y + _pointError);
	
	// 性器化
	D3DXVec2Normalize(&TtoNUnitVec,&TanktoNaviPoint);
	D3DXVec2Normalize(&NtoNUnitVec,&NaviToNavi);

	dot = D3DXVec2Dot(&TtoNUnitVec,&NtoNUnitVec);
	
	if(dot<0){
		if( _point >= CTankIntDummy::_StageData->getRootNum()-1 ){
			_point = 0;	// ナビポイントリセット
		}else{
			_point++;	// 次のポイントへ
			}
		_pointError = (rand()%POINT_ERROR_NUM) - POINT_ERROR_NUM / 2;
	}
	_MoveDir = D3DXVECTOR2(TtoNUnitVec.x,TtoNUnitVec.y);	// ナビポイントへ移動
	
}

/***********************************************************************/
/*! @brief 近くの敵をうつ関数
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::shot(){
	static int aimNum;
//	return;
	// 射撃処理
	if(getRand(SHOT_PROB) == 1){	// 撃つ確率
		
		// 狙う敵のナンバー設定
		if(rand()%2){aimNum = 1;}else{aimNum = -1;}	

		const uint myRank = CTankIntDummy::CTankIntInter::_pMyTank->getRank();
		
		if(myRank + aimNum < 0 || ((*CTankIntDummy::_Ranking)[myRank + aimNum]) == NULL ||  myRank +aimNum > OBJMNG->getList(OBJGROUPKEY::TANK())->size())
			return;
		
		// 銃口向けて
		CTankIntDummy::_TargetPoint.x =
			(*CTankIntDummy::_Ranking)[myRank + aimNum ]->getMatBottom()->_41;
		CTankIntDummy::_TargetPoint.z =
			(*CTankIntDummy::_Ranking)[myRank + aimNum ]->getMatBottom()->_43;
		// 発射
		CTankIntDummy::_FireFlg = true;
		
	}

}