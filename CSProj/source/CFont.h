/***********************************************************************/
/*! @file  CFont.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

/***********************************************************************/
//	ヘッダファイル
/***********************************************************************/
#include<d3dx9.h>
#include<d3d9.h>
#include"CSingleton.h"
#include"CDevice.h"
#include"commonstruct.h"

/***********************************************************************/
//	マクロ定義
/***********************************************************************/
#define FONT CFont::getInst()	//	インスタンスの取得


class CFont:public CSingleton<CFont>
{
	friend class CSingleton<CFont>;
private:
	explicit CFont();
	~CFont();
public:
	void init();	///<	初期化
	void init(INT Height,UINT Width,UINT Weight);	///<	引数つき初期化
	void release();									///<	開放
	void DrawStr(char	pStr[MAX_PATH],RECT& rect);	///<	文字列描画
	void DrawInt(char	pStr[MAX_PATH], int		nNum, RECT& rect);	///<	整数描画
	void DrawFloat(char pStr[MAX_PATH], float	fNum, RECT& rect);	///<	小数描画
	void DrawLong(char	pStr[MAX_PATH], long	lNum, RECT& rect);	///<	32ビット整数描画
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] color 
	 *  @retval void
	 */
	/***********************************************************************/
	void setColor(D3DCOLOR color){_Color = color;}					///<	描画色設定

	//++++++++++++++++++++++++++++++++++++
	//	メンバ変数
	//++++++++++++++++++++++++++++++++++++
private:
	LPD3DXFONT _pFont;		///<	描画フォント
	D3DXFONT_DESC _LogFont;	
	D3DCOLOR _Color;		///<	描画色
};

