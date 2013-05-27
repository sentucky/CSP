/***********************************************************************/
/*! @file  CInputCommon.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//===================================================================
//	インクルードガード
//===================================================================
#pragma once
//===================================================================
//	インクルード
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#include"CSingleton.h"
#include"CInputJoystick.h"
#include"CInputKeyboard.h"
#include"CInputMouse.h"
#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#define INITGUID
#include"dinput.h" 
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dinput8.lib")

//===================================================================
//	マクロ定義
//===================================================================
#define INPUTCOMMON		(CInputCommon::getInst())
#define KEYBOARD	(CInputCommon::getInst()->getKeyboard())
#define JOYSTICK	(CInputCommon::getInst()->getJoystick())
#define MOUSE		(CInputCommon::getInst()->getMouse())
#define MOUSEPTR	(CInputCommon::getInst()->getMousePtr())

//===================================================================
//	列挙定義
//===================================================================

//===================================================================
//	構造体定義
//===================================================================

//===================================================================
//	クラス定義
//===================================================================
class CInputCommon:public CSingleton<CInputCommon>
{
	friend class CSingleton<CInputCommon>;
private:
	//===コンストラクタ・デストラクタ===//
	CInputCommon();			///<コンストラクタ
	~CInputCommon();		///<デストラクタ

public:
	//===メンバ関数===//
	//...共通項目
	void init();	///<初期化
	void update();	///<更新
	void release();	///<解放

	void createKeyboard();
	
	void createMouse();
	
	void createJoystick();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval CInputJoystick& 
	 */
	/***********************************************************************/
	CInputJoystick& getJoystick(){return *_pJoystick;}	
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval CInputKeyboard& 
	 */
	/***********************************************************************/
	CInputKeyboard& getKeyboard(){return *_pKeyboard;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval CInputMouse* 
	 */
	/***********************************************************************/
	CInputMouse*	getMousePtr(){return _pMouse;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval CInputMouse& 
	 */
	/***********************************************************************/
	CInputMouse&	getMouse(){return *_pMouse;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval LPDIRECTINPUT8 
	 */
	/***********************************************************************/
	LPDIRECTINPUT8  getInterface(){return _pDInput;}

private:
	//===メンバ変数===//
	LPDIRECTINPUT8	_pDInput;			///<入力インターフェース
	CInputJoystick*	_pJoystick;			///<ジョイスティック
	CInputKeyboard*	_pKeyboard;			///<キーボード
	CInputMouse*	_pMouse;			///<マウス
};
//EOF