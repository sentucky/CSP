/***********************************************************************/
/*! @file  CLight.cpp
 *  @brief ライトクラス
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	ファイル名	CLight.h
//	概要			ライトクラス
//	制作者		川原佑介
//	更新履歴		
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CLight.h"	//ライトクラスヘッダ
#include"CDevice.h"	//デバイスクラスヘッダ

/***********************************************************************/
//	静的メンバ初期化
/***********************************************************************/
int CLight::_nSumId = 0;
bool CLight::_bRegistorState[sc_nMaxRegistor];

/***********************************************************************/
/*! @brief コンストラクタ
 */
/***********************************************************************/
CLight::CLight()
{
	//---値の初期化---//
	if(_nSumId > sc_nMaxRegistor)
	{//	登録限界数を超えていたとき、登録できない
		delete this;
		return;
	}
	for(int nCnt = 0; nCnt < sc_nMaxRegistor; nCnt++)
	{
		if(false == _bRegistorState[nCnt])
		{
			init();
			_bRegistorState[nCnt] = true;
			_nId = nCnt;
			_nSumId++;
			lightON();
			return;
		}
	}
	if(sc_nMaxRegistor >= sc_nMaxRegistor)
	{
		delete this;
	}
}


/***********************************************************************/
/*! @brief デストラクタ
 */
/***********************************************************************/
CLight::~CLight()
{
	if(_nId == -1)
	{
		return;
	}

}

/***********************************************************************/
/*! @brief 初期化処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::init()
{
	D3DMATERIAL9 mtrlInitializer;
	ZeroMemory( &_Light, sizeof(D3DLIGHT9));	//メモリの零クリア
	ZeroMemory( &mtrlInitializer, sizeof(D3DMATERIAL9));	//メモリの零クリア
	_Light.Type = D3DLIGHT_DIRECTIONAL;		//ライトタイプの設定
	_Light.Diffuse.r = 1.0f;					//ディフューズ色赤
	_Light.Diffuse.g = 1.0f;					//			　 青
	_Light.Diffuse.b = 1.0f;					//			　 緑
	_Light.Diffuse.a = 1.0f;					//			　 アルファ
	_Light.Direction.x = 0.0f;					//光の向きX
	_Light.Direction.y = -1.0f;					//       Y
	_Light.Direction.z = 0.0f;					//		 Z
	_Light.Position.y = 0.0f;					//発光点X
	_Light.Position.x = 0.0f;					//      Y
	_Light.Position.z = 0.0f;					//		Z
	_Light.Range = 1000.0f;					//光の届く距離
	_Light.Attenuation0 = 0.0f;
	_Light.Attenuation1 = 1.0f;
	_Light.Attenuation2 = 0.0f;
	_Light.Phi   = D3DX_PI;
	_Light.Theta = D3DX_PI;	//0 ～ phi
	_Light.Falloff = 1.0f;

	
	mtrlInitializer.Ambient.a = mtrlInitializer.Diffuse.a = 1.0f;
	mtrlInitializer.Ambient.r = mtrlInitializer.Diffuse.r = 1.0f;
	mtrlInitializer.Ambient.g = mtrlInitializer.Diffuse.g = 1.0f;
	mtrlInitializer.Ambient.b = mtrlInitializer.Diffuse.b = 1.0f;
	D3DDEVICE->SetMaterial( &mtrlInitializer );
	setLightType(D3DLIGHT_DIRECTIONAL);
	activeLight();
}


/***********************************************************************/
/*! @brief ライトの有効化
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::activeLight()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = D3DDEVICE;
	//---ライトの有効化---//
	hr = pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
	if(FAILED(hr))
	{
		MessageBox(NULL, "ライト有効化時エラー","",MB_OK);
		exit(1);
	}
	
	pDevice->SetLight( _nId, &_Light);	//ライトの設置
	pDevice->SetRenderState(D3DRS_AMBIENT , 0x00444444 );	//明りで照らす
	pDevice = NULL;
}


/***********************************************************************/
/*! @brief ライト情報取得
 * 
 *  @retval D3DLIGHT9* 
 */
