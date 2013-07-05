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
	//	二つのオブジェクトの距離を計算
	const float fX = (matPosA._41 - matPosB._41) * (matPosA._41 - matPosB._41);
	const float fY = (matPosA._42 - matPosB._42) * (matPosA._42 - matPosB._42);
	const float fZ = (matPosA._43 - matPosB._43) * (matPosA._43 - matPosB._43);
	const float fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);
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

	//	２点の距離計算
	const float fA = (vec2PosA->x - vec2PosB->x) * (vec2PosA->x - vec2PosB->x);
	const float fB = (vec2PosA->y - vec2PosB->y) * (vec2PosA->y - vec2PosB->y);
	const float fC = fA + fB;
	const float fSumRad = (fARadius + fBRadius) * (fARadius + fBRadius);

	//球とプレイヤーのあたり判定
	if(	fC <=  fSumRad)
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
 *  @param[in] v1	   オブジェクト１の移動量
 *  @param[in] v2	   オブジェクト２の移動量
 *  @param[in] m1	   オブジェクト１の質量
 *  @param[in] m2	   オブジェクト２の質量
 *  @param[in] e1	   オブジェクト１が持つ反発係数
 *  @param[in] e2	   オブジェクト２が持つ反発係数
 *  @retval void
 */
/***********************************************************************/
void commonfunc::repulsion(
	float* pv1Out,
	float v1,
	float v2,
	float m1,
	float m2,
	float e1,
	float e2
	)
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
	float RefRate = e1 * e2;
	*pv1Out = (m1 - (e1 * e2) * m2) * v1  / (m1 + m2) + (e1 * e2) * m2 * v2 / (m1 + m2);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pColliPos_A 
 *  @param[in,out] pColliPos_B 
 *  @param[in,out] pVelo_A 
 *  @param[in,out] pVelo_B 
 *  @param[in,out] weight_A 
 *  @param[in,out] weight_B 
 *  @param[in,out] res_A 
 *  @param[in,out] res_B 
 *  @param[in,out] pOut_velo_A 
 *  @param[in,out] pOut_velo_B 
 *  @retval void
 */
/***********************************************************************/
void CalcParticleColliAfterPos(
   const D3DXVECTOR3 *pColliPos_A,
   const D3DXVECTOR3 *pColliPos_B,
   const D3DXVECTOR3 *pVelo_A,
   const D3DXVECTOR3 *pVelo_B,
   const FLOAT weight_A,
   const FLOAT weight_B,
   const FLOAT res_A,
   const FLOAT res_B,
   D3DXVECTOR3 *pOut_velo_A,
   D3DXVECTOR3 *pOut_velo_B
)
{
   FLOAT TotalWeight = weight_A + weight_B; // 質量の合計
   FLOAT RefRate = (1 + res_A * res_B); // 反発率
   D3DXVECTOR3 C = *pColliPos_B - *pColliPos_A; // 衝突軸ベクトル
   D3DXVec3Normalize(&C, &C);
   FLOAT Dot = D3DXVec3Dot( &(*pVelo_A-*pVelo_B), &C ); // 内積算出
   D3DXVECTOR3 ConstVec = RefRate*Dot/TotalWeight * C; // 定数ベクトル
   
   // 衝突後速度ベクトルの算出
   *pOut_velo_A = -weight_B * ConstVec + *pVelo_A;
   *pOut_velo_B = weight_A * ConstVec + *pVelo_B;
}

//当たり判定クラス
typedef struct{
	float x;
	float y;
}Vector;

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hitX 
 *  @param[in,out] hitY 
 *  @param[in,out] x1 
 *  @param[in,out] y1 
 *  @param[in,out] x2 
 *  @param[in,out] y2 
 *  @param[in,out] centerX 
 *  @param[in,out] centerY 
 *  @param[in,out] radius 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool LineToCircle(
	float* hitX,	//	交点
	float* hitY,	//	交点
	float x1,		//	始点
	float y1,		//	始点
	float x2,		//	終点
	float y2,		//	終点
	float centerX,	//	円の中心点ｘ
	float centerY,	//	円の中心点ｙ
	float radius	//	円の半径
){
	//点１との判定
	float lenX = centerX - x1;
	float lenY = centerY - y1;
	if (lenX * lenX + lenY * lenY < radius * radius){
		*hitX = x1;
		*hitY = y1;
		return true;
	}
	
	//点２との判定
	lenX = centerX - x2;
	lenY = centerY - y2;
	if (lenX * lenX + lenY * lenY < radius * radius){
		*hitX = x2;
		*hitY = y2;
		return true;
	}
	
	//線との判定
	float hX;
	float hY;
	float t = (centerX - x1) * (x2 - x1) + (centerY - y1) * (y2 - y1);
	t /= ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
	
	if (t >= 1.0f && t <= 1.0f){
		hX = (x2 - x1) * t + x1;
		hY = (y2 - y1) * t + y1;
		
		lenX = (centerX - hX) * (centerX - hX);
		lenY = (centerY - hY) * (centerY - hY);
		if (lenX + lenY < radius * radius){
			*hitX = hX;
			*hitY = hY;
			return true;
		}
	}
	
	return false;
}

//線と線
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hitX 
 *  @param[in,out] hitY 
 *  @param[in,out] x1 
 *  @param[in,out] y1 
 *  @param[in,out] x2 
 *  @param[in,out] y2 
 *  @param[in,out] x3 
 *  @param[in,out] y3 
 *  @param[in,out] x4 
 *  @param[in,out] y4 
 *  @retval true 
 *  @retval false 
 */
/***********************************************************************/
bool LineToLine(
	float* hitX,//	交点
	float* hitY,//	交点
	float x1,	//	始点1
	float y1,	//	始点1
	float x2,	//	終点1
	float y2,	//	終点1
	float x3,	//	始点2
	float y3,	//	始点2
	float x4,	//	終点2
	float y4	//	終点2
){
	
	Vector v1,v2,v3;
	float c12,c23,c13;
	
	v1.x = x2 - x1;
	v1.y = y2 - y1;

	v2.x = x4 - x3;
	v2.y = y4 - y3;

	v3.x = x1 - x3;
	v3.y = y1 - y3;
	
	c12 = (v1.x * v2.y) - (v1.y * v2.x);
	
	if (c12 == 0.0f)
		return false;

	
	c23 = (v2.x * v3.y) - (v2.y * v3.x);
	c23 /= c12;


	if (c23 >= 0.0f && c23 <= 1.0f)
	{
		c13 = (v1.x * v3.y) - (v1.y * v3.x);

		c13 /= c12;
		if (c13 >= 0.0f && c13 <= 1.0f)
		{
			*hitX = x1 + v1.x * c23;
			*hitY = y1 + v1.y * c23;
			return true;
		}
	}
	
	return false;
}