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
	//	�C���X�^���X���ǉ�
	SumInst_ += 1;

	//	�C���X�^���X�̐�����̎��ɏ��������s
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
 *  @param[in] VtxBufType	���_�o�b�t�@�̃^�C�v
 *  @param[in] NumVtx		���_��
 *  @retval	S_OK		����
 *	@retval	S_FALSE		���s
 */
/***********************************************************************/
HRESULT CPolygon::setVtxBufType(uint VtxBufType,uint NumVtx)
{
	//	�������s�̔���
	HRESULT hr = S_OK;

	//	���_�o�b�t�@�̌^�T�C�Y�擾
	CurVtxType_ = VtxBufType;								//	���_�^�C�v�̍X�V
	kuint VtxBufSize = VtxDeclInfo_.getVtxBufSize(CurVtxType_);	//	�T�C�Y�擾
	
	//	���_�o�b�t�@�쐬
	hr = createVtxBuf(VtxBufSize,NumVtx);
	if(FAILED(hr))return hr;


	//	Decl�̍쐬
	D3DVERTEXELEMENT9* Decl;
	Decl = VtxDeclInfo_.getDecl(CurVtxType_);
	hr = Device_->CreateVertexDeclaration( Decl, &decl_ );
	if(FAILED(hr))
	{
		MessageAlert("Decl�̍쐬���s","error from CPolygon::setVtxBufType");
		return hr;
	}


	//	���_�o�b�t�@�X�g���[���̃o�C���h
	hr = Device_->SetStreamSource( 0, VtxBuf_, 0, VtxBufSize*NumVtx);
	if(FAILED(hr))
	{
		MessageAlert("���_�o�b�t�@�X�g���[���o�C���h�̎��s","error from CPolygon::setVtxBufType");
		return hr;
	}

	return hr;
}
 
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in]			VtxSize	���_�T�C�Y
 *  @param[in]			NumVtx	���_��
 *  @retval	S_OK		����
 *	@retval	S_FALSE		���s
 */
/***********************************************************************/
HRESULT CPolygon::createVtxBuf(uint VtxSize,uint NumVtx)
{
	//	�������s����
	HRESULT hr = S_OK;

	//	���_�o�b�t�@�̍쐬
	hr = Device_->CreateVertexBuffer(
		VtxSize  * NumVtx,	//���_�� * �T�C�Y
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

		MessageAlert("���_�o�b�t�@�̍쐬�Ɏ��s","error from CPolygon::CreateVtxBuf");
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
	//FVF�ݒ�
#ifdef _DEBUG
	HRESULT hr;
	hr = Device_->SetVertexDeclaration( decl_ );
	if(FAILED(hr))
	{
		MessageAlert("decl�ݒ�G���[","error from CPolygonDraw");
	}
	hr = Device_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	if(FAILED(hr))
	{
		MessageAlert("�`��G���[","error from CPolygonDraw");
	}
#else
	Device_->SetVertexDeclaration( decl_ );
	Device_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
#endif
}

HRESULT CPolygon::LockVtx(void** OutBuf)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	���_�o�b�t�@�̃��b�N
	hr = VtxBuf_->Lock(0,0,(void**)OutBuf,0);

	if(FAILED(hr))
	{
		MessageAlert("���_�o�b�t�@�̃��b�N�Ɏ��s���܂���","CPolygon::LockVtx");
		return hr;
	}
	return hr;
}

HRESULT CPolygon::UnLockVtx()
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	hr = VtxBuf_->Unlock();

	if(FAILED(hr))
	{
		MessageAlert("�A�����b�N�G���[","CPolygon::setPos");
		return hr;
	}

	return hr;
}


HRESULT CPolygon::setPos(const D3DXVECTOR3* Pos,kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->pos = *Pos;	break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setPos(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* Pos;
	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		Pos = &(static_cast<VB_PTNU*>(buf) + VtxNum)->pos;
		Pos->x = x; Pos->y = y; Pos->z = z; break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setUV(const D3DXVECTOR2* UV, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->UV = *UV;	break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setUV(kfloat x,kfloat y, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR2* UV;

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		UV = &(static_cast<VB_PTNU*>(buf) + VtxNum)->UV;
		UV->x = x; UV->y = y;													break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setNormal(const D3DXVECTOR3* NormalVector, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->NormalVec = *NormalVector;	break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setNormal(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* NromalVec;

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		NromalVec = &(static_cast<VB_PTNU*>(buf) + VtxNum)->NormalVec;
		NromalVec->x = x; NromalVec->y = y; NromalVec->z = z; break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setTangent(const D3DXVECTOR3* Tangent, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:(static_cast<VB_PTNU*>(buf) + VtxNum)->Tangent = *Tangent;	break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;}

HRESULT CPolygon::setTangent(kfloat x, kfloat y, kfloat z, kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);
	D3DXVECTOR3* Tangent;

	//	���_�o�b�t�@�̒l�X�V
	switch(CurVtxType_)
	{
	case VBT_POS_TAN_NOR_UV:
		Tangent = &(static_cast<VB_PTNU*>(buf) + VtxNum)->Tangent;
		Tangent->x = x; Tangent->y = y; Tangent->z = z; break;
	default:																	break;
	}

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

HRESULT CPolygon::setVtxBuf(void* VtxBuf,kuint VtxBufType,kuint VtxNum)
{
	//	���ʕϐ�
	HRESULT hr = S_OK;

	if(CurVtxType_ != VtxBufType)
	{
		//	Decl�̍쐬
		D3DVERTEXELEMENT9* Decl;
		Decl = VtxDeclInfo_.getDecl(CurVtxType_);
		SAFE_RELEASE(decl_);
		hr = Device_->CreateVertexDeclaration( Decl, &decl_ );
		if(FAILED(hr))
		{
			MessageAlert("Decl�̍쐬���s","error from CPolygon::setVtxBuf");
			return hr;
		}
	}

	//	�o�b�t�@�擾
	void* buf = NULL;
	LockVtx(&buf);
	if(FAILED(hr))return hr;

	kuint size = VtxDeclInfo_.getVtxBufSize(CurVtxType_);

	memcpy(buf,VtxBuf,size * VtxNum);

	//	�A�����b�N
	hr = VtxBuf_->Unlock();
	if(FAILED(hr))return hr;

	Device_->SetStreamSource( 0, VtxBuf_, 0, size);
	return hr;	
}