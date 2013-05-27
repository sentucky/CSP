/***********************************************************************/
/*! @file  CFadeInOut.cpp
 *  @brief フェードインアウト
 *  
 *  @author 川原　佑介
 *  @date	
 */
/***********************************************************************/
//*******************************************************************
//	インクルード
//*******************************************************************
#include"CFadeInOut.h"
#include"CWindow.h"
#include"const.h"
#include"CSpriteFactory.h"
#include"CSprite.h"
#include"common.h"

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CFadeInOut::CFadeInOut()
	:_unFadeSpeed(1),
	_pSprite(SPRITEFACTORY->create(TEXKEY::FADEMASK())),
	_State(FADE_NONE)
{
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CFadeInOut::~CFadeInOut()
{
	SAFE_DELETE(_pSprite);
}

/***********************************************************************/
/*! @brief フェード処理
 * 
 *  @retval BOOL 処理終了フラグ
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
/*! @brief フェードアウト開始
 * 
 *  @param[in] unDenominator フェードにかかる総フレーム数
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
/*! @brief フェードイン開始
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
/*! @brief ブラインドのアルファ値計算
 * 
 *  @retval int アルファ値
 */
/***********************************************************************/
int CFadeInOut::calcBlind()
{
	return (int)((float)0xff * (float)_unNumerator / (float)_unDenominator);
}


/***********************************************************************/
/*! @brief 描画処理
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
/*! @brief 更新処理
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
/*! @brief 状態の取得
* 
*  @retval const uint 現在の状態
*/
/***********************************************************************/
const uint CFadeInOut::getState(){return _State;}
//EOF