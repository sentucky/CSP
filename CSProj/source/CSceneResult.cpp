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
#include"CSceneGame.h"
#include"CSceneTitle.h"
#include"CSprite.h"
#include"CSpriteFactory.h"
#include"const.h"
#include"TextureKey.h"
#include"CInputCommon.h"

const uint SumResultSprite = 7;		//	スプライト最大数
D3DXVECTOR2 vecResultPos[SumResultSprite];
CSprite* pResultSprite[SumResultSprite] = {NULL,};	//	スプライトポインタ
POINT ResultClickpos;
bool Resultchangebutton[2];
int reslutgotoscene = 0;

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
	vecResultPos[1] = D3DXVECTOR2(400.0f, 150.0f);
	pResultSprite[2] = SPRITEFACTORY->create(TEXKEY::RESULT_RANK());
	vecResultPos[2] = D3DXVECTOR2(400.0f, 150.0f);
	pResultSprite[3] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON01());
	vecResultPos[3] = D3DXVECTOR2(400.0f, 370.0f);
	pResultSprite[4] = SPRITEFACTORY->create(TEXKEY::RETRY_BUTTON01());
	vecResultPos[4] = D3DXVECTOR2(400.0f, 515.0f);
	pResultSprite[5] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON02());
	vecResultPos[5] = D3DXVECTOR2(400.0f, 370.0f);
	pResultSprite[6] = SPRITEFACTORY->create(TEXKEY::RETRY_BUTTON02());
	vecResultPos[6] = D3DXVECTOR2(400.0f, 515.0f);
	
	for(int i = 0; i < 2; i++)
	{
		Resultchangebutton[i] = false;
	}

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

	const RECTEX *size;
	D3DXVECTOR2 colpos;

	CHECK_UPDATE;

	ResultClickpos = MOUSE.getPointWindow();	
	for(uint i = 3; i < SumResultSprite; i++)
	{
		if(pResultSprite[i] == NULL)
		{
			continue;
		}
		
		size = pResultSprite[i]->getUV();
		colpos.x = vecResultPos[i].x - static_cast<float>(size->right / 2);
		colpos.y = vecResultPos[i].y - static_cast<float>(size->bottom / 2);

		if(bindRect(&colpos, (RECT *) size, &D3DXVECTOR2(static_cast<float>(ResultClickpos.x), static_cast<float>(ResultClickpos.y))))
		{
			Resultchangebutton[i - 3] = true;
			if(MOUSE.getTrgMouseButton(0))
			{	
				this->_EndFlg = true;
				reslutgotoscene = i - 4;
			}
		}
		else
		{
			Resultchangebutton[i - 3] = false;
		}		
	}
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

	pResultSprite[0]->draw(0,	&D3DXVECTOR3(vecResultPos[0].x, vecResultPos[0].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	pResultSprite[1]->draw(0,	&D3DXVECTOR3(vecResultPos[1].x, vecResultPos[1].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	pResultSprite[2]->draw(0,	&D3DXVECTOR3(vecResultPos[2].x, vecResultPos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));

	if(Resultchangebutton[0])
	{
		pResultSprite[6]->draw(0,	&D3DXVECTOR3(vecResultPos[3].x, vecResultPos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pResultSprite[4]->draw(0,	&D3DXVECTOR3(vecResultPos[3].x, vecResultPos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}

	if(Resultchangebutton[1])
	{
		pResultSprite[5]->draw(0,	&D3DXVECTOR3(vecResultPos[4].x, vecResultPos[4].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pResultSprite[3]->draw(0,	&D3DXVECTOR3(vecResultPos[4].x, vecResultPos[4].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
}			
/***********************************************************************/
/*! @brief 
 * 
 *  @retval CSceneBase* 
 */
/***********************************************************************/
CSceneBase* CSceneResult::nextScene()
{
	switch(reslutgotoscene)
	{
	case 1:
		return new CSceneGame;
		break;
	case 2:
		return new CSceneTitle;
		break;
	}

	return this;
}
