/***********************************************************************/
/*! @file  CEffectToon.cpp
 *  @brief �g�D�[���V�F�[�f�B���O
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CEffectToon.h"
#include"CDevice.h"
#include"CScreen.h"
#include"CMesh.h"
#include"CCamera.h"
/***********************************************************************/
/*! @namespace EFFECTTOON
 *  @brief 
 * 
 */
/***********************************************************************/
namespace EFFECTTOON
{
D3DVERTEXELEMENT9 DECL[] =
{
	{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0},
	{0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};
};

/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CEffectToon::CEffectToon(
	):CEffectBase("data/fx/Toon.fx"),
	_techTechHandle(NULL),
	_paramWVP(NULL),
	_paramLight(NULL),	
	_paramColor(NULL),
	_paramDecalTex(NULL),
	_paramToonTex(NULL),
	_lightDir(NULL)
{
	strcpy(_ToonTexPath,"data/texture/ToonTex.bmp");
	create();
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CEffectToon::~CEffectToon()
{
	SAFE_RELEASE(_pToonTex);
}


/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in,out] copy 
 */
/***********************************************************************/
CEffectToon::CEffectToon(const CEffectToon& copy):CEffectBase(NULL){}


/***********************************************************************/
/*! @brief �G�t�F�N�g�쐬
 * 
 *  @retval void
 */
/***********************************************************************/
void CEffectToon::create()
{

	HRESULT hr;
	LPD3DXBUFFER error = NULL;

	// �V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	if(FAILED(hr = D3DXCreateEffectFromFile(
					D3DDEVICE,					// LPDIRECT3DDEVICE9�ւ̃|�C���^�[
					_FXFilePath,					// �G�t�F�N�g�t�@�C���ւ̃p�X
					NULL,						// �v���v���Z�b�T��`��p�ӂ��Ă���ꍇ�i�g�p���Ȃ��j
					NULL,						// #include �[�����߂̏����Ɏg���i�g�p���Ȃ��j
					0,							// D3DXSHADER �Ŏ��ʂ����R���p�C���I�v�V����
					NULL,						// �قȂ�G�t�F�N�g�ԂŃp�����[�^�����L����ꍇ�Ɏg�p����i�g�p���Ȃ��j
					&_Effect,					// �R���p�C�����ꂽ�G�t�F�N�g���i�[�����
					&error)))					// �R���p�C���G���[�̈ꗗ���i�[�����o�b�t�@
	{
		// �R���p�C���G���[�\��
		if(error != NULL)
		{
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffectToon::create");;
		}
		else
		{
			MessageAlert("�t�@�C���������Ă�H","error from CEffectToon::create");
		}
	}

	// �G���[�p�̃o�b�t�@�J��
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	// �g�D�[���p�̃e�N�X�`���쐬
	if(FAILED(D3DXCreateTextureFromFileEx(
								D3DDEVICE,			// LPDIRECT3DDEVICE9�ւ̃|�C���^�[
                                _ToonTexPath,		// �t�@�C����
                                D3DX_DEFAULT,		// ��(�s�N�Z��)
                                D3DX_DEFAULT,		// ����(�s�N�Z��)
                                1,					// �~�v�}�b�v���x��
                                0,					// �`��^�[�Q�b�g���T�[�t�F�[�X�Ƃ��Ďg���ꍇ�ݒ�i����͎g�p���Ȃ��j
                                D3DFMT_UNKNOWN,		// �s�N�Z���t�H�[�}�b�g
                                D3DPOOL_MANAGED,	// �e�N�X�`���̔z�u��ƂȂ郁�����N���X���L�q
                                D3DX_DEFAULT,		// �C���[�W���t�B���^�����O������@
                                D3DX_DEFAULT,		// �C���[�W���t�B���^�����O������@
                                0x0,				// �J���[�L�[ �J���[�L�[�𖳌��ɂ���ꍇ��0���w�肷��
                                NULL,				// �\�[�X�C���[�W�t�@�C�����̃f�[�^�̋L�q
                                NULL,				// �i�[����256�F�p���b�g��\��
                                &_pToonTex		// �쐬���ꂽ�e�N�X�`���I�u�W�F�N�g��\��
								)))
	{
		MessageAlert("�e�N�X�`���[���[�h���s�I","error from CEffectToon::Create");
	}

	// �e�N�j�b�N�@�n���h���擾
	_techTechHandle = _Effect->GetTechniqueByName("Toon");
	// �J������F���[�J���`�ˉe��ԍ��W�ϊ��s��@�n���h���擾
	_paramWVP = _Effect->GetParameterByName(NULL, "WVP");
	// ���b�V���F�@�n���h���擾
	_paramColor = _Effect->GetParameterByName(NULL, "Color");
	// ���C�g�����@�n���h���擾
	_paramLight = _Effect->GetParameterByName(NULL, "LightDir");
	// �ʏ�e�N�X�`���@�n���h���擾
	_paramDecalTex= _Effect->GetParameterByName( NULL, "DecalTex" );
	// �e�e�N�X�`���@�n���h���擾
	_paramToonTex= _Effect->GetParameterByName( NULL, "ToonTex" );

	createVtxDecl(EFFECTTOON::DECL);
}


