/***********************************************************************/
/*! @file  CShell.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___BULLET___
#define ___BULLET___

class CTaskList;
class CMesh;
class CTank;
class CStageData;

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
				CMesh*	Mesh,
				const int power
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

	//
	void hitTestTank(CTank* pTank);	///<	戦車との衝突
	void hitTestWall();

	//	ゲッタ
	D3DXVECTOR3& getTrajectory();
	D3DXVECTOR3& getMoveVector();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const D3DXMATRIXA16* 
	 */
	/***********************************************************************/
	const D3DXMATRIXA16* getMatW(){return &_matW;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const CTank* 
	 */
	/***********************************************************************/
	const CTank* getOwner(){
		return _Owner;
	}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const int 
	 */
	/***********************************************************************/
	const int	getPower(){return _Power;}

	void moveVector(const D3DXVECTOR3* MoveVec);

	//	セッタ
	void setPos(const D3DXMATRIXA16*	pos);
	void setPos(const D3DXVECTOR3*		pos);
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] pTank 
	 *  @retval void
	 */
	/***********************************************************************/
	void setOwner(CTank* pTank){
		_Owner = pTank;
	}

private:
	D3DXMATRIXA16	_matW;			///<	ワールドマトリクス
	D3DXVECTOR3		_OldPos;		///<	旧座標
	D3DXVECTOR3		_Trajectory;	///<	軌道ベクトル
	D3DXVECTOR3		_MoveVector;	///<	移動ベクトル
	CMesh*			_pMesh;			///<	メッシュ
	float			_MoveSpeed;		///<	移動速度
	int				_Power;			///<	威力
	const int		_nMaxLife;		///<	ライフ
	int				_nLife;			////<
	CTank*			_Owner;			///<	発射した戦車

	//	タスク
	CTaskList*		_TaskListDraw;			///<	描画タスク
	CTaskList*		_TaskListMove;			///<	移動タスク
	CTaskList*		_TaskListCheckAlive;	///<	生死確認タスク
	CTaskList*		_TaskListExplosion;		///<	爆発タスク

	static CStageData* _StageData;

#ifdef _DEBUG
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const float 
	 */
	/***********************************************************************/
	const float getRad(){return _fRad;}
	float _fRad;
#endif

};

#endif