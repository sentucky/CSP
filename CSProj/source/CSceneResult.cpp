/***********************************************************************/
/*! @file  CSceneResult.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSceneResult.h"

#include"CSceneStageSelect.h"
#include"CSprite.h"
#include"CSpriteFactory.h"
#include"const.h"
#include"TextureKey.h"
#include"CInputCommon.h"

const uint SumResultSprite = 7;		//	スプライト最大数
D3DXVECTOR2 vecResultPos[SumResultSprite];
CSprite* pResultSprite[SumResultSprite] = {NULL,};	//	スプライトポインタ
POINT ResultClickpos;
bool Resultchangebutton;

int rank;
int destroy;

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneResult::CSceneResult()
{
	init();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneResult::~CSceneResult()
{
	release();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneResult::init()
{
	pResultSprite[0] = SPRITEFACTORY->create(TEXKEY::RESULT_BG());
	vecResultPos[0] = D3DXVECTOR2(400.0f, 320.0f);
	pResultSprite[1] = SPRITEFACTORY->create(TEXKEY::RESULT_LOSE());
	vecResultPos[1] = D3DXVECTOR2(200.0f, 100.0f);
	pResultSprite[2] = SPRITEFACTORY->create(TEXKEY::RESULT_RANK());
	vecResultPos[2] = D3DXVECTOR2(220.0f, 150.0f);
	pResultSprite[3] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON01());
	vecResultPos[3] = D3DXVECTOR2(400.0f, 370.0f);
	pResultSprite[4] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON02());
	vecResultPos[4] = D3DXVECTOR2(400.0f, 370.0f);
	pResultSprite[5] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON01());
	vecResultPos[5] = D3DXVECTOR2(400.0f, 515.0f);
	pResultSprite[6] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON02());
	vecResultPos[6] = D3DXVECTOR2(400.0f, 515.0f);
	
	Resultchangebutton = false;

}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneResult::release()
{
}			
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneResult::update()
{
	CHECK_UPDATE;


}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneResult::draw()
{
	CHECK_DRAW;
}			
/***********************************************************************/
/*! @brief 
 * 
 *  @retval CSceneBase* 
 */
/***********************************************************************/
CSceneBase* CSceneResult::nextScene()
{
	return this;
}
