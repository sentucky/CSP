/***********************************************************************/
/*! @file  CPolygon.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CPolygon.h"



D3DVERTEXELEMENT9*	(CPolygon::VtxDecl::DeclAry_[VBT_SUM])	=	{0,};
uint				CPolygon::VtxDecl::VtxBufSize_[VBT_SUM]	=	{0,};
int					CPolygon::VtxDecl::SumInst_				=	0;
LPDIRECT3DDEVICE9	CPolygon::Device_ = NULL;
CPolygon::VtxDecl	CPolygon::VtxDeclInfo_;
/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
CPolygon::VtxDecl::VtxDecl()
{
	//	インスタンス数追加
	SumInst_ += 1;

	//	インスタンスの数が一つの時に初期化実行
	if(SumInst_ > 1)
	{
		return;
	}

	release();
	init();
}

/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
CPolygon::VtxDecl::~VtxDecl()
{
	release();
}


/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
void CPolygon::VtxDecl::init()
{
	DeclAry_[VBT_POS_TAN_NOR_UV]  = new D3DVERTEXELEMENT9[5];
	D3DVERTEXELEMENT9 temp[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
		{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
		{0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	memcpy(DeclAry_[VBT_POS_TAN_NOR_UV] ,temp,sizeof(temp));
	VtxBufSize_[VBT_POS_TAN_NOR_UV] = sizeof(VB_PTNU);
}

/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
void CPolygon::VtxDecl::release()
{
	for(uint cnt = 0; cnt < VBT_SUM; ++cnt)
	{
		SAFE_DELETE(DeclAry_[cnt]);
	}
}

/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
CPolygon::CPolygon()
{
}
/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
CPolygon::~CPolygon()
{
}


/***********************************************************************/
/*! @brief 
 */
/***********************************************************************/
void CPolygon::release()
{
	SAFE_RELEASE(decl_);
	SAFE_RELEASE(VtxBuf_);
	CurVtxType_ = VBT_NONE;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] VtxBufType	頂点バッファのタイプ
 *  @param[in] NumVtx		頂点数
 *  @retval	S_OK		成功
 *	@retval	S_FALSE		失敗
 */
/***********************************************************************/
HRESULT CPolygon::setVtxBufType(uint VtxBufType,uint NumVtx)
{
	//	成功失敗の判定
	HRESULT hr = S_OK;

	//	頂点バッファの型サイズ取得
	CurVtxType_ = VtxBufType;								//	頂点タイプの更新
	kuint VtxBufSize = VtxDeclInfo_.getVtxBufSize(CurVtxType_);	//	サイズ取得
	
	//	頂点バッファ作成
	hr = createVtxBuf(VtxBufSize,NumVtx);
	if(FAILED(hr))return hr;


	//	Declの作成
	D3DVERTEXELEMENT9* Decl;
	Decl = VtxDeclInfo_.getDecl(CurVtxType_);
	hr = Device_->CreateVertexDeclaration( Decl, &decl_ );
	if(FAILED(hr))
	{
		MessageAlert("Declの作成失敗","error from CPolygon::setVtxBufType");
		return hr;
	}


	//	頂点バッファストリームのバインド
	hr = Device_->SetStreamSource( 0, VtxBuf_, 0, VtxBufSize*NumVtx);
	if(FAILED(hr))
	{
		MessageAlert("頂点バッファストリームバインドの失敗","error from CPolygon::setVtxBufType");
		return hr;
	}

	return hr;
}
 
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in]			VtxSize	頂点サイズ
 *  @param[in]			NumVtx	頂点数
 *  @retval	S_OK		成功
 *	@retval	S_FALSE		失敗
 */
