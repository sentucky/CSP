/***********************************************************************/
/*! @file  CMesh.h
 *  @brief メッシュクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルードガード
/***********************************************************************/
#pragma once

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include <d3d9.h>
#include <d3dx9.h>
#include"CDevice.h"
#include"common.h"
/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CEffectBase;

/***********************************************************************/
//	構造体定義
/***********************************************************************/
typedef struct _D3DVERTEX
{
	D3DXVECTOR3 v;
	float   nx,ny,nz;
	float   XXXX;
	float   Corrdsx,Coordsy;
}VERTEX;

struct BVERTEX {
	D3DXVECTOR3	pos;
	D3DXVECTOR3	norm;
	D3DXVECTOR2	tex;
};

struct TINDEX
{
	WORD A;
	WORD B;
	WORD C;
};

/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CMesh 
{

	friend class CMeshFactory;
	friend class CModel;
	FRIEND_DELETE
	FRIEND_RELEASE
public:
	CMesh(LPCSTR szMeshName);	///<	コンストラクタ
	CMesh(const CMesh& copy);	///<	コピーコンストラクタ
	~CMesh();					///<	デストラクタ

public:
	void draw(const D3DXMATRIXA16* matWorld);							///< 描画設定

private:
	void drawEffectOff(const D3DXMATRIXA16* matWorld);					///<	エフェクトなし描画

public:
	const DWORD			getSumVertex();					///< 頂点数の取得
	const DWORD			getSumFaces();					///< フェイス数の取得
	const DWORD			getMaterials();					///< マテリアル総数の取得
	const D3DXVECTOR3*	getVertexKPtr();				///< 頂点配列の先頭の参照を返す
	const D3DXVECTOR3*	getVertexKPtr(DWORD dwVtxID);	///< 頂点配列の先頭の参照を返す
	const TINDEX&		getIndex(const DWORD dwIndexId);	///<	インデックス取得

	LPDIRECT3DTEXTURE9*	getTexture();		///<	テクスチャ情報取得
	LPD3DXMESH			getMesh();			///<	メッシュ情報取得
	D3DMATERIAL9*		getMaterialColor();	///<	マテリアルカラー取得

	void setMeshColor(
		const float r,
		const float g,
		const float b,
		const float a);	///<	メッシュカラー設定
	void setEffect(CEffectBase* pEffect);	///<	エフェクト設定


private:
	HRESULT loadMesh(LPCSTR szMeshName);				///<	メッシュ読み込み
	HRESULT loadMaterial(LPD3DXBUFFER pD3DXMatlBuffer);	///<	マテリアル関連情報読み込み
	void	loadVertex();								///<	頂点情報取得
	void	clone();									///<	クローン作成

protected:
	LPDIRECT3DTEXTURE9*	_pd3dMeshTexture;	///<	テクスチャポインタ
	LPD3DXMESH			_pd3dMesh;			///<	メッシュポインタ
	D3DCOLORVALUE*		_pd3dMeshColor;		///<	メッシュカラー
	D3DMATERIAL9*		_pd3dMeshMaterial;	///<	メッシュマテリアルカラー
	DWORD				_dwNumMaterials;	///<	マテリアル数
	D3DXVECTOR3*		_pvec3Vertex;		///<	頂点情報
	TINDEX*				_pwIndex;			///<	頂点情報
	LPCSTR				_szMeshFileName;	///<	メッシュファイル名
	uint*				_pSumProduct;		///<	自分+複製数
	CEffectBase*		_pEffect;			///<	エフェクトクラス
};
//EOF