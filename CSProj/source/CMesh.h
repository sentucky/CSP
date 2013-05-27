/***********************************************************************/
/*! @file  CMesh.h
 *  @brief ���b�V���N���X
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
#include"CDevice.h"
#include"common.h"
/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CEffectBase;

/***********************************************************************/
//	�\���̒�`
/***********************************************************************/
typedef struct _D3DVERTEX
{
	D3DXVECTOR3 v;
	float   nx,ny,nz;
	float   XXXX;
	float   Corrdsx,Coordsy;
}VERTEX;

struct BVERTEX {
	D3DXVECTOR3	pos;
	D3DXVECTOR3	norm;
	D3DXVECTOR2	tex;
};

struct TINDEX
{
	WORD A;
	WORD B;
	WORD C;
};

/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CMesh 
{

	friend class CMeshFactory;
	friend class CModel;
	FRIEND_DELETE
	FRIEND_RELEASE
public:
	CMesh(LPCSTR szMeshName);	///<	�R���X�g���N�^
	CMesh(const CMesh& copy);	///<	�R�s�[�R���X�g���N�^
	~CMesh();					///<	�f�X�g���N�^

public:
	void draw(const D3DXMATRIXA16* matWorld);							///< �`��ݒ�

private:
	void drawEffectOff(const D3DXMATRIXA16* matWorld);					///<	�G�t�F�N�g�Ȃ��`��

public:
	const DWORD			getSumVertex();					///< ���_���̎擾
	const DWORD			getSumFaces();					///< �t�F�C�X���̎擾
	const DWORD			getMaterials();					///< �}�e���A�������̎擾
	const D3DXVECTOR3*	getVertexKPtr();				///< ���_�z��̐擪�̎Q�Ƃ�Ԃ�
	const D3DXVECTOR3*	getVertexKPtr(DWORD dwVtxID);	///< ���_�z��̐擪�̎Q�Ƃ�Ԃ�
	const TINDEX&		getIndex(const DWORD dwIndexId);	///<	�C���f�b�N�X�擾

	LPDIRECT3DTEXTURE9*	getTexture();		///<	�e�N�X�`�����擾
	LPD3DXMESH			getMesh();			///<	���b�V�����擾
	D3DMATERIAL9*		getMaterialColor();	///<	�}�e���A���J���[�擾

	void setMeshColor(
		const float r,
		const float g,
		const float b,
		const float a);	///<	���b�V���J���[�ݒ�
	void setEffect(CEffectBase* pEffect);	///<	�G�t�F�N�g�ݒ�


private:
	HRESULT loadMesh(LPCSTR szMeshName);				///<	���b�V���ǂݍ���
	HRESULT loadMaterial(LPD3DXBUFFER pD3DXMatlBuffer);	///<	�}�e���A���֘A���ǂݍ���
	void	loadVertex();								///<	���_���擾
	void	clone();									///<	�N���[���쐬

protected:
	LPDIRECT3DTEXTURE9*	_pd3dMeshTexture;	///<	�e�N�X�`���|�C���^
	LPD3DXMESH			_pd3dMesh;			///<	���b�V���|�C���^
	D3DCOLORVALUE*		_pd3dMeshColor;		///<	���b�V���J���[
	D3DMATERIAL9*		_pd3dMeshMaterial;	///<	���b�V���}�e���A���J���[
	DWORD				_dwNumMaterials;	///<	�}�e���A����
	D3DXVECTOR3*		_pvec3Vertex;		///<	���_���
	TINDEX*				_pwIndex;			///<	���_���
	LPCSTR				_szMeshFileName;	///<	���b�V���t�@�C����
	uint*				_pSumProduct;		///<	����+������
	CEffectBase*		_pEffect;			///<	�G�t�F�N�g�N���X
};
//EOF