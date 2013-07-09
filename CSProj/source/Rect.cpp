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
	/*
	D3DMATERIAL9 materials2;
	materials2.Specular.a = 1.0f;
	materials2.Ambient .a = 1.0f;
	materials2.Diffuse.b = 	materials2.Diffuse.g = 	materials2.Diffuse.r = 	materials2.Diffuse.a = 1.0f;
	materials2.Power = 1.0f;
	materials2.Emissive.b = materials2.Emissive.g = materials2.Emissive.r = 0.25f;
	materials2.Emissive.a = 1.0f;
	*/

	//FVFの設定
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);

	//テクスチャ設定
	mDevice_pr->SetTexture(0,mTexture_pr);

	//ポリゴン描画
	mDevice_pr->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,mVtx,sizeof(VERTEX_RECT));
}

void CRect::DrawBump()
{
	/*
	mVtx[0].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[1].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[2].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);
	mVtx[3].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);

	LPDIRECT3DVERTEXBUFFER9 vb = NULL;
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);
	mDevice_pr->CreateVertexBuffer(
		sizeof(VERTEX_RECT)*4,
		D3DUSAGE_DYNAMIC,
		0,
		D3DPOOL_MANAGED,
		&vb,
		NULL);

	
	mDevice_pr->SetSamplerState(0,D3DTSS_MINFILTER,D3DTEXF_LINER);
	mDevice_pr->SetStreamSource(0,vb,0,sizeof(VERTEX_RECT));
	mDevice_pr->SetIndices(



	VERTEX_RECT* v = NULL;
	vb->Lock(0,0,(void**)&v,0);
	memcpy(v,mVtx,sizeof(VERTEX_RECT)*4);
	vb->Unlock();
	mDevice_pr->SetStreamSource(0,vb,0,sizeof(VERTEX_RECT));
	mDevice_pr->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,4);
	vb->Release();
	*/d
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


void MakeBillboardMat(D3DXMATRIX* out,D3DXMATRIX* pos)
{
	D3DXVECTOR3 camera;
	camera = CCamera::getAt() - CCamera::getEye();
	D3DXVec3Normalize(&camera,&camera);
	camera *= -1;

	D3DXMatrixIdentity(out);
	D3DXMatrixLookAtLH(out,&D3DXVECTOR3(0.0f,0.0f,0.0f),&camera,&D3DXVECTOR3(0.0f,1.0f,0.0f));
	D3DXMatrixInverse(out,NULL,out);
	*out = (*out) * (*pos);
}