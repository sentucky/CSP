/***********************************************************************/
/*! @file  CInputCommon.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	CInput.cpp
//	概要			入力クラス
//	制作者		川原佑介
//	更新履歴		
/***********************************************************************/
//===================================================================
//	インクルード
//===================================================================
#include"CInputCommon.h"
#include"CWindow.h"

//===================================================================
//	マクロ定義
//===================================================================

//===================================================================
//	列挙定義
//===================================================================

//===================================================================
//	グローバル変数
//===================================================================

//===================================================================
//	プロトタイプ宣言
//===================================================================


//===================================================================
//	関数定義
//===================================================================
//-----------------------------------------------
//	コンストラクタ
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputCommon::CInputCommon()
{
	init();
}


//-----------------------------------------------
//	デストラクタ
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputCommon::~CInputCommon()
{
	//入力インタフェースの解放
	SAFE_RELEASE(_pDInput);
	SAFE_DELETE(_pJoystick);
	SAFE_DELETE(_pKeyboard);	
	SAFE_DELETE(_pMouse);	
}


//-----------------------------------------------
//	概要
//		入力の初期設定
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::init()
{
	//===変数宣言===//
	HRESULT hr;
	HINSTANCE hInst;
	HWND hWnd;
	
	//===初期処理===//
	_pDInput = NULL;		//インターフェースの初期化
	_pJoystick = NULL;		//キーボード設定の初期化
	_pKeyboard = NULL;		//マウスの初期化
	_pMouse	   = NULL;		//ジョイスティックの初期化
	hInst = WINDOW->getHInst();
	hWnd = WINDOW->getWnd();


	//===DInputのオブジェクト作成===//
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&_pDInput, NULL);	//IDInp8インターフェースの取得

	if(FAILED(hr))
	{
		MessageBox(NULL,"インタフェース設定エラー","エラーメッセージ",MB_OK);
		return;
	}

}

//-----------------------------------------------
//	概要
//		キーボードの作成
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::createKeyboard()
{
	if(_pKeyboard == NULL)
	{
		_pKeyboard = new CInputKeyboard;
		_pKeyboard->init(_pDInput);
	}
}


//-----------------------------------------------
//	概要
//		マウスの作成
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::createMouse()
{
	if(_pMouse == NULL)
	{
		_pMouse = new CInputMouse;
		_pMouse->init(_pDInput);
	}
}

//-----------------------------------------------
//	概要
//		ジョイスティックの作成
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::createJoystick()
{
	if(_pJoystick == NULL)
	{
		_pJoystick = new CInputJoystick;
		_pJoystick->init(_pDInput);
	}
}

//-----------------------------------------------
//	概要
//		更新処理
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::update()
{
	if(_pKeyboard != NULL)
	{//キーボードの実態があれば処理
		_pKeyboard->update();
	}
	if(_pMouse != NULL)
	{//マウスの実態があれば処理
		_pMouse->update();	
	}
	if(_pJoystick != NULL)
	{//ジョイスティックの実態があれば処理
		_pJoystick->update();
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pdidInstance 
 *  @param[in,out] pContext 
 *  @retval BOOL CALLBACK 
 */
/***********************************************************************/
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	hr = INPUTCOMMON->getInterface()->CreateDevice( pdidInstance->guidInstance, &INPUTCOMMON->getJoystick().getJoystickDevice()[INPUTCOMMON->getJoystick().getSumjoysticks()], NULL);

	INPUTCOMMON->getJoystick().addSumJoysticks();
	if(FAILED(hr))
		return DIENUM_CONTINUE;

	if(MAX_JOYSTICKS == INPUTCOMMON->getJoystick().getSumjoysticks())
		return DIENUM_STOP;
	else
		return DIENUM_CONTINUE;

}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pdidoi 
 *  @param[in,out] pContext 
 *  @retval BOOL CALLBACK 
 */
/***********************************************************************/
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext )
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize       = sizeof( DIPROPRANGE );
	diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.diph.dwObj        = pdidoi->dwType;
	diprg.lMin              = AXES_MAX;
	diprg.lMax              = AXES_MIN;
	hr = INPUTCOMMON->getJoystick().getJoystickDevice()[INPUTCOMMON->getJoystick().getSumjoysticks()]->SetProperty( DIPROP_RANGE , &diprg.diph );

	if ( FAILED( hr ) ) return DIENUM_STOP;

	return DIENUM_CONTINUE;
}
