/***********************************************************************/
/*! @file  CSceneTitle.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSceneTitle.h"

#include"CSceneGame.h"
#include"CSprite.h"
#include"CSpriteFactory.h"
#include"const.h"
#include"TextureKey.h"
#include"CInputCommon.h"

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

const uint SumSprite = 3;		//	�X�v���C�g�ő吔
D3DXVECTOR2 vecPos[SumSprite];
CSprite* pSprite[SumSprite] = {NULL,};	//	�X�v���C�g�|�C���^
POINT clickpos;
int gotoscene = 0;
bool changebutton[2];


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneTitle::CSceneTitle()
{
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneTitle::~CSceneTitle()
{
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTitle::init()
{
	pSprite[0] = SPRITEFACTORY->create(TEXKEY::TITLE_BG());
	vecPos[0] = D3DXVECTOR2(400.0f, 320.0f);
	pSprite[1] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON01());
	vecPos[1] = D3DXVECTOR2(400.0f, 380.0f);
	pSprite[2] = SPRITEFACTORY->create(TEXKEY::TITLE_BUTTON02());
	vecPos[2] = D3DXVECTOR2(400.0f, 525.0f);
	for(int i = 0; i < 2; i++)
	{
		changebutton[i] = false;
	}
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTitle::update()
{
	const RECTEX *size;
	D3DXVECTOR2 colpos;

	
	clickpos = MOUSE.getPointWindow();	
	for(uint i = 1; i < SumSprite; i++)
	{
		if(pSprite[i] == NULL)
		{
			continue;
		}
		
		size = pSprite[i]->getUV();
		colpos.x = vecPos[i].x - size->right / 2;
		colpos.y = vecPos[i].y - size->bottom / 2;

		if(bindRect(&colpos, (RECT *) size, &D3DXVECTOR2(clickpos.x, clickpos.y)))
		{
			changebutton[i - 1] = true;
			if(MOUSE.getTrgMouseButton(0))
			{		
				this->_EndFlg = true;
				gotoscene = i;
			}
		}
		else
		{
			changebutton[i - 1] = false;
		}
	}
}

void CSceneTitle::draw()
{
	pSprite[0]->draw(0,	&D3DXVECTOR3(vecPos[0].x, vecPos[0].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));

	if(changebutton[0])
	{
		pSprite[2]->draw(0,	&D3DXVECTOR3(vecPos[1].x, vecPos[1].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pSprite[1]->draw(0,	&D3DXVECTOR3(vecPos[1].x, vecPos[1].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}

	if(changebutton[1])
	{
		pSprite[2]->draw(0,	&D3DXVECTOR3(vecPos[2].x, vecPos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pSprite[1]->draw(0,	&D3DXVECTOR3(vecPos[2].x, vecPos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTitle::release()
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
CSceneBase* CSceneTitle::nextScene()
{
	switch(gotoscene)
	{
	case 1:
		return new CSceneGame;
		break;
	case 2:
		break;
	}
	return this;
}	//!<	�V�[���؂�ւ�
