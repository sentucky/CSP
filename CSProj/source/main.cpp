/***********************************************************************/
/*! @file  main.cpp
 *  @brief �G���g���[�|�C���g
 *  
 *  @author �쌴�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//    �C���N���[�h
/***********************************************************************/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include"common.h"
//----�@�\�n
#include"CWindow.h"			//�E�B���h�E�N���X�w�b�_
#include"Game.h"
#include"CTime.h"			//�^�C���N���X


#pragma comment( lib , "d3d9.lib" )
#pragma comment( lib , "d3dx9.lib")
#pragma comment( lib , "winmm.lib")



/***********************************************************************/
//    �v���g�^�C�v�錾
/***********************************************************************/

void	release();




/***********************************************************************/
//    ���C���֐�
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
#ifdef DEBUG
   _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	//���������[�N�`�F�b�J�[�̓K�p
#endif
	//===�ϐ��錾===//

   //===��������===//
	//�E�B���h�E�̏�����
	if(!WINDOW->init( hInst, nCmdShow))
		return FALSE;

	gameInit();	//������

	CTimer* pTime = CTIMER;


	//---���C�����[�v---//
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
				//�Q�[���̏���
				if(gameLoop() == false)
				{
					break;
				}
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