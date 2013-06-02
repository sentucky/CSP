/***********************************************************************/
/*! @file  CInputMouse.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	：CInputMouse.h
//	概要			：マウス入力情報
//	制作者		：川原佑介
//	更新履歴		：
/***********************************************************************/

#include"CInputMouse.h"
#include"common.h"
#include"CWindow.h"
#include"CDevice.h"
#include"CCamera.h"
#include"CScreen.h"

//===================================================================
//	コンストラクタ
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
//	デストラクタ
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
//	メンバ関数定義
//===================================================================
//-----------------------------------------------
//	概要
//		マウスの初期化
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
	//	変数宣言
	HRESULT Hr;
	DIPROPDWORD dipDw;
	
	////////////////////////////
	//	初期処理
	ZeroMemory(&_MousePos,sizeof(POINT));		//マウス座標の初期化
	ZeroMemory(&_MousePosPrev,sizeof(POINT));	//マウス旧座標の初期化
	dipDw.diph.dwSize = sizeof(DIPROPDWORD);
	dipDw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipDw.diph.dwObj = 0;
	dipDw.diph.dwHow = DIPH_DEVICE;
	dipDw.dwData = DIPROPAXISMODE_REL; // 相対座標モード
//	dipDw.dwData = DIPROPAXISMODE_ABS; // 絶対座標モード

	memset(&_MousePosWindowPrev,NULL,sizeof(_MousePosWindowPrev));
	memset(&_MousePosWindow,NULL,sizeof(_MousePosWindowPrev));
	
	//デバイスオブジェクトの作成
	pDInput->CreateDevice( GUID_SysMouse, &_pDIDMouse, NULL);

	
	//データフォーマットを設定
	Hr = _pDIDMouse->SetDataFormat( &c_dfDIMouse2);

	
	//強調モードを設定
	Hr = _pDIDMouse->SetCooperativeLevel(WINDOW->getWnd(),DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	//マウスの座標モード設定
	_pDIDMouse->SetProperty(DIPROP_AXISMODE,&dipDw.diph);

	//マウスの有効化
	_pDIDMouse->Acquire();
}

//-----------------------------------------------
//	概要
//		マウスの更新
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
	//	変数宣言
	HRESULT hr;


	/////////////////////////
	//	初期処理
	_MouseStatePrev = _MouseState;		//旧入力情報の取得
	

	////////////////////////////
	//	更新処理
	hr = _pDIDMouse->GetDeviceState(sizeof(_MouseState),&_MouseState);	//デバイスから入力情報を取得
	

	//...リリース・トリガーの取得
	for(int nCnt = 0; nCnt < 8; nCnt++)
	{
		_MouseStateTrg.rgbButtons[nCnt] = ( _MouseState.rgbButtons[nCnt] ^ _MouseStatePrev.rgbButtons[nCnt]) & _MouseState.rgbButtons[nCnt];
		_MouseStateRls.rgbButtons[nCnt] = ( _MouseState.rgbButtons[nCnt] ^ _MouseStatePrev.rgbButtons[nCnt]) & _MouseStatePrev.rgbButtons[nCnt];
	}

	_MousePosPrev.x = _MousePos.x;
	_MousePosPrev.y = _MousePos.y;
	_MousePos.x += _MouseState.lX;	//マウスポインタのX軸総移動量
	_MousePos.y += _MouseState.lY;	//マウスポインタのY軸総移動量


	_MousePosWindowPrev = _MousePosWindow;
	GetCursorPos(&_MousePosWindow);
	ScreenToClient(WINDOW->getWnd(),&_MousePosWindow);

	//マウスカーソルの可視化
	ShowCursor(TRUE);

	if( _MousePos.x != _MousePosPrev.x || _MousePos.y != _MousePosPrev.y)
		_DragFlg = TRUE;
	else
		_DragFlg = FALSE;

	calcMouseRay();

	//...非アクティブ時の処理
	if(FAILED(hr))
	{
		_pDIDMouse->Acquire();
	}
}

//-----------------------------------------------
//	概要
//		マウスの解放
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
      // 床交点
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
//	概要
//		入力情報取得
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
//	概要
//		旧入力情報取得
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
//	概要
//		トリガー情報取得
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
//	概要
//		リリース情報の取得
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
//	概要
//		入力情報取得
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
//	概要
//		旧入力情報取得
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
//	概要
//		トリガー情報取得
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
//	概要
//		リリース情報の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタ旧位置の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタ旧位置の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタ位置の取得
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
//	概要
//		マウスポインタの移動量X軸方向の取得
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
//	概要
//		マウスポインタの移動量Y軸方向の取得
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
//	概要
//		ドラッグフラグを返す
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
//	概要
//		ダブルクリックされたフラグの取得
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