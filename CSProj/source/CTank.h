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
#include"StageData.h"
#include <dsound.h>



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
		CMesh* pMeshTop,		///< トップメッシュ
		CMesh* pMeshBottom,		///< ボトムメッシュ
		CMesh* pMeshBottom2,	///< ボトムメッシュ２
		uint   unThisType,		///< インテリジェンス
		CShell* pShellProto,	///< 
		const float fMoveSpeed,	///< 速度
		const float fTurnSpeed,	///< 旋回速度
		const int	Life		///< 
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
	void pLap();				///<	自機ラップ
	void destroyed();			///<	非破壊
	void stepReset();			///<	足下情報更新

	//	呼出し
	void hitTestTank(CTank* pTank);		///<	あたり判定
	void hitTestShell(CShell* pShell);	///<	弾とのあたり判定後処理
	void hitTestWall();					///<	壁とのあたり判定の処理
	void raceEnd();				///<	レース終了時処理
private:
	void turnTop();				///<	上部の回転
	void drawDestroyed();		///<	非破壊時の描画処理

public:
	void enableTask();			///<	タスク有効化
	void disableTask();			///<	タスク無効化

	static const bool lower(const CTank* A,const CTank* B);
	void rotationY(const float fY);	

	///	ゲッタ
	CTankBottom*				getTankBottom()	{return _pTankBottom;}
	const D3DXMATRIXA16*	getMatBottom();	///<	ボトムのマトリクス取得
	const D3DXVECTOR3*		getMoveVec();	///<	移動ベクトル
	const float				getRadius();	///<	半径の取得
	const BOOL				getDestroyed()		{return _Destroyed;		}	///<	被破壊フラグ取得
	const BOOL				getFlgGoal()		{return _FlgGoal;		}
	const uint				getThisType()		{return _unThisType;	}
	const float				getlapVal()			{return _lapVal;		}
	const int				getlap()			{return _lap;			}
	const int				getradiate()		{return _radiate;		}
	const int				getMaxradiateTime()	{return _MaxRadiateTime;}
	const int				getlife()			{return _life;			}
	const int				getmaxlife()		{return _Maxlife;		}
	const uint				getRank()			{return _Rank;			}
	const uint*				getCurStep()		{return _CurStep;		}
	const uint				getTankType()		{return _unThisType;	}
	const CTankIntInter*	getIntelligence()	{return _pIntelligence;	}		// 施行取得

	///	セッタ
	void setMoveVec( D3DXVECTOR3& MoveVec );
	void setMoveVec( const D3DXVECTOR3 *MoveVec );
	void setPos(const float x,const float z);
	void setRank(const uint Rank){_Rank = Rank;}

	static void setTankPlayer(CTank* Player){_Player = Player;};
	static void setStageData(const CStageData* pStageData		){	_StageData = pStageData;}
	static void setSoundFire(const LPDIRECTSOUNDBUFFER SoundFire){ _SoundFire = SoundFire;}
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTaskList*		_pTaskCalcAM;
	CTaskList*		_pTaskRap;
	CTaskList*		_pTaskDestroyed;
	CTaskList*		_pTaskStepReset;

	CTankTop*		_pTankTop;			///<	戦車の上部
	CTankBottom*	_pTankBottom;		///<	戦車の下部
	CTankIntInter*	_pIntelligence;		///<	思考

	float			_fRadius;			///<	半径
	BOOL			_Destroyed;			///<	破壊判定フラグ
	BOOL			_FlgGoal;			///<	ゴールフラグ
	uint			_unThisType;		///<	タイプ
	float			_lapVal;			//	進行状態
	int				_lap;				//	ラップ数	
	int				_reverse;
	int				_radiate;			///<	放熱状況
	int				_MaxRadiateTime;	///<	放熱時間の最大値
	int				_life;				///<	耐久力
	const int		_Maxlife;			///<	耐久力
	uint			_Rank;				///<	ランク
	uint			_CurStep[2];		///<	現在の足下タイル

	int				_deldelayCount;	
	OUTPUT*         _Panel;				//
	OUTPUT*         _prevPanel;			//


	CSprite*		_SpriteExpload;
	D3DXMATRIXA16	_effectMatrix;
	bool			_expflag;

	static CTank* _Player;

public:
	static const uint TYPE_PLAYER = 0;
	static const uint TYPE_ENEMY01 = -1;
private:
	static LPDIRECTSOUNDBUFFER _SoundFire;
	static const int _maxdeldelayCount = 60;
	static const CStageData* _StageData;

#ifdef _DEBUG
LPD3DXMESH debugMesh;
#endif
};
#endif