/***********************************************************************/
/*! @file  CEffect.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CEffect.h"
#include"CDevice.h"
#include"CMesh.h"
#include"CScreen.h"
#include"CCamera.h"
// ���_�錾
D3DVERTEXELEMENT9 DECL[] =
{
	{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0},
	{0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};

/***********************************************************************/
/*! @brief 
 *  @param[in] constcharFXFilePath[MAX_PATH] 
 *  @param[in] constcharTechnicHandle[MAX_PATH] 
 *  @param[in] constcharTextureHandle[MAX_PATH] 
 *  @param[in] constcharWVPHandle[MAX_PATH] 
 */
/***********************************************************************/
CEffect::CEffect(
	const char FXFilePath[MAX_PATH],
	const char TechnicHandle[MAX_PATH],
	const char TextureHandle[MAX_PATH],
	const char WVPHandle[MAX_PATH]
):CEffectBase(FXFilePath),
	_TechniqueHandle(TechnicHandle),
	_TextureHandle(TextureHandle),
	_WVPHandle(WVPHandle)
{
	create();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CEffect::~CEffect()
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CEffect::create(
)
{
	HRESULT hr;
	LPD3DXBUFFER error = NULL;

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
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffect::create");
		}
		else
		{
			MessageAlert("�t�@�C����������܂���","error from CEffect::create");
		}
	}

	_TechniqueHandle = _Effect->GetTechniqueByName(_TechniqueHandle);		//	�e�N�j�b�N�n���h���擾

	_TextureHandle = _Effect->GetParameterByName(NULL,_TextureHandle);	//	�e�N�X�`���n���h���擾

	_WVPHandle = _Effect->GetParameterByName(NULL,_WVPHandle);			//	���[���h�r���[�v���W�F�N�V�����s��n���h���擾

	//	�G���[�o�b�t�@���
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	//	���_�錾
	createVtxDecl(DECL);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] pMesh 
 *  @param[in] matView 
 *  @param[in] matWorld 
 *  @retval void
 */
/***********************************************************************/
void CEffect::draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld)
{
	D3DXMATRIXA16 WVPMatrix;
	D3DDEVICE->SetFVF(FVF_VERTEX_3D);	// ���_�t�H�[�}�b�g�̐ݒ�

	D3DDEVICE->SetVertexDeclaration(getDecl());

	_Effect->SetTechnique(_TechniqueHandle);

	WVPMatrix = *matWorld * *CCamera::getMatView() * *CSCREEN->getProjPtr();

	_Effect->SetMatrix(_WVPHandle,&WVPMatrix);

	_Effect->Begin(NULL,0);

	const LPDIRECT3DTEXTURE9* pTexture  = pMesh->getTexture();
	const DWORD				  Materials = pMesh->getMaterials();
	
	for(DWORD dwCnt = 0; dwCnt < Materials; ++dwCnt)
	{
		_Effect->SetTexture(_TextureHandle,*pTexture);
		pTexture+=1;
		
		_Effect->BeginPass(0);

		pMesh->getMesh()->DrawSubset(dwCnt);
	
		_Effect->EndPass();
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] TechHandle 
 *  @retval void
 */
/***********************************************************************/
void CEffect::setTechniqueHandle( const D3DXHANDLE TechHandle)
{
	strcpy(
		(char*)(_TechniqueHandle),
		(const char*)(TechHandle)
		);
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] TexHandle 
 *  @retval void
 */
/***********************************************************************/
void CEffect::setTextureHandle( const D3DXHANDLE TexHandle)
{
	strcpy(
		(char*)(_TextureHandle),
		(const char*)(TexHandle)
		);
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] WVPHandle 
 *  @retval void
 */
/***********************************************************************/
void CEffect::setWVPHandle( const D3DXHANDLE WVPHandle)
{
	strcpy(
		(char*)(_WVPHandle),
		(const char*)(WVPHandle)
		);
}