/***********************************************************************/
D3DLIGHT9* CLight::getLight()
{
	return &_Light;
}

/***********************************************************************/
/*! @brief ライトタイプ設定
 * 
 *  @param[in] sType 
 *  @retval void
 */
/***********************************************************************/
void CLight::setLightType(const D3DLIGHTTYPE sType)
{
	_Light.Type = sType;
}

/***********************************************************************/
/*! @brief ディフューズ色設定
 * 
 *  @param[in] fR 
 *  @param[in] fG 
 *  @param[in] fB 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffRGBA(const float fR,const float fG,const float fB,const float fA)	//青
{
	_Light.Diffuse.r = fR;
	_Light.Diffuse.g = fG;
	_Light.Diffuse.b = fB;
	_Light.Diffuse.a = fA;
}

/***********************************************************************/
/*! @brief ディフューズ色赤設定
 * 
 *  @param[in] fR 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffR(const float fR)	//赤
{
	_Light.Diffuse.r = fR;
}

/***********************************************************************/
/*! @brief ディフューズ色緑設定
 * 
 *  @param[in] fG 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffG(const float fG)	//緑
{
	_Light.Diffuse.g = fG;
}

/***********************************************************************/
/*! @brief ディフューズ色青設定
 * 
 *  @param[in] fB 
 *  @retval void setDiffA 
 */
/***********************************************************************/
void CLight::setDiffB(const float fB)	//青
{
	_Light.Diffuse.b = fB;
}

/***********************************************************************/
/*! @brief ディフューズ色アルファ設定
 * 
 *  @param[in] fA 
 *  @retval void setDiffA 
 */
/***********************************************************************/
void CLight::setDiffA(const float fA)	//青
{
	_Light.Diffuse.a = fA;
}

/***********************************************************************/
/*! @brief ライトベクトルの設定
 * 
 *  @param[in] vec3Direction 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDirection( D3DXVECTOR3& vec3Direction)
{
	_Light.Direction = vec3Direction;
}

/***********************************************************************/
/*! @brief 光の届く距離を設定
 * 
 *  @param[in] fRange 
 *  @retval void
 */
/***********************************************************************/
void CLight::setRange(const float fRange)	//光の届く距離設定
{
	_Light.Range = fRange;
}

/***********************************************************************/
/*! @brief ライトをつける
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::lightON()
{
	D3DDEVICE->LightEnable( _nId , TRUE);		//明りをつける
}

/***********************************************************************/
/*! @brief ライトを消す
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::lightOFF()
{
	D3DDEVICE->LightEnable( _nId , FALSE);		//明りを
}

/***********************************************************************/
/*! @brief ライトの座標を設定
 * 
 *  @param[in] vec3Pos 
 *  @retval void
 */
/***********************************************************************/
void CLight::setPos( D3DXVECTOR3& vec3Pos)
{
	_Light.Position.x = vec3Pos.x;
	_Light.Position.y = vec3Pos.y;
	_Light.Position.z = vec3Pos.z;
}

/***********************************************************************/
/*! @brief ライトを設定
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::setLight()
{
	D3DDEVICE->SetLight(_nId, &_Light);
}

/***********************************************************************/
/*! @brief 減衰率の設定
 * 
 *  @param[in] eNo 
 *  @param[in] fAttenuation 
 *  @retval void
 */
