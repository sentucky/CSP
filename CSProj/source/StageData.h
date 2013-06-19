/***********************************************************************/
/*! @file  StageData.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//================================================================================
// StageData.h
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
#pragma once

#include "CSingleton.h"
#include "common.h"
#include "d3dx9.h"
#include "d3d9.h"
#include "Rect.h"


#pragma pack(push,1)
typedef struct{
	int no;
	float rot;
	float posX;
	float posY;
	int	  root;
}OUTPUT;


typedef struct
{
	int no;
	float rot;
	float posX;
	float posY;
}INPUTDATA;

typedef struct{
	int no;
	D3DXVECTOR3 pos;
}OBJ;

#pragma pack (pop)

#define CSTAGEDATA		CStageData::GetInstance()
#define MAX_DATA		16
#define TILE_LINE		50.0f;

//================================================================================
// �C���N���[�h
//================================================================================

class CSprite;

//================================================================================
// �N���X��`
//	�v�f
//================================================================================

struct LINE
{
	D3DXVECTOR3 vtx;
	D3DCOLOR diffuse;
};


#define FVF_LINE	( D3DFVF_XYZ | D3DFVF_DIFFUSE )

class CStageData
{
public:
		CStageData(const char* stageDataPath);	//�R���X�g���N�^
		~CStageData();							//�f�X�g���N�^

		void Init();							//������
		void Update();							//�X�V
		void Draw();							//�`��

		void Load(const char* stageDataPath);	//���[�h

private:
		void initwall(OUTPUT tile[MAX_DATA][MAX_DATA]);	//�ǔ���쐬

public:
	void wallFlg(RECT* pOutWallFlg,uint TileX,uint TileY)const ;
	void step(uint* xOut,uint* yOut,const float x,const float z)const ;
	OUTPUT* step2(float x,float z)const;

	const OUTPUT* getStartTile()const;
	const OUTPUT* getSecondTile()const;
	const OUTPUT* getLastTile()const;
	const D3DXVECTOR2* getRoot()const{return root;}
	const int getRootNum()const{return rootNum;};
	const void getTile(const OUTPUT ary[MAX_DATA][MAX_DATA])const;

	static const int STARTPANEL = 3;
private:
	//===========================
	// �����o�ϐ� - ����J
	//===========================
	OUTPUT tile[MAX_DATA][MAX_DATA];
	int rootNum;
	int rootTileNum;

	D3DXVECTOR2 root[512];

	BOOL LINE2[2][MAX_DATA+1][MAX_DATA + 1];
	OBJ obj[512];

	OUTPUT* _StartTile;
	OUTPUT* _SecondTile;
	OUTPUT* _LastTile;

	LPDIRECT3DTEXTURE9 _pTex[4];
	CRect draw;
};


