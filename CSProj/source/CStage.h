/***********************************************************************/
/*! @file  CStage.h
 *  @brief ステージオブジェクト
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSTAGE___
#define ___CSTAGE___	///<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CObjBase.h"


/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CMesh;
class CTaskList;
class CStageData;
/***********************************************************************/
/*!
 *	@class	CStage
 *	@brift	ステージオブジェクト
 */
/***********************************************************************/
class CStage:public CObjBase
{
public:
	CStage(
		const char* StageDataPath,
		CMesh* pMesh
		);
	~CStage();
	CStage(const CStage& src);
	void release();
	void enableTask();
	void disableTask();
	void draw();


	const CStageData*		getStageData();
private:
	const char*		_StageDataPath;		///<	ステージデータパス
	CStageData*		_StageData;			///<	ステージデータ
	CTaskList*		_pTaskDraw;			///<	描画関数
	CMesh*			_Mesh;				///<	メッシュ
	D3DXMATRIXA16	_matW;				///<	マトリクス
};

#endif