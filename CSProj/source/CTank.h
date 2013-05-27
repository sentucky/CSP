/***********************************************************************/
/*! @file  CTank.h
 *  @brief タスククラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANK___
#define ___CTANK___	///<	インクルード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CObjBase.h"


/***********************************************************************/
//	先行宣言
/***********************************************************************/
template<class T>
class CListItem;
class CTaskBase;
class CTaskList;
class CMesh;
class CTankIntInter;
class CShell;
class CTankTop;
class CTankBottom;
/***********************************************************************/
/*!
 *	@class CTank
 *	@brift タンククラス
 */
/***********************************************************************/
class CTank:public CObjBase
{
public:
	CTank(
		CMesh* pMeshTop,		///<	トップメッシュ
		CMesh* pMeshBottom,		///<	ボトムメッシュ
		uint   unIntType,		///<	インテリジェンス
		CShell* pShellProto,
		const float fMoveSpeed,	///<	速度
		const float fTurnSpeed	//	旋回速度
		);
	~CTank();					///<	デストラクタ
	CTank(const CTank& src);	///<	コピーコンストラクタ

private:
	void release();				///<	解放処理
public:
	void draw();				///<	描画処理
	void intelligence();		///<	思考更新
	void pause();				///<	姿勢の更新
	void move();				///<	移動処理
	void fire();				///<	発砲


private:


	void turnTop();

public:
	void enableTask();			///<	タスク有効化
	void disableTask();			///<	タスク無効化

	const D3DXMATRIXA16* getMatBottom();	//	ボトムのマトリクス取得
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTankTop*		_pTankTop;			///<	戦車の上部
	CTankBottom*	_pTankBottom;		///<	戦車の下部

	CTankIntInter*	_pIntelligence;		///<	思考

	uint			_unIntType;			///<	思考タイプ
};
#endif