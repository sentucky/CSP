/***********************************************************************/
/*! @file  CTime.h
 *  @brief ���Ԍn�N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h�K�[�h
/***********************************************************************/
#pragma once

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include<Windows.h>
#include <mmsystem.h>
#include"CSingleton.h"
#include"common.h"
#pragma comment( lib , "winmm.lib" )


/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define CTIMER CTimer::getInst()

/***********************************************************************/
//	�萔��`
/***********************************************************************/
const float FRAME_RATE = 1000.0f / 30.0f;	///<�t���[�����[�g

class CTimer: public CSingleton<CTimer>
{
	//	�t�����h�o�^
	friend class CSingleton<CTimer>;
private:
	CTimer();				///<	�R���X�g���N�^
	~CTimer();				///<	�f�X�g���N�^
	CTimer(const CTimer&);	///<	�R�s�[�R���X�g���N�^

public:
	void init();							///<	����������
	void update();							///<	�X�V����
	void release();							///<	�J��������
	const ulong getFPS();					///<	FPS�擾
	const ulong getCurrentTime();			///<	���ݎ����̎擾
	bool updateFrame();						///<	�X�V����
	const ulong getTotalElapFrame();		///<	���o�߃t���[����
	const ulong getTotalElapFrame()const;	///<	���o�߃t���[����
	void countupTotalElapFrame();			///<	���o�߃t���[�������Z

private:
	ulong _ulExecLastTime;		///<	�ŏI��������
	ulong _ulFPSLastTime;		///<	�e�o�r�ŏI�X�V����
	ulong _ulCurrentTime;		///<	���ݎ���
	ulong _ulTotalElapFrame;	///<	���o�ߎ���
	ulong _ulFrameCount;		///<	�t���[���J�E���g
	ulong _ulFPS;				///<	����FPS
};

