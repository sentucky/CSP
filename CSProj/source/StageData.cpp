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
#include"CTextureFactory.h"
#include"CCamera.h"
#include"const.h"
#include"TextureKey.h"
#include"CFont.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CStageData::CStageData(const char* stageDataPath)
	:rootNum(0),
	_StartTile(NULL),
	_SecondTile(NULL),
	_LastTile(NULL)
{
	Init();
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
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Init()
{
	draw.SetSize(500.0f / (float)MAX_DATA,500.0f / (float)MAX_DATA);
	draw.SetTexture(NULL);

	_pTex[0] = NULL;
	_pTex[1] = (TEXTUREFACTORY->getTexture(TEXKEY::TILESTRAIGHT()))->getTexture();
	_pTex[2] = (TEXTUREFACTORY->getTexture(TEXKEY::TILECURVE()))->getTexture();
	_pTex[3] = (TEXTUREFACTORY->getTexture(TEXKEY::TILESTART()))->getTexture();

	Load("data/stage/stageData00.dat");	//暫定
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Update()
{
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Draw()
{
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	int i,j;

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DDEVICE->SetFVF(FVF_VERTEX_RECT);
	
	for (i = 0 ; i < MAX_DATA ; i++){
		for (j = 0 ; j < MAX_DATA ; j++){

			D3DXMatrixRotationYawPitchRoll(&matRot,tile[i][j].rot,-D3DX_PI / 2.0f,0.0f);
			D3DXMatrixTranslation(&matPos,tile[i][j].posX,0.0f,tile[i][j].posY);
			matRot *= matPos;
			D3DDEVICE->SetTransform(D3DTS_WORLD,&matRot);
			if (tile[i][j].no != 0){
				draw.SetTexture(_pTex[tile[i][j].no]);
				draw.Draw();
			}
		}
	}
	//ライン描画
#ifdef _DEBUG
	LINE line[512];

	for (i = 0 ; i < rootNum ; i++){
		line[i].vtx.x = root[i].x;
		line[i].vtx.y = 0.1f;
		line[i].vtx.z = root[i].y;
		line[i].diffuse = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
	}
	
	D3DDEVICE->SetFVF(FVF_LINE);
	D3DDEVICE->SetTexture(0,NULL);
	static float size = 5.0f;
	D3DXMatrixIdentity(&matRot);
	D3DDEVICE->SetTransform(D3DTS_WORLD,&matRot);
	D3DDEVICE->SetRenderState(D3DRS_POINTSIZE,*((DWORD*)&size));
	D3DDEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,rootNum - 1,&line[0],sizeof(LINE));
	D3DDEVICE->DrawPrimitiveUP(D3DPT_POINTLIST,rootNum,&line[0],sizeof(LINE));
#endif
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,TRUE);

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

	INPUTDATA tileIn[MAX_DATA][MAX_DATA];

	fread(tileIn,sizeof(INPUTDATA),MAX_DATA * MAX_DATA,fp);

	fread(&rootNum,sizeof(int),1,fp);
	fread(root,sizeof(D3DXVECTOR2),rootNum,fp);
	
	float strot;
	int i;
	int j;

	int stx;
	int sty;

	fclose(fp);

	for(i = 0; i< 16; i++)
	{
		for(j = 0; j< 16; j++)
		{
			tile[j][i].posX = tileIn[j][i].posX;
			tile[j][i].posY = tileIn[j][i].posY;
			tile[j][i].no	= tileIn[j][i].no;
			tile[j][i].rot  = tileIn[j][i].rot;
			tile[j][i].root  = -1;

			if(tileIn[j][i].no == STARTPANEL)
			{
				stx = j;
				sty = i;
				strot = tile[j][i].rot;
				_StartTile = &(tile[j][i]);
			}
		}
	}


	for (i = 0 ; i < 512 ; i++){
		obj[i].no = -1;
	}


	int scx,scy,lsx,lsy;
	if(strot >= 1.5 * D3DX_PI){
		scx = stx - 1;
		lsx = stx + 1; 
		scy = lsy = sty;
	}
	else if(strot >= 1.0f * D3DX_PI)
	{
		scy = sty + 1;
		lsy = sty - 1;
		scx = lsx = stx;
	}
	else if(strot >= 0.5f * D3DX_PI)
	{
		scx = stx + 1;
		lsx = stx - 1; 
		scy = lsy = sty;
	}
	else
	{
		scy = sty - 1;
		lsy = sty + 1;
		scx = lsx = stx;
	}



	_SecondTile = &tile[scx][scy];
	_LastTile = &tile[lsx][lsy];

	initwall(tile);


	//	以下がルートタイル情報初期化処理
	i = sty;
	j = stx;


	tile[j][i].root = 0;

	int prev = 0;
	const int left		= 0;
	const int top		= 1;
	const int right		= 2;
	const int bottom	= 3;

	const float pi = 3.14159265359f;

	//	開始タイルの情報
	if(tile[j][i].rot >= 1.5 * pi){
		prev = left;
		j -= 1;
	}
	else if(tile[j][i].rot >= 1.0f * pi){
		prev = bottom;
		i += 1;
	}
	else if(tile[j][i].rot >= 0.5f * pi){
		prev = right;
		j += 1;
	}
	else{
		prev = top;
		i -= 1;
	}

	int next[2]={0,};
	rootTileNum = 1;	//	総ルートタイル数

	//	第二タイル以降を初期化
	while(1 )
	{

		tile[j][i].root = rootTileNum;
		rootTileNum += 1;

		switch(tile[j][i].no)
		{
		case 1:	//	ストレート
		case 3:	//	スタート
			if(tile[j][i].rot >= 1.5 * pi || ( tile[j][i].rot < 1.0f * pi &&tile[j][i].rot >= 0.5f * pi)){
				next[0] = left;
				next[1] = right;
			}
			else{
				next[0] = top;
				next[1] = bottom;
			}
			break;
		case 2:	//	カーブ
			if(tile[j][i].rot >= 1.5 * pi){
				next[0] = top;
				next[1] = right;
			}
			else if(tile[j][i].rot >= 1.0f * pi){
				next[0] = top;
				next[1] = left;
			}
			else if(tile[j][i].rot >= 0.5f * pi){
				next[0] = bottom;
				next[1] = left;
			}
			else{
				next[0] = bottom;
				next[1] = right;
			}
			break;
		}


		//	次のタイルへ対応する形へ変換
		prev = (prev + 2) % 4;

		//	前と不一致の連結点が次の連結点
		prev = prev == next[0] ? next[1] : next[0];


		switch(prev)
		{
		case left:	j-=1;break;
		case top:	i-=1;break;
		case right:	j+=1;break;
		case bottom:i+=1;break;
		}

		if(tile[j][i].root == 0)
		{
			break;
		}
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::initwall(OUTPUT tile2[MAX_DATA][MAX_DATA])
{
	int i,j;

	BOOL* top		= NULL;
	BOOL* left		= NULL;
	BOOL* bottom	= NULL;
	BOOL* right		= NULL;
	RECT workRect	= {0,0,0,0};
	BOOL work		= FALSE;

	for (i = 0 ; i < MAX_DATA ; i++)
	{
		for (j = 0 ; j < MAX_DATA ; j++)
		{
			workRect.top = workRect.left = workRect.bottom = workRect.right = TRUE;
			top		= &LINE2[1][i][j];	//	トップライン
			left	= &LINE2[0][i][j];	//	レフトライン	
			bottom	= &LINE2[1][i][j+1];	//	ボトムライン
			right	= &LINE2[0][i+1][j];	//	ライトライン

			*top = *left = *bottom = *right = TRUE;

			//	壁配置
			switch(tile[i][j].no)
			{
			case 1://	縦
			case 3://	スタート
				workRect.top = workRect.bottom = FALSE;
				break;
			case 2://	右カーブ
				workRect.bottom = workRect.right = FALSE;
				break;
			}

			//	回転
			if(tile[i][j].rot / 3.14f >= 1.5f)
			{
				work = workRect.top;
				workRect.top = workRect.right;
				workRect.right = workRect.bottom;
				workRect.bottom = workRect.left;
				workRect.left = work;
			}
			else if(tile[i][j].rot / 3.14f >= 1.0f)
			{
				work			= workRect.bottom;
				workRect.bottom = workRect.top;
				workRect.top	= work;
				work			= workRect.left;
				workRect.left	= workRect.right;
				workRect.right	= work;
			}
			else if(tile[i][j].rot / 3.14f >= 0.5f)
			{
				work = workRect.top;
				workRect.top = workRect.left;
				workRect.left = workRect.bottom;
				workRect.bottom = workRect.right;
				workRect.right = work;
			}

			//	壁の有無フラグ設定
			if(workRect.top	== FALSE)
				*top	= workRect.top;
			if(workRect.left	== FALSE)
				*left	= workRect.left;
			if(workRect.bottom	== FALSE)
				*bottom= workRect.bottom;
			if(workRect.right	== FALSE)
				*right	= workRect.right;
		}
	}
	//	外縁の設定
	for (j = 0 ; j < MAX_DATA+1 ; j++)
	{		
		LINE2[1][j][16] = TRUE;	
		LINE2[0][j][16] = TRUE;	
		LINE2[1][16][j] = TRUE;	
		LINE2[0][16][j] = TRUE;	
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
const OUTPUT* CStageData::getStartTile()const
{
	return _StartTile;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
const OUTPUT* CStageData::getSecondTile()const
{
	return _SecondTile;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
const OUTPUT* CStageData::getLastTile()const
{
	return _LastTile;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
const void CStageData::getTile(const OUTPUT ary[MAX_DATA][MAX_DATA])const
{
	 memcpy((void*)ary,(void*)tile,sizeof(tile));
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::wallFlg(RECT* pOutWallFlg,uint TileX,uint TileY)const 
{
	pOutWallFlg->top	= LINE2[1][TileX][TileY];
	pOutWallFlg->left	= LINE2[0][TileX][TileY];
	pOutWallFlg->bottom = LINE2[1][TileX][TileY+1];
	pOutWallFlg->right	= LINE2[0][TileX+1][TileY];
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
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


	static const float kankaku = 500.0f / MAX_DATA;

	static float ary[17]={0,};
	if(ary[0] == 0){
		ary[0] = -250.0f;
		for(uint Cnt = 1; Cnt < MAX_DATA+1; Cnt+=1){
			ary[Cnt] = kankaku * Cnt + ary[0];
		}
	}

	int min = 0;
	int max = MAX_DATA;
	int mid;

	while(min<=max ){
		mid = (min + max) / 2;
		//	一致
		if(ary[mid] <= tX && ary[mid + 1] > tX ){
			break;
		}
		else if(ary[mid+1] < tX){
			min = mid+1;
		}
		else{
			max = mid-1;
		}
	}
	*xOut = mid;

	min = 0;
	max = MAX_DATA;

	while(min<=max ){
		//	一致
		mid = (min + max) / 2;
		//	一致
		if(ary[mid] <= tZ && ary[mid + 1] > tZ ){
			break;
		}
		else if(ary[mid+1] < tZ){
			min = mid+1;
		}
		else{
			max = mid-1;
		}
	}
	*zOut = 15 - mid;
}


OUTPUT* CStageData::step2(float x,float z)const
{
	if (x < -250.0f || z < -250.0f || x > 250.0f || z > 250.0f)
		return NULL;

	return const_cast<OUTPUT*>(&tile[(int)((x + 250.0f) / (500.0f / 16.0f))][15 - (int)((z + 250.0f) / (500.0f / 16.0f))]);
}