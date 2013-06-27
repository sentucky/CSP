/***********************************************************************/
/*! @file  Rect.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//================================================================================
// Rect.cpp
//
// 3D矩形描画クラス											
//--------------------------------------------------------------------------------
// 更新履歴
//	2011/9/25
//		作成開始
//================================================================================
//================================================================================
// インクルード
//================================================================================
#include "Rect.h"
#include"CDevice.h"

//================================================================================
// クラス関数定義
//================================================================================

//コンストラクタ
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CRect::CRect()
{
	//初期化
	mTexture_pr = NULL;
	for (int i = 0 ; i< SQUARE_VTX ; i++)
	{
		mVtx[i].vtx =	D3DXVECTOR3(0.0f,0.0f,0.0f);
		mDeffuse[i] = D3DCOLOR_RGBA(255,255,255,255);
		mVtx[i].diffuse = mDeffuse[i];
	}
	mVtx[0].uv =	D3DXVECTOR2(0.0f,0.0f);
	mVtx[1].uv =	D3DXVECTOR2(1.0f,0.0f);
	mVtx[2].uv =	D3DXVECTOR2(0.0f,1.0f);
	mVtx[3].uv =	D3DXVECTOR2(1.0f,1.0f);
	mIsUpdate = true;
	mSize = D3DXVECTOR2(0.0f,0.0f);
	mDevice_pr = D3DDEVICE;
}

//デストラクタ
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CRect::~CRect()
{

}

//描画
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CRect::Draw()
{
	//更新
	if (mIsUpdate)
		this->Update();

	D3DMATERIAL9 materials2;
	materials2.Specular.a = 1.0f;
	materials2.Ambient .a = 1.0f;
	materials2.Diffuse.b = 	materials2.Diffuse.g = 	materials2.Diffuse.r = 	materials2.Diffuse.a = 1.0f;
	materials2.Power = 1.0f;
	materials2.Emissive.b = materials2.Emissive.g = materials2.Emissive.r = 0.25f;
	materials2.Emissive.a = 1.0f;


	//FVFの設定
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);

	//テクスチャ設定
	mDevice_pr->SetTexture(0,mTexture_pr);

	mDevice_pr->SetMaterial((D3DMATERIAL9*)&materials2);

	//ポリゴン描画
	mDevice_pr->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,mVtx,sizeof(VERTEX_RECT));
}


//更新
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CRect::Update(){

	//頂点
	mVtx[0].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[1].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[2].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);
	mVtx[3].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);
	
	//カラー
	for (int i = 0 ; i< SQUARE_VTX ; i++)
	{
		mVtx[i].diffuse = mDeffuse[i];
	}

	if (!mDevice_pr)
		mDevice_pr  = D3DDEVICE;

	mIsUpdate = false;
}
