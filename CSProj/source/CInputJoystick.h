/***********************************************************************/
/*! @file  CInputJoystick.h
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
#define AXES_MAX		( 1000)
#define AXES_MIN		(-1000)
#define MAX_JOYSTICKS	(2)
//===================================================================
//	列挙定義
//===================================================================
typedef enum
{
	D_ONE	= 22500,
	D_TWO	= 18000,
	D_THREE	= 13500,
	D_FOUR	= 27000,
	D_FIVE	= -1,
	D_SIX	= 90000,
	D_SEVEN	= 31500,
	D_EIGHT	= 0,
	D_NINE	= 45000,
}ePOV_DIRECT;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext );

//===================================================================
//	クラス定義
//===================================================================
class CInputJoystick
{
	//===========================================
	//	コンストラクタ	
	//===========================================
public:
	CInputJoystick();

	//===========================================
	//	デストラクタ		
	//===========================================
public:
	~CInputJoystick();

	//===========================================
	//	メンバ関数		
	//===========================================
public:
	void init(LPDIRECTINPUT8 pDInput);		///<ジョイスティックの初期化
	void update();		///<ジョイスティックの更新
	void release();
	bool getPrsPadButton(short sJoystickID, short sButton);		///<入力情報の取得
	bool getTrgPadButton(short sJoystickID, short sButton);		///<トリガー入力情報の取得
	bool getRlsPadButton(short sJoystickID, short sButton);		///<リリース情報の取得
	bool getPrsPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<ハットスイッチの入力情報
	bool getTrgPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<ハットスイッチの入力情報
	bool getRlsPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<ハットスイッチの入力情報
	LONG getPrsLX(short JoystickID);
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval short 
	 */
	/***********************************************************************/
	short getSumjoysticks(){return _sSumJoysticks;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval void
	 */
	/***********************************************************************/
	void addSumJoysticks(){_sSumJoysticks++;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval LPDIRECTINPUTDEVICE8* 
	 */
	/***********************************************************************/
	LPDIRECTINPUTDEVICE8* getJoystickDevice(){return _pDIDJoystick;}

protected:
private:

	//===========================================
	//	メンバ変数		
	//===========================================
protected:
private:
	LPDIRECTINPUTDEVICE8 _pDIDJoystick[MAX_JOYSTICKS];	///<ジョイスティックデバイス
	DIDEVCAPS _diDevCaps;
	short _sSumJoysticks;						///<ジョイスティックの登録数
	DIJOYSTATE2 _PrsJoystick[MAX_JOYSTICKS];	///<ジョイスティックの入力情報
	DIJOYSTATE2 _PstJoystick[MAX_JOYSTICKS];	///<ジョイスティックの旧入力情報
	DIJOYSTATE2 _TrgJoystick[MAX_JOYSTICKS];	///<ジョイスティックのトリガー情報
	DIJOYSTATE2 _RlsJoystick[MAX_JOYSTICKS];	///<ジョイスティックのリリース情報
};
//EOF