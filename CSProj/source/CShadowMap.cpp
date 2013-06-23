#include"CShadowMap.h"

#include"common.h"
#include"CCamera.h"
#include"CScreen.h"

#include"CMesh.h"

#if 1
static const D3DXMATRIXA16 TEX_MATRIX(
						0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, -0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.5f, 0.5f, 0.0f, 1.0f
					);


CShadowMap::CShadowMap(
	const char path[MAX_PATH],
	const char FXFilePath[MAX_PATH]
)
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
	// 影用のテクスチャ作成
	if(FAILED(hr = D3DDEVICE->CreateTexture(
			2048,
			2048,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&_ShadowTex,
			NULL
		)))
	{
		//ERROR_MSG_BOX("影テクスチャ作成失敗！");
		return ;
	}

	// テクスチャへ描画するためのサーフェスを取得
	if(FAILED(hr = _ShadowTex->GetSurfaceLevel(0, &shadowSurf_)))
	{
		//ERROR_MSG_BOX("サーフェス取得失敗！");
		return ;
	}

	// 影描画に使用するZバッファ作成
	if(FAILED(hr = D3DDEVICE->CreateDepthStencilSurface(
			2048,
			2048,
			D3DFMT_D24S8,
			D3DMULTISAMPLE_NONE,
			0,
			TRUE,
			&shadowTexZ_,
			NULL
		)))
	{
		//ERROR_MSG_BOX("影用Zバッファ作成失敗！");
		return ;
	}

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
	D3DXVECTOR3 eye    = D3DXVECTOR3(0, 600, 600);
	D3DXVECTOR3 lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up     = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMATRIXA16 lightViewMatrix;
	D3DXMatrixLookAtLH(&lightViewMatrix, &eye, &lookAt, &up);

	// プロジェクション行列作成
	D3DXMATRIXA16 projMatrix;
	D3DXMatrixPerspectiveFovLH(&projMatrix, D3DXToRadian(60.0f), 1, 500.0f, 2500.0f);

	D3DXMATRIXA16 lightVpMatrix = lightViewMatrix * projMatrix;

	_Effect->SetTechnique(_techniqueHandle);
	D3DDEVICE->SetVertexDeclaration(_Decl);

	_Effect->Begin(NULL, 0);

	draw1(pMesh,matWorld,&lightVpMatrix);

	_Effect->SetTexture(_ShadowTexHandle, _ShadowTex);

	draw2(pMesh,matWorld,&lightVpMatrix);

	_Effect->End();
	///*

	{
		D3DDEVICE->SetTextureStageState(0,D3DTSS_COLOROP,	D3DTOP_SELECTARG1);
		D3DDEVICE->SetTextureStageState(0,D3DTSS_COLORARG1,	D3DTA_TEXTURE);
		D3DDEVICE->SetTextureStageState(1,D3DTSS_COLOROP,    D3DTOP_DISABLE);
		float scale = 256.0f;
		typedef struct {FLOAT p[4]; FLOAT tu, tv;} TVERTEX;
		TVERTEX Vertex[4] = {
			{    0,    0,0, 1, 0, 0,},
			{scale,    0,0, 1, 1, 0,},
			{scale,scale,0, 1, 1, 1,},
			{    0,scale,0, 1, 0, 1,},
		};
		D3DDEVICE->SetTexture(0, _ShadowTex);
		D3DDEVICE->SetVertexShader(NULL);
		D3DDEVICE->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
		D3DDEVICE->SetPixelShader(0);
		D3DDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Vertex, sizeof(TVERTEX));
		D3DDEVICE->SetTexture(0, NULL);
	}
	//*/
}

