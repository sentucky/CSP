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
class CStageData;
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
		const float fTurnSpeed	//		旋回速度
		);
	~CTank();					///<	デストラクタ
	CTank(const CTank& src);	///<	コピーコンストラクタ

private:
	void release();				///<	解放処理
public:
	//	タスク
	void draw();				///<	描画処理
	void intelligence();		///<	思考更新
	void pause();				///<	姿勢の更新
	void move();				///<	移動処理
	void fire();				///<	発砲
	void calcMove();			///<	移動量計算

	//	呼出し
	void hitTestTank(CTank* pTank);	///<	あたり判定
	void hitTestShell(CShell* pShell);
	void hitTestWall();

private:
	void turnTop();				///<	上部の回転

public:
	void enableTask();			///<	タスク有効化
	void disableTask();			///<	タスク無効化

	const D3DXMATRIXA16*	getMatBottom();	///<	ボトムのマトリクス取得
	const D3DXVECTOR3*		getMoveVec();	///<	移動ベクトル
	const float				getRadius();	///<	半径の取得
	const float				getMass();		///<	質量の取得

	void setMoveVec( D3DXVECTOR3& MoveVec );
	void setMoveVec( const D3DXVECTOR3 *MoveVec );
	void setPos(const float x,const float z);
	static void setStageData(const CStageData* pStageData)
	{
		_StageData = pStageData;
	}
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTaskList*		_pTaskCalcAM;
	CTankTop*		_pTankTop;			///<	戦車の上部
	CTankBottom*	_pTankBottom;		///<	戦車の下部

	CTankIntInter*	_pIntelligence;		///<	思考

	float			_fRadius;			///<	半径
	float			_fMass;				///<	質量
	uint			_unIntType;			///<	思考タイプ
#ifdef _DEBUG
LPD3DXMESH debugMesh;;
#endif

	static const CStageData* _StageData;
};
#endif