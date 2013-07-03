/***********************************************************************/
/*! @file  CMesh.cpp
 *  @brief メッシュクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CMesh.h"
#include"CScreen.h"
#include"common.h"
#include"CEffectBase.h"
#include"CCamera.h"


/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/***********************************************************************/
/*! @brief コンストラクタ
 * 
 *  @param[in] szMeshName ファイルパス
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
/*! @brief コピーコンストラクタ
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
/*! @brief デストラクタ
 */
/***********************************************************************/
CMesh::~CMesh()
{
	*_pSumProduct -= 1;

	/////////////////////////
	//	メモリ解放
	if(*_pSumProduct == 0)
	{
		SAFE_RELEASE_ARRAY(_pd3dMeshTexture,_dwNumMaterials);	//	テクスチャ解放
		SAFE_DELETE_ARRAY(_pd3dMeshColor);						//	メッシュ色情報を削除
		SAFE_DELETE_ARRAY(_pd3dMeshMaterial);					//	マテリアル情報の削除
		SAFE_DELETE(_pvec3Vertex);								//	頂点情報の削除
		SAFE_RELEASE(_pd3dMesh);								//	メッシュの解放
		SAFE_DELETE_ARRAY(_pwIndex);
		SAFE_DELETE(_pSumProduct);
		_szMeshFileName = NULL;									//	ファイルパスのクリア
	}
}


/***********************************************************************/
/*! @brief メッシュ読み込み
 * 
 *  @param[in] szMeshName ファイルパス
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CMesh::loadMesh(LPCSTR szMeshName)
{
	//	変数宣言
	HRESULT					hr = 0;
	LPD3DXBUFFER			pD3DXMatlBuffer;


	//	初期化
	_pd3dMeshTexture	= NULL;		//	テクスチャポインタ
	_pd3dMeshColor		= NULL;		//	メッシュカラー
	_pd3dMesh			= NULL;		//	マテリアル数
	_pd3dMeshMaterial	= NULL;		//	メッシュマテリアルカラー
	_pvec3Vertex		= NULL;
	_szMeshFileName		= szMeshName;

	//	メッシュ読み込み
	//---メッシュファイルの読み込み
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
/*! @brief マテリアル読み込み
 * 
 *  @param[in,out] pD3DXMatlBuffer 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CMesh::loadMaterial(LPD3DXBUFFER pD3DXMatlBuffer)
{
	HRESULT					hr;
	
	//---マテリアル保存用配列の確保
	_pd3dMeshColor		= new D3DCOLORVALUE[_dwNumMaterials];
	_pd3dMeshTexture	= new LPDIRECT3DTEXTURE9[_dwNumMaterials];
	_pd3dMeshMaterial	= new D3DMATERIAL9[_dwNumMaterials];

	//---マテリアル情報バッファのポインタ取得
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMatlBuffer->GetBufferPointer();

	char curDir[MAX_PATH];
	int n = 0;

	//---マテリアル情報バッファを保存
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

		//	テクスチャ読み込み
		hr = D3DXCreateTextureFromFileA(
						D3DDEVICE,
						curDir,//d3dxMaterials[dwCnt].pTextureFilename,
						&_pd3dMeshTexture[dwCnt]);

		if(d3dxMaterials[dwCnt].pTextureFilename &&	FAILED(hr))
		{
			//エラーメッセージ
			MessageBox(NULL,"テクスチャ読み込みエラー","",MB_OK|MB_ICONWARNING);
		}
	}
	return hr;
}

/***********************************************************************/
/*! @brief 頂点情報読み込み
 * 
 *  @retval void
 */
/***********************************************************************/
void CMesh::loadVertex()
{

	VERTEX					*d3dvertex;
	TINDEX					*pwIndex;

	/////////////////////////
	//	頂点情報の取得
	//----準備
	DWORD dwSumVertex;
	DWORD dwSumIndex;

	//----メッシュ情報の取得
	dwSumVertex = _pd3dMesh->GetNumVertices();							//	頂点数の取得
	dwSumIndex = _pd3dMesh->GetNumFaces();								//	インデックス数取得
	_pd3dMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&d3dvertex);	//	頂点バッファの取得
	_pd3dMesh->LockIndexBuffer(D3DLOCK_READONLY,(LPVOID*)&pwIndex);		//	頂点バッファの取得
	_pvec3Vertex = new D3DXVECTOR3[dwSumVertex];						//	頂点情報を保持するインスタンスの作成
	_pwIndex = new TINDEX[dwSumIndex];									//	頂点情報を保持するインスタンスの作成
	
	//---情報のコピー
	//.....頂点
	for(DWORD dwCnt = 0; dwCnt < dwSumVertex; dwCnt++)					
	{
		_pvec3Vertex[dwCnt] = d3dvertex->v;
		d3dvertex++;
	}

	for(DWORD dwCnt = 0; dwCnt < dwSumIndex; dwCnt++)
	{
		_pwIndex[dwCnt] = pwIndex[dwCnt];
	}

	//---バッファの解放
	_pd3dMesh->UnlockVertexBuffer();
	_pd3dMesh->UnlockIndexBuffer();
}


