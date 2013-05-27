/***********************************************************************/
/*! @file  CMeshFactory.h
 *  @brief メッシュファクトリ
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
#include"CMesh.h"
#include"commonfunc.h"
#include"CSingleton.h"
#include<vector>

/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define MESHFACTORY	CMeshFactory::getInst()


/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CMeshFactory:public CSingleton<CMeshFactory>
{
	//	フレンド登録
	friend class CSingleton<CMeshFactory>;
private:
	CMeshFactory();						///<	コンストラクタ
	CMeshFactory(const CMeshFactory&);	///<	コピーコンストラクタ
	~CMeshFactory();					///<	デストラクタ

public:
	CMesh* create(const uint nMeshKeyName);	///<	メッシュ作成
	void registMesh(const uint unKeyName,const char*pszMeshFilePath);	///<	メッシュ登録
	void release();							///<	解放処理
	void reserve(const uint unReserveSize);	///<	容量予約


private:
	typedef std::vector<CMesh*> vector_mesh;
	vector_mesh _vectorMesh;					//!< メッシュの原型を入れるベクタ
};
//EOF