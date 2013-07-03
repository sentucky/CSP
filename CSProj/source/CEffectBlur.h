#ifndef ___CEFFECTBLUR___
#define ___CEFFECTBLUR___	///<	インクルードガード

#include"CEffectBase.h"
#include"CEffectBlur.h"
#include"CSingleton.h"

class CMesh;

#define EFFECTBLUR CEffectBlur::getInst()

class CEffectBlur:public CEffectBase,public CSingleton<CEffectBlur>
{
	friend class CSingleton<CEffectBlur>;
private:
	CEffectBlur();						// コンストラクタ
	~CEffectBlur();				// デストラクタ
public:
	void release();							// 開放関数
	HRESULT init();							// 準備関数
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);
private:
	void drawVelocityMap();					// 速度マップ

	void create();

	static const D3DVERTEXELEMENT9 DECL[];


private:
	D3DXMATRIXA16	_worldMatrix ;			//!< ワールド行列
	D3DXMATRIXA16	_lastWVMatrix ;			//!< 1フレーム前ワールドビュー行列
	LPD3DXEFFECT	_effect ;				//!< エフェクト
	D3DXHANDLE		_techniqueHandle ;		//!< テクニック ハンドル
	D3DXHANDLE		_wvHandle ;				//!< ワールド *ビュー行列 ハンドル
	D3DXHANDLE		_lastWVHandle ;			//!< １フレーム前ワールド *ビュー行列 ハンドル
	D3DXHANDLE		_projHandle ;			//!< プロジェクション行列 ハンドル
	D3DXHANDLE		_lightDirHandle ;		//!< ライト方向ハンドル
	D3DXHANDLE		_colorHandle ;			//!< マテリアル色ハンドル
	LPDIRECT3DVERTEXDECLARATION9 _decl ;	//!< 頂点宣言
	CMesh*			_model ;				//!< モデルデータ
	FLOAT			_rotate ;				//!< 回転角
};



#endif