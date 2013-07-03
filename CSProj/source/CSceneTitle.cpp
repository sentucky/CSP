/***********************************************************************/
/*! @file  CSceneTitle.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSceneTitle.h"

#include"CSceneStageSelect.h"
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
CSprite* pTitleSprite

//	02TEXKEY::TILE01�̃X�v���C�g���쐬
pTitleSprite = 	SPRITEFACTORY->create(TEXKEY::TILE01());

draw()�̓���pTitleSprite->draw(....)�����s
�\���͉摜�̒��S�����_

//---
pTitleSprite->getUV()�ŉ摜�̋�`�T�C�Y���擾�ł���
�}�E�X���W�ƕ��p���Ă����蔻�肵�Ă�������
*/

const uint SumTitleSprite = 6;		//	�X�v���C�g�ő吔
D3DXVECTOR2 vecTitlePos[SumTitleSprite];
CSprite* pTitleSprite[SumTitleSprite] = {NULL,};	//	�X�v���C�g�|�C���^
POINT TitleClickpos;
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
	release();
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTitle::init()
{
	pTitleSprite[0] = SPRITEFACTORY->create(TEXKEY::TITLE_BG());
	vecTitlePos[0] = D3DXVECTOR2(400.0f, 320.0f);
	pTitleSprite[1] = SPRITEFACTORY->create(TEXKEY::TITLE_STR());
	vecTitlePos[1] = D3DXVECTOR2(-200.0f, 160.0f);
	pTitleSprite[2] = SPRITEFACTORY->create(TEXKEY::SELECT_BUTTON01());
	vecTitlePos[2] = D3DXVECTOR2(400.0f, 370.0f);
	pTitleSprite[3] = SPRITEFACTORY->create(TEXKEY::END_BUTTON01());
	vecTitlePos[3] = D3DXVECTOR2(400.0f, 515.0f);
	pTitleSprite[4] = SPRITEFACTORY->create(TEXKEY::SELECT_BUTTON02());
	vecTitlePos[4] = D3DXVECTOR2(400.0f, 370.0f);
	pTitleSprite[5] = SPRITEFACTORY->create(TEXKEY::END_BUTTON02());
	vecTitlePos[5] = D3DXVECTOR2(400.0f, 515.0f);
	for(int i = 0; i < 2; i++)
	{
		changebutton[i] = false;
	}
//#ifndef _DEBUG
	CSOUND->GetSound(SOUNDKEY::TITLEBGM())->Play(0,0,1);
//#endif
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

	CHECK_UPDATE;

	if(vecTitlePos[1].x < 400.0f)
	{
		vecTitlePos[1].x += 5.0f;
	}
	
	TitleClickpos = MOUSE.getPointWindow();	
	for(uint i = 2; i < SumTitleSprite; i++)
	{
		if(pTitleSprite[i] == NULL)
		{
			continue;
		}
		
		size = pTitleSprite[i]->getUV();
		colpos.x = vecTitlePos[i].x - static_cast<float>(size->right / 2);
		colpos.y = vecTitlePos[i].y - static_cast<float>(size->bottom / 2);

		if(bindRect(&colpos, (RECT *) size, &D3DXVECTOR2(static_cast<float>(TitleClickpos.x), static_cast<float>(TitleClickpos.y))))
		{
			changebutton[i - 2] = true;
			if(MOUSE.getTrgMouseButton(0))
			{		
				this->_EndFlg = true;
				gotoscene = i - 3;
			}
		}
		else
		{
			changebutton[i - 2] = false;
		}
	}
}

void CSceneTitle::draw()
{
	CHECK_DRAW;

	pTitleSprite[0]->draw(0, &D3DXVECTOR3(vecTitlePos[0].x, vecTitlePos[0].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	pTitleSprite[1]->draw(0, &D3DXVECTOR3(vecTitlePos[1].x, vecTitlePos[1].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));

	if(changebutton[0])
	{
		pTitleSprite[4]->draw(0,	&D3DXVECTOR3(vecTitlePos[2].x, vecTitlePos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pTitleSprite[2]->draw(0,	&D3DXVECTOR3(vecTitlePos[2].x, vecTitlePos[2].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}

	if(changebutton[1])
	{
		pTitleSprite[5]->draw(0,	&D3DXVECTOR3(vecTitlePos[3].x, vecTitlePos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
	}
	else
	{
		pTitleSprite[3]->draw(0,	&D3DXVECTOR3(vecTitlePos[3].x, vecTitlePos[3].y, 0.0f), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1,1,0));
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
	for(uint i = 0; i < SumTitleSprite; i++)
	{
		SAFE_DELETE(pTitleSprite[i]);
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
		return new CSceneStageSelect;
		break;
	case 2:
		return (CSceneBase *)0;
		break;
	}
	return this;
}	//!<	�V�[���؂�ւ�
