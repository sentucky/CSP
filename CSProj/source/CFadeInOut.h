/***********************************************************************/
/*! @file  CFadeInOut.h
 *  @brief フェードインアウト
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
#include"CSingleton.h"
#include"common.h"

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CSprite;

/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define FADEINOUT CFadeInOut::getInst()

/***********************************************************************/
//	列挙定義
/***********************************************************************/
enum
{
	FADE_ON,
	FADE_NONE,
};

/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CFadeInOut:public CSingleton<CFadeInOut>
{
	//	フレンド登録
	friend class CSingleton<CFadeInOut>;

private:
	CFadeInOut();	///<	コンストラクタ
	~CFadeInOut();	///<	デストラクタ

public:
	void update();							///<	更新処理
	BOOL fadeInOut();						///<	フェード更新処理
	void fadeOutStart( uint unDenominator);	///<	フェードアウト開始
	void fadeInStart(  uint unDenominator);	///<	フェードイン開始
	int calcBlind();						///<	ブラインドのアルファ値計算
	void draw();							///<	ブラインド描画
	const uint getState();					///<	状態取得
private:
	int _unDenominator;	//!< ブラインド濃度の分母
	int _unNumerator;	//!< ブラインド濃度の分子
	int _unFadeSpeed;	//!< フェード速度
	CSprite* _pSprite;	//!< スプライト
	uint _State;		//!< 状態
};