/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @param[in] matView	ビュー座標
 *  @param[in] matWorld ワールド座標
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
/*! @brief エフェクトなし描画
 * 
 *  @param[in] matView 　ビュー座標
 *  @param[in] matWorld  ワールド座標
 *  @retval void
 */
/***********************************************************************/
void CMesh::drawEffectOff(const D3DXMATRIXA16* matWorld)
{
	/////////////////////////
	//	マトリクス変換
	D3DDEVICE->SetFVF(FVF_VERTEX_3D);	// 頂点フォーマットの設定
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//ビュー座標変換
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatView());			//カメラ座標変換
	D3DDEVICE->SetTransform(D3DTS_WORLD,matWorld);						//ワールド座標変換

	/////////////////////////
	//	描画処理
	for(DWORD dwCnt = 0; dwCnt < _dwNumMaterials; dwCnt++)
	{
		D3DDEVICE->SetMaterial(&_pd3dMeshMaterial[dwCnt]);
		D3DDEVICE->SetTexture(0,_pd3dMeshTexture[dwCnt]);

		_pd3dMesh->DrawSubset(dwCnt);
	}
}

/***********************************************************************/
/*! @brief 頂点数取得
 * 
 *  @retval const DWORD 
 */
/***********************************************************************/
const DWORD			CMesh::getSumVertex(){return _pd3dMesh->GetNumVertices();}			
/***********************************************************************/
/*! @brief フェイス数取得
 * 
 *  @retval const DWORD 
 */
/***********************************************************************/
const DWORD			CMesh::getSumFaces(){return _pd3dMesh->GetNumFaces();}				
/***********************************************************************/
/*! @brief マテリアル数取得
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
/*! @brief 頂点配列取得
 * 
 *  @param[in] dwVtxID 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3*	CMesh::getVertexKPtr(DWORD dwVtxID){return &_pvec3Vertex[dwVtxID];}	
/***********************************************************************/
/*! @brief インデックス配列取得
 * 
 *  @param[in] dwIndexId 
 *  @retval const TINDEX& 
 */
/***********************************************************************/
const TINDEX&		CMesh::getIndex(const DWORD dwIndexId){ return _pwIndex[dwIndexId];}
/***********************************************************************/
/*! @brief テクスチャ取得
 * 
 *  @retval LPDIRECT3DTEXTURE9* 
 */
/***********************************************************************/
LPDIRECT3DTEXTURE9*	CMesh::getTexture(){return _pd3dMeshTexture;}
/***********************************************************************/
/*! @brief メッシュ情報取得
 * 
 *  @retval LPD3DXMESH 
 */
/***********************************************************************/
LPD3DXMESH			CMesh::getMesh(){return _pd3dMesh;}
/***********************************************************************/
/*! @brief マテリアルカラー取得
 * 
 *  @retval D3DMATERIAL9* 
 */
/***********************************************************************/
D3DMATERIAL9*		CMesh::getMaterialColor(){return _pd3dMeshMaterial;}


/***********************************************************************/
/*! @brief メッシュカラー設定
 * 
 *  @param[in] fR レッド
 *  @param[in] fG グリーン
 *  @param[in] fB ブルー
 *  @param[in] fA アルファ
 *  @retval void
 */
/***********************************************************************/
void CMesh::setMeshColor(const float fR,const float fG,const float fB,const float fA)
{
	this->_pd3dMeshColor->r = fR;	//赤
	this->_pd3dMeshColor->g = fG;	//緑
	this->_pd3dMeshColor->b = fB;	//青
	this->_pd3dMeshColor->a = fA;	//アルファ
}

/***********************************************************************/
/*! @brief エフェクトの設定
 * 
 *  @param[in] pEffect エフェクト
 *  @retval void
 */
/***********************************************************************/
void CMesh::setEffect(CEffectBase* pEffect)
{
	_pEffect = pEffect;
}
