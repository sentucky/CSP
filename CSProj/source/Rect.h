//================================================================================
// Rect.h
//
// 3D矩形描画クラス											
//--------------------------------------------------------------------------------
// 更新履歴
//	2011/12/17
//		作成開始
//================================================================================
#pragma once

//================================================================================
// マクロ定義
//================================================================================
//頂点フォーマット(頂点座標[2D] / 反射光 / テクスチャ座標)
#define FVF_VERTEX_RECT			(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//================================================================================
// インクルード
//================================================================================
#include"CDevice.h"

//================================================================================
// 構造体定義
//================================================================================
//上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;
	D3DCOLOR diffuse;
	D3DXVECTOR2 uv;
}VERTEX_RECT;

//================================================================================
// クラス定義
//================================================================================
class CRect
{
	private:
		//===========================
		// クラス内定数
		//===========================
		static const int SQUARE_VTX = 4;
	public:
		//===========================
		// メンバ関数 - 公開
		//===========================
		//コンストラクタ
		CRect();
		//デストラクタ
		~CRect();

		//描画
		void Draw(void);

		//テクスチャセット
		CRect* SetTexture(LPDIRECT3DTEXTURE9 p)					{mTexture_pr = p; return this;}

		//サイズの取得/格納
		CRect* SetSize(D3DXVECTOR2 size)						{mSize = size; mIsUpdate = true; return this;}
		CRect* SetSize(float sizeX,float sizeY)					{mSize.x = sizeX;mSize.y = sizeY; mIsUpdate = true; return this;}
		CRect* SetSizeX(float sizeX)							{mSize.x = sizeX; mIsUpdate = true; return this;}
		CRect* SetSizeY(float sizeY)							{mSize.y = sizeY; mIsUpdate = true; return this;}

		D3DXVECTOR2 GetSize()									{return mSize;}
		float GetSizeX()										{return mSize.x;}
		float GetSizeY()										{return mSize.y;}

		//カラーの取得/格納
		CRect* SetColor(int no,float r,float g,float b)			{mDeffuse[no].r = r;mDeffuse[no].g = g;mDeffuse[no].b = b; mIsUpdate = true; return this;}
		CRect* SetColor(float r,float g,float b)				{SetColor(0,r,g,b); SetColor(1,r,g,b); SetColor(2,r,g,b); SetColor(3,r,g,b); mIsUpdate = true; return this;}
		D3DXCOLOR GetColor(int no)								{return mDeffuse[no];}

		//アルファ値の取得/格納
		CRect* SetAlpha(float a)								{mDeffuse[0].a = mDeffuse[1].a = mDeffuse[2].a = mDeffuse[3].a = a; mIsUpdate = true; return this;}
		float GetAlpha()										{return mDeffuse[0].a;}

		//UVの取得/格納
		CRect* SetUV(int no,D3DXVECTOR2 uv)						{mVtx[no].uv = uv; return this;}
		D3DXVECTOR2 GetUV(int no)								{return mVtx[no].uv;}
	private:
		//===========================
		// メンバ関数 - 非公開
		//===========================
		//更新
		void Update(void);

		//===========================
		// メンバ変数 - 非公開
		//===========================
		//描画情報
		VERTEX_RECT				 mVtx[SQUARE_VTX];		//頂点配列
		LPDIRECT3DTEXTURE9		 mTexture_pr;			//テクスチャポインタ
		LPDIRECT3DDEVICE9		 mDevice_pr;			//DirectXデバイス

		bool					 mIsUpdate;				//更新の可否
		D3DXVECTOR2				 mSize;					//サイズ
		D3DXCOLOR				 mDeffuse[SQUARE_VTX];	//カラー
};