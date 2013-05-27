/***********************************************************************/
/*! @file  CSceneBase.cpp
 *  @brief	シーンクラスベース
 *  
 *  @author 川原　佑介
 *  @date	2013/04/30
 */
/***********************************************************************/
#include"CSceneBase.h"


/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CSceneBase::CSceneBase(
	)
	:_UpdateFlg(TRUE),
	_DrawFlg(TRUE),
	_EndFlg(FALSE)
{
}


/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CSceneBase::~CSceneBase()
{
}

/***********************************************************************/
/*! @brief 更新処理フラグOFF
 */
/***********************************************************************/
void CSceneBase::updateFlgOFF(){_UpdateFlg = FALSE;}


/***********************************************************************/
/*! @brief 描画処理フラグOFF
 */
/***********************************************************************/
void CSceneBase::drawFlgOFF(){ _DrawFlg = FALSE;}


/***********************************************************************/
/*! @brief 更新処理フラグON
 */
/***********************************************************************/
void CSceneBase::updateFlgON(){ _UpdateFlg = TRUE;}


/***********************************************************************/
/*! @brief 描画処理フラグON
 */
/***********************************************************************/
void CSceneBase::drawFlgON(){ _DrawFlg = TRUE;}


/***********************************************************************/
/*! @brief 更新処理フラグ取得
 * 
 *  @retval const BOOL 更新処理フラグ
 */
/***********************************************************************/
const BOOL CSceneBase::getUpdateFlg(){return	_UpdateFlg;}	//	更新処理フラグ取得


/***********************************************************************/
/*! @brief 描画処理フラグ取得
 * 
 *  @retval const BOOL 描画処理フラグ
 */
/***********************************************************************/
const BOOL CSceneBase::getDrawFlg(){return	_DrawFlg;}


/***********************************************************************/
/*! @brief 削除処理フラグ取得
 * 
 *  @retval const BOOL 削除処理フラグ
 */
/***********************************************************************/
const BOOL CSceneBase::getEndFlg(){return _EndFlg;}