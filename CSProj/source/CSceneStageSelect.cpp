/***********************************************************************/
/*! @file  CSceneStageSelect.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSceneStageSelect.h"

#include"CSceneGame.h"
#include"CSceneResult.h"
#include"CSceneTitle.h"
#include"CSprite.h"
#include"CSpriteFactory.h"
#include"const.h"
#include"TextureKey.h"
#include"CInputCommon.h"
#include"CSound.h"
#include"CSoundKey.h"

/*
//---
	����
MOUSE.getTrgMouseButton(0);	//	���N���b�N�g���K
MOUSE.getPrsMouseButton(0);	//	���N���b�N����
MOUSE.getPointWindow();		//	�E�B���h�E���2�c���W�擾
//---
	�`��܂ł̗���
//	01�X�v���C�g�|�C���^�p��
CSprite* pSprite

//	02TEXKEY::TILE01�̃X�v���C�g���쐬
pSprite = 	SPRITEFACTORY->create(TEXKEY::TILE01());

draw()�̓���pSprite->draw(....)�����s
�\���͉摜�̒��S�����_

//---
pSprite->getUV()�ŉ摜�̋�`�T�C�Y���擾�ł���
�}�E�X���W�ƕ��p���Ă����蔻�肵�Ă�������
*/

bool backflag;
const uint SumSprite = 5;		//	�X�v���C�g�ő吔
D3DXVECTOR2 vecPos[SumSprite];
CSprite* pSprite[SumSprite] = {NULL,};	//	�X�v���C�g�|�C���^
POINT StageSelectClickpos;
bool changebutton;


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneStageSelect::CSceneStageSelect()
{
	init();
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneStageSelect::~CSceneStageSelect()
{
	release();
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneStageSelect::init()
{
	pSprite[0] = SPRITEFACTORY->create(TEXKEY::TITLE_BG());
	vecPos[0] = D3DXVECTOR2(400.0f, 320.0f);
	pSprite[1] = SPRITEFACTORY->create(TEXKEY::SELECT_COURSE1());
	vecPos[1] = D3DXVECTOR2(400.0f, 220.0f);
	pSprite[2] = SPRITEFACTORY->create(TEXKEY::BACK_BUTTON());
	vecPos[2] = D3DXVECTOR2(100.0f, 560.0f);
	pSprite[3] = SPRITEFACTORY->create(TEXKEY::START_BUTTON01());
	vecPos[3] = D3DXVECTOR2(400.0f, 500.0f);
	pSprite[4] = SPRITEFACTORY->create(TEXKEY::START_BUTTON02());
	vecPos[4] = D3DXVECTOR2(400.0f, 500.0f);
	
	changebutton = false;
	backflag = false;
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneStageSelect::update()
{
	const RECTEX *size;
	D3DXVECTOR2 colpos;

	CHECK_UPDATE;

	StageSelectClickpos = MOUSE.getPointWindow();	
	for(uint i = 2; i < SumSprite; i++)
	{
		if(pSprite[i] == NULL)
		{
			continue;
		}
		
		size = pSprite[i]->getUV();
		colpos.x = vecPos[i].x - static_cast<float>(size->right / 2);
		colpos.y = vecPos[i].y - static_cast<float>(size->bottom / 2);

		if(bindRect(&colpos, (RECT *) size, &D3DXVECTOR2(static_cast<float>(StageSelectClickpos.x), static_cast<float>(StageSelectClickpos.y))))
		{
			
			if(MOUSE.getTrgMouseButton(0))
			{	
				if(i == 2)
				{
					backflag = true;
				}
				this->_EndFlg = true;
			}

			if(i > 2)
			{
				changebutton = true;
			}	
		}
		else
		{
			if(i > 2)
			{
				changebutton = false;
			}	
		}		
	}
}

void CSceneStageSelect::draw()
{
	CHECK_DRAW;

	pSprite[0]->draw(0,	&D3DXVECTOR3(vecPos[0].x, vecPos[0].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	pSprite[1]->draw(0,	&D3DXVECTOR3(vecPos[1].x, vecPos[1].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	pSprite[2]->draw(0,	&D3DXVECTOR3(vecPos[2].x, vecPos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));

	if(changebutton)
	{
		pSprite[4]->draw(0,	&D3DXVECTOR3(vecPos[3].x, vecPos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pSprite[3]->draw(0,	&D3DXVECTOR3(vecPos[3].x, vecPos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneStageSelect::release()
{

	for(uint i = 0; i < SumSprite; i++)
	{
		SAFE_DELETE(pSprite[i]);
	}
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval CSceneBase* 
 */
/***********************************************************************/
CSceneBase* CSceneStageSelect::nextScene()
{
	if(this->_EndFlg == TRUE && backflag == true)
	{
		return new CSceneTitle;
	}
	else
	{
		CSOUND->GetSound(SOUNDKEY::TITLEBGM())->Stop();
		return new CSceneGame;
		//return new CSceneResult;
	}
	return this;
}	//!<	�V�[���؂�ւ�
