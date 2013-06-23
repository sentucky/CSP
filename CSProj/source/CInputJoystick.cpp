/***********************************************************************/
/*! @file  CInputJoystick.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CInputJoystick.h"
#include"CWindow.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputJoystick::CInputJoystick()
{
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CInputJoystick::~CInputJoystick()
{
	//�W���C�X�e�B�b�N�̔�A�N�e�B�u
	for(int nLpCnt = 0; nLpCnt < MAX_JOYSTICKS; nLpCnt++)
	{
		if(NULL != _pDIDJoystick[nLpCnt])
		{
			_pDIDJoystick[nLpCnt]->Unacquire();
		}
	}
	//�W���C�X�e�B�b�N�f�o�C�X�̉��
	for(int nLpCnt = 0; nLpCnt < MAX_JOYSTICKS;nLpCnt++)
	{
		if(NULL != _pDIDJoystick[nLpCnt])
		{
			_pDIDJoystick[nLpCnt]->Release();
		}
	}
}
//-----------------------------------------------
//	�T�v
//		�W���C�X�e�B�b�N�֘A�̏�����
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDInput 
 *  @retval void
 */
/***********************************************************************/
void CInputJoystick::init(LPDIRECTINPUT8 pDInput)
{	
	//---�ϐ��錾---//
	HRESULT hr;
	HWND hWnd;

	hWnd = WINDOW->getWnd();


	//---�W���C�X�e�B�b�N�f�o�C�X�̃|�C���^�擾---//
	hr = pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr))
	{
#ifdef _DEBUG
		//		MessageBox(NULL, "�W���C�X�e�B�b�N","01",MB_OK);
#endif
	}

	_sSumJoysticks = 0;

	for(int nLpCnt = 0; nLpCnt < MAX_JOYSTICKS; nLpCnt++)	//�擾�������W���C�X�e�B�b�N�̐��������[�v����
	{

		//	�f�o�C�X��������Ȃ����̓X�L�b�v����
		if(NULL == _pDIDJoystick[nLpCnt])
			return;


		hr = _pDIDJoystick[nLpCnt]->SetDataFormat( &c_dfDIJoystick);
		if(FAILED(hr))
		{
#ifdef _DEBUG
			MessageBox(NULL, "�W���C�X�e�B�b�N","02",MB_OK);
#endif
		}

		hr = _pDIDJoystick[nLpCnt]->SetCooperativeLevel( hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if(FAILED(hr))
		{
#ifdef _DEBUG
			MessageBox(NULL, "�W���C�X�e�B�b�N","03",MB_OK);
#endif
		}

		_diDevCaps.dwSize = sizeof(DIDEVCAPS);
		hr = _pDIDJoystick[nLpCnt]->GetCapabilities( &_diDevCaps);
		if(FAILED(hr))
		{
#ifdef _DEBUG
			MessageBox(NULL, "�W���C�X�e�B�b�N","04",MB_OK);
#endif
		}

		hr = _pDIDJoystick[nLpCnt]->EnumObjects( EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
		if(FAILED(hr))
		{
#ifdef _DEBUG
			MessageBox(NULL, "�W���C�X�e�B�b�N","05",MB_OK);
#endif
		}

		hr = _pDIDJoystick[nLpCnt]->Poll();
		if(FAILED(hr))
		{
			hr = _pDIDJoystick[nLpCnt]->Acquire();
			while( hr == DIERR_INPUTLOST )
			{
				hr = _pDIDJoystick[nLpCnt]->Acquire();
			}
		}

		_sSumJoysticks += 1;

		if(FAILED(hr))
		{
#ifdef _DEBUG
			MessageBox(NULL, "�W���C�X�e�B�b�N","08",MB_OK);
#endif
		}
		//�W���C�X�e�B�b�N�X�e�[�g�̏�����
		for(int nLpCnt = 0; nLpCnt < MAX_JOYSTICKS; nLpCnt++)
		{
			for(int nButtonID = 0; nButtonID < 32; nButtonID++)
			{//�{�^��������
				_PrsJoystick[nLpCnt].rgbButtons[nButtonID] = 0;
			}
			for(int nPovID = 0; nPovID < 4; nPovID++)
			{//�n�b�g�X�C�b�`������
				_PrsJoystick[nLpCnt].rgdwPOV[nPovID] = -1;
			}
		}

		ZeroMemory(_pDIDJoystick,sizeof(_pDIDJoystick));
		_sSumJoysticks = 0;		//�W���C�X�e�B�b�N���v���̏�����
	}
}
//-----------------------------------------------
//	�T�v
//		�W���C�X�e�B�b�N�̍X�V
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputJoystick::update()
{
	HRESULT hr;

	for(int nLpCnt = 0; nLpCnt < MAX_JOYSTICKS; nLpCnt++)
	{
		_PstJoystick[nLpCnt] = _PrsJoystick[nLpCnt];

		if(_pDIDJoystick[nLpCnt] == NULL)
		{
			return;
		}

		hr = _pDIDJoystick[nLpCnt]->Poll();
		if(FAILED(hr))
		{	
#ifdef _DEBUG
			//			MessageBox(NULL, "�W���C�X�e�B�b�N","06",MB_OK);
#endif
			hr = _pDIDJoystick[nLpCnt]->Acquire();
			while(hr == DIERR_INPUTLOST )
			{
				hr = _pDIDJoystick[nLpCnt]->Acquire();
			}
		}
		hr = _pDIDJoystick[nLpCnt]->GetDeviceState( sizeof(DIJOYSTATE), &(_PrsJoystick[nLpCnt]));
#ifdef _DEBUG
		if(FAILED(hr))
		{
		}
#endif

		for(int nLpCntButton = 0; nLpCntButton < 32; nLpCntButton++)
		{//�{�^���̃g���K�[�����[�X���̎擾
			_TrgJoystick[nLpCnt].rgbButtons[nLpCntButton] = ( _PrsJoystick[nLpCnt].rgbButtons[nLpCntButton] & _PstJoystick[nLpCnt].rgbButtons[nLpCntButton] ) ^ _PrsJoystick[nLpCnt].rgbButtons[nLpCntButton];
			_RlsJoystick[nLpCnt].rgbButtons[nLpCntButton] = ( _PrsJoystick[nLpCnt].rgbButtons[nLpCntButton] & _PstJoystick[nLpCnt].rgbButtons[nLpCntButton] ) ^ _PstJoystick[nLpCnt].rgbButtons[nLpCntButton];
		}

		for(int nLpCntPov = 0; nLpCntPov < 4; nLpCntPov++)
		{//�n�b�g�X�C�b�`�̃g���K�[�����[�X���̎擾
			_TrgJoystick[nLpCnt].rgdwPOV[nLpCntPov] = ( _PrsJoystick[nLpCnt].rgdwPOV[nLpCntPov] & _PstJoystick[nLpCnt].rgdwPOV[nLpCntPov] ) ^ _PrsJoystick[nLpCnt].rgdwPOV[nLpCntPov];
			_RlsJoystick[nLpCnt].rgdwPOV[nLpCntPov] = ( _PrsJoystick[nLpCnt].rgdwPOV[nLpCntPov] & _PstJoystick[nLpCnt].rgdwPOV[nLpCntPov] ) ^ _PstJoystick[nLpCnt].rgdwPOV[nLpCntPov];
		}
	}
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputJoystick::release()
{
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] sButton 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getPrsPadButton(short sJoystickID,short sButton)
{
	if(_PrsJoystick[sJoystickID].rgbButtons[sButton] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] sButton 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getTrgPadButton(short sJoystickID,short sButton)
{
	if(_TrgJoystick[sJoystickID].rgbButtons[sButton] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] sButton 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getRlsPadButton(short sJoystickID,short sButton)
{
	if(_RlsJoystick[sJoystickID].rgbButtons[sButton] & 0x0080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] ePovDirect 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getPrsPov(short sJoystickID, ePOV_DIRECT ePovDirect)		//�n�b�g�X�C�b�`�̓��͏��
{
	if(_PrsJoystick[sJoystickID].rgdwPOV[0] == ePovDirect)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] ePovDirect 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getTrgPov(short sJoystickID, ePOV_DIRECT ePovDirect)		//�n�b�g�X�C�b�`�̓��͏��
{
	if(_TrgJoystick[sJoystickID].rgdwPOV[0] == ePovDirect)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @param[in,out] ePovDirect 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool CInputJoystick::getRlsPov(short sJoystickID, ePOV_DIRECT ePovDirect)		//�n�b�g�X�C�b�`�̓��͏��
{
	if(_RlsJoystick[sJoystickID].rgdwPOV[0] == ePovDirect)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] sJoystickID 
 *  @retval LONG 
 */
/***********************************************************************/
LONG CInputJoystick::getPrsLX(short sJoystickID)
{
	return _PrsJoystick[sJoystickID].lX;
}
//EOF