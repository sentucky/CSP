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
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
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
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CRect::~CRect()
{

}

//�`��
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CRect::Draw()
{
	//�X�V
	if (mIsUpdate)
		this->Update();

	D3DMATERIAL9 materials2;
	materials2.Specular.a = 1.0f;
	materials2.Ambient .a = 1.0f;
	materials2.Diffuse.b = 	materials2.Diffuse.g = 	materials2.Diffuse.r = 	materials2.Diffuse.a = 1.0f;
	materials2.Power = 1.0f;
	materials2.Emissive.b = materials2.Emissive.g = materials2.Emissive.r = 0.25f;
	materials2.Emissive.a = 1.0f;


	//FVF�̐ݒ�
	mDevice_pr->SetFVF(FVF_VERTEX_RECT);

	//�e�N�X�`���ݒ�
	mDevice_pr->SetTexture(0,mTexture_pr);

	mDevice_pr->SetMaterial((D3DMATERIAL9*)&materials2);

	//�|���S���`��
	mDevice_pr->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,mVtx,sizeof(VERTEX_RECT));
}


//�X�V
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
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
