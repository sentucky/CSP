/***********************************************************************/
/*! @file  CInputCommon.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//===================================================================
//	�C���N���[�h�K�[�h
//===================================================================
#pragma once
//===================================================================
//	�C���N���[�h
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#include"CSingleton.h"
#include"CInputJoystick.h"
#include"CInputKeyboard.h"
#include"CInputMouse.h"
#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#define INITGUID
#include"dinput.h" 
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"dinput8.lib")

//===================================================================
//	�}�N����`
//===================================================================
#define INPUTCOMMON		(CInputCommon::getInst())
#define KEYBOARD	(CInputCommon::getInst()->getKeyboard())
#define JOYSTICK	(CInputCommon::getInst()->getJoystick())
#define MOUSE		(CInputCommon::getInst()->getMouse())
#define MOUSEPTR	(CInputCommon::getInst()->getMousePtr())

//===================================================================
//	�񋓒�`
//===================================================================

//===================================================================
//	�\���̒�`
//===================================================================

//===================================================================
//	�N���X��`
//===================================================================
class CInputCommon:public CSingleton<CInputCommon>
{
	friend class CSingleton<CInputCommon>;
private:
	//===�R���X�g���N�^�E�f�X�g���N�^===//
	CInputCommon();			///<�R���X�g���N�^
	~CInputCommon();		///<�f�X�g���N�^

public:
	//===�����o�֐�===//
	//...���ʍ���
	void init();	///<������
	void update();	///<�X�V
	void release();	///<���

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
	//===�����o�ϐ�===//
	LPDIRECTINPUT8	_pDInput;			///<���̓C���^�[�t�F�[�X
	CInputJoystick*	_pJoystick;			///<�W���C�X�e�B�b�N
	CInputKeyboard*	_pKeyboard;			///<�L�[�{�[�h
	CInputMouse*	_pMouse;			///<�}�E�X
};
//EOF