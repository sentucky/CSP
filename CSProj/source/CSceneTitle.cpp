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
	入力
MOUSE.getTrgMouseButton(0);	//	左クリックトリガ
MOUSE.getPrsMouseButton(0);	//	左クリック押し
MOUSE.getPointWindow();		//	ウィンドウ上の2Ｄ座標取得
//---
	描画までの流れ
//	01スプライトポインタ用意
CSprite* pSprite

//	02TEXKEY::TILE01のスプライトを作成
pSprite = 	SPRITEFACTORY->create(TEXKEY::TILE01());

draw()の内でpSprite->draw(....)を実行
表示は画像の中心が原点

//---
pSprite->getUV()で画像の矩形サイズが取得できる
マウス座標と併用してあたり判定してください
*/

const uint SumSprite = 50;		//	スプライト最大数

CSprite* pSprite[SumSprite] = {NULL,};	//	スプライトポインタ

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
}	//!<	シーン切り替え
