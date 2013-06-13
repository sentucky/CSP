//================================================================================
// Rect.h
//
// 3D��`�`��N���X											
//--------------------------------------------------------------------------------
// �X�V����
//	2011/12/17
//		�쐬�J�n
//================================================================================
#pragma once

//================================================================================
// �}�N����`
//================================================================================
//���_�t�H�[�}�b�g(���_���W[2D] / ���ˌ� / �e�N�X�`�����W)
#define FVF_VERTEX_RECT			(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//================================================================================
// �C���N���[�h
//================================================================================
#include"CDevice.h"

//================================================================================
// �\���̒�`
//================================================================================
//��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;
	D3DCOLOR diffuse;
	D3DXVECTOR2 uv;
}VERTEX_RECT;

//================================================================================
// �N���X��`
//================================================================================
class CRect
{
	private:
		//===========================
		// �N���X���萔
		//===========================
		static const int SQUARE_VTX = 4;
	public:
		//===========================
		// �����o�֐� - ���J
		//===========================
		//�R���X�g���N�^
		CRect();
		//�f�X�g���N�^
		~CRect();

		//�`��
		void Draw(void);

		//�e�N�X�`���Z�b�g
		CRect* SetTexture(LPDIRECT3DTEXTURE9 p)					{mTexture_pr = p; return this;}

		//�T�C�Y�̎擾/�i�[
		CRect* SetSize(D3DXVECTOR2 size)						{mSize = size; mIsUpdate = true; return this;}
		CRect* SetSize(float sizeX,float sizeY)					{mSize.x = sizeX;mSize.y = sizeY; mIsUpdate = true; return this;}
		CRect* SetSizeX(float sizeX)							{mSize.x = sizeX; mIsUpdate = true; return this;}
		CRect* SetSizeY(float sizeY)							{mSize.y = sizeY; mIsUpdate = true; return this;}

		D3DXVECTOR2 GetSize()									{return mSize;}
		float GetSizeX()										{return mSize.x;}
		float GetSizeY()										{return mSize.y;}

		//�J���[�̎擾/�i�[
		CRect* SetColor(int no,float r,float g,float b)			{mDeffuse[no].r = r;mDeffuse[no].g = g;mDeffuse[no].b = b; mIsUpdate = true; return this;}
		CRect* SetColor(float r,float g,float b)				{SetColor(0,r,g,b); SetColor(1,r,g,b); SetColor(2,r,g,b); SetColor(3,r,g,b); mIsUpdate = true; return this;}
		D3DXCOLOR GetColor(int no)								{return mDeffuse[no];}

		//�A���t�@�l�̎擾/�i�[
		CRect* SetAlpha(float a)								{mDeffuse[0].a = mDeffuse[1].a = mDeffuse[2].a = mDeffuse[3].a = a; mIsUpdate = true; return this;}
		float GetAlpha()										{return mDeffuse[0].a;}

		//UV�̎擾/�i�[
		CRect* SetUV(int no,D3DXVECTOR2 uv)						{mVtx[no].uv = uv; return this;}
		D3DXVECTOR2 GetUV(int no)								{return mVtx[no].uv;}
	private:
		//===========================
		// �����o�֐� - ����J
		//===========================
		//�X�V
		void Update(void);

		//===========================
		// �����o�ϐ� - ����J
		//===========================
		//�`����
		VERTEX_RECT				 mVtx[SQUARE_VTX];		//���_�z��
		LPDIRECT3DTEXTURE9		 mTexture_pr;			//�e�N�X�`���|�C���^
		LPDIRECT3DDEVICE9		 mDevice_pr;			//DirectX�f�o�C�X

		bool					 mIsUpdate;				//�X�V�̉�
		D3DXVECTOR2				 mSize;					//�T�C�Y
		D3DXCOLOR				 mDeffuse[SQUARE_VTX];	//�J���[
};