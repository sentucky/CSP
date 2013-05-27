/***********************************************************************/
/*! @file  CInputJoystick.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	
//	�T�v			
//	�����		
//	�X�V����		
/***********************************************************************/
//===================================================================
//	�C���N���[�h�K�[�h
//===================================================================
//===================================================================
//	�C���N���[�h
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#define INITGUID
#include"dInput.h" 
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dInput8.lib")
//===================================================================
//	�}�N����`
//===================================================================
#define AXES_MAX		( 1000)
#define AXES_MIN		(-1000)
#define MAX_JOYSTICKS	(2)
//===================================================================
//	�񋓒�`
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
//	�N���X��`
//===================================================================
class CInputJoystick
{
	//===========================================
	//	�R���X�g���N�^	
	//===========================================
public:
	CInputJoystick();

	//===========================================
	//	�f�X�g���N�^		
	//===========================================
public:
	~CInputJoystick();

	//===========================================
	//	�����o�֐�		
	//===========================================
public:
	void init(LPDIRECTINPUT8 pDInput);		///<�W���C�X�e�B�b�N�̏�����
	void update();		///<�W���C�X�e�B�b�N�̍X�V
	void release();
	bool getPrsPadButton(short sJoystickID, short sButton);		///<���͏��̎擾
	bool getTrgPadButton(short sJoystickID, short sButton);		///<�g���K�[���͏��̎擾
	bool getRlsPadButton(short sJoystickID, short sButton);		///<�����[�X���̎擾
	bool getPrsPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<�n�b�g�X�C�b�`�̓��͏��
	bool getTrgPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<�n�b�g�X�C�b�`�̓��͏��
	bool getRlsPov(short sJoystickID, ePOV_DIRECT ePovDirect);	///<�n�b�g�X�C�b�`�̓��͏��
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
	//	�����o�ϐ�		
	//===========================================
protected:
private:
	LPDIRECTINPUTDEVICE8 _pDIDJoystick[MAX_JOYSTICKS];	///<�W���C�X�e�B�b�N�f�o�C�X
	DIDEVCAPS _diDevCaps;
	short _sSumJoysticks;						///<�W���C�X�e�B�b�N�̓o�^��
	DIJOYSTATE2 _PrsJoystick[MAX_JOYSTICKS];	///<�W���C�X�e�B�b�N�̓��͏��
	DIJOYSTATE2 _PstJoystick[MAX_JOYSTICKS];	///<�W���C�X�e�B�b�N�̋����͏��
	DIJOYSTATE2 _TrgJoystick[MAX_JOYSTICKS];	///<�W���C�X�e�B�b�N�̃g���K�[���
	DIJOYSTATE2 _RlsJoystick[MAX_JOYSTICKS];	///<�W���C�X�e�B�b�N�̃����[�X���
};
//EOF