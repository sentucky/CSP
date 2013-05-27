/***********************************************************************/
/*! @file  commonfunc.cpp
 *  @brief
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"commonfunc.h"

/***********************************************************************/
//	グローバル関数定義
/***********************************************************************/
/***********************************************************************/
/*! @brief 座標変換
 * 
 *  @param[out] matWorld	座標変換マトリクスポインタ
 *  @param[in] refvec3Pos	移動ベクトルの参照
 *  @param[in] refvec3Rot	軸ごとの回転量の参照
 *  @param[in] refvec3Scale 拡大率の参照
 *  @retval void
 */
/***********************************************************************/
void worldMatrixTransform(
	D3DXMATRIXA16* matWorld,
	const D3DXVECTOR3& refvec3Pos,
	const D3DXVECTOR3& refvec3Rot,
	const D3DXVECTOR3& refvec3Scale 
	)
{
	////////////////////////////
	//	変数宣言
	D3DXMATRIXA16 rot;		//回転マトリクス
	D3DXMATRIXA16 scale;	//サイズマトリクス
	D3DXMATRIXA16 pos;		//座標マトリクス
	

	////////////////////////////
	//	座標変換
	//---拡大率
	D3DXMatrixScaling(
		&scale,
		refvec3Scale.x,
		refvec3Scale.y,
		refvec3Scale.z
		);

	//---回転
	D3DXMatrixRotationYawPitchRoll(
		&rot,
		D3DXToRadian(refvec3Rot.y),
		D3DXToRadian(refvec3Rot.x),
		D3DXToRadian(refvec3Rot.z)
		);
	
	//---座標
	D3DXMatrixTranslation( 
		&pos,
		refvec3Pos.x,
		refvec3Pos.y,
		refvec3Pos.z
		);

	//---マトリクスのかけ合わせ
	*matWorld *= scale;	//拡大率
	*matWorld *= rot;	//回転
	*matWorld *= pos;	//座標

}


/***********************************************************************/
/*! @brief 重力加速
 * 
 *  @param[in] fElTime 経過時間
 *  @retval float 落下移動量
 */
/***********************************************************************/
float gravAcc(float fElTime)
{
	return 0.5f * grvityacc * fElTime * fElTime;
}


/***********************************************************************/
/*! @brief 乱数の取得
 * 
 *  @param[in] nBetween 
 *  @retval uint 乱数の幅
 */
/***********************************************************************/
uint getRand(uint nBetween)
{
	static bool bFirst = true;
	if(bFirst)
	{
		srand((uint)time(NULL));
		bFirst = false;
	}

	if(nBetween <= 0)
	{
		return 0;
	}
	return rand() % nBetween;
}


/***********************************************************************/
/*! @brief アラートのメッセージボックスを表示するだけ
 * 
 *  @param[in] charszText[MAX_PATH] 
 *  @param[in] charszCaption[MAX_PATH] 
 *  @retval void
 */
/***********************************************************************/
void MessageAlert( char szText[MAX_PATH], char szCaption[MAX_PATH])
{
	MessageBox( NULL, szText, szCaption,MB_ICONWARNING | MB_OK);
}


