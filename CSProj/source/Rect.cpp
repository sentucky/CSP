//================================================================================
// Rect.cpp
//
// 3D��`�`��N���X											
//--------------------------------------------------------------------------------
// �X�V����
//	2011/9/25
//		�쐬�J�n
//================================================================================
//================================================================================
// �C���N���[�h
//================================================================================
#include "Rect.h"
#include"CDevice.h"

//================================================================================
// �N���X�֐���`
//================================================================================

//�R���X�g���N�^
CRect::CRect()
{
	//������
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

//�f�X�g���N�^
CRect::~CRect()
{

}

//�`��
void CRect::Draw()
{
	//�X�V
	if (mIsUpdate)
		this->Update();

	//FVF�̐ݒ�
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);

	//�e�N�X�`���ݒ�
	mDevice_pr->SetTexture(0,mTexture_pr);

	//�|���S���`��
	mDevice_pr->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,mVtx,sizeof(VERTEX_RECT));
}


//�X�V
void CRect::Update(){

	//���_
	mVtx[0].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[1].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,-(mSize.y) / 2.0f,0.0f);
	mVtx[2].vtx = D3DXVECTOR3(-(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);
	mVtx[3].vtx = D3DXVECTOR3(+(mSize.x) / 2.0f,+(mSize.y) / 2.0f,0.0f);
	
	//�J���[
	for (int i = 0 ; i< SQUARE_VTX ; i++)
	{
		mVtx[i].diffuse = mDeffuse[i];
	}

	if (!mDevice_pr)
		mDevice_pr  = D3DDEVICE;

	mIsUpdate = false;
}