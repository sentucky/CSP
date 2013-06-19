#include"CShadowMap.h"

#include"common.h"
#include"CCamera.h"
#include"CScreen.h"

#include"CMesh.h"

#if 0

CShadowMap::CShadowMap(const char FXFilePath[MAX_PATH])
	:CEffectBase(FXFilePath)
{
	create();
}

CShadowMap::~CShadowMap()
{
}

CShadowMap::CShadowMap(const CShadowMap& src)
	:CEffectBase(src._FXFilePath)
{
}

void CShadowMap::create()
{

	// 頂点宣言
	D3DVERTEXELEMENT9 DECL[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0},
		{0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	HRESULT hr;
	LPD3DXBUFFER error = NULL;

	if(FAILED(hr = D3DXCreateEffectFromFile(
		D3DDEVICE,
		_FXFilePath,
		NULL,
		NULL,
		0,
		NULL,
		&_Effect,
		&error)))
	{
		// コンパイルエラー表示
		if(error != NULL)
		{
			MessageAlert((char*)error->GetBufferPointer(),"error from CShadowMap::create");;
		}
		else
		{
			MessageAlert("ファイル名あってる？","error from CShadowMap::create");
		}
	}


	//	ハンドルの初期化
	
	// テクニック　ハンドル取得
	_techniqueHandle = _Effect->GetTechniqueByName("ShadowMap");
	// カメラ基準：ローカル～射影空間座標変換行列　ハンドル取得
	_wvpHandle = _Effect->GetParameterByName(NULL, "WVP");
	// ライト基準：ローカル～射影空間座標変換行列　ハンドル取得
	_wlpHandle = _Effect->GetParameterByName(NULL, "WLP");
	// ライト基準：ローカル～テクスチャ座標変換行列　ハンドル取得
	_wlpbHandle = _Effect->GetParameterByName(NULL, "WLPB");
	// メッシュ色　ハンドル取得
	_colorHandle = _Effect->GetParameterByName(NULL, "Color");
	// ライト方向　ハンドル取得
	_lightDirHandle = _Effect->GetParameterByName(NULL, "LightDir");
	// 通常テクスチャ　ハンドル取得
	_DecaleTexHandle = _Effect->GetParameterByName( NULL, "DecaleTex" );
	// 影テクスチャ　ハンドル取得
	_ShadowTexHandle = _Effect->GetParameterByName( NULL, "ShadowMap" );


	// エラー用のバッファ開放
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	// 頂点宣言作成
	if(FAILED(hr = D3DDEVICE->CreateVertexDeclaration(
									DECL, 
									&_Decl
									)))
	{
		MessageAlert("頂点宣言間違い！","error from create");
		return;
	}
}

void CShadowMap::draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld)
{
	D3DXVECTOR3 eye    = D3DXVECTOR3(0, 100.0f, 0);
	D3DXVECTOR3 lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up     = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMATRIXA16 lightViewMatrix;
	D3DXMatrixLookAtLH(&lightViewMatrix, &eye, &lookAt, &up);

	// プロジェクション行列作成
	D3DXMATRIXA16 projMatrix;
	D3DXMatrixPerspectiveFovLH(&projMatrix, D3DXToRadian(60.0f), 1, 500.0f, 2500.0f);

	D3DXMATRIXA16 lightVpMatrix = lightViewMatrix * projMatrix;
	D3DXMATRIXA16 cameraVpMatrix = *CCamera::getMatView() * *CSCREEN->getProjPtr();

	_Effect->SetTechnique(_techniqueHandle);
	D3DDEVICE->SetVertexDeclaration(_Decl);

	_Effect->Begin(NULL, 0);
		// 深度テクスチャを作成
		drawDepth(pMesh,matWorld);
		// 作成した深度テクスチャを設定
		_Effect->SetTexture(_ShadowTexHandle, _ShadowTex);
		drawScene();
	_Effect->End();
}


void CShadowMap::drawDepth(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix)
{
	D3DXMATRIXA16 wvpMatrix, wlpMatrix, wlpbMatrix, invMatrix;
	D3DXVECTOR4 color, lightDir;

	D3DXVECTOR4 lightPos = D3DXVECTOR4(0, 100.0f, 0, 1.0f);
	
	// ドーナッツ描画
	lightDir = lightPos * -1.0f;
	D3DXMatrixInverse(&invMatrix, NULL, matWorld);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	D3DXVec4Normalize(&lightDir, &lightDir);

	wvpMatrix = *matWorld * *CCamera::getMatView();
	wlpMatrix = *matWorld * lightVpMatrix;
	wlpbMatrix = wlpMatrix * TEX_MATRIX;

	_Effect->SetMatrix(_wvpHandle, &wvpMatrix);
	_Effect->SetMatrix(_wlpHandle, &wlpMatrix);
	_Effect->SetMatrix(_wlpbHandle, &wlpbMatrix);
	_Effect->SetVector(_lightDirHandle, &lightDir);

	const LPDIRECT3DTEXTURE9* textures = pMesh->getTexture();
	const D3DMATERIAL9* materials = pMesh->getMaterialColor();

	const uint MaterialNum = pMesh->getMaterials();
	for(DWORD i = 0; i < MaterialNum; i++)
	{
		color.x = materials->Diffuse.r;
		color.y = materials->Diffuse.g;
		color.z = materials->Diffuse.b;
		color.w = materials->Diffuse.a;

		_Effect->SetVector(_colorHandle, &color);
		_Effect->SetTexture(_DecaleTexHandle, textures[i]);
		_Effect->BeginPass(1);
		// メッシュの描画
		pMesh->getMesh()->DrawSubset(i);
		_Effect->EndPass();
	}
	/*
	// 地形描画
	lightDir = lightPos * -1.0f;
	D3DXMatrixInverse(&invMatrix, NULL, &_landWorldMatrix);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	D3DXVec4Normalize(&lightDir, &lightDir);

	wvpMatrix = landWorldMatrix_ * cameraVpMatrix_;
	wlpMatrix = landWorldMatrix_ * lightVpMatrix_;
	wlpbMatrix = wlpMatrix * TEX_MATRIX;

	effect_->SetMatrix(wvpHandle_, &wvpMatrix);
	effect_->SetMatrix(wlpHandle_, &wlpMatrix);
	effect_->SetMatrix(wlpbHandle_, &wlpbMatrix);
	effect_->SetVector(lightDirHandle_, &lightDir);
	textures = landModel_->GetTextures();
	materials = landModel_->GetMaterials();
	*/
	for(DWORD i = 0; i < landModel_->GetMaterialNum(); i++)
	{
		color.x = materials->Diffuse.r;
		color.y = materials->Diffuse.g;
		color.z = materials->Diffuse.b;
		color.w = materials->Diffuse.a;

		_Effect->SetVector(colorHandle_, &color);
		_Effect->SetTexture(decaleTexHandle_, textures[i]);
		_Effect->BeginPass(1);
		// メッシュの描画
		landModel_->GetMesh()->DrawSubset(i);
		_Effect->EndPass();
	}
}
#endif