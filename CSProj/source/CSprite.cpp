/***********************************************************************/
/*! @file  CSprite.cpp
 *  @brief スプライト
 *  
 *  @author 川原　佑介
 *  @date	2013/5/11	コピーコンストラクタの修正
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CSprite.h"
#include"CScreen.h"
#include"common.h"

/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define D3DCOLORA(a) ( a & 0xff << 24)
#define D3DCOLORR(a) ( a & 0xff << 16)
#define D3DCOLORG(a) ( a & 0xff <<  8)
#define D3DCOLORB(a) ( a & 0xff )

/***********************************************************************/
/*! @brief コンストラクタ
 * 
 *  @param[in] pTexture 
 */
/***********************************************************************/
CSprite::CSprite(CTexture* pTexture)
	:_pTexture(pTexture),
	 _pD3DSprite(NULL),	
	 _vecCenter(D3DXVECTOR3(0,0,0)),		
	 _UV(RECTEX(0,0,0,0)),			
	 _colorRevision(D3DXCOLOR(0,0,0,1.0f)),
	 _bDrawFlg(TRUE)
{
	_pTexture = pTexture;	//テクスチャの登録
	create();
}

/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] copy 
 */
/***********************************************************************/
CSprite::CSprite(const CSprite& copy)
	:_pTexture(copy._pTexture),
	_pD3DSprite(NULL),	
	 _vecCenter(copy._vecCenter),		
	 _UV(copy._UV),			
	 _colorRevision(copy._colorRevision),
	 _bDrawFlg(TRUE)
{
	create();
}
	
/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CSprite::~CSprite()
{
	if(_pTexture != NULL)
	{//テクスチャが設定されていたとき
		_pTexture = NULL;
	}
	SAFE_RELEASE(_pD3DSprite);
}

/***********************************************************************/
/*! @brief 初期化
 * 
 *  @retval void
 */
/***********************************************************************/
void CSprite::init()
{
	_pTexture = NULL;		//テクスチャ
	_pD3DSprite =NULL;		//スプライト
	_bDrawFlg = TRUE;
	_vecCenter = D3DXVECTOR3(0,0,0);
	_UV = RECTEX(0,0,0,0);
	setColorRevision(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));	//色補正
}


/***********************************************************************/
/*! @brief スプライト作成
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CSprite::create()
{
	/////////////////////////
	//	処理判定
	if(_pTexture == NULL)
	{
		return 0;	//処理しない
	}

	HRESULT hr;	//処理結果判定
	
	hr = D3DXCreateSprite(D3DDEVICE, &_pD3DSprite);

	if(FAILED(hr))
	{
		MessageAlert("スプライトの作成に失敗しました","error from CSprite::Create");
		return hr;
	}

	//	UV座標の取得
	_UV.right = _pTexture->getSrcInfoRef().Width;
	_UV.bottom = _pTexture->getSrcInfoRef().Height;

	//	中心座標の設定
	_vecCenter.x = (float)_UV.right * 0.5f;	
	_vecCenter.y = (float)_UV.bottom * 0.5f;
	return hr;
}

/***********************************************************************/
/*! @brief 中心座標計算
 * 
 *  @retval void
 */
/***********************************************************************/
void CSprite::calcCenter()
{
	_vecCenter.x = (float)(_UV.right - _UV.left) * 0.5f;
	_vecCenter.y = (float)(_UV.bottom - _UV.top) * 0.5f;

}

/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @param[in] SpriteType	描画のオプション
 *  @param[in] vec3Pos		座標
 *  @param[in] vec3Rot		回転量
 *  @param[in] vec3Scale	拡大率
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXVECTOR3* vec3Pos,const D3DXVECTOR3* vec3Rot,const D3DXVECTOR3* vec3Scale)
{
	/////////////////////////
	//	処理判定
	if(_pTexture == NULL)
	{
		return;	//処理しない
	}
	
	/////////////////////////
	//	変数宣言
	D3DXMATRIXA16 rot;		//回転マトリクス
	D3DXMATRIXA16 scale;	//サイズマトリクス
	D3DXMATRIXA16 pos;		//座標マトリクス
	D3DXMATRIXA16 posRot;	//回転用座標マトリクス
	D3DXMATRIXA16 matWorld;	//ワールド座標マトリクス


	////////////////////////////
	//	初期処理
	//...マトリクスの初期化
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixIdentity( &rot );
	D3DXMatrixIdentity( &scale );
	D3DXMatrixIdentity( &pos );
	D3DXMatrixIdentity( &posRot );


	////////////////////////////
	//	座標変換
	D3DDEVICE->SetFVF(FVF_VERTEX_2D);

	if(vec3Scale != 0)
	{
		D3DXMatrixScaling( &scale, vec3Scale->x, vec3Scale->y, 0.0f );	//スケール拡大縮小処理
		matWorld *= scale;
	}
	if(vec3Rot != 0)
	{//回転処理
		D3DXMatrixRotationYawPitchRoll( 
			&rot,
			D3DXToRadian(vec3Rot->y),
			D3DXToRadian(vec3Rot->x),
			D3DXToRadian(vec3Rot->z)
			);	
		matWorld *= rot;
	}
	
	if(vec3Pos != 0)
	{
		D3DXMatrixTranslation( &pos, vec3Pos->x, vec3Pos->y, vec3Pos->z );	//移動処理
		matWorld *= pos;
	}
//	calcCenter();

	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);		//レンダリング
	_pD3DSprite->SetTransform(&matWorld);
	_pD3DSprite->Begin(SpriteType );	//描画開始
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,0, _colorRevision);
	_pD3DSprite->End();	//描画終了
}


