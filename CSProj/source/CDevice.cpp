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
	//===変数宣言===//
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

	
	// レンダリングステートパラメータの設定
    _d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			// カリングを行わない
	_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	_d3dDevice->SetRenderState(D3DRS_LIGHTING , TRUE );					//ライトの無効化
	_d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);				//深度バッファの設定
	_d3dDevice->SetRenderState(D3DRS_AMBIENT , 0x00444444 );			//明りで照らす
//	_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//
	_d3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_d3dDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE);

	// サンプラーステートパラメータの設定
	_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

	// アルファチャンネル有効に
	_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); 

	return TRUE;
}
//EOF