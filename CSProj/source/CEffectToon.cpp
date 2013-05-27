/***********************************************************************/
/*! @file  CEffectToon.cpp
 *  @brief トゥーンシェーディング
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
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
/*! @brief コンストラクタ
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
/*! @brief デストラクタ
 */
/***********************************************************************/
CEffectToon::~CEffectToon()
{
	SAFE_RELEASE(_pToonTex);
}


/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in,out] copy 
 */
/***********************************************************************/
CEffectToon::CEffectToon(const CEffectToon& copy):CEffectBase(NULL){}


/***********************************************************************/
/*! @brief エフェクト作成
 * 
 *  @retval void
 */
/***********************************************************************/
void CEffectToon::create()
{

	HRESULT hr;
	LPD3DXBUFFER error = NULL;

	// シェーダの読み込みとコンパイル
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
			MessageAlert((char*)error->GetBufferPointer(),"error from CEffectToon::create");;
		}
		else
		{
			MessageAlert("ファイル名あってる？","error from CEffectToon::create");
		}
	}

	// エラー用のバッファ開放
	if(error != NULL)
	{
		error->Release();
		error = NULL;
	}

	// トゥーン用のテクスチャ作成
	if(FAILED(D3DXCreateTextureFromFileEx(
								D3DDEVICE,			// LPDIRECT3DDEVICE9へのポインター
                                _ToonTexPath,		// ファイル名
                                D3DX_DEFAULT,		// 幅(ピクセル)
                                D3DX_DEFAULT,		// 高さ(ピクセル)
                                1,					// ミプマップレベル
                                0,					// 描画ターゲット等サーフェースとして使う場合設定（今回は使用しない）
                                D3DFMT_UNKNOWN,		// ピクセルフォーマット
                                D3DPOOL_MANAGED,	// テクスチャの配置先となるメモリクラスを記述
                                D3DX_DEFAULT,		// イメージをフィルタリングする方法
                                D3DX_DEFAULT,		// イメージをフィルタリングする方法
                                0x0,				// カラーキー カラーキーを無効にする場合は0を指定する
                                NULL,				// ソースイメージファイル内のデータの記述
                                NULL,				// 格納する256色パレットを表す
                                &_pToonTex		// 作成されたテクスチャオブジェクトを表す
								)))
	{
		MessageAlert("テクスチャーロード失敗！","error from CEffectToon::Create");
	}

	// テクニック　ハンドル取得
	_techTechHandle = _Effect->GetTechniqueByName("Toon");
	// カメラ基準：ローカル～射影空間座標変換行列　ハンドル取得
	_paramWVP = _Effect->GetParameterByName(NULL, "WVP");
	// メッシュ色　ハンドル取得
	_paramColor = _Effect->GetParameterByName(NULL, "Color");
	// ライト方向　ハンドル取得
	_paramLight = _Effect->GetParameterByName(NULL, "LightDir");
	// 通常テクスチャ　ハンドル取得
	_paramDecalTex= _Effect->GetParameterByName( NULL, "DecalTex" );
	// 影テクスチャ　ハンドル取得
	_paramToonTex= _Effect->GetParameterByName( NULL, "ToonTex" );

	createVtxDecl(EFFECTTOON::DECL);
}


/***********************************************************************/
/*! @brief 描画処理
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


	//	テクニック指定
	_Effect->SetTechnique(_techTechHandle);

	//	パラメタ指定
	_Effect->SetMatrix(_paramWVP,&wvpMatrix);
	_Effect->SetTexture(_paramToonTex,_pToonTex);


	//	ライト設定
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