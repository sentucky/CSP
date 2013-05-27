/***********************************************************************/
/*! @file  CSprite.h
 *  @brief �X�v���C�g�N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h�K�[�h
/***********************************************************************/
#pragma once

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include <d3d9.h>
#include <d3dx9.h>
#include"CDevice.h"	//�f�o�C�X�w�b�_
#include"CTexture.h"
#include"common.h"
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


const DWORD kdwColorRevisionMax = 0xffffffff;
/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CSprite
{
	//	�t�����h�o�^
	friend class CSpriteFactory;	///<�X�v���C�g�t�@�N�g��

public:
	explicit CSprite(CTexture* pTexture);
	CSprite(const CSprite& copy);
	virtual~CSprite();

public:
	//---����������
	void init();

	//---�`�揈��
	void draw(
		DWORD SpriteType,
		const D3DXVECTOR3* vec3Pos,
		const D3DXVECTOR3* vec3Rot,
		const D3DXVECTOR3* vec3Scale);		///<	�`�揈��
	void draw(
		DWORD SpriteType,
		const D3DXMATRIXA16* pMatWorld,
		const D3DXMATRIXA16* pMatView);		///<	�`��
	void draw(
		DWORD SpriteType,
		const D3DXMATRIXA16* pmatWorld);	///<	2D�`��

	//---�e�N�X�`���X�v���C�g�̍쐬
	HRESULT create();							///<	�X�v���C�g�����

	//...���S���W�v�Z
	void calcCenter();							///<	���S���W���v�Z���Đݒ�

	//---�l�̐ݒ�
	//....�e�N�X�`���̐ݒ�
	void setTexture(CTexture* pTexture);		///<	�e�N�X�`���ݒ�

	void setCenter(float x, float y, float z);	///<	���S���W�ݒ�
	void setCenter(D3DXVECTOR3* pos);			///<	���S���W�ݒ�

	//....��`�̈�
	void setUV(long lLeft,long lTop,long lRight,long lBottom);	///<	UV�l�̐ݒ�
	void setUV(RECT& );											///<	UV�l�̐ݒ�

	//...�F�␳�l
	void setColorRevision(D3DXCOLOR&);			///<	�F�␳�̐ݒ�
	void setColorRevision(						//	�F�␳�̐ݒ�
		const float fR,
		const float fG,
		const float fB,
		const float fA
		);
	void setColorRevisionR(const float fR);		///<	�F�␳�ʐݒ�R
	void setColorRevisionG(const float fG);		///<	�F�␳�ʐݒ�G
	void setColorRevisionB(const float fB);		///<	�F�␳�ʐݒ�B
	void setColorRevisionA(const float fA);		///<	�F�␳�ʐݒ�A


	//....�F�␳
	D3DCOLOR CSprite::getColorRevision();	///<	�F�␳�̎擾

	//...�e�N�X�`�����̎擾
	const D3DXIMAGE_INFO* getTextureInfo();	///<	�e�N�X�`�����擾


protected:
	CTexture*			_pTexture;		//!<	�e�N�X�`��
	LPD3DXSPRITE		_pD3DSprite;	//!<	�X�v���C�g
	D3DXVECTOR3			_vecCenter;		//!<	�X�v���C�g���S�_
	RECTEX				_UV;			//!<	Rect�̒l
	D3DCOLOR			_colorRevision;	//!<	�F�␳�̒l
	BOOL				_bDrawFlg;		//!<	�`��t���O
};
//EOF