/***********************************************************************/
/*! @file  CTankIntPlayer.cpp
 *  @brief �^���N�@�v���C���[�v�l
 *  
 *  @author �쌴�@�C��
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
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CTankIntPlayer::CTankIntPlayer(CTank* pPlayerTank)
	:CTankIntInter(pPlayerTank)
{
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTankIntPlayer::~CTankIntPlayer()
{
}

/***********************************************************************/
/*! @brief �X�V����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntPlayer::update()
{
	//	�ړ�����
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


	//	���C�t���O
	_FireFlg = MOUSE.getTrgMouseButton(0) ? TRUE : FALSE;

	MOUSE.mousePoint3D(&_TargetPoint,50);
}

void CTankIntPlayer::moveSight()
{

}