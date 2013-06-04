/***********************************************************************/
/*! @file  CTankIntInter.h
 *  @brief タンク思考インターフェース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTASKINTINTER___
#define ___CTASKINTINTER___	///<	インクルードガード


/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"common.h"

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CTank;
class CStageData;

/***********************************************************************/
//	定数
/***********************************************************************/
/*! @brift 旋回方向*/
enum eTANK_MOVE
{
	TMV_1 = 1,
	TMV_2,
	TMV_3,
	TMV_4,
	TMV_5,
	TMV_6,
	TMV_7,
	TMV_8,
	TMV_9,
};


/***********************************************************************/
/*!	@class CTankIntInter
 *	@brift タンク思考インターフェース
 */
/***********************************************************************/
class CTankIntInter
{
public:
	CTankIntInter(CTank*);					///<	コンストラクタ
	virtual ~CTankIntInter();				///<	デストラクタ
	
	virtual void update() = 0;				///<	更新関数

protected:
	void myStep();						//	足下確認
public:

	const BOOL getFireFlg();				///<	発砲フラグの取得
	const uint getMoveFlg();				///<	移動方向フラグの取得
	const D3DXVECTOR3* getTargetPoint();	///<	砲塔を向ける先を取得
	static void setStageData(const CStageData* StageData);	//	ステージデータの設定
protected:
	BOOL	_FireFlg;					///<	発砲フラグ
	uint	_MoveDir;					///<	移動方向フラグ
	CTank*	_pMyTank;					///<	思考が反映される戦車
	D3DXVECTOR3			_TargetPoint;	///<	ターゲットの座標
	static CTank*		_pPlayerTank;	///<	プレイヤータンクのポインタ
	static const CStageData*	_StageData;		///<	ステージデータ
};


#endif