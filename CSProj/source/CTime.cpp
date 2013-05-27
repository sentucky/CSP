/***********************************************************************/
/*! @file  CTime.cpp
 *  @brief ���ԃN���X
 *  
 *  @author �쌴�@�C��
 *  @date	
 */
/***********************************************************************/
#include"CTime.h"



/***********************************************************************/
/*! @brief �f�t�H���g�R���X�g���N�^
 */
/***********************************************************************/
CTimer::CTimer()
{
	init();
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTimer::~CTimer()
{
}


/***********************************************************************/
/*! @brief �������֐�
 * 
 *  @retval void
 */
/***********************************************************************/
void CTimer::init()
{
	timeBeginPeriod(1);
	_ulExecLastTime = _ulFPSLastTime  = timeGetTime();
	_ulCurrentTime  = _ulFrameCount   = 0;
	_ulTotalElapFrame = 0;
	_ulFrameCount = 0;
	_ulFPS = 0;
}

/***********************************************************************/
/*! @brief �X�V�֐�
 * 
 *  @retval void
 */
/***********************************************************************/
void CTimer::update()
{
	//���ݎ����̍X�V
	_ulCurrentTime = timeGetTime();

	//�e�o�r�J�E���g�̍X�V
	if((_ulCurrentTime - _ulFPSLastTime) >= 1000)
	{
		_ulFPSLastTime = _ulCurrentTime;
		_ulFPS = _ulFrameCount;
		_ulFrameCount = 0;
	}
}

/***********************************************************************/
/*! @brief FPS�̎擾
 * 
 *  @retval const ulong FPS�擾
 */
/***********************************************************************/
const ulong CTimer::getFPS()
{
	return _ulFPS;
}
/***********************************************************************/
/*! @brief ���ݎ����̎擾
* 
*  @retval const ulong ���ݎ���
*/
/***********************************************************************/
const ulong CTimer::getCurrentTime(){return _ulCurrentTime;}

/***********************************************************************/
/*! @brief ���݃t���[�����X�V
 * 
 *  @retval true �@���̃t���[���֍X�V
 *  @retval false  �X�V�Ȃ�
 */
/***********************************************************************/
bool CTimer::updateFrame()
{
	if((_ulCurrentTime - _ulExecLastTime) >= FRAME_RATE)
	{
		++_ulFrameCount;
		_ulExecLastTime = _ulCurrentTime;
		return true;
	}

	return false;
}


/***********************************************************************/
/*! @brief ���o�߃t���[�����擾
 * 
 *  @retval const ulong ���o�߃t���[����
 */
/***********************************************************************/
const ulong CTimer::getTotalElapFrame()
{
	return _ulTotalElapFrame;
}


/***********************************************************************/
/*! @brief ���o�߃t���[�����擾
 * 
 *  @retval const ulong ���o�߃t���[����
 */
/***********************************************************************/
const ulong CTimer::getTotalElapFrame()const
{
	return _ulTotalElapFrame;
}


/***********************************************************************/
/*! @brief ���o�߃t���[�����Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CTimer::countupTotalElapFrame()
{
	++_ulTotalElapFrame;
}
