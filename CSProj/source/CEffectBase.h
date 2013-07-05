/***********************************************************************/
/*! @file  CEffectBase.h
 *  @brief エフェクトベース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CEFFECTBASE___
#define ___CEFFECTBASE___	//!<	インクルードガード

/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"common.h"
#include<WinDef.h>

/***********************************************************************/
//	先行宣言
/***********************************************************************/
class CMesh;


/***********************************************************************/
//	クラス定義
/***********************************************************************/
class CEffectBase
{
public:
	CEffectBase(char FXFilePath[MAX_PATH]);	///<	コンストラクタ
	virtual ~CEffectBase();							///<	デストラクタ
	CEffectBase(const CEffectBase& src);
private:
public:
	void release();
	virtual BOOL create()		= 0;	//	初期化処理
	virtual BOOL cloneCreate()	= 0;	//	被コピー時の初期化


	uint begin(uint Technique);
	void end();					//	描画後処理
	BOOL beginPass(uint Pass);	//
	void endPass();				//
	void commitChanges();

	virtual void setHandles(uint HandleID,D3DXHANDLE) = 0;

protected:
	char*						 _FxPath;	//!<	fxファイルパス
	LPD3DXEFFECT				 _Effect;	//!<	エフェクト
};
#endif