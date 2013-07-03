#include"CEffectBlur.h"
#include"CDevice.h"
#include"CMesh.h"
#include"CCamera.h"
#include"CScreen.h"

const D3DVERTEXELEMENT9 CEffectBlur::DECL[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0},
		D3DDECL_END()
	};

// ���_�錾

CEffectBlur::CEffectBlur() :CEffectBase("data/fx/MotionBlur.fx"),
	_effect(NULL),
	_techniqueHandle(NULL),
	_wvHandle(NULL),
	_lastWVHandle(NULL),
	_projHandle(NULL),
	_lightDirHandle(NULL),
	_colorHandle(NULL),
	_decl(NULL),
	_model(NULL),
	_rotate(0.0f)
{
	init();
}

CEffectBlur::~CEffectBlur()
{
	release();
}

void CEffectBlur::create(){
}

void CEffectBlur::release()
{
	if(_effect != NULL)
	{
		_effect->Release();
		_effect = NULL;
	}
	if(_decl != NULL)
	{
		_decl->Release();
		_decl = NULL;
	}

	_techniqueHandle = NULL;
	_wvHandle = NULL;
	_lastWVHandle = NULL;
	_projHandle = NULL;
	_lightDirHandle = NULL;
	_colorHandle = NULL;

}

//-------------------------------------------------------------------------------------------------
/** 
 * @brief	�����֐�
 */
HRESULT CEffectBlur::init()
{
	release();

	// �V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	HRESULT hr;
	LPD3DXBUFFER error = NULL;
	if(FAILED(hr = D3DXCreateEffectFromFile(
					D3DDEVICE,					// LPDIRECT3DDEVICE9�ւ̃|�C���^�[
					"data/fx/MotionBlur.fx",	// �G�t�F�N�g�t�@�C���ւ̃p�X
					NULL,						// �v���v���Z�b�T��`��p�ӂ��Ă���ꍇ�i�g�p���Ȃ��j
					NULL,						// #include �[�����߂̏����Ɏg���i�g�p���Ȃ��j
					0,							// D3DXSHADER �Ŏ��ʂ����R���p�C���I�v�V����
					NULL,						// �قȂ�G�t�F�N�g�ԂŃp�����[�^�����L����ꍇ�Ɏg�p����i�g�p���Ȃ��j
					&_effect,					// �R���p�C�����ꂽ�G�t�F�N�g���i�[�����
					&error)))					// �R���p�C���G���[�̈ꗗ���i�[�����o�b�t�@
	{
		// �R���p�C���G���[�\��
		if(error != NULL)
		{
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffectBlur");
		}
		else
		{
			MessageAlert("�t�@�C�������m�F���Ă�������","error from CEffectBlur");
		}

		return E_FAIL;
	}

	// �e�N�j�b�N�@�n���h���擾
	_techniqueHandle = _effect->GetTechniqueByName("Blur");
	// ���[���h�r���[�s��@�n���h���擾
	_wvHandle = _effect->GetParameterByName(NULL, "WV");
	// 1�t���[���O���[���h�r���[�s��@�n���h���擾
	_lastWVHandle = _effect->GetParameterByName(NULL, "LastWV");
	// �v���W�F�N�V�����s��@�n���h���擾
	_projHandle = _effect->GetParameterByName(NULL, "PROJ");
	// ���C�g�����@�n���h���擾
	_lightDirHandle = _effect->GetParameterByName(NULL, "LightDir");
	// �}�e���A���F�@�n���h���擾
	_colorHandle = _effect->GetParameterByName(NULL, "Color");

	// �G���[�p�̃o�b�t�@�J��
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	// ���_�錾�쐬
	if(FAILED(hr = D3DDEVICE->CreateVertexDeclaration(
									DECL, 
									&_decl
									)))
	{
		MessageAlert("���_�錾�ԈႢ�I","error from CEffectBlur");
		return E_FAIL;
	}

	// ���[���h�s�񏉊���
	D3DXMatrixIdentity(&_worldMatrix);
	D3DXMatrixIdentity(&_lastWVMatrix);

	// ���N���X�̏����֐��Ăяo��
}

//-------------------------------------------------------------------------------------------------
/** 
 * @brief	�`��֐�
 */
void CEffectBlur::draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld)
{
	_model = pMesh;
	D3DXMATRIXA16 wvMatrix, invMatrix;
	D3DXVECTOR4 color;

	// ���[���h�r���[�s��쐬
	D3DXMatrixMultiply(&wvMatrix, &_worldMatrix, CCamera::getMatView());

	// ���C�g���������[�J�����W�ɕϊ�
	D3DXMatrixInverse(&invMatrix, NULL, &_worldMatrix);
	D3DXVECTOR4 lightDir(-1.0f, -1.0f, -1.0f, 0.0f);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	lightDir.w = 0.0f;
	D3DXVec4Normalize(&lightDir, &lightDir);

	// ���_�錾�w��
	D3DDEVICE->SetVertexDeclaration(_decl);

	// �e�N�j�b�N�w��
	_effect->SetTechnique(_techniqueHandle);

	// ���[���h�r���[�s��o�^
	_effect->SetMatrix(_wvHandle, &wvMatrix);
	// �P�t���[���O���[���h�r���[�s��o�^
	_effect->SetMatrix(_lastWVHandle, &_lastWVMatrix);
	// �v���W�F�N�V�����s��o�^
	_effect->SetMatrix(_projHandle, CSCREEN->getProjPtr());
	// ���̃t���[���Ŏg���P�t���[���O�̃��[���h�r���[�s���ޔ������Ă���
	_lastWVMatrix = wvMatrix;

	// ���C�g�����o�^
	_effect->SetVector(_lightDirHandle, &lightDir);

	// �`��J�n
	UINT passNum;
	_effect->Begin(&passNum, 0);
	for(UINT i = 0; i < passNum; i++)
	{
		// �p�X�̕`��J�n
		_effect->BeginPass(i);
		const LPDIRECT3DTEXTURE9* textures = _model->getTexture();
		const D3DMATERIAL9* materials = _model->getMaterialColor();
		for(DWORD j = 0; j < _model->getMaterials(); j++)
		{
			color.x = materials[j].Diffuse.r;
			color.y = materials[j].Diffuse.g;
			color.z = materials[j].Diffuse.b;
			color.w = materials[j].Diffuse.a;

			// �}�e���A���F�o�^
			_effect->SetVector(_colorHandle, &color);
			
			// ���b�V���̕`��
			_effect->CommitChanges();
			_model->getMesh()->DrawSubset(j);
		}
		// �p�X�̕`��I��
		_effect->EndPass();
	}
	// �`��I��
	_effect->End();
}
