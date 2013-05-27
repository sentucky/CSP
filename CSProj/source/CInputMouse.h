/***********************************************************************/
/*! @file  CInputMouse.h
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
#include"common.h"
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
class CInputMouse
{
	//===========================================
	//	コンストラクタ	
	//===========================================
public:
	CInputMouse();

	//===========================================
	//	デストラクタ		
	//===========================================
public:
	~CInputMouse();

	//===========================================
	//	メンバ関数		
	//===========================================
public:
	void init(LPDIRECTINPUT8 pDInput);
	void update();
	void release();
	void calcMouseRay();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval LPDIRECTINPUTDEVICE8 
	 */
	/***********************************************************************/
	LPDIRECTINPUTDEVICE8 getDiDMouse(){return _pDIDMouse;}	///<マウス
	BYTE getPrsMouseButton(short sButton);
	BYTE getPrevMouseButton(short sButton);
	BYTE getTrgMouseButton(short sButton);
	BYTE getRlsMouseButton(short sButton);
	BYTE getPrsMouseButton(short sButton)const;
	BYTE getPrevMouseButton(short sButton)const;
	BYTE getTrgMouseButton(short sButton)const;
	BYTE getRlsMouseButton(short sButton)const;
	POINT getPrevPoint();
	POINT getPoint();
	POINT getPointWindow();
	POINT getPointWindowPrev();
	POINT getPrevPoint()const;
	POINT getPoint()const;
	POINT getPointWindow()const;
	POINT getPointWindowPrev()const;
	LONG getMouselX();
	LONG getMouselY();
	BOOL getDragFlg();
	D3DXVECTOR3& getRay();	///<	3D座標の取得
	void mousePoint3D(D3DXVECTOR3* pOut,const float fY);
protected:
private:

	//===========================================
	//	メンバ変数		
	//===========================================
protected:
private:
	LPDIRECTINPUTDEVICE8 _pDIDMouse;	///<マウス
	DIMOUSESTATE2	_MouseState;		///< マウス情報配列
	DIMOUSESTATE2	_MouseStatePrev;	///< 直前マウス情報配列
	DIMOUSESTATE2	_MouseStateTrg;		///< トリガーマウス情報配列
	DIMOUSESTATE2	_MouseStateRls;		///< リリースマウス情報配列
	POINT			_MousePos;			///< マウス座標
	POINT			_MousePosPrev;		///< マウス座標
	POINT			_MousePosWindow;	///< マウス座標
	POINT			_MousePosWindowPrev;///< マウス座標
	BOOL			_DragFlg;			///< ドラッグフラグ
	D3DXVECTOR3		_Ray;			///< マウスの三次元空間レイ
	D3DXVECTOR3		_P13D;			///< マウスの三次元空間レイ
	D3DXVECTOR3		_P03D;			///< マウスの三次元空間レイ
};
//EOF