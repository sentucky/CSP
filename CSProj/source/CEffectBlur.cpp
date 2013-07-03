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

// 頂点宣言

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
 * @brief	準備関数
 */
HRESULT CEffectBlur::init()
{
	release();

	// シェーダの読み込みとコンパイル
	HRESULT hr;
	LPD3DXBUFFER error = NULL;
	if(FAILED(hr = D3DXCreateEffectFromFile(
					D3DDEVICE,					// LPDIRECT3DDEVICE9へのポインター
					"data/fx/MotionBlur.fx",	// エフェクトファイルへのパス
					NULL,						// プリプロセッサ定義を用意している場合（使用しない）
					NULL,						// #include 擬似命令の処理に使う（使用しない）
					0,							// D3DXSHADER で識別されるコンパイルオプション
					NULL,						// 異なるエフェクト間でパラメータを共有する場合に使用する（使用しない）
					&_effect,					// コンパイルされたエフェクトが格納される
					&error)))					// コンパイルエラーの一覧が格納されるバッファ
	{
		// コンパイルエラー表示
		if(error != NULL)
		{
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffectBlur");
		}
		else
		{
			MessageAlert("ファイル名を確認してください","error from CEffectBlur");
		}

		return E_FAIL;
	}

	// テクニック　ハンドル取得
	_techniqueHandle = _effect->GetTechniqueByName("Blur");
	// ワールドビュー行列　ハンドル取得
	_wvHandle = _effect->GetParameterByName(NULL, "WV");
	// 1フレーム前ワールドビュー行列　ハンドル取得
	_lastWVHandle = _effect->GetParameterByName(NULL, "LastWV");
	// プロジェクション行列　ハンドル取得
	_projHandle = _effect->GetParameterByName(NULL, "PROJ");
	// ライト方向　ハンドル取得
	_lightDirHandle = _effect->GetParameterByName(NULL, "LightDir");
	// マテリアル色　ハンドル取得
	_colorHandle = _effect->GetParameterByName(NULL, "Color");

	// エラー用のバッファ開放
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	// 頂点宣言作成
	if(FAILED(hr = D3DDEVICE->CreateVertexDeclaration(
									DECL, 
									&_decl
									)))
	{
		MessageAlert("頂点宣言間違い！","error from CEffectBlur");
		return E_FAIL;
	}

	// ワールド行列初期化
	D3DXMatrixIdentity(&_worldMatrix);
	D3DXMatrixIdentity(&_lastWVMatrix);

	// 基底クラスの準備関数呼び出し
}

//-------------------------------------------------------------------------------------------------
/** 
 * @brief	描画関数
 */
void CEffectBlur::draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld)
{
	_model = pMesh;
	D3DXMATRIXA16 wvMatrix, invMatrix;
	D3DXVECTOR4 color;

	// ワールドビュー行列作成
	D3DXMatrixMultiply(&wvMatrix, &_worldMatrix, CCamera::getMatView());

	// ライト方向をローカル座標に変換
	D3DXMatrixInverse(&invMatrix, NULL, &_worldMatrix);
	D3DXVECTOR4 lightDir(-1.0f, -1.0f, -1.0f, 0.0f);
	D3DXVec4Transform(&lightDir, &lightDir, &invMatrix);
	lightDir.w = 0.0f;
	D3DXVec4Normalize(&lightDir, &lightDir);

	// 頂点宣言指定
	D3DDEVICE->SetVertexDeclaration(_decl);

	// テクニック指定
	_effect->SetTechnique(_techniqueHandle);

	// ワールドビュー行列登録
	_effect->SetMatrix(_wvHandle, &wvMatrix);
	// １フレーム前ワールドビュー行列登録
	_effect->SetMatrix(_lastWVHandle, &_lastWVMatrix);
	// プロジェクション行列登録
	_effect->SetMatrix(_projHandle, CSCREEN->getProjPtr());
	// 次のフレームで使う１フレーム前のワールドビュー行列を退避させておく
	_lastWVMatrix = wvMatrix;

	// ライト方向登録
	_effect->SetVector(_lightDirHandle, &lightDir);

	// 描画開始
	UINT passNum;
	_effect->Begin(&passNum, 0);
	for(UINT i = 0; i < passNum; i++)
	{
		// パスの描画開始
		_effect->BeginPass(i);
		const LPDIRECT3DTEXTURE9* textures = _model->getTexture();
		const D3DMATERIAL9* materials = _model->getMaterialColor();
		for(DWORD j = 0; j < _model->getMaterials(); j++)
		{
			color.x = materials[j].Diffuse.r;
			color.y = materials[j].Diffuse.g;
			color.z = materials[j].Diffuse.b;
			color.w = materials[j].Diffuse.a;

			// マテリアル色登録
			_effect->SetVector(_colorHandle, &color);
			
			// メッシュの描画
			_effect->CommitChanges();
			_model->getMesh()->DrawSubset(j);
		}
		// パスの描画終了
		_effect->EndPass();
	}
	// 描画終了
	_effect->End();
}