/***********************************************************************/
/*! @brief 球と球のあたり判定
 * 
 *  @param[in] vec3PosA オブジェクトＡの位置ベクトル
 *  @param[in] fARadius オブジェクトＡの半径
 *  @param[in] vec3PosB オブジェクトＢの位置ベクトル
 *  @param[in] fBRadius オブジェクトＢの半径
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindBall(D3DXVECTOR3& vec3PosA,float fARadius,D3DXVECTOR3& vec3PosB,float fBRadius)
{
	////////////////////////////
	//	変数宣言
	float fX;
	float fY;
	float fZ;
	float fDistance;


	////////////////////////////
	//	二つのオブジェクトの距離を計算
	fX = (vec3PosA.x - vec3PosB.x) * (vec3PosA.x - vec3PosB.x);
	fY = (vec3PosA.y - vec3PosB.y) * (vec3PosA.y - vec3PosB.y);
	fZ = (vec3PosA.z - vec3PosB.z) * (vec3PosA.z - vec3PosB.z);


	////////////////////////////
	//	物体と接触する距離の計算
	fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);

	////////////////////////////
	//	接触判定
	if(	fX + fY + fZ <=  fDistance)
	{
		return TRUE;
	}
	return FALSE;
}


/***********************************************************************/
/*! @brief 球と球のあたり判定
 * 
 *  @param[in] matPosA	オブジェクトＡのマトリクス
 *  @param[in] fARadius オブジェクトＡの半径
 *  @param[in] matPosB	オブジェクトＢのマトリクス
 *  @param[in] fBRadius オブジェクトＢの半径
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindBall(D3DXMATRIXA16& matPosA,float fARadius,D3DXMATRIXA16& matPosB,float fBRadius)
{
	////////////////////////////
	//	変数宣言
	float fX;
	float fY;
	float fZ;
	float fDistance;


	////////////////////////////
	//	二つのオブジェクトの距離を計算
	fX = (matPosA._41 - matPosB._41) * (matPosA._41 - matPosB._41);
	fY = (matPosA._42 - matPosB._42) * (matPosA._42 - matPosB._42);
	fZ = (matPosA._43 - matPosB._43) * (matPosA._43 - matPosB._43);
	fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);
	//球とプレイヤーのあたり判定
	if(	fX + fY + fZ <=  fDistance)
	{
		return TRUE;
	}
	return FALSE;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] vec2PosA 
 *  @param[in] fARadius 
 *  @param[in] vec2PosB 
 *  @param[in] fBRadius 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindCircle(D3DXVECTOR2* vec2PosA,float fARadius,D3DXVECTOR2* vec2PosB,float fBRadius)
{
	float fX;
	float fY;
	float fDistance;
	fX = (vec2PosA->x - vec2PosB->x) * (vec2PosA->x - vec2PosB->x);
	fY = (vec2PosA->y - vec2PosB->y) * (vec2PosA->y - vec2PosB->y);
	fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);
	//球とプレイヤーのあたり判定
	if(	
		fX
		+	fY
		<=  fDistance
		)
	{
		return TRUE;
	}
	return FALSE;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] pvec2PosA 
 *  @param[in] pRectSizeA 
 *  @param[in] pvec2PosB 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindRect(D3DXVECTOR2* pvec2PosA, RECT*  pRectSizeA,D3DXVECTOR2* pvec2PosB)
{
	if(	pvec2PosA->x < pvec2PosB->x		//	左端
		&&	pvec2PosA->x + pRectSizeA->right > pvec2PosB->x	//右端
		&&	pvec2PosA->y < pvec2PosB->y	//	上端
		&&	pvec2PosA->y + pRectSizeA->bottom > pvec2PosB->y
		)
	{
		return TRUE;
	}

	return FALSE;
}


/***********************************************************************/
/*! @brief 衝突後の運動計算
 * 
 *  @param[out] pv1Out オブジェクト１の衝突後の移動量
 *  @param[in] v1	   オブジェクト２の衝突後の移動量
 *  @param[in] v2	   オブジェクト１の移動量
 *  @param[in] m1	   オブジェクト２の上と同軸の移動量
 *  @param[in] m2	   オブジェクト１の質量
 *  @param[in] e1	   オブジェクト２の質量
 *  @param[in] e2	   オブジェクト１が持つ反発係数
 *  @retval void	   オブジェクト２が持つ反発係数
 */
/***********************************************************************/
void commonfunc::repulsion(float* pv1Out,float v1, float v2,float m1,float m2, float e1, float e2)
{
#ifdef _DEBUG
	if(e1 > 1 || 0 > e1)
	{
		MessageAlert("e1に不正な値が入力されています","error from repulsion");
	}
	if(e2 > 1 || 0 > e2)
	{
		MessageAlert("e2に不正な値が入力されています","error from repulsion");
	}
#endif
	*pv1Out = (m1 - (e1 * e2) * m2) * v1  / (m1 + m2) + (1 + e1 * e2) * m2 * v2 / (m1 + m2);
}