/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @param[in] SpriteType	描画オプション 
 *  @param[in] pmatWorld	ワールドマトリクス
 *  @param[in] pmatView		ビューマトリクス
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXMATRIXA16* pmatWorld, const D3DXMATRIXA16* pmatView)
{
	/////////////////////////
	//	処理判定
	if(_pTexture == NULL)
	{
		return;	//処理しない
	}

	////////////////////////////
	//	座標変換
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//ビュー座標変換
	if(pmatView != NULL)
	{
		D3DDEVICE->SetTransform(D3DTS_VIEW, pmatView);					//カメラ座標変換
	}
	D3DDEVICE->SetTransform(D3DTS_WORLD, pmatWorld);					//ワールド座標変換
//		calcCenter();

	////////////////////////////
	//	描画処理
	D3DDEVICE->SetFVF(FVF_VERTEX_2D);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);			//	レンダリング
	_pD3DSprite->SetTransform(pmatWorld);						//
	_pD3DSprite->Begin(SpriteType | D3DXSPRITE_OBJECTSPACE);	//	描画開始
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,NULL, _colorRevision);
	_pD3DSprite->End();	//描画終了
}

/***********************************************************************/
/*! @brief 2D用描画
 * 
 *  @param[in] SpriteType 
 *  @param[in] pmatWorld 
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXMATRIXA16* pmatWorld)
{
	/////////////////////////
	//	処理判定
	if(_pTexture == NULL)
	{
		return;	//処理しない
	}

	////////////////////////////
	//	座標変換
	D3DDEVICE->SetTransform(D3DTS_WORLD, pmatWorld);					//ワールド座標変換

//	calcCenter();

	////////////////////////////
	//	描画処理
	D3DDEVICE->SetFVF(FVF_VERTEX_2D);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);					//レンダリング
	_pD3DSprite->SetTransform(pmatWorld);
	_pD3DSprite->Begin(SpriteType | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);			//描画開始
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,NULL, _colorRevision);
	_pD3DSprite->End();	//描画終了
}

/***********************************************************************/
/*! @brief テクスチャ設定
 * 
 *  @param[in] pTexture 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setTexture(CTexture* pTexture)
{
	_pTexture = pTexture;
	create();
}


/***********************************************************************/
/*! @brief 中心座標の設定
 * 
 *  @param[in] x 
 *  @param[in] y 
 *  @param[in] z 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setCenter(float x, float y, float z)
{
	_vecCenter.x = x;
	_vecCenter.y = y;
	_vecCenter.z = z;
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pos 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setCenter(D3DXVECTOR3* pos)
{
	_vecCenter = *pos;
}



/***********************************************************************/
/*! @brief UV座標の設定
 * 
 *  @param[in] lLeft 
 *  @param[in] lTop 
 *  @param[in] lRight 
 *  @param[in] lBottom 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setUV(long lLeft,long lTop,long lRight,long lBottom)
{
	_UV.left = lLeft;		//左端の設定
	_UV.top  = lTop;		//上端の設定
	_UV.right = lRight;		//右端の設定
	_UV.bottom = lBottom;	//下端の設定
}


/***********************************************************************/
/*! @brief UV座標の設定
 * 
 *  @param[in] rect 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setUV(RECT& rect)
{
	_UV = rect;
}

/***********************************************************************/
/*! @brief 色補正の設定
 * 
 *  @param[in] colorRevision 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevision(D3DXCOLOR& colorRevision)
{
	_colorRevision = colorRevision;
}


/***********************************************************************/
/*! @brief 色補正の設定
 * 
 *  @param[in] fR 
 *  @param[in] fG 
 *  @param[in] fB 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevision(
	const float fR,
	const float fG,
	const float fB,
	const float fA
	)
{
	_colorRevision = D3DXCOLOR(fR,fG,fB,fA);
}
/***********************************************************************/
/*! @brief 色補正赤指定
 * 
 *  @param[in] fR 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionR(const float fR)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fR);
	_colorRevision &= 0xff00ffff;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief 色補正緑指定
 * 
 *  @param[in] fG 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionG(const float fG)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fG);
	_colorRevision &= 0xffff00ff;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief 色補正青指定
 * 
 *  @param[in] fB 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionB(const float fB)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fB);
	_colorRevision &= 0xffffff00;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief 色補正アルファ指定
 * 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionA(const float fA)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fA);
	_colorRevision &= 0x00ffffff;
	_colorRevision |= D3DCOLORR(unRVal);
}

/***********************************************************************/
/*! @brief 色補正値取得
 * 
 *  @retval D3DCOLOR 
 */
/***********************************************************************/
D3DCOLOR CSprite::getColorRevision()
{
	return _colorRevision;
}

/***********************************************************************/
/*! @brief テクスチャ情報取得
 * 
 *  @retval const D3DXIMAGE_INFO* 
 */
/***********************************************************************/
const D3DXIMAGE_INFO* CSprite::getTextureInfo()
{
	return &_pTexture->getSrcInfoRef();
}


//	EOF