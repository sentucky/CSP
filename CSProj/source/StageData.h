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

typedef struct{
	int no;
	int rot;
	float posX;
	float posY;
}TILE;

#pragma pack(push,1)
typedef struct{
	int no;
	float rot;
	float posX;
	float posY;
}OUTPUT;
#pragma pack (pop)

#define CSTAGEDATA		CStageData::GetInstance()
#define MAX_DATA		16
#define TILE_LINE		50.0f;

//================================================================================
// �C���N���[�h
//================================================================================
#include "CSingleton.h"
#include "common.h"
#include "d3dx9.h"
#include "d3d9.h"

class CSprite;

//================================================================================
// �N���X��`
//	�v�f
//================================================================================
struct LINE{
	D3DXVECTOR3 vtx;
	D3DCOLOR	color;

};

#define FVF_LINE	( D3DFVF_XYZ | D3DFVF_DIFFUSE )



class CStageData
{
	public:
		//�R���X�g���N�^
		CStageData(const char* stageDataPath);

		//�f�X�g���N�^
		~CStageData();

		void Draw();

private:
		void Init();
		void Load(const char* stageDataPath);
		void initwall(TILE tile[][16]);

public:
		void wallFlg(RECT* pOutWallFlg,uint TileX,uint TileY)const ;
		void step(
		uint* xOut,
		uint* yOut,
		const float x,
		const float z)const ;
	const TILE* startTile()const;
	const void getTile(const TILE ary[MAX_DATA][MAX_DATA])const;


private:
		//===========================
		// �����o�ϐ� - ����J
		//===========================
		int rot;
		TILE tile[MAX_DATA][MAX_DATA];
		BOOL LINE2[2][MAX_DATA+1][MAX_DATA + 1];
		int rootNum;
		static CSprite*	pSprite[6];
		D3DXVECTOR2 root[512];
		TILE* StartTile;
		LINE line[512];
};
