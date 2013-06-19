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
		CStageData(const char* stageDataPath);	//コンストラクタ
		~CStageData();							//デストラクタ

		void Init();							//初期化
		void Update();							//更新
		void Draw();							//描画

		void Load(const char* stageDataPath);	//ロード

private:
		void initwall(OUTPUT tile[MAX_DATA][MAX_DATA]);	//壁判定作成

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
	// メンバ変数 - 非公開
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