/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @param[in] pMesh 
 *  @param[in] pMatView 
 *  @param[in] matWorld 
 *  @retval void
 */
/***********************************************************************/
void CEffectToon::draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld)
{
	D3DXMATRIXA16 wvpMatrix,invMatrix;
	wvpMatrix = (*matWorld) * (*CCamera::getMatView()) * (*CSCREEN->getProjPtr());


	//	�e�N�j�b�N�w��
	_Effect->SetTechnique(_techTechHandle);

	//	�p�����^�w��
	_Effect->SetMatrix(_paramWVP,&wvpMatrix);
	_Effect->SetTexture(_paramToonTex,_pToonTex);


	//	���C�g�ݒ�
	D3DXVECTOR4 lightDir(1.0f,1.0f,1.0f,1.0f);
	D3DXVECTOR4* plightDir = NULL;

	if(_lightDir == NULL)
	{
		plightDir = &lightDir;
	}
	else
	{
		plightDir = _lightDir;
	}

	D3DXMatrixInverse(&invMatrix,NULL,matWorld);

	D3DXVec4Transform(&lightDir, plightDir, &invMatrix);
	D3DXVec4Normalize(&lightDir, plightDir);

	_Effect->SetVector(_paramLight,&lightDir);

	uint passNum;
	_Effect->Begin(&passNum,0);

	D3DXVECTOR4 Color;

	const DWORD dwSumMaterials = pMesh->getMaterials();

	for(uint unCnt = 0; unCnt < passNum; ++unCnt)
	{
		_Effect->BeginPass(unCnt);
		const LPDIRECT3DTEXTURE9* pTex = pMesh->getTexture();
		const D3DMATERIAL9*	pMaterialColor = pMesh->getMaterialColor(); 
		for(DWORD dwCnt2 = 0; dwCnt2 < dwSumMaterials; ++dwCnt2)
		{
			Color.x = pMaterialColor->Diffuse.r;
			Color.y = pMaterialColor->Diffuse.g;
			Color.z = pMaterialColor->Diffuse.b;
			Color.w = pMaterialColor->Diffuse.a;

			_Effect->SetVector(_paramColor,&Color);
			_Effect->SetTexture(_paramDecalTex,pTex[dwCnt2]);

			_Effect->CommitChanges();
			++pMaterialColor;

			pMesh->getMesh()->DrawSubset(dwCnt2);
		}
		_Effect->EndPass();
	}
	_Effect->End();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] lightDir 
 *  @retval void
 */
/***********************************************************************/
void CEffectToon::setlightDir(D3DXVECTOR4* lightDir)
{
	_lightDir = lightDir;
}