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
	ZeroMemory(LINE2,sizeof(LINE2));
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
	const float haba = (500.0f / (float)MAX_DATA);

	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			tile[i][j].no = 0;
			tile[i][j].rot = 0;
			tile[i][j].posX = haba * i - 250.0f;// + haba * 0.5f;
			tile[i][j].posY = haba * j - 250.0f;// + haba * 0.5f;
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

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DDEVICE->SetRenderState(D3DRS_ZENABLE,FALSE);
	D3DDEVICE->SetFVF(FVF_LINE);
	static float size = 10.0f;
	D3DDEVICE->SetRenderState(D3DRS_POINTSIZE,*((DWORD*)&size));

	D3DDEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,rootNum - 1, &line[0],sizeof(LINE));
	D3DDEVICE->DrawPrimitiveUP(D3DPT_POINTLIST,rootNum , &line[0],sizeof(LINE));

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,TRUE);
	D3DDEVICE->SetRenderState(D3DRS_ZENABLE,TRUE);

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
			tile[i][j].posY *= -1;

			tile[i][j].no = out[i][j].no;
			if(tile[i][j].no == 3)
			{
				StartTile = &(tile[i][j]);
			}
			if (out[i][j].rot >= (3.14f / 2.0f) * 3.0f)tile[i][j].rot = 3;
			else if (out[i][j].rot >= (3.14f / 2.0f) * 2.0f)tile[i][j].rot = 2;
			else if (out[i][j].rot >= (3.14f / 2.0f) * 1.0f)tile[i][j].rot = 1;
			else tile[i][j].rot = 0;
		}
	}

	initwall(tile);

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
			/*
			x = tile[i][j].no;
			tile[i][j].no = tile[i][16 - j].no;
			tile[i][16 - j].no = x;
			//*/
		}
	}
//	*/
	fclose(fp);
}

void CStageData::initwall(TILE tile2[][16])
{
	int i,j;
	int rot;

	BOOL* top		= NULL;
	BOOL* left		= NULL;
	BOOL* bottom	= NULL;
	BOOL* right		= NULL;
	RECT workRect;
	BOOL work;
	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			top		= &LINE2[1][i][j];	//	トップライン
			left	= &LINE2[0][i][j];	//	レフトライン	
			bottom	= &LINE2[1][i][j+1];	//	ボトムライン
			right	= &LINE2[0][i+1][j];	//	ライトライン

			tile[i][j].rot;
			//	壁配置
			switch(tile[i][j].no)
			{
			case 1://	縦
			case 3://	スタート
				workRect.top = workRect.bottom = FALSE;
				workRect.left = workRect.right = TRUE;
				break;
			case 2://	右カーブ
				workRect.top = workRect.left = TRUE;
				workRect.bottom = workRect.right = FALSE;
				break;
			default:workRect.top = workRect.left = workRect.bottom = workRect.right = TRUE;break;
			}

			//	回転
			switch(tile[i][j].rot)
			{
			case 1://	90
				work = workRect.top;
				workRect.top = workRect.left;
				workRect.left = workRect.bottom;
				workRect.bottom = workRect.right;
				workRect.right = work;
				break;
			case 2://	180
				work			= workRect.bottom;
				workRect.bottom = workRect.top;
				workRect.top	= work;
				work			= workRect.left;
				workRect.left	= workRect.right;
				workRect.right	= work;
				break;
			case 3://	270
				work = workRect.top;
				workRect.top = workRect.right;
				workRect.right = workRect.bottom;
				workRect.bottom = workRect.left;
				workRect.left = work;
				break;
			default:;break;
			}
			*top	= workRect.top;
			*left	= workRect.left;
			*bottom	= workRect.bottom;
			*right	= workRect.right;
		}
		LINE2[1][i][j] = TRUE;	
		LINE2[0][i][j] = TRUE;	
		LINE2[1][i][j+1] = TRUE;
		LINE2[0][i+1][j] = TRUE;
	}
	for (j = 0 ; j < MAX_DATA ; j++)
	{
		LINE2[1][i][j] = TRUE;	
		LINE2[0][i][j] = TRUE;	
		LINE2[1][i][j+1] = TRUE;
		LINE2[0][i+1][j] = TRUE;
	}

}


const TILE* CStageData::startTile()const
{
	return StartTile;
}


const void CStageData::getTile(const TILE ary[MAX_DATA][MAX_DATA])const
{
	 memcpy((void*)ary,(void*)tile,sizeof(tile));
}

void CStageData::wallFlg(RECT* pOutWallFlg,uint TileX,uint TileY)const 
{
	pOutWallFlg->top	= LINE2[1][TileX][TileY];
	pOutWallFlg->left	= LINE2[0][TileX][TileY];
	pOutWallFlg->bottom = LINE2[1][TileX][TileY+1];
	pOutWallFlg->right	= LINE2[0][TileX+1][TileY];
}

void CStageData::step(
	uint* xOut,
	uint* zOut,
	const float tX,
	const float tZ
	)const 
{
		//....二分探索で自分が立っている場所を探す

	*xOut = 8;
	*zOut = 8;

	float ary[17]={0,};
	ary[0] = tile[0][0].posX;
	for(uint Cnt = 0; Cnt < MAX_DATA+1; Cnt+=1)
	{
		ary[Cnt] = 500.0f / MAX_DATA * Cnt + ary[0] - 500.0f / MAX_DATA * 0.25f;
	}



	int min = 0;
	int max = MAX_DATA;
	int mid;

	while(min<=max )
	{
		mid = (min + max) / 2;
		//	一致
		if(ary[mid] <= tX && ary[mid + 1] > tX )
		{
			break;
		}
		else if(ary[mid+1] < tX)
		{
			min = mid+1;
		}
		else
		{
			max = mid-1;
		}
	}
	*xOut = mid;

min = 0;
max = MAX_DATA;
	while(min<=max )
	{
		//	一致
		mid = (min + max) / 2;
		//	一致
		if(ary[mid] <= tZ && ary[mid + 1] > tZ )
		{
			break;
		}
		else if(ary[mid+1] < tZ)
		{
			min = mid+1;
		}
		else
		{
			max = mid-1;
		}
	}
	*zOut = 16 - mid;

}