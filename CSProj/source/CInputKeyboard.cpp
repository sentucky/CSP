/***********************************************************************/
/*! @file  CInputKeyboard.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "CInputKeyboard.h"
#include "CWindow.h"
#include "commonfunc.h"


/////////////////////////////////////////////////////////////////////
//	キーボード関連
/////////////////////////////////////////////////////////////////////
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputKeyboard::CInputKeyboard()
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputKeyboard::~CInputKeyboard()
{
	staticKeyboard();		//入力の非アクティブ
	SAFE_RELEASE(_pDIDKeyboard);
}



//-----------------------------------------------
//	概要
//		キーボード設定の初期化
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDInput 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::init(LPDIRECTINPUT8 pDInput)
{
	//===変数宣言===//
	HRESULT hr;
	HWND hWnd;

	hWnd = WINDOW->getWnd();
	_pDIDKeyboard = NULL;	//キーボードデバイスの初期化
	m_dwFlag_Back_or_Fore = DISCL_FOREGROUND;
	m_dwFlag_Ex_or_NonEx	= DISCL_NONEXCLUSIVE;
	m_dwFlag_WindowsKey	= NULL;

	//---デバイス設定---//
	hr = pDInput->CreateDevice(GUID_SysKeyboard, &_pDIDKeyboard,NULL);								//IDInp8Deviceインターフェースの取得
	if(FAILED(hr) || _pDIDKeyboard == NULL)
	{
		MessageBox(NULL,"デバイス設定エラー","エラーメッセージ",MB_OK);
		return;
	}

	//---フォーマット設定---//
	hr = _pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard );	//データフォーマット指定
	if(FAILED(hr))
	{
		MessageBox(NULL,"フォーマット設定エラー","エラーメッセージ",MB_OK);
		return;
	}

	//---協調レベル設定---//
	hr = _pDIDKeyboard->SetCooperativeLevel(hWnd, m_dwFlag_Back_or_Fore | m_dwFlag_Ex_or_NonEx );	//協調レベル設定
	if(FAILED(hr))
	{
		MessageBox(NULL,"協調レベル設定エラー","エラーメッセージ",MB_OK);
		return;
	}

	//---動作状態設定---//
	activeKeyboard();	//入力アクティブ化

	
	//キーボードステートの初期化
	ZeroMemory(_PrsKeyState,sizeof(_PrsKeyState));
	
}


//-----------------------------------------------
//	概要
//		キーボード有力情報の更新
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::update()
{
	//===変数宣言===//
	HRESULT hr = NULL;
	BYTE PstKeyState[256] = {0,};	//旧入力情報


	//===初期処理===//
	activeKeyboard();		//入力アクティブ化
	for(int i = 0; i < 256; i++)
	{
		PstKeyState[i] = _PrsKeyState[i];		//旧入力情報の取得
	}

	//---入力情報の取得---//
	hr = _pDIDKeyboard->GetDeviceState( sizeof(_PrsKeyState),_PrsKeyState);	//入力情報の取得
	/*	if(FAILED(hr))
	{
	//		MessageBox(NULL,"取得エラー","m_updateKey",MB_OK);
	//		exit(1);
	}*/


	//---トリガー・リリースの取得---//
	for(int i = 0; i < 256; i++)
	{
		_TrgKeyState[i] = ( _PrsKeyState[i] & PstKeyState[i] ) ^ _PrsKeyState[i];	//トリガー情報の取得
		_RlsKeyState[i] = ( _PrsKeyState[i] & PstKeyState[i] ) ^ PstKeyState[i];	//リリース情報の取得
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::release()
{
}
//-----------------------------------------------
//	概要
//		キーボードの入力のアクティブ
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::activeKeyboard()
{
	//===変数宣言===//
	HRESULT hr = NULL;


	//---動作状態設定---//
	if(_pDIDKeyboard)
	{
		hr = _pDIDKeyboard->Acquire();
	}
}


//-----------------------------------------------
//	概要
//		キーボードの入力の非アクティブ
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::staticKeyboard()
{
	//---状態設定---//
	_pDIDKeyboard->Unacquire();
}


//-----------------------------------------------
//	概要
//		プレスキー情報の取得
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sInpKey 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputKeyboard::getPrsKey(short sInpKey)
{
	if(_PrsKeyState[sInpKey] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//-----------------------------------------------
//	概要
//		トリガーキー情報の取得
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sInpKey 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputKeyboard::getTrgKey(short sInpKey)
{
	if(_TrgKeyState[sInpKey] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//-----------------------------------------------
//	概要
//		リリースキー情報の取得
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sInpKey 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputKeyboard::getRlsKey(short sInpKey)
{
	if(_RlsKeyState[sInpKey] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}
