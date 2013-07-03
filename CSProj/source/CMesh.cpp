/***********************************************************************/
/*! @file  CMesh.cpp
 *  @brief ���b�V���N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CMesh.h"
#include"CScreen.h"
#include"common.h"
#include"CEffectBase.h"
#include"CCamera.h"


/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] szMeshName �t�@�C���p�X
 *  @retval  
 */
/***********************************************************************/
CMesh::CMesh(LPCSTR szMeshName)
	:_pSumProduct(new uint(1)),
	 _pd3dMeshTexture	(NULL),	
	 _pd3dMesh			(NULL),			
	 _pd3dMeshColor		(NULL),		
	 _pd3dMeshMaterial	(NULL),	
	 _dwNumMaterials	(0	),	
	 _pvec3Vertex		(NULL),		
	 _pwIndex			(NULL),			
	 _szMeshFileName	(NULL),
	 _pEffect			(NULL)
{
	loadMesh(szMeshName);
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] copy 
 */
/***********************************************************************/
CMesh::CMesh(const CMesh& copy)
	:_pd3dMeshTexture	(copy._pd3dMeshTexture	),	
	 _pd3dMesh			(copy._pd3dMesh),			
	 _pd3dMeshColor		(copy._pd3dMeshColor	),		
	 _pd3dMeshMaterial	(copy._pd3dMeshMaterial	),	
	 _dwNumMaterials	(copy._dwNumMaterials	),	
	 _pvec3Vertex		(copy._pvec3Vertex	),		
	 _pwIndex			(copy._pwIndex		),			
	 _szMeshFileName	(copy._szMeshFileName),
	 _pSumProduct		(copy._pSumProduct	),
	 _pEffect			(NULL)
{
	

	*_pSumProduct += 1;
}


/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CMesh::~CMesh()
{
	*_pSumProduct -= 1;

	/////////////////////////
	//	���������
	if(*_pSumProduct == 0)
	{
		SAFE_RELEASE_ARRAY(_pd3dMeshTexture,_dwNumMaterials);	//	�e�N�X�`�����
		SAFE_DELETE_ARRAY(_pd3dMeshColor);						//	���b�V���F�����폜
		SAFE_DELETE_ARRAY(_pd3dMeshMaterial);					//	�}�e���A�����̍폜
		SAFE_DELETE(_pvec3Vertex);								//	���_���̍폜
		SAFE_RELEASE(_pd3dMesh);								//	���b�V���̉��
		SAFE_DELETE_ARRAY(_pwIndex);
		SAFE_DELETE(_pSumProduct);
		_szMeshFileName = NULL;									//	�t�@�C���p�X�̃N���A
	}
}


