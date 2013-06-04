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
// インクルード
//================================================================================
#include "CSingleton.h"
#include "d3dx9.h"
#include "d3d9.h"

class CSprite;

//================================================================================
// クラス定義
//	要素
//================================================================================
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
		void Load(const char* stageDataPath);

public:
		const TILE* startTile()const;
		const TILE** getTile()const;


	private:
		//===========================
		// メンバ変数 - 非公開
		//===========================
		int rot;
		TILE tile[MAX_DATA][MAX_DATA];
		bool line[MAX_DATA + 1][MAX_DATA + 1];
		int rootNum;
		static CSprite*	pSprite[6];
		D3DXVECTOR2 root[512];

		TILE* StartTile;
};