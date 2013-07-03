#ifndef ___CEFFECTBLUR___
#define ___CEFFECTBLUR___	///<	�C���N���[�h�K�[�h

#include"CEffectBase.h"
#include"CEffectBlur.h"
#include"CSingleton.h"

class CMesh;

#define EFFECTBLUR CEffectBlur::getInst()

class CEffectBlur:public CEffectBase,public CSingleton<CEffectBlur>
{
	friend class CSingleton<CEffectBlur>;
private:
	CEffectBlur();						// �R���X�g���N�^
	~CEffectBlur();				// �f�X�g���N�^
public:
	void release();							// �J���֐�
	HRESULT init();							// �����֐�
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);
private:
	void drawVelocityMap();					// ���x�}�b�v

	void create();

	static const D3DVERTEXELEMENT9 DECL[];


private:
	D3DXMATRIXA16	_worldMatrix ;			//!< ���[���h�s��
	D3DXMATRIXA16	_lastWVMatrix ;			//!< 1�t���[���O���[���h�r���[�s��
	LPD3DXEFFECT	_effect ;				//!< �G�t�F�N�g
	D3DXHANDLE		_techniqueHandle ;		//!< �e�N�j�b�N �n���h��
	D3DXHANDLE		_wvHandle ;				//!< ���[���h *�r���[�s�� �n���h��
	D3DXHANDLE		_lastWVHandle ;			//!< �P�t���[���O���[���h *�r���[�s�� �n���h��
	D3DXHANDLE		_projHandle ;			//!< �v���W�F�N�V�����s�� �n���h��
	D3DXHANDLE		_lightDirHandle ;		//!< ���C�g�����n���h��
	D3DXHANDLE		_colorHandle ;			//!< �}�e���A���F�n���h��
	LPDIRECT3DVERTEXDECLARATION9 _decl ;	//!< ���_�錾
	CMesh*			_model ;				//!< ���f���f�[�^
	FLOAT			_rotate ;				//!< ��]�p
};



#endif