/***********************************************************************/
/*! @brief ���b�V���ǂݍ���
 * 
 *  @param[in] szMeshName �t�@�C���p�X
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CMesh::loadMesh(LPCSTR szMeshName)
{
	//	�ϐ��錾
	HRESULT					hr = 0;
	LPD3DXBUFFER			pD3DXMatlBuffer;


	//	������
	_pd3dMeshTexture	= NULL;		//	�e�N�X�`���|�C���^
	_pd3dMeshColor		= NULL;		//	���b�V���J���[
	_pd3dMesh			= NULL;		//	�}�e���A����
	_pd3dMeshMaterial	= NULL;		//	���b�V���}�e���A���J���[
	_pvec3Vertex		= NULL;
	_szMeshFileName		= szMeshName;

	//	���b�V���ǂݍ���
	//---���b�V���t�@�C���̓ǂݍ���
	hr = D3DXLoadMeshFromX(
		_szMeshFileName,
		D3DXMESH_SYSTEMMEM,
		D3DDEVICE,
		NULL,
		&pD3DXMatlBuffer,
		NULL,
		&_dwNumMaterials,
		&_pd3dMesh
		);

	loadMaterial(pD3DXMatlBuffer);

	SAFE_RELEASE(pD3DXMatlBuffer);

	loadVertex();

	return hr;
}

/***********************************************************************/
/*! @brief �}�e���A���ǂݍ���
 * 
 *  @param[in,out] pD3DXMatlBuffer 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CMesh::loadMaterial(LPD3DXBUFFER pD3DXMatlBuffer)
{
	HRESULT					hr;
	
	//---�}�e���A���ۑ��p�z��̊m��
	_pd3dMeshColor		= new D3DCOLORVALUE[_dwNumMaterials];
	_pd3dMeshTexture	= new LPDIRECT3DTEXTURE9[_dwNumMaterials];
	_pd3dMeshMaterial	= new D3DMATERIAL9[_dwNumMaterials];

	//---�}�e���A�����o�b�t�@�̃|�C���^�擾
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMatlBuffer->GetBufferPointer();

	char curDir[MAX_PATH];
	int n = 0;

	//---�}�e���A�����o�b�t�@��ۑ�
	for(DWORD dwCnt = 0; dwCnt < _dwNumMaterials; dwCnt++)
	{
		_pd3dMeshColor[dwCnt]			 = d3dxMaterials[dwCnt].MatD3D.Diffuse;
		_pd3dMeshMaterial[dwCnt]		 = d3dxMaterials[dwCnt].MatD3D;
		_pd3dMeshMaterial[dwCnt].Ambient = _pd3dMeshMaterial[dwCnt].Diffuse;
		_pd3dMeshTexture[dwCnt] = NULL;

		memset(curDir,0,sizeof(curDir));
		strcpy(curDir,_szMeshFileName);
		for(n = sizeof(curDir); n >= 0 && curDir[n] != '/'; n--);
		curDir[n+1] = '\0';

		if(d3dxMaterials[dwCnt].pTextureFilename == NULL)
			continue;

		strcat(curDir,d3dxMaterials[dwCnt].pTextureFilename);

		//	�e�N�X�`���ǂݍ���
		hr = D3DXCreateTextureFromFileA(
						D3DDEVICE,
						curDir,//d3dxMaterials[dwCnt].pTextureFilename,
						&_pd3dMeshTexture[dwCnt]);

		if(d3dxMaterials[dwCnt].pTextureFilename &&	FAILED(hr))
		{
			//�G���[���b�Z�[�W
			MessageBox(NULL,"�e�N�X�`���ǂݍ��݃G���[","",MB_OK|MB_ICONWARNING);
		}
	}
	return hr;
}

/***********************************************************************/
/*! @brief ���_���ǂݍ���
 * 
 *  @retval void
 */
/***********************************************************************/
void CMesh::loadVertex()
{

	VERTEX					*d3dvertex;
	TINDEX					*pwIndex;

	/////////////////////////
	//	���_���̎擾
	//----����
	DWORD dwSumVertex;
	DWORD dwSumIndex;

	//----���b�V�����̎擾
	dwSumVertex = _pd3dMesh->GetNumVertices();							//	���_���̎擾
	dwSumIndex = _pd3dMesh->GetNumFaces();								//	�C���f�b�N�X���擾
	_pd3dMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&d3dvertex);	//	���_�o�b�t�@�̎擾
	_pd3dMesh->LockIndexBuffer(D3DLOCK_READONLY,(LPVOID*)&pwIndex);		//	���_�o�b�t�@�̎擾
	_pvec3Vertex = new D3DXVECTOR3[dwSumVertex];						//	���_����ێ�����C���X�^���X�̍쐬
	_pwIndex = new TINDEX[dwSumIndex];									//	���_����ێ�����C���X�^���X�̍쐬
	
	//---���̃R�s�[
	//.....���_
	for(DWORD dwCnt = 0; dwCnt < dwSumVertex; dwCnt++)					
	{
		_pvec3Vertex[dwCnt] = d3dvertex->v;
		d3dvertex++;
	}

	for(DWORD dwCnt = 0; dwCnt < dwSumIndex; dwCnt++)
	{
		_pwIndex[dwCnt] = pwIndex[dwCnt];
	}

	//---�o�b�t�@�̉��
	_pd3dMesh->UnlockVertexBuffer();
	_pd3dMesh->UnlockIndexBuffer();
}


