/***********************************************************************/
/*! @file  CSceneTitle.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSceneTitle.h"


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

const uint SumSprite = 50;		//	�X�v���C�g�ő吔

CSprite* pSprite[SumSprite] = {NULL,};	//	�X�v���C�g�|�C���^

CSceneTitle::CSceneTitle()
{
}
CSceneTitle::~CSceneTitle()
{
	for(uint i = 0; i < SumSprite; i++)
	{
		SAFE_DELETE(pSprite[i]);
	}
}
void CSceneTitle::init()
{
	pSprite[0] = SPRITEFACTORY->create(TEXKEY::TILE01());
}
void CSceneTitle::update()
{
}
void CSceneTitle::draw()
{
	for(uint i = 0; i < SumSprite; i++)
	{
		if(pSprite[i] == NULL)
			continue;

		pSprite[i]->draw(
			0,
			&D3DXVECTOR3(0,0,0),
			&D3DXVECTOR3(0,0,0),
			&D3DXVECTOR3(1,1,0));

	}
}
void CSceneTitle::release()
{
}
CSceneBase* CSceneTitle::nextScene()
{
	return this;
}	//!<	�V�[���؂�ւ�
