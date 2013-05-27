/***********************************************************************/
/*! @file  CTextureFactory.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	：
//	概要			：
//	制作者		：
//	更新履歴		：
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CTextureFactory.h"
#include"commonfunc.h"

/***********************************************************************/
//	コンストラクタ
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTextureFactory::CTextureFactory()
{
}
/***********************************************************************/
//	デストラクタ
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTextureFactory::~CTextureFactory()
{
	const uint SUMTEXTURE = _vecTexture.size();

	for(uint unCnt = 0; unCnt != SUMTEXTURE; ++unCnt)
	{//	マップの先頭から終端まで削除
		SAFE_DELETE(_vecTexture[unCnt]);
	}
	_vecTexture.clear();	//マップ要素の解放
}
/***********************************************************************/
//	メンバ関数定義
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unReserveSize 
 *  @retval void
 */
/***********************************************************************/
void CTextureFactory::reserve(const uint unReserveSize)
{
	_vecTexture.reserve(unReserveSize);
	_vecTexture.resize(unReserveSize);
}

//===================================================================
//	概要
//		テクスチャの登録
//	引数	
//		char*				キーネーム
//		char*				ファイルパス
//	戻り値
//		BOOL				登録の有無判別フラグ
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @param[in,out] pszTextureFilePath 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CTextureFactory::registTexture(const int nId,const char* pszTextureFilePath)
{
	/////////////////////////
	//	変数宣言
	vec_texture::iterator itr;	//テクスチャマスタイテレータ
	

	/////////////////////////
	//	重複チェック
	//----ファイルパスの重複チェック
	uint SUMTEXTURE = _vecTexture.size();

	if(SUMTEXTURE <= nId)
	{
#ifdef _DEBUG
		char szErrorMessage[MAX_PATH];
		sprintf(szErrorMessage,"テクスチャ格納配列の容量不足です。\n容量を追加します",pszTextureFilePath);
		MessageAlert(szErrorMessage,"error from CTextureFatory::registTexture");
#endif
		reserve(nId);
	}

#ifdef _DEBUG
	for(uint unCnt = 0; unCnt < SUMTEXTURE; ++unCnt)
	{
		if(_vecTexture[unCnt] == NULL)
		{
			continue;
		}
		if(_vecTexture[unCnt]->getFilePath() == pszTextureFilePath)
		{
			char szErrorMessage[MAX_PATH];
			sprintf(szErrorMessage,"テクスチャファイル\"%s\"は既に登録されています",pszTextureFilePath);
			MessageAlert(szErrorMessage,"error from CTextureFatory::registTexture");
			return FALSE;
		}
	}
#endif
	/////////////////////////
	//	登録処理
	_vecTexture[nId] = new CTexture(pszTextureFilePath);
	return TRUE;
}


//===================================================================
//	概要
//		テクスチャの解放
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CTextureFactory::releaseTexture(const int nId)
{
	if(_vecTexture[nId] == NULL)
	{
#ifdef _DEBUG
		MessageAlert("指定されたテクスチャは登録されていません","error from releaseTexture");
#endif
		return FALSE;
	}

	const uint SUMTEXTURE = _vecTexture.size();

	if(nId >= SUMTEXTURE)
	{
#ifdef _DEBUG
		MessageAlert("容量を超えています","error from releaseTexture");
		return FALSE;
#endif
	}

	SAFE_DELETE(_vecTexture[nId]);
	return TRUE;
}

//===================================================================
//	概要
//		テクスチャの取得
//	引数	
//		char*				キーネーム
//	戻り値
//		texture*			テクスチャポインタ
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @retval CTexture* 
 */
/***********************************************************************/
CTexture* CTextureFactory::getTexture(const int nId)
{
	/////////////////////////
	//	確認処理
	//----キーネームの有無
	if(_vecTexture[nId] == NULL)
	{
#ifdef _DEBUG
		char szErrorMessage[MAX_PATH];
		sprintf(szErrorMessage,"テクスチャファクトリーキー\"%d\"が見つかりません",nId);
		MessageAlert(szErrorMessage,"error from CTextureFatory::getTexture");
#endif
		return NULL;
	}

	return _vecTexture[nId];
}
//EOF