/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @param[in] matView	�r���[���W
 *  @param[in] matWorld ���[���h���W
 *  @retval void
 */
/***********************************************************************/
void CMesh::draw(const D3DXMATRIXA16* matWorld)
{
	for(uint unSun = 0; unSun < _pd3dMesh->GetNumVertices()/2; unSun++)
	{
		(_pvec3Vertex+unSun)->y  += 0.1f;
	}

	if(_pEffect == NULL)
	{
		drawEffectOff(matWorld);
		return;
	}

	_pEffect->draw(this, matWorld);
}


/***********************************************************************/
/*! @brief �G�t�F�N�g�Ȃ��`��
 * 
 *  @param[in] matView �@�r���[���W
 *  @param[in] matWorld  ���[���h���W
 *  @retval void
 */
/***********************************************************************/
void CMesh::drawEffectOff(const D3DXMATRIXA16* matWorld)
{
	/////////////////////////
	//	�}�g���N�X�ϊ�
	D3DDEVICE->SetFVF(FVF_VERTEX_3D);	// ���_�t�H�[�}�b�g�̐ݒ�
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//�r���[���W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatView());			//�J�������W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_WORLD,matWorld);						//���[���h���W�ϊ�

	/////////////////////////
	//	�`�揈��
	for(DWORD dwCnt = 0; dwCnt < _dwNumMaterials; dwCnt++)
	{
		D3DDEVICE->SetMaterial(&_pd3dMeshMaterial[dwCnt]);
		D3DDEVICE->SetTexture(0,_pd3dMeshTexture[dwCnt]);

		_pd3dMesh->DrawSubset(dwCnt);
	}
}

/***********************************************************************/
/*! @brief ���_���擾
 * 
 *  @retval const DWORD 
 */
/***********************************************************************/
const DWORD			CMesh::getSumVertex(){return _pd3dMesh->GetNumVertices();}			
/***********************************************************************/
/*! @brief �t�F�C�X���擾
 * 
 *  @retval const DWORD 
 */
/***********************************************************************/
const DWORD			CMesh::getSumFaces(){return _pd3dMesh->GetNumFaces();}				
/***********************************************************************/
/*! @brief �}�e���A�����擾
 * 
 *  @retval const DWORD 
 */
/***********************************************************************/
const DWORD			CMesh::getMaterials(){return _dwNumMaterials;}						
/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3*	CMesh::getVertexKPtr(){return _pvec3Vertex;}						
/***********************************************************************/
/*! @brief ���_�z��擾
 * 
 *  @param[in] dwVtxID 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3*	CMesh::getVertexKPtr(DWORD dwVtxID){return &_pvec3Vertex[dwVtxID];}	
/***********************************************************************/
/*! @brief �C���f�b�N�X�z��擾
 * 
 *  @param[in] dwIndexId 
 *  @retval const TINDEX& 
 */
/***********************************************************************/
const TINDEX&		CMesh::getIndex(const DWORD dwIndexId){ return _pwIndex[dwIndexId];}
/***********************************************************************/
/*! @brief �e�N�X�`���擾
 * 
 *  @retval LPDIRECT3DTEXTURE9* 
 */
/***********************************************************************/
LPDIRECT3DTEXTURE9*	CMesh::getTexture(){return _pd3dMeshTexture;}
/***********************************************************************/
/*! @brief ���b�V�����擾
 * 
 *  @retval LPD3DXMESH 
 */
/***********************************************************************/
LPD3DXMESH			CMesh::getMesh(){return _pd3dMesh;}
/***********************************************************************/
/*! @brief �}�e���A���J���[�擾
 * 
 *  @retval D3DMATERIAL9* 
 */
/***********************************************************************/
D3DMATERIAL9*		CMesh::getMaterialColor(){return _pd3dMeshMaterial;}


/***********************************************************************/
/*! @brief ���b�V���J���[�ݒ�
 * 
 *  @param[in] fR ���b�h
 *  @param[in] fG �O���[��
 *  @param[in] fB �u���[
 *  @param[in] fA �A���t�@
 *  @retval void
 */
/***********************************************************************/
void CMesh::setMeshColor(const float fR,const float fG,const float fB,const float fA)
{
	this->_pd3dMeshColor->r = fR;	//��
	this->_pd3dMeshColor->g = fG;	//��
	this->_pd3dMeshColor->b = fB;	//��
	this->_pd3dMeshColor->a = fA;	//�A���t�@
}

/***********************************************************************/
/*! @brief �G�t�F�N�g�̐ݒ�
 * 
 *  @param[in] pEffect �G�t�F�N�g
 *  @retval void
 */
/***********************************************************************/
void CMesh::setEffect(CEffectBase* pEffect)
{
	_pEffect = pEffect;
}
