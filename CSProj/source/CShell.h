#ifndef ___BULLET___
#define ___BULLET___

class CTaskList;
class CMesh;

#include"CObjBase.h"

/*!
 *	@class CShell
 *	@brift 砲弾
 */
class CShell:public CObjBase
{
public:
	//	コンストラクタ
	CShell(
		const	int		MaxLife,
				float	MoveSpeed,
				CMesh*	Mesh
		);
	//	デストラクタ
	~CShell();
	//	コピーコンストラクタ
	CShell(const CShell& src);

	//	タスクの有効化・無効化
	void enableTask();
	void disableTask();
	
	//	タスク系
	void draw();
	void move();
	void checkAlive();
	void explosion();

	//	ゲッタ
	D3DXVECTOR3& getTrajectory();
	D3DXVECTOR3& getMoveVector();

	//	セッタ
	void setMoveVector(const D3DXVECTOR3* MoveVec);
	void setPos(const D3DXMATRIXA16*	pos);
	void setPos(const D3DXVECTOR3*		pos);

private:
	D3DXMATRIXA16	_matW;			///<	ワールドマトリクス
	D3DXVECTOR3		_OldPos;		///<	旧座標
	D3DXVECTOR3		_Trajectory;	///<	軌道ベクトル
	D3DXVECTOR3		_MoveVector;	///<	移動ベクトル
	CMesh*			_pMesh;			///<	メッシュ
	float			_MoveSpeed;		///<	移動速度
	const int		_nMaxLife;		///<	ライフ最大値
	int				_nLife;			///<	現在ライフ

	//	タスク
	CTaskList*		_TaskListDraw;			///<	描画タスク
	CTaskList*		_TaskListMove;			///<	移動タスク
	CTaskList*		_TaskListCheckAlive;	///<	生死確認タスク
	CTaskList*		_TaskListExplosion;		///<	爆発タスク

};

#endif