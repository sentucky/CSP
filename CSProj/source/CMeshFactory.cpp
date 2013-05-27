/***********************************************************************/
/*! @file  CMeshFactory.cpp
 *  @brief シングルトン
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CMeshFactory.h"


CMeshFactory::CMeshFactory(){}
/***********************************************************************/
/*! @brief デストラクタ
 * 
 *  @retval  
 */
/***********************************************************************/
CMeshFactory::~CMeshFactory(){
	release();
	_vectorMesh.clear();
}


/***********************************************************************/
/*! @brief メッシュを渡す
 * 
 *  @param[in] unMeshKeyName メッシュファイルパス
 *  @retval CMesh* 
 */
/***********************************************************************/
CMesh* CMeshFactory::create(const uint unMeshKeyName)
{
	//	未登録時処理
#ifdef _DEBUG
	if(_vectorMesh[unMeshKeyName] == NULL)
	{
		MessageAlert("そんな名前のメッシュないです","error from CModelFactory::create");
		return NULL;
	}

	const uint SUMMESH = _vectorMesh.size();

	if(unMeshKeyName >= SUMMESH)
	{
		MessageAlert("容量が足りていません","error from CModelFactory::create");
		return NULL;
	}

#endif
	return new CMesh(*_vectorMesh[unMeshKeyName]);
}


/***********************************************************************/
/*! @brief メッシュの登録
 * 
 *  @param[in] unKeyName		メッシュの個別番号
 *  @param[in] pszMeshFilePath	メッシュファイルパス
 *  @retval BOOL 
 */
/***********************************************************************/
void CMeshFactory::registMesh(const uint unKeyName,const char*pszMeshFilePath)
{
	//	変数宣言
	const uint SUMMESH = _vectorMesh.size();

	//	重複チェック
	//----キーネームの重複チェック
	if(_vectorMesh[unKeyName] != NULL)
	{
#ifdef _DEBUG
		MessageAlert("登録済み番号","error from CMeshFactory::registMesh");
#endif
		return;
	}
	//----ファイルパスの重複チェック
	for(uint unCnt = 0; unCnt < SUMMESH;++unCnt)
	{
		if(_vectorMesh[unCnt] == NULL)
		{
			continue;
		}
		if(_vectorMesh[unCnt]->_szMeshFileName == pszMeshFilePath)
		{
#ifdef _DEBUG
		MessageAlert("ファイルパスが重複しています","error from CMeshFactory::registMesh");
#endif
			return;
		}
	}
	//	登録処理
	_vectorMesh[unKeyName] = new CMesh(pszMeshFilePath);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMeshFactory::release()
{
	const uint SUMMESH = _vectorMesh.size();
	for(uint unCnt = 0; unCnt < SUMMESH; ++unCnt)
	{
		SAFE_DELETE(_vectorMesh[unCnt]);
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] unReserveSize 
 *  @retval void
 */
/***********************************************************************/
void CMeshFactory::reserve(const uint unReserveSize)
{
	_vectorMesh.reserve(unReserveSize);
	_vectorMesh.resize(unReserveSize);
}

//EOF