/***********************************************************************/
void CLight::setAttenuation(const eATTENUATIONID eNo,const float fAttenuation)
{
	switch(eNo)
	{
	case ATT_0:
		_Light.Attenuation0 = fAttenuation;
		break;
	case ATT_1:
		_Light.Attenuation1 = fAttenuation;
		break;
	case ATT_2:
		_Light.Attenuation2 = fAttenuation;
		break;
	default:
		break;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] fTheta 
 *  @retval void
 */
/***********************************************************************/
void CLight::setInsideCorn(const float fTheta)
{
	_Light.Theta = fTheta;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] fPhi 
 *  @retval void
 */
/***********************************************************************/
void CLight::setOutsideCorn(const float fPhi)
{
	_Light.Phi = fPhi;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] fFallout 
 *  @retval void
 */
/***********************************************************************/
void CLight::setCornFallout(const float fFallout)
{
	_Light.Falloff = fFallout;
}


/***********************************************************************/
/*! @brief ポイントライトの設定
 * 
 *  @param[in] DiffColor 
 *  @param[in] vec3Pos 
 *  @param[in] fRange 
 *  @param[in] fAtt0 
 *  @param[in] fAtt1 
 *  @param[in] fAtt2 
 *  @retval void
 */
/***********************************************************************/
void CLight::setPointLight(
						   D3DCOLORVALUE& DiffColor,
						   D3DXVECTOR3& vec3Pos,
						   float fRange,
						   float fAtt0,
						   float fAtt1,
						   float fAtt2
						   )
{
	_Light.Type = D3DLIGHT_POINT;
	_Light.Diffuse.a = DiffColor.a;
	_Light.Diffuse.r = DiffColor.r;
	_Light.Diffuse.g = DiffColor.g;
	_Light.Diffuse.b = DiffColor.b;
	_Light.Position = vec3Pos;
	_Light.Range = fRange;
	_Light.Attenuation0 = fAtt0;
	_Light.Attenuation1 = fAtt1;
	_Light.Attenuation2 = fAtt2;
}

/***********************************************************************/
/*! @brief ディレクショナルライトの設定
 * 
 *  @param[in] DiffColor 
 *  @param[in] vec3Direct 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDirectionalLight(D3DCOLORVALUE& DiffColor, D3DXVECTOR3& vec3Direct)
{
	_Light.Type = D3DLIGHT_DIRECTIONAL;
	_Light.Diffuse.a = DiffColor.a;
	_Light.Diffuse.r = DiffColor.r;
	_Light.Diffuse.g = DiffColor.g;
	_Light.Diffuse.b = DiffColor.b;
	_Light.Direction = vec3Direct;
}

/***********************************************************************/
/*! @brief スポットライトの設定
 * 
 *  @param[in] DiffColor 
 *  @param[in] vec3Direct 
 *  @param[in] fRange 
 *  @param[in] vec3Pos 
 *  @param[in] fAtt0 
 *  @param[in] fAtt1 
 *  @param[in] fAtt2 
 *  @param[in] fInsideCorn 
 *  @param[in] fOutsideCorn 
 *  @param[in] fCornFallout 
 *  @retval void
 */
/***********************************************************************/
void CLight::setSpotLight(
						  D3DCOLORVALUE& DiffColor,
						  D3DXVECTOR3& vec3Direct,
						  const float fRange,
						  D3DXVECTOR3& vec3Pos,
						  const float fAtt0,
						  const float fAtt1,
						  const float fAtt2,
						  const float fInsideCorn,
						  const float fOutsideCorn,
						  const float fCornFallout
						  )
{
	_Light.Type = D3DLIGHT_SPOT;
	_Light.Diffuse.a = DiffColor.a;
	_Light.Diffuse.r = DiffColor.r;
	_Light.Diffuse.g = DiffColor.g;
	_Light.Diffuse.b = DiffColor.b;
	_Light.Direction = vec3Direct;
	_Light.Position = vec3Pos;
	_Light.Range = fRange;
	_Light.Attenuation0 = fAtt0;
	_Light.Attenuation1 = fAtt1;
	_Light.Attenuation2 = fAtt2;
	_Light.Theta = D3DXToRadian(fInsideCorn);
	_Light.Phi = D3DXToRadian(fOutsideCorn);
	_Light.Falloff = fCornFallout;
}
//EOF