/***********************************************************************/
/*! @file  CInputMouse.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	�FCInputMouse.h
//	�T�v			�F�}�E�X���͏��
//	�����		�F�쌴�C��
//	�X�V����		�F
/***********************************************************************/

#include"CInputMouse.h"
#include"common.h"
#include"CWindow.h"
#include"CDevice.h"
#include"CCamera.h"
#include"CScreen.h"

//===================================================================
//	�R���X�g���N�^
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputMouse::CInputMouse()
	:_Ray(0,0,0)

{
	_DragFlg = FALSE;
}

//===================================================================
//	�f�X�g���N�^
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputMouse::~CInputMouse()
{
}

//===================================================================
//	�����o�֐���`
//===================================================================
//-----------------------------------------------
//	�T�v
//		�}�E�X�̏�����
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDInput 
 *  @retval void
 */
/***********************************************************************/
void CInputMouse::init(LPDIRECTINPUT8 pDInput)
{
	////////////////////////////
	//	�ϐ��錾
	HRESULT Hr;
	DIPROPDWORD dipDw;
	
	////////////////////////////
	//	��������
	ZeroMemory(&_MousePos,sizeof(POINT));		//�}�E�X���W�̏�����
	ZeroMemory(&_MousePosPrev,sizeof(POINT));	//�}�E�X�����W�̏�����
	dipDw.diph.dwSize = sizeof(DIPROPDWORD);
	dipDw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipDw.diph.dwObj = 0;
	dipDw.diph.dwHow = DIPH_DEVICE;
	dipDw.dwData = DIPROPAXISMODE_REL; // ���΍��W���[�h
//	dipDw.dwData = DIPROPAXISMODE_ABS; // ��΍��W���[�h

	memset(&_MousePosWindowPrev,NULL,sizeof(_MousePosWindowPrev));
	memset(&_MousePosWindow,NULL,sizeof(_MousePosWindowPrev));
	
	//�f�o�C�X�I�u�W�F�N�g�̍쐬
	pDInput->CreateDevice( GUID_SysMouse, &_pDIDMouse, NULL);

	
	//�f�[�^�t�H�[�}�b�g��ݒ�
	Hr = _pDIDMouse->SetDataFormat( &c_dfDIMouse2);

	
	//�������[�h��ݒ�
	Hr = _pDIDMouse->SetCooperativeLevel(WINDOW->getWnd(),DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	//�}�E�X�̍��W���[�h�ݒ�
	_pDIDMouse->SetProperty(DIPROP_AXISMODE,&dipDw.diph);

	//�}�E�X�̗L����
	_pDIDMouse->Acquire();
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�̍X�V
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputMouse::update()
{
	/////////////////////////
	//	�ϐ��錾
	HRESULT hr;


	/////////////////////////
	//	��������
	_MouseStatePrev = _MouseState;		//�����͏��̎擾
	

	////////////////////////////
	//	�X�V����
	hr = _pDIDMouse->GetDeviceState(sizeof(_MouseState),&_MouseState);	//�f�o�C�X������͏����擾
	

	//...�����[�X�E�g���K�[�̎擾
	for(int nCnt = 0; nCnt < 8; nCnt++)
	{
		_MouseStateTrg.rgbButtons[nCnt] = ( _MouseState.rgbButtons[nCnt] ^ _MouseStatePrev.rgbButtons[nCnt]) & _MouseState.rgbButtons[nCnt];
		_MouseStateRls.rgbButtons[nCnt] = ( _MouseState.rgbButtons[nCnt] ^ _MouseStatePrev.rgbButtons[nCnt]) & _MouseStatePrev.rgbButtons[nCnt];
	}

	_MousePosPrev.x = _MousePos.x;
	_MousePosPrev.y = _MousePos.y;
	_MousePos.x += _MouseState.lX;	//�}�E�X�|�C���^��X�����ړ���
	_MousePos.y += _MouseState.lY;	//�}�E�X�|�C���^��Y�����ړ���


	_MousePosWindowPrev = _MousePosWindow;
	GetCursorPos(&_MousePosWindow);
	ScreenToClient(WINDOW->getWnd(),&_MousePosWindow);

	//�}�E�X�J�[�\���̉���
	ShowCursor(TRUE);

	if( _MousePos.x != _MousePosPrev.x || _MousePos.y != _MousePosPrev.y)
		_DragFlg = TRUE;
	else
		_DragFlg = FALSE;

	calcMouseRay();

	//...��A�N�e�B�u���̏���
	if(FAILED(hr))
	{
		_pDIDMouse->Acquire();
	}
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�̉��
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputMouse::release()
{
	SAFE_RELEASE(_pDIDMouse);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputMouse::calcMouseRay()
{
	D3DXVECTOR3 p0(_MousePosWindow.x,_MousePosWindow.y, 0);
	D3DXVECTOR3 p1(_MousePosWindow.x,_MousePosWindow.y, 1.0f);

	D3DVIEWPORT9 vp;
	D3DDEVICE->GetViewport(&vp);
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	const D3DXMATRIXA16 *matProj = CSCREEN->getProjPtr();
	const D3DXMATRIXA16 *matView = CCamera::getMatView();

	D3DXVec3Unproject(&_P03D, &p0, &vp, matProj, matView, &mat);
	D3DXVec3Unproject(&_P13D, &p1, &vp, matProj, matView, &mat);
	_Ray = _P13D - _P03D;
	D3DXVec3Normalize(&_Ray,&_Ray);



}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pOut 
 *  @param[in,out] fY 
 *  @retval void
 */
/***********************************************************************/
void CInputMouse::mousePoint3D(D3DXVECTOR3* pOut,const float fY)
{
  if( _Ray.y <= 0 ) {
      // ����_
      float Lray = D3DXVec3Dot( &_Ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-_P03D), &D3DXVECTOR3(0,1,0) );
      *pOut = _P03D + ( LP0 / Lray)  * _Ray;
   }
   else 
   {
      *pOut = _P13D;
   }
}


//-----------------------------------------------
//	�T�v
//		���͏��擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getPrsMouseButton(short sButton)
{
	return _MouseState.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�����͏��擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getPrevMouseButton(short sButton)
{
	return _MouseStatePrev.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�g���K�[���擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getTrgMouseButton(short sButton)
{
	return _MouseStateTrg.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�����[�X���̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getRlsMouseButton(short sButton)
{
	return _MouseStateRls.rgbButtons[sButton];
}
//-----------------------------------------------
//	�T�v
//		���͏��擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getPrsMouseButton(short sButton)const
{
	return _MouseState.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�����͏��擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getPrevMouseButton(short sButton)const
{
	return _MouseStatePrev.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�g���K�[���擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getTrgMouseButton(short sButton)const
{
	return _MouseStateTrg.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�����[�X���̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sButton 
 *  @retval BYTE 
 */
/***********************************************************************/
BYTE CInputMouse::getRlsMouseButton(short sButton)const
{
	return _MouseStateRls.rgbButtons[sButton];
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPoint()
{
	return _MousePos;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^���ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPrevPoint()
{
	return _MousePosPrev;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPointWindow()
{
	return _MousePosWindow;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPointWindowPrev()
{
	return _MousePosWindowPrev;
}
//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPoint()const
{
	return _MousePos;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^���ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPrevPoint()const
{
	return _MousePosPrev;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPointWindow()const
{
	return _MousePosWindow;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�ʒu�̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval POINT 
 */
/***********************************************************************/
POINT CInputMouse::getPointWindowPrev()const
{
	return _MousePosWindowPrev;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�̈ړ���X�������̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval LONG 
 */
/***********************************************************************/
LONG CInputMouse::getMouselX()
{
	return _MouseState.lX;
}

//-----------------------------------------------
//	�T�v
//		�}�E�X�|�C���^�̈ړ���Y�������̎擾
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval LONG 
 */
/***********************************************************************/
LONG CInputMouse::getMouselY()
{
	return _MouseState.lY;
}


//-----------------------------------------------
//	�T�v
//		�h���b�O�t���O��Ԃ�
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CInputMouse::getDragFlg()
{
	return _DragFlg;
}


//-----------------------------------------------
//	�T�v
//		�_�u���N���b�N���ꂽ�t���O�̎擾
//-----------------------------------------------
//BOOL CInputMouse::getDoubleClickFlg()
//{
//	return _DoubleClickFlg;
//}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval D3DXVECTOR3& 
 */
/***********************************************************************/
D3DXVECTOR3& CInputMouse::getRay()
{
	return _Ray;
}
//EOF