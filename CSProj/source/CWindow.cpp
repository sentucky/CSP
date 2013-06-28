/***********************************************************************/
/*! @file  CWindow.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CWindow.h"
//-----------------------------------------------------------------
//    Window Proc.
//-----------------------------------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hWnd 
 *  @param[in,out] msg 
 *  @param[in,out] wParam 
 *  @param[in,out] lp 
 *  @retval LRESULT CALLBACK 
 */
/***********************************************************************/
LRESULT CALLBACK WndProc( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lp )
{
	switch( msg ){
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_SETCURSOR:
	while(ShowCursor(FALSE) < 0 )
	break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			SendMessage(  // 1 �܂��͕����̃E�B���h�E�ցA�w�肳�ꂽ���b�Z�[�W�𑗐M���܂��B
				hWnd,       // ���M��E�B���h�E�̃n���h��
				WM_DESTROY,   // ���b�Z�[�W
				0,          // ���b�Z�[�W�̍ŏ��̃p�����[�^
				0);         // ���b�Z�[�W�� 2 �Ԗڂ̃p�����[�^
			break;
		}
		default:
			return DefWindowProc( hWnd , msg , wParam , lp );
	}
	
	return 0;
}

//-------------------------------------
//	�T�v
//		����������
//	����
//		HINSTANCE
//		int
//	�߂�l
//		BOOL	��������������
//-------------------------------------
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hInst 
 *  @param[in,out] nCmdShow 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CWindow::init(HINSTANCE hInst, int nCmdShow)
{
	WNDCLASS wc;
	_hInst = hInst;
	char szClassName[] = "Tank-1";
	
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance     = _hInst;
	wc.hCursor       = LoadCursor( NULL , IDC_ARROW );
	wc.hIcon         = LoadIcon( NULL , IDI_APPLICATION );
	wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszClassName = szClassName;
	wc.lpszMenuName  = NULL;
	wc.lpfnWndProc   = WndProc;
	wc.cbWndExtra    = 0;
	wc.cbClsExtra    = 0;

	if ( !RegisterClass( &wc ) ) return FALSE;
	
	_hWnd = CreateWindow( 
		szClassName,
		szClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		_hInst,
		NULL
		);
	if ( !_hWnd ) return FALSE;
	
	ShowWindow( _hWnd , nCmdShow );
	UpdateWindow( _hWnd );

	return TRUE;	//����������
}

