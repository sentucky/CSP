/***********************************************************************/
/*! @file  CDevice.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CDevice.h"
#include"CWindow.h"
#include"commonfunc.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CDevice::CDevice()
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CDevice::~CDevice()
{
	SAFE_RELEASE(_d3d9);
	SAFE_RELEASE(_d3dDevice);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CDevice::init()
{
	//===�ϐ��錾===//
	D3DPRESENT_PARAMETERS d3dpp;
	HRESULT hr;
	HWND hWnd = WINDOW->getWnd();

	if ( NULL == ( _d3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
		MessageBox( hWnd , "Can't create Direct3D." , "Error" , MB_OK );
		return FALSE;
	}
	ZeroMemory( &d3dpp , sizeof( d3dpp ) );
	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount		= 1;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	hr = _d3d9->CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , hWnd ,
	                           D3DCREATE_SOFTWARE_VERTEXPROCESSING ,
	                           &d3dpp , &_d3dDevice );
	if ( FAILED( hr ) )
	{
		MessageBox( hWnd , "Can't create device." , "Error" , MB_OK );
		return FALSE;
	}

	
	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Z�o�b�t�@���g�p
	_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��
	_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	_d3dDevice->SetRenderState(D3DRS_LIGHTING , TRUE );				//���C�g��yuu����
	_d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);				//�[�x�o�b�t�@�̐ݒ�
	_d3dDevice->SetRenderState(D3DRS_AMBIENT , 0x00444444 );			//����ŏƂ炷
	_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	_d3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_d3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

	// �A���t�@�`�����l���L����
	_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); 
	
	return TRUE;
}
//EOF