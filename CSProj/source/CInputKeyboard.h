/***********************************************************************/
/*! @file  CINPUTKeyboard.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	
//	概要			
//	制作者		
//	更新履歴		
/***********************************************************************/
//===================================================================
//	インクルードガード
//===================================================================
//===================================================================
//	インクルード
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#define INITGUID
#include"dInput.h" 
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dInput8.lib")
//===================================================================
//	マクロ定義
//===================================================================
//===================================================================
//	列挙定義
//===================================================================
//===================================================================
//	クラス定義
//===================================================================
class CInputKeyboard
{
	//===========================================
	//	コンストラクタ	
	//===========================================
public:
	CInputKeyboard();

	//===========================================
	//	デストラクタ		
	//===========================================
public:
	~CInputKeyboard();

	//===========================================
	//	メンバ関数		
	//===========================================
public:
	void init(LPDIRECTINPUT8 pDInput);		///<初期化
	void update();					///<入力情報の更新
	void release();					///<解放
	void activeKeyboard();			///<入力のアクティブ
	void staticKeyboard();			///<入力の非アクティブ
	bool getPrsKey(short sInpKey);	///<プレスキー情報の取得
	bool getTrgKey(short sInpKey);	///<トリガーキー情報の取得
	bool getRlsKey(short sInpKey);	///<リリースキー情報の取得
protected:
private:
	//===========================================
	//	メンバ変数		
	//===========================================
protected:
private:
	//...キーボード
	BYTE _PrsKeyState[256];				///<プレスキー入力情報
	BYTE _TrgKeyState[256];				///<トリガーキー入力情報
	BYTE _RlsKeyState[256];				///<リリースキー入力情報
	LPDIRECTINPUTDEVICE8 _pDIDKeyboard;	///<キーボードデバイス
	DWORD m_dwFlag_Back_or_Fore;
	DWORD m_dwFlag_Ex_or_NonEx;
	DWORD m_dwFlag_WindowsKey;
};


//EOF