void CShadowMap::draw1(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix)
{
	LPDIRECT3DSURFACE9 oldBackBuffer, oldZBuffer;
	D3DVIEWPORT9 oldViewport;

	D3DDEVICE->GetRenderTarget(0, &oldBackBuffer);
	D3DDEVICE->GetDepthStencilSurface(&oldZBuffer);
	D3DDEVICE->GetViewport(&oldViewport);

	D3DDEVICE->SetRenderTarget(0, shadowSurf_);
	D3DDEVICE->SetDepthStencilSurface(shadowTexZ_);

	D3DVIEWPORT9 viewport = {0,0				// 左上の座標
							, 2048			// 幅
							, 2048			// 高さ
							, 0.0f,1.0f};		// 前面、後面
	D3DDEVICE->SetViewport(&viewport);

	// シャドウテクスチャのクリア
	D3DDEVICE->Clear(
		0L, 
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xFFFFFFFF,
		1.0f,
		0L
		);

	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);

	// ドーナッツ描画
	D3DXMATRIXA16 wlpMatrix;
	wlpMatrix = *matWorld * *lightVpMatrix;
	_Effect->SetMatrix(_wlpHandle, &wlpMatrix);
	for(DWORD i = 0; i < pMesh->getMaterials(); i++)
	{
		_Effect->BeginPass(0);
		// メッシュの描画
		_Effect->CommitChanges();
		pMesh->getMesh()->DrawSubset(i);
		_Effect->EndPass();
	}

	// 地形描画
	wlpMatrix = landMat * *lightVpMatrix;
	_Effect->SetMatrix(_wlpHandle, &wlpMatrix);
	for(DWORD i = 0; i < _pMeshLand->getMaterials(); i++)
	{
		_Effect->BeginPass(0);
		// メッシュの描画
		_Effect->CommitChanges();
		_pMeshLand->getMesh()->DrawSubset(i);
		_Effect->EndPass();
	}

	D3DDEVICE->SetRenderTarget(0, oldBackBuffer);
	D3DDEVICE->SetDepthStencilSurface(oldZBuffer);
	D3DDEVICE->SetViewport(&oldViewport);
	if(oldBackBuffer != NULL)
	{
		oldBackBuffer->Release();
		oldBackBuffer = NULL;
	}
	if(oldZBuffer != NULL)
	{
		oldZBuffer->Release();
		oldZBuffer = NULL;
	}
}

void CShadowMap::draw2(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix)
{
	D3DXMATRIXA16 wvpMatrix, wlpMatrix, wlpbMatrix, invMatrix;
	D3DXVECTOR4 color, lightDir;

	D3DXVECTOR4 lightPos = D3DXVECTOR4(0, 600, 600, 1.0f);
	
	// ドーナッツ描画
	lightDir = lightPos * -1.0f;
	D3DXMatrixInverse(&invMatrix, NULL, matWorld);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	D3DXVec4Normalize(&lightDir, &lightDir);

	D3DXMATRIXA16 cameraVpMatrix = *CCamera::getMatView() * *CSCREEN->getProjPtr();


	wvpMatrix = *matWorld * cameraVpMatrix;
	wlpMatrix = *matWorld * *lightVpMatrix;
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
		_Effect->CommitChanges();
		_Effect->BeginPass(1);
		// メッシュの描画
		pMesh->getMesh()->DrawSubset(i);
		_Effect->EndPass();
	}
	// 地形描画
	lightDir = lightPos * -1.0f;

	LPD3DXMESH landmesh = _pMeshLand->getMesh();
	

	D3DXMatrixInverse(&invMatrix, NULL, &landMat);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	D3DXVec4Normalize(&lightDir, &lightDir);

	wvpMatrix = landMat * cameraVpMatrix;
	wlpMatrix = landMat * *lightVpMatrix;
	wlpbMatrix = wlpMatrix * TEX_MATRIX;

	_Effect->SetMatrix(_wvpHandle, &wvpMatrix);
	_Effect->SetMatrix(_wlpHandle, &wlpMatrix);
	_Effect->SetMatrix(_wlpbHandle, &wlpbMatrix);

	_Effect->SetVector(_lightDirHandle, &lightDir);
	textures = _pMeshLand->getTexture();
	materials = _pMeshLand->getMaterialColor();



	for(DWORD i = 0; i < _pMeshLand->getMaterials(); i++)
	{
		color.x = materials->Diffuse.r;
		color.y = materials->Diffuse.g;
		color.z = materials->Diffuse.b;
		color.w = materials->Diffuse.a;

		_Effect->SetVector(_colorHandle, &color);
		_Effect->SetTexture(_DecaleTexHandle, textures[i]);
		_Effect->CommitChanges();

		_Effect->BeginPass(1);
		// メッシュの描画
		_pMeshLand->getMesh()->DrawSubset(i);
		_Effect->EndPass();
	}
	
}
#endif