/***********************************************************************/
/*! @file  StageData.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//================================================================================
// StageData.cpp
//
// ステージデータクラス											
//--------------------------------------------------------------------------------
// 更新履歴
//	2011/9/17
//		コメント更新
//================================================================================
//================================================================================
// マクロ定義
//================================================================================

//================================================================================
// インクルード
//================================================================================
#include "StageData.h"
#include "CTexture.h"
#include "CInputCommon.h"

#include"CSprite.h"
#include"CSpriteFactory.h"
#include"CCamera.h"
#include"const.h"
#include"CFont.h"

//================================================================================
// クラス定義
//================================================================================

const float rotY(int nDir)
{
	float retval = 0;

	switch(nDir)
	{
	case 0:				break;
	case 1:retval = 0.5f;break;
	case 2:retval = 1.0f;break;
	case 3:retval = 1.5f;break;
	}

	return retval;
}

CSprite*	CStageData::pSprite[6] = {NULL,NULL,NULL,NULL,NULL,NULL,};

//コンストラクタ
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CStageData::CStageData(const char* stageDataPath)
	:rot(0),
	rootNum(0)
{
	Init();
	Load(stageDataPath);

	pSprite[0] = SPRITEFACTORY->create(TEXKEY::TILE01());
	pSprite[1] = SPRITEFACTORY->create(TEXKEY::TILE02());
	pSprite[2] = SPRITEFACTORY->create(TEXKEY::TILE03());
	pSprite[3] = SPRITEFACTORY->create(TEXKEY::TILE04());
	pSprite[4] = SPRITEFACTORY->create(TEXKEY::TILE05());
	pSprite[5] = SPRITEFACTORY->create(TEXKEY::TILE06());
}

//デストラクタ
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CStageData::~CStageData()
{
	for(int i =0;i < 6; i++)
		SAFE_DELETE(pSprite[i]);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Init()
{
	int i,j;
	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			tile[i][j].no = 0;
			tile[i][j].rot = 0;
			tile[i][j].posX = (500.0f / (float)MAX_DATA) * i + 50.0f;
			tile[i][j].posY = (500.0f / (float)MAX_DATA) * j + 50.0f;
		}
	}
	
	for (i = 0 ; i < MAX_DATA + 1 ; i++)
	{
		for (j = 0 ; j < MAX_DATA + 1 ; j++)
		{
			line[i][j] = false;
		}
	}
	
	for (i = 0 ; i < 512 ; i++)
	{
		root[i].x = 0.0f;
		root[i].y = 0.0f;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Draw()
{
	int i,j;
	static float rot;
	

	D3DXMATRIXA16 matW;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matScale;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixScaling(&matScale,0.12f,0.12f,0.12f);

	
	FONT->DrawFloat("rot",rot,RECTEX(0,300,0,0));

	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			D3DXMatrixRotationX(&matRot,-0.5 * 3.14f);
			matW = matRot;
			D3DXMatrixRotationY(&matRot,rotY(tile[i][j].rot) *3.14f);
			matW *= matRot * matScale;
			matW._41 = tile[i][j].posX;
			matW._42 = 0.0f;
			matW._43 = tile[i][j].posY;
			pSprite[tile[i][j].no]->draw(0 ,&matW,CCamera::getMatView());
		}
	}
}



/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Load(const char* stageDataPath)
{
	FILE* fp;
	fp = fopen(stageDataPath,"rb");
	
	int a;
	fread(&a,sizeof(int),1,fp);

	OUTPUT out[MAX_DATA][MAX_DATA];
	fread(out,sizeof(OUTPUT),MAX_DATA * MAX_DATA,fp);
	int i,j;
	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			tile[i][j].no = out[i][j].no;
			if (out[i][j].rot >= (3.14f / 2.0f) * 3.0f)tile[i][j].rot = 3;
			else if (out[i][j].rot >= (3.14f / 2.0f) * 2.0f)tile[i][j].rot = 2;
			else if (out[i][j].rot >= (3.14f / 2.0f) * 1.0f)tile[i][j].rot = 1;
			else tile[i][j].rot = 0;
		}
	}

	fread(&rootNum,sizeof(int),1,fp);
	fread(root,sizeof(D3DXVECTOR2),rootNum,fp);
	
	for (i = 0 ; i < 512 ; i++)
	{
		root[i].x += 300.0f;
		root[i].y += 300.0f;
	}

	float x;
	float y;
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 8;j++)
		{
			x		= tile[i][15 - j].posX;
			y		= tile[i][15 - j].posY;
			tile[i][15 - j].posX	= tile[i][j].posX;
			tile[i][15 - j].posY	= tile[i][j].posY;
			tile[i][j].posX = x;
			tile[i][j].posY = y;
		}
	}

	fclose(fp);
}