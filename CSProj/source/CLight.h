/***********************************************************************/
/*! @file  CLight.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	CLight.h
//	概要			ライトクラスヘッダ
//	制作者		川原佑介
//	更新履歴		
/***********************************************************************/
//===================================================================
//	インクルードガード
//===================================================================
#pragma once
//===================================================================
//	インクルード
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#include"common.h"

//===================================================================
//	インライン関数
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] a 
 *  @param[in,out] r 
 *  @param[in,out] g 
 *  @param[in,out] b 
 *  @retval inline D3DCOLORVALUE 
 */
/***********************************************************************/
inline D3DCOLORVALUE COLORVALUE(float a, float r, float g, float b)
{
	/////////////////////////
	//	変数宣言
	D3DCOLORVALUE ColorValue;	///<色の値格納

	/////////////////////////
	//	色値の設定
	ColorValue.a = a;
	ColorValue.r = r;
	ColorValue.g = g;
	ColorValue.b = b;

	/////////////////////////
	//	色値の設定
	return ColorValue;
}
//===================================================================
//	列挙定義
//===================================================================
//---------------------------
//	概要
//		アテニュエーション番号
//---------------------------
typedef enum
{
	ATT_0 = 0,
	ATT_1 = 1,
	ATT_2 = 2,
}eATTENUATIONID;

//===================================================================
//	クラス定義
//===================================================================
class CLight
{
public:
	/////////////////////////
	//	コンストラクタ
	CLight(	);


	/////////////////////////
	//	デストラクタ
	~CLight();

public:
	/////////////////////////
	//	メンバ関数
	void init();		///<初期化
	void update();		///<更新
	void release();		///<解放

	void activeLight();								///<ライトの有効化
	void setLightType(const D3DLIGHTTYPE sType);	///<ライトタイプの設定

	static D3DCOLORVALUE COLORVALUE();

	D3DLIGHT9* getLight();

	//...ディフューズ色設定
	void setDiffR(float fR);	///<赤
	void setDiffG(float fG);	///<緑
	void setDiffB(float fB);	///<青
	void setDiffA(float fA);	///<青
	void setDiffRGBA(float fR,float fG,float fB,float fA);	///<赤緑青

	void setLight();
	void setPos(D3DXVECTOR3& vec3Pos);				///<発光の座標
	void setDirection(D3DXVECTOR3& vec3Direction);	///<光のベクトル設定
	void setRange(const float fRange);					///<光の届く距離設定
	void setAttenuation(const eATTENUATIONID eNo,const float fAttenuation);
	void setInsideCorn(const float fTheta);	///<
	void setOutsideCorn(const float fPhi);
	void setCornFallout(const float fFallout);
	void setupLight();	///<ライトの設置
	void lightON();		///<明かりをつける
	void lightOFF();	///<明かりを消す

	void setPointLight(
		D3DCOLORVALUE& DiffColor,
		D3DXVECTOR3& vec3Direct,
		float fRange,
		float fAtt0,
		float fAtt1,
		float fAtt2
		);
	void setDirectionalLight(D3DCOLORVALUE& DiffColor, D3DXVECTOR3& vec3Direct);
	void setSpotLight(
		D3DCOLORVALUE& DiffColor, 
		D3DXVECTOR3& vec3Direct,
		const float fRange,
		D3DXVECTOR3& _vec3Pos,
		const float fAtt1, 
		const float fAtt3,
		const float fAtt2,
		const float fInsideCorn,
		const float fOutsideCornm,
		const float fCornFallout
		);

private:
	////////////////////////
	//	メンバ変数
	static const int	sc_nMaxRegistor = 10;				///<最大登録可能数
	D3DLIGHT9			_Light;								///<ライト構造体
	DWORD				_nId;								///<自身のID
	static bool			_bRegistorState[sc_nMaxRegistor];	///<登録されているIDのリスト
	static int			_nSumId;							///<登録IDの数
};


//EOF