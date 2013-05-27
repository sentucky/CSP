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
//	�L�[�{�[�h�֘A
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
	staticKeyboard();		//���͂̔�A�N�e�B�u
	SAFE_RELEASE(_pDIDKeyboard);
}



//-----------------------------------------------
//	�T�v
//		�L�[�{�[�h�ݒ�̏�����
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
	//===�ϐ��錾===//
	HRESULT hr;
	HWND hWnd;

	hWnd = WINDOW->getWnd();
	_pDIDKeyboard = NULL;	//�L�[�{�[�h�f�o�C�X�̏�����
	m_dwFlag_Back_or_Fore = DISCL_FOREGROUND;
	m_dwFlag_Ex_or_NonEx	= DISCL_NONEXCLUSIVE;
	m_dwFlag_WindowsKey	= NULL;

	//---�f�o�C�X�ݒ�---//
	hr = pDInput->CreateDevice(GUID_SysKeyboard, &_pDIDKeyboard,NULL);								//IDInp8Device�C���^�[�t�F�[�X�̎擾
	if(FAILED(hr) || _pDIDKeyboard == NULL)
	{
		MessageBox(NULL,"�f�o�C�X�ݒ�G���[","�G���[���b�Z�[�W",MB_OK);
		return;
	}

	//---�t�H�[�}�b�g�ݒ�---//
	hr = _pDIDKeyboard->SetDataFormat( &c_dfDIKeyboard );	//�f�[�^�t�H�[�}�b�g�w��
	if(FAILED(hr))
	{
		MessageBox(NULL,"�t�H�[�}�b�g�ݒ�G���[","�G���[���b�Z�[�W",MB_OK);
		return;
	}

	//---�������x���ݒ�---//
	hr = _pDIDKeyboard->SetCooperativeLevel(hWnd, m_dwFlag_Back_or_Fore | m_dwFlag_Ex_or_NonEx );	//�������x���ݒ�
	if(FAILED(hr))
	{
		MessageBox(NULL,"�������x���ݒ�G���[","�G���[���b�Z�[�W",MB_OK);
		return;
	}

	//---�����Ԑݒ�---//
	activeKeyboard();	//���̓A�N�e�B�u��

	
	//�L�[�{�[�h�X�e�[�g�̏�����
	ZeroMemory(_PrsKeyState,sizeof(_PrsKeyState));
	
}


//-----------------------------------------------
//	�T�v
//		�L�[�{�[�h�L�͏��̍X�V
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::update()
{
	//===�ϐ��錾===//
	HRESULT hr = NULL;
	BYTE PstKeyState[256] = {0,};	//�����͏��


	//===��������===//
	activeKeyboard();		//���̓A�N�e�B�u��
	for(int i = 0; i < 256; i++)
	{
		PstKeyState[i] = _PrsKeyState[i];		//�����͏��̎擾
	}

	//---���͏��̎擾---//
	hr = _pDIDKeyboard->GetDeviceState( sizeof(_PrsKeyState),_PrsKeyState);	//���͏��̎擾
	/*	if(FAILED(hr))
	{
	//		MessageBox(NULL,"�擾�G���[","m_updateKey",MB_OK);
	//		exit(1);
	}*/


	//---�g���K�[�E�����[�X�̎擾---//
	for(int i = 0; i < 256; i++)
	{
		_TrgKeyState[i] = ( _PrsKeyState[i] & PstKeyState[i] ) ^ _PrsKeyState[i];	//�g���K�[���̎擾
		_RlsKeyState[i] = ( _PrsKeyState[i] & PstKeyState[i] ) ^ PstKeyState[i];	//�����[�X���̎擾
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
//	�T�v
//		�L�[�{�[�h�̓��͂̃A�N�e�B�u
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::activeKeyboard()
{
	//===�ϐ��錾===//
	HRESULT hr = NULL;


	//---�����Ԑݒ�---//
	if(_pDIDKeyboard)
	{
		hr = _pDIDKeyboard->Acquire();
	}
}


//-----------------------------------------------
//	�T�v
//		�L�[�{�[�h�̓��͂̔�A�N�e�B�u
//-----------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CInputKeyboard::staticKeyboard()
{
	//---��Ԑݒ�---//
	_pDIDKeyboard->Unacquire();
}


//-----------------------------------------------
//	�T�v
//		�v���X�L�[���̎擾
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
//	�T�v
//		�g���K�[�L�[���̎擾
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
//	�T�v
//		�����[�X�L�[���̎擾
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
