/***********************************************************************/
/*! @file  main.cpp
 *  @brief エントリーポイント
 *  
 *  @author 川原佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//    インクルード
/***********************************************************************/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include"common.h"
//----機能系
#include"CWindow.h"			//ウィンドウクラスヘッダ
#include"Game.h"
#include"CTime.h"			//タイムクラス


#pragma comment( lib , "d3d9.lib" )
#pragma comment( lib , "d3dx9.lib")
#pragma comment( lib , "winmm.lib")



/***********************************************************************/
//    プロトタイプ宣言
/***********************************************************************/

void	release();




/***********************************************************************/
//    メイン関数
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] hInst 
 *  @param[in] hPrevinst 
 *  @param[in] nCmdLine 
 *  @param[in] nCmdShow 
 *  @retval int WINAPI 
 */
/***********************************************************************/
int WINAPI WinMain( HINSTANCE hInst , HINSTANCE hPrevinst , LPSTR nCmdLine , int nCmdShow )
{
#ifdef _DEBUG
   _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	//メモリリークチェッカーの適用
#endif
	//===変数宣言===//

   //===初期処理===//
	//ウィンドウの初期化
	if(!WINDOW->init( hInst, nCmdShow))
		return FALSE;

	gameInit();	//初期化

	CTimer* pTime = CTIMER;


	//---メインループ---//
	while(1)
	{
		if ( PeekMessage( WINDOW->getMsgPtr() , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if(	WINDOW->getMsg().message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( WINDOW->getMsgPtr() );
				DispatchMessage( WINDOW->getMsgPtr() );
			}
		}
		else
		{
			pTime->update();
			if(pTime->updateFrame())
			{
				gameLoop();	//ゲームの処理
				if(GetAsyncKeyState(VK_ESCAPE))
				{
					break;
				}
				pTime->countupTotalElapFrame();
			}
		}
	}
	
	gameRelease();
	return WINDOW->getMsg().wParam;
}
//EOF