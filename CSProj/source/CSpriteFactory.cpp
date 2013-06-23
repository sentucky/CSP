/***********************************************************************/
/*! @file  CSpriteFactory.cpp
 *  @brief	スプライトファクトリ
 *  
 *  @author 川原　佑介
 *  @date	
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CSpriteFactory.h"
#include"CSprite.h"
#include"common.h"

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CSpriteFactory::CSpriteFactory()
{
}

/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] constCSpriteFactory& 
 *  @retval  
 */
/***********************************************************************/
CSpriteFactory::CSpriteFactory(const CSpriteFactory&)
{
}

/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CSpriteFactory::~CSpriteFactory()
{
}

/***********************************************************************/
/*! @brief スプライト作成
 * 
 *  @param[in] nId 
 *  @retval CSprite* 
 */
/***********************************************************************/
CSprite* CSpriteFactory::create(const int nId)
{
	//	変数宣言
	CTexture*	pTex = NULL;

	//	テクスチャキーチェック
	pTex =  TEXTUREFACTORY->getTexture( nId);
#ifdef _DEBUG
	if(NULL == pTex)
	{
		MessageAlert("そんな名前のテクスチャないです","erorr from CSpriteFactory::create");
		return NULL;
	}
#endif
	return 	new CSprite(pTex);
}


/***********************************************************************/
/*! @brief テクスチャ登録
 * 
 *  @param[in] nId 
 *  @param[in] constcharszTextureFilePath[MAX_PATH] 
 *  @retval const BOOL 
 */
/***********************************************************************/
const BOOL CSpriteFactory::registTexture(
	const int nId,
	const char szTexFilePath[MAX_PATH]
)
{
	return TEXTUREFACTORY->registTexture( nId,szTexFilePath);
}

//EOF