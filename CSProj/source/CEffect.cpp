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
// 頂点宣言
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
		D3DDEVICE,					// LPDIRECT3DDEVICE9へのポインター
		_FXFilePath,					// エフェクトファイルへのパス
		NULL,						// プリプロセッサ定義を用意している場合（使用しない）
		NULL,						// #include 擬似命令の処理に使う（使用しない）
		0,							// D3DXSHADER で識別されるコンパイルオプション
		NULL,						// 異なるエフェクト間でパラメータを共有する場合に使用する（使用しない）
		&_Effect,					// コンパイルされたエフェクトが格納される
		&error)))					// コンパイルエラーの一覧が格納されるバッファ
	{
		// コンパイルエラー表示
		if(error != NULL)
		{
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffect::create");
		}
		else
		{
			MessageAlert("ファイルが見つかりません","error from CEffect::create");
		}
	}

	_TechniqueHandle = _Effect->GetTechniqueByName(_TechniqueHandle);		//	テクニックハンドル取得

	_TextureHandle = _Effect->GetParameterByName(NULL,_TextureHandle);	//	テクスチャハンドル取得

	_WVPHandle = _Effect->GetParameterByName(NULL,_WVPHandle);			//	ワールドビュープロジェクション行列ハンドル取得

	//	エラーバッファ解放
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	//	頂点宣言
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
	D3DDEVICE->SetFVF(FVF_VERTEX_3D);	// 頂点フォーマットの設定

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


