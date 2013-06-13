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
// �X�e�[�W�f�[�^�N���X											
//--------------------------------------------------------------------------------
// �X�V����
//	2011/9/17
//		�R�����g�X�V
//================================================================================
//================================================================================
// �}�N����`
//================================================================================

//================================================================================
// �C���N���[�h
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
// �N���X��`
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

//�R���X�g���N�^
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CStageData::CStageData(const char* stageDataPath)
	:rootNum(0)
{
	pSprite[0] = SPRITEFACTORY->create(TEXKEY::TILE01());
	pSprite[1] = SPRITEFACTORY->create(TEXKEY::TILE02());
	pSprite[2] = SPRITEFACTORY->create(TEXKEY::TILE03());
	pSprite[3] = SPRITEFACTORY->create(TEXKEY::TILE04());
	pSprite[4] = SPRITEFACTORY->create(TEXKEY::TILE05());
	pSprite[5] = SPRITEFACTORY->create(TEXKEY::TILE06());
	Init();
	initwall(tile);
}

//�f�X�g���N�^
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
	/*
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
	*/
	vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	FILE* fp;
	fp = fopen("data/stage/stageData00.dat","rb");

//	draw.SetSize((500.0f / (float)MAX_DATA),(500.0f / (float)MAX_DATA));
//	draw.SetTexture(CTEXTURE->GetTexture("001"));
	
	int a;
	fread(&a,sizeof(int),1,fp);

	fread(tile,sizeof(OUTPUT),MAX_DATA * MAX_DATA,fp);

	fread(&rootNum,sizeof(int),1,fp);
	fread(root,sizeof(D3DXVECTOR2),rootNum,fp);
	
	fclose(fp);

	for(int i = 0; i< 16; i++)
		for(int j = 0; j< 16; j++)
		{
			if(tile[j][i].no == 3)
			{
				StartTile = &(tile[j][i]);
			}
		}
	objNum = 0;
	type = 0;
	for (int i = 0 ; i < 512 ; i++){
		obj[i].no = -1;
	}
//	draw2 = C3DOBJECTMANAGER->Get3DObject("�I�u�W�F");
}


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
	/*
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
	*/
	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	int i,j;

	for (i = 0 ; i < MAX_DATA ; i++){
		for (j = 0 ; j < MAX_DATA ; j++){
/*
			if (i % 2 - j % 2)draw.SetTexture(CTEXTURE->GetTexture("001"));
			else draw.SetTexture(CTEXTURE->GetTexture("002"));
			
			if (tile[i][j].no == 1)draw.SetTexture(CTEXTURE->GetTexture("004"));
			if (tile[i][j].no == 2)draw.SetTexture(CTEXTURE->GetTexture("005"));
			if (tile[i][j].no == 3)draw.SetTexture(CTEXTURE->GetTexture("006"));
*/
			D3DXMatrixRotationYawPitchRoll(&matRot,tile[i][j].rot,-D3DX_PI / 2.0f,0.0f);
			D3DXMatrixScaling(&matPos,0.12f,0.12f,0.12f);
			matRot *= matPos;
			D3DXMatrixTranslation(&matPos,tile[i][j].posX,0.0f,tile[i][j].posY);
			matRot *= matPos;
			D3DDEVICE->SetTransform(D3DTS_WORLD,&matRot);
//			draw.Draw();
			pSprite[tile[i][j].no]->draw(
				0,
				&matRot,
				CCamera::getMatView());
		}
	}
	
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
/*	
	//��������I�u�W�F
	if (type == 0)draw2->SetMesh(CMESH->GetMesh("001"));
	if (type == 1)draw2->SetMesh(CMESH->GetMesh("002"));
	if (type == 2)draw2->SetMesh(CMESH->GetMesh("003"));
	
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

	for (i = 0 ; i < objNum ; i++){
		draw2->SetPos(obj[i].pos);
		if (obj[i].no == 0)draw2->SetMesh(CMESH->GetMesh("001"));
		if (obj[i].no == 1)draw2->SetMesh(CMESH->GetMesh("002"));
		if (obj[i].no == 2)draw2->SetMesh(CMESH->GetMesh("003"));
		draw2->Update();
		if (i == target)
			draw2->Draw(1);
		else
			draw2->Draw(3);
	}
	draw2->SetPos(vec);
	draw2->Update();
	draw2->Draw(0);

	CDIRECTXDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	*/
}



/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CStageData::Load(const char* stageDataPath)
{
}

void CStageData::initwall(OUTPUT tile2[MAX_DATA][MAX_DATA])
{
	int i,j;

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
			workRect.top = workRect.left = workRect.bottom = workRect.right = TRUE;
			top		= &LINE2[1][i][j];	//	�g�b�v���C��
			left	= &LINE2[0][i][j];	//	���t�g���C��	
			bottom	= &LINE2[1][i][j+1];	//	�{�g�����C��
			right	= &LINE2[0][i+1][j];	//	���C�g���C��

			*top = *left = *bottom = *right = TRUE;

			tile[i][j].rot;
			//	�ǔz�u
			switch(tile[i][j].no)
			{
			case 1://	�c
			case 3://	�X�^�[�g
				workRect.top = workRect.bottom = FALSE;
				break;
			case 2://	�E�J�[�u
				workRect.bottom = workRect.right = FALSE;
				break;
			}

			//	��]
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

			//	�ǂ̗L���t���O�ݒ�
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
	//	�O���̐ݒ�
	for (j = 0 ; j < MAX_DATA+1 ; j++)
	{		
		LINE2[1][j][16] = TRUE;	
		LINE2[0][j][16] = TRUE;	
		LINE2[1][16][j] = TRUE;	
		LINE2[0][16][j] = TRUE;	
	}

}


const OUTPUT* CStageData::startTile()const
{
	return StartTile;
}


const void CStageData::getTile(const OUTPUT ary[MAX_DATA][MAX_DATA])const
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
		//....�񕪒T���Ŏ����������Ă���ꏊ��T��

	*xOut = 8;
	*zOut = 8;

	float ary[17]={0,};


	static const float kankaku = 500.0f / MAX_DATA;

	ary[0] = -250.0f;

	for(uint Cnt = 1; Cnt < MAX_DATA+1; Cnt+=1)
	{
		ary[Cnt] = kankaku * Cnt + ary[0];
	}



	int min = 0;
	int max = MAX_DATA;
	int mid;

	while(min<=max )
	{
		mid = (min + max) / 2;
		//	��v
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

	ary[0] = -250.0f;


	for(uint Cnt = 1; Cnt < MAX_DATA+1; Cnt+=1)
	{
		ary[Cnt] = kankaku * Cnt + ary[0];
	}



	float fff=0.0;
	while(min<=max )
	{
		//	��v
		mid = (min + max) / 2;
		//	��v
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
	*zOut = 15 - mid;

}