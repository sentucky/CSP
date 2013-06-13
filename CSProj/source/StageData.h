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
// ステージデータクラス											
//--------------------------------------------------------------------------------
// 更新履歴
//	2011/9/17
//		コメント更新
//================================================================================
//================================================================================
// マクロ定義
//================================================================================
#pragma once

#include "CSingleton.h"
#include "common.h"
#include "d3dx9.h"
#include "d3d9.h"
#include "Rect.h"


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

typedef struct{
	int no;
	D3DXVECTOR3 pos;
}OBJ;

#pragma pack (pop)

#define CSTAGEDATA		CStageData::GetInstance()
#define MAX_DATA		16
#define TILE_LINE		50.0f;

//================================================================================
// インクルード
//================================================================================

class CSprite;

//================================================================================
// クラス定義
//	要素
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
		//コンストラクタ
		CStageData(const char* stageDataPath);

		//デストラクタ
		~CStageData();

		void Draw();

private:
		void Init();

		void Update();

		void Load(const char* stageDataPath);

		void initwall(OUTPUT tile[MAX_DATA][MAX_DATA]);

public:
		void wallFlg(RECT* pOutWallFlg,uint TileX,uint TileY)const ;
		void step(
		uint* xOut,
		uint* yOut,
		const float x,
		const float z)const ;
	const OUTPUT* startTile()const;
	const void getTile(const OUTPUT ary[MAX_DATA][MAX_DATA])const;


private:
		//===========================
		// メンバ変数 - 非公開
		//===========================
		OUTPUT tile[MAX_DATA][MAX_DATA];
		int rootNum;

		D3DXVECTOR2 root[512];
		D3DXVECTOR3 vec;
		CRect draw;
//		C3DObject* draw2;


		BOOL LINE2[2][MAX_DATA+1][MAX_DATA + 1];

		static CSprite*	pSprite[6];
		int objNum;
		int type;
		OBJ obj[512];
		int target;

		OUTPUT* StartTile;
};

