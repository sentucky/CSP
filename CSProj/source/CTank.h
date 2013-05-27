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


private:
	void intFire();				///<
	void intMove();				///<	

	void calcDir();				///<	向きの更新
	void calcDirBottom();		///<	ボトムの向き計算
	void calcActiveMoveVec();	///<	能動的移動ベクトル計算


	void turnBottom(const float fTurnSpeed);
	void turnTop();

public:
	void enableTask();			///<	タスク有効化
	void disableTask();			///<	タスク無効化

	D3DXMATRIXA16* getMatBottom();	//	ボトムのマトリクス取得
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;

	CMesh*			_MeshTop;			///<	トップメッシュ
	CMesh*			_MeshBottom;		///<	ボトムメッシュ



	D3DXVECTOR3		_TopDir;			///<	トップの回転角
	D3DXVECTOR3		_BottomDir;			///<	ボトムの回転角

	D3DXVECTOR3		_MoveVec;			///<	移動ベクトル

	D3DXMATRIXA16	_matTop;			///<	トップのマトリクス
	D3DXMATRIXA16	_matBottom;			///<	ボトムのマトリクス
	
	float			_fNormalMoveSpeed;	///<	単位移動速度
	float			_fMoveSpeed;		///<	移動速度
	float			_fTurnSpeed;		///<	旋回速度

	CTankIntInter*	_pIntelligence;		///<	思考
	CShell*			_pShellProto;		///<	砲弾

	uint			_unIntType;			///<	思考タイプ
};
#endif