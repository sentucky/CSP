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

	//FVFの設定
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);

	//テクスチャ設定
	mDevice_pr->SetTexture(0,mTexture_pr);

	//ポリゴン描画
	mDevice_pr->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,mVtx,sizeof(VERTEX_RECT));
}

IDirect3DVertexDeclaration9 *decl = 0;		//頂点デコレーション（FVF）
IDirect3DVertexBuffer9 		*pTopVerTex;	//頂点バッファ
struct STop{ 
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Tangent;
	D3DXVECTOR3 NormalVec;
	D3DXVECTOR2 UV;
 };


void initBump()
{
	//頂点情報構造体
	//頂点情報
	STop sTop[]={
		{D3DXVECTOR3(-1, 1,0),D3DXVECTOR3(0,1,0),D3DXVECTOR3(-1, 1,-1),D3DXVECTOR2(0,0)},
		{D3DXVECTOR3(-1,-1,0),D3DXVECTOR3(0,1,0),D3DXVECTOR3(-1,-1,-1),D3DXVECTOR2(0,1)},
		{D3DXVECTOR3( 1, 1,0),D3DXVECTOR3(0,1,0),D3DXVECTOR3( 1, 1,-1),D3DXVECTOR2(1,0)},
		{D3DXVECTOR3( 1,-1,0),D3DXVECTOR3(0,1,0),D3DXVECTOR3( 1,-1,-1),D3DXVECTOR2(1,1)},
	};

	//頂点登録(pTopVerTexの作成)
	D3DDEVICE->CreateVertexBuffer(
		sizeof( STop ) * 4,	//頂点数 * サイズ
		0,
		D3DFVF_XYZ,
		D3DPOOL_MANAGED,
		&pTopVerTex,
		0 );

	//頂点のメモリを直でコピーする
	STop *vTop;
	pTopVerTex->Lock( 0,0, (void**)&vTop, 0);
	memcpy( vTop, sTop, sizeof( sTop ) ); 
	pTopVerTex->Unlock();

	//頂点宣言(FVFみたいなもの)
	D3DVERTEXELEMENT9 declAry[] = {
        {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
        {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
        {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
        D3DDECL_END()
	};
	//FVF作成
	D3DDEVICE->CreateVertexDeclaration( declAry, &decl );
	//使用ストリーム指定と頂点バッファ設定
	D3DDEVICE->SetStreamSource( 0, pTopVerTex, 0, sizeof( STop ) );
}
void CRect::DrawBump()
{
	static int a = 0;
	if(a == 0)
	{
		initBump();
		a = 1;
	}


	//FVF設定
	D3DDEVICE->SetVertexDeclaration( decl );
	//描画(面二つと０から始まる頂点と指定)
	D3DDEVICE->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
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