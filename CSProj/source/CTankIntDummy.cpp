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


float debug,debug2,debug3,debug4,debug5;
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
	/*
	switch(getRand(2))
	{
	case 0:
		_MoveDir = 1;
		break;
	case 1:
		_MoveDir = 8;
		break;
	}
	*/

	CTankIntDummy::root();
	Debug();
	
}
/***********************************************************************/
/*! @brief ルートに従う関数
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::root(){
	/*
	static D3DXVECTOR2* i = new D3DXVECTOR2;// 現在位置から目的ナビポイントまでのベクトル
	static D3DXVECTOR2* o = new D3DXVECTOR2;// 前ナビポイントから目的ナビポイントまでのベクトル
	static D3DXVECTOR2* a = new D3DXVECTOR2;
	static D3DXVECTOR2* b = new D3DXVECTOR2;
	// 現在位置から目的ナビポイントまで
	/*
	i->x = CTankIntDummy::_StageData->getRoot()[_point].x - CTankIntDummy::_pMyTank->getMatBottom()->_41;
	i->y = CTankIntDummy::_StageData->getRoot()[_point].y - CTankIntDummy::_pMyTank->getMatBottom()->_43;
	//前ナビポイントから目的ナビポイントまで
	o->x = CTankIntDummy::_StageData->getRoot()[_point].x - CTankIntDummy::_StageData->getRoot()[_point-1].x;
	o->y = CTankIntDummy::_StageData->getRoot()[_point].y - CTankIntDummy::_StageData->getRoot()[_point-1].y;
	
	// 性器化
	D3DXVec2Normalize(a,i);
	D3DXVec2Normalize(b,o);

	float k = D3DXVec2Dot(a,b);
	debug = k;
	debug2 =  CTankIntDummy::_StageData->getRoot()[_point].x;
	debug3 =  CTankIntDummy::_StageData->getRoot()[_point].y;
	debug4 = CTankIntDummy::_pMyTank->getMatBottom()->_41;
	debug5 = CTankIntDummy::_pMyTank->getMatBottom()->_43;
	*/
	/*
	if(k<0){
	/*
		if(_MoveDir = 8)_MoveDir = 2;
		else _MoveDir = 8;
		*/
	/*
		_point++;	// 次のポイントへ
	
	}
	
	//CTankIntDummy::_pMyTank->getMatBottom()->_41;
	*/
}

// デバッグ出力
void CTankIntDummy::Debug(){
	FONT->DrawFloat("navipointNormalize:",debug,RECTEX(0,16,0,0));
	FONT->DrawFloat("navipointX:",debug2,RECTEX(0,32,0,0));
	FONT->DrawFloat("Y:",debug3,RECTEX(250,32,0,0));
	FONT->DrawFloat("enemyX:",debug4,RECTEX(0,176,0,0));
	FONT->DrawFloat("enemyy:",debug5,RECTEX(0,192,0,0));

}