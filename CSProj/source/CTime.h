/***********************************************************************/
/*! @file  CTime.h
 *  @brief 時間系クラス
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
#include<Windows.h>
#include <mmsystem.h>
#include"CSingleton.h"
#include"common.h"
#pragma comment( lib , "winmm.lib" )


/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define CTIMER CTimer::getInst()

/***********************************************************************/
//	定数定義
/***********************************************************************/
const float FRAME_RATE = 1000.0f / 60.0f;	///<フレームレート

class CTimer: public CSingleton<CTimer>
{
	//	フレンド登録
	friend class CSingleton<CTimer>;
private:
	CTimer();				///<	コンストラクタ
	~CTimer();				///<	デストラクタ
	CTimer(const CTimer&);	///<	コピーコンストラクタ

public:
	void init();							///<	初期化処理
	void update();							///<	更新処理
	void release();							///<	開放時処理
	const ulong getFPS();					///<	FPS取得
	const ulong getCurrentTime();			///<	現在時刻の取得
	bool updateFrame();						///<	更新処理
	const ulong getTotalElapFrame();		///<	総経過フレーム数
	const ulong getTotalElapFrame()const;	///<	総経過フレーム数
	void countupTotalElapFrame();			///<	総経過フレーム数加算

private:
	ulong _ulExecLastTime;		///<	最終処理時刻
	ulong _ulFPSLastTime;		///<	ＦＰＳ最終更新時刻
	ulong _ulCurrentTime;		///<	現在時刻
	ulong _ulTotalElapFrame;	///<	総経過時間
	ulong _ulFrameCount;		///<	フレームカウント
	ulong _ulFPS;				///<	現在FPS
};

