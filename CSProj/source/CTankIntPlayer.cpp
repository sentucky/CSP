/***********************************************************************/
/*! @file  CTankIntPlayer.cpp
 *  @brief タンク　プレイヤー思考
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"CTankIntPlayer.h"
#include"CInputCommon.h"
#include"CTank.h"
#include"CWindow.h"

#include"CInputCommon.h"
#include"CScreen.h"
#include"CMesh.h"
#include"CCamera.h"
#include"CDevice.h"
#include"CTaskList.h"
#include"CTaskMng.h"
#include"CObjMng.h"
#include"CFactory.h"

#include"CObjBase.h"
#include"CPin.h"

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CTankIntPlayer::CTankIntPlayer(CTank* pPlayerTank)
	:CTankIntInter(pPlayerTank)
{
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CTankIntPlayer::~CTankIntPlayer()
{
}

/***********************************************************************/
/*! @brief 更新処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntPlayer::update()
{
	//	移動方向
	if(KEYBOARD.getPrsKey(DIK_W))
	{
		_MoveDir = 7;
	}
	else if(KEYBOARD.getPrsKey(DIK_S))
	{
		_MoveDir = 1;
	}
	else
	{
		_MoveDir = 4;
	}

	if(KEYBOARD.getPrsKey(DIK_D))
	{
		_MoveDir += 2;
	}
	else if(!KEYBOARD.getPrsKey(DIK_A))
	{
		_MoveDir += 1;
	}


	//	発砲フラグ
	_FireFlg = MOUSE.getTrgMouseButton(0) ? TRUE : FALSE;

	MOUSE.mousePoint3D(&_TargetPoint,50);
}

void CTankIntPlayer::moveSight()
{

}