/***********************************************************************/
HRESULT CPolygon::createVtxBuf(uint VtxSize,uint NumVtx)
{
	//	成功失敗判定
	HRESULT hr = S_OK;

	//	頂点バッファの作成
	hr = Device_->CreateVertexBuffer(
		VtxSize  * NumVtx,	//頂点数 * サイズ
		0,
		D3DFVF_XYZ,
		D3DPOOL_MANAGED,
		&VtxBuf_,
		0 
		);

	if(FAILED(hr))
	{
		SAFE_RELEASE(decl_);
		SAFE_RELEASE(VtxBuf_);
		CurVtxType_	= VBT_NONE;

		MessageAlert("頂点バッファの作成に失敗","error from CPolygon::CreateVtxBuf");
		return hr;
	}
		return hr;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CPolygon::draw()
{
	//FVF設定
#ifdef _DEBUG
	HRESULT hr;
	hr = Device_->SetVertexDeclaration( decl_ );
	if(FAILED(hr))
	{
		MessageAlert("decl設定エラー","error from CPolygonDraw");
	}
	hr = Device_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	if(FAILED(hr))
	{
		MessageAlert("描画エラー","error from CPolygonDraw");
	}
#else
	Device_->SetVertexDeclaration( decl_ );
	Device_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
#endif
}

HRESULT CPolygon::LockVtx(void** OutBuf)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	頂点バッファのロック
	hr = VtxBuf_->Lock(0,0,(void**)OutBuf,0);

	if(FAILED(hr))
	{
		MessageAlert("頂点バッファのロックに失敗しました","CPolygon::LockVtx");
		return hr;
	}
	return hr;
}

HRESULT CPolygon::UnLockVtx()
{
	//	結果変数
	HRESULT hr = S_OK;

	hr = VtxBuf_->Unlock();

	if(FAILED(hr))
	{
		MessageAlert("アンロックエラー","CPolygon::setPos");
		return hr;
	}

	return hr;
}


HRESULT CPolygon::setPos(const D3DXVECTOR3* Pos,kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->pos = *Pos;	break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setPos(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* Pos;
	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		Pos = &(static_cast<VB_PTNU*>(buf) + VtxNum)->pos;
		Pos->x = x; Pos->y = y; Pos->z = z; break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setUV(const D3DXVECTOR2* UV, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->UV = *UV;	break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setUV(kfloat x,kfloat y, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR2* UV;

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		UV = &(static_cast<VB_PTNU*>(buf) + VtxNum)->UV;
		UV->x = x; UV->y = y;													break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setNormal(const D3DXVECTOR3* NormalVector, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->NormalVec = *NormalVector;	break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setNormal(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* NromalVec;

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		NromalVec = &(static_cast<VB_PTNU*>(buf) + VtxNum)->NormalVec;
		NromalVec->x = x; NromalVec->y = y; NromalVec->z = z; break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setTangent(const D3DXVECTOR3* Tangent, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->Tangent = *Tangent;	break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setTangent(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* Tangent;

	//	頂点バッファの値更新
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		Tangent = &(static_cast<VB_PTNU*>(buf) + VtxNum)->Tangent;
		Tangent->x = x; Tangent->y = y; Tangent->z = z; break;
	default:																	break;
	}

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setVtxBuf(void* VtxBuf,kuint VtxBufType,kuint VtxNum)
{
	//	結果変数
	HRESULT hr = S_OK;

	if(CurVtxType_ != VtxBufType)
	{
		//	Declの作成
		D3DVERTEXELEMENT9* Decl;
		Decl = VtxDeclInfo_.getDecl(CurVtxType_);
		SAFE_RELEASE(decl_);
		hr = Device_->CreateVertexDeclaration( Decl, &decl_ );
		if(FAILED(hr))
		{
			MessageAlert("Declの作成失敗","error from CPolygon::setVtxBuf");
			return hr;
		}
	}

	//	バッファ取得
	void* buf = NULL;
	LockVtx(&buf);
	if(FAILED(hr))return hr;

	kuint size = VtxDeclInfo_.getVtxBufSize(CurVtxType_);

	memcpy(buf,VtxBuf,size * VtxNum);

	//	アンロック
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	Device_->SetStreamSource( 0, VtxBuf_, 0, size);
	return hr;	
}