/***********************************************************************/
/*! @file  CFadeInOut.cpp
 *  @brief �t�F�[�h�C���A�E�g
 *  
 *  @author �쌴�@�C��
 *  @date	
 */
/***********************************************************************/
//*******************************************************************
//	�C���N���[�h
//*******************************************************************
#include"CFadeInOut.h"
#include"CWindow.h"
#include"const.h"
#include"TextureKey.h"
#include"CSpriteFactory.h"
#include"CSprite.h"
#include"common.h"

/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CFadeInOut::CFadeInOut()
	:_unFadeSpeed(1),
	_pSprite(SPRITEFACTORY->create(TEXKEY::FADEMASK())),
	_State(FADE_NONE)
{
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CFadeInOut::~CFadeInOut()
{
	SAFE_DELETE(_pSprite);
}

/***********************************************************************/
/*! @brief �t�F�[�h����
 * 
 *  @retval BOOL �����I���t���O
 */
/***********************************************************************/
BOOL CFadeInOut::fadeInOut()
{
	_unNumerator+=_unFadeSpeed;

	if(_unNumerator > _unDenominator)
	{
		_unNumerator = _unDenominator;
		_State = FADE_NONE;
		return TRUE;
	}
	else if(_unNumerator < 0)
	{
		_unNumerator = 0;
		_State = FADE_NONE;
		return TRUE;
	}
	return FALSE;
}


/***********************************************************************/
/*! @brief �t�F�[�h�A�E�g�J�n
 * 
 *  @param[in] unDenominator �t�F�[�h�ɂ����鑍�t���[����
 *  @retval void
 */
/***********************************************************************/
void CFadeInOut::fadeOutStart(uint unDenominator)
{
	_unNumerator = 0;
	_unDenominator = unDenominator;
	_State = FADE_ON;
	_unFadeSpeed = 1;
}
/***********************************************************************/
/*! @brief �t�F�[�h�C���J�n
 * 
 *  @param[in] unDenominator 
 *  @retval void 
 */
/***********************************************************************/
void CFadeInOut::fadeInStart(uint unDenominator)
{
	_unNumerator = unDenominator;
	_unDenominator = unDenominator;
	_unFadeSpeed = -1;
	_State = FADE_ON;
}

/***********************************************************************/
/*! @brief �u���C���h�̃A���t�@�l�v�Z
 * 
 *  @retval int �A���t�@�l
 */
/***********************************************************************/
int CFadeInOut::calcBlind()
{
	return (int)((float)0xff * (float)_unNumerator / (float)_unDenominator);
}


/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @retval void
 */
/***********************************************************************/
void CFadeInOut::draw()
{
	_pSprite->draw(
		0,
		&D3DXVECTOR3(400,320,0.0f),
		0,
		0);
	_pSprite->setColorRevision( D3DXCOLOR(D3DCOLOR_ARGB(calcBlind(),0,0,0)));

}

/***********************************************************************/
/*! @brief �X�V����
 * 
 *  @retval void
 */
/***********************************************************************/
void CFadeInOut::update()
{
	switch(_State)
	{
	case FADE_ON:
		if(fadeInOut())
		{
			_State = FADE_NONE;
		}
		break;
	case FADE_NONE:
		break;
	default:
		break;
	}
}


/***********************************************************************/
/*! @brief ��Ԃ̎擾
* 
*  @retval const uint ���݂̏��
*/
/***********************************************************************/
const uint CFadeInOut::getState(){return _State;}
//EOF