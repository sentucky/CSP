/***********************************************************************/
/*! @file  CInputCommon.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	CInput.cpp
//	�T�v			���̓N���X
//	�����		�쌴�C��
//	�X�V����		
/***********************************************************************/
//===================================================================
//	�C���N���[�h
//===================================================================
#include"CInputCommon.h"
#include"CWindow.h"

//===================================================================
//	�}�N����`
//===================================================================

//===================================================================
//	�񋓒�`
//===================================================================

//===================================================================
//	�O���[�o���ϐ�
//===================================================================

//===================================================================
//	�v���g�^�C�v�錾
//===================================================================


//===================================================================
//	�֐���`
//===================================================================
//-----------------------------------------------
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputCommon::~CInputCommon()
{
	//���̓C���^�t�F�[�X�̉��
	SAFE_RELEASE(_pDInput);
	SAFE_DELETE(_pJoystick);
	SAFE_DELETE(_pKeyboard);	
	SAFE_DELETE(_pMouse);	
}


//-----------------------------------------------
//	�T�v
//		���͂̏����ݒ�
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputCommon::init()
{
	//===�ϐ��錾===//
	HRESULT hr;
	HINSTANCE hInst;
	HWND hWnd;
	
	//===��������===//
	_pDInput = NULL;		//�C���^�[�t�F�[�X�̏�����
	_pJoystick = NULL;		//�L�[�{�[�h�ݒ�̏�����
	_pKeyboard = NULL;		//�}�E�X�̏�����
	_pMouse	   = NULL;		//�W���C�X�e�B�b�N�̏�����
	hInst = WINDOW->getHInst();
	hWnd = WINDOW->getWnd();


	//===DInput�̃I�u�W�F�N�g�쐬===//
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&_pDInput, NULL);	//IDInp8�C���^�[�t�F�[�X�̎擾

	if(FAILED(hr))
	{
		MessageBox(NULL,"�C���^�t�F�[�X�ݒ�G���[","�G���[���b�Z�[�W",MB_OK);
		return;
	}

}

//-----------------------------------------------
//	�T�v
//		�L�[�{�[�h�̍쐬
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
//	�T�v
//		�}�E�X�̍쐬
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
//	�T�v
//		�W���C�X�e�B�b�N�̍쐬
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
//	�T�v
//		�X�V����
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
	{//�L�[�{�[�h�̎��Ԃ�����Ώ���
		_pKeyboard->update();
	}
	if(_pMouse != NULL)
	{//�}�E�X�̎��Ԃ�����Ώ���
		_pMouse->update();	
	}
	if(_pJoystick != NULL)
	{//�W���C�X�e�B�b�N�̎��Ԃ�����Ώ���
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
