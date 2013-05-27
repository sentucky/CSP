//-------------------------------------------------------------------------------------------------
/** 
 * @file	ShadowMap.fx
 * @brief	シャドウマップサンプル
 *
 * @author	Koichi Kusano
 * @version 1.0
 *
 * Copyright (C) 2010 Koichi Kusano, Inc. All rights reserved.
 */

//=================================================================================================
//
// グローバル変数
//
float4x4 WVP;								// カメラ位置基準：座標変換の行列(ローカル～射影空間)
float4 Color;								// メッシュの色
float4 LightDir;							// 光の位置（ローカル座標系）

const float EdgeThickness = 0.01f;			// 輪郭の暑さ

//=================================================================================================
//
// テクスチャ
//
// 通常のテクスチャ
texture DecalTex;
sampler DecalSamp = sampler_state
{
    Texture = <DecalTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};

// トゥーン用のテクスチャ
texture ToonTex;
sampler ToonSamp = sampler_state
{
    Texture = <ToonTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};

//=================================================================================================
//
// 頂点シェーダからピクセルシェーダに渡すデータ
//
struct VS_OUTPUT0
{
    	float4 Pos		: POSITION;
	float2 DecalTex		: TEXCOORD0;
	float2 ToonTex		: TEXCOORD1;
};

struct VS_OUTPUT1
{
    float4 Pos			: POSITION;
};

//=================================================================================================
//
// 頂点シェーダ
//
VS_OUTPUT0 vsToon(
	float4 Pos      : POSITION,								// ローカル位置座標
	float4 Normal   : NORMAL,								// 法線ベクトル
	float2 Texcoord : TEXCOORD0								// UV座標
)
{
    VS_OUTPUT0 Out = (VS_OUTPUT0)0;							// 出力データ

	Out.Pos = mul(Pos,WVP);
	
	float3 N = Normal.xyz;
	float3 L = -LightDir.xyz;
	
	
	
	Out.DecalTex = Texcoord;


	Out.ToonTex.x = Out.ToonTex.y = max(0,dot(N,-L));

 	return Out;
}

VS_OUTPUT1 vsEdge(
	float4 Pos      : POSITION,								// ローカル位置座標
	float4 Normal   : NORMAL,								// 法線ベクトル
	float2 Texcoord : TEXCOORD0								// UV座標
)
{
    VS_OUTPUT1 Out = (VS_OUTPUT1)0;							// 出力データ

    Out.Pos = Pos + Normal * EdgeThickness;
    Out.Pos = mul(Out.Pos,WVP);

 	return Out;
}

//=================================================================================================
//
// ピクセルシェーダー
//
float4 psToon(VS_OUTPUT0 In) : COLOR
{
	float4 OutPut = (float4)0;
	
	float4 Dc = tex2D(
	DecalSamp,
	In.DecalTex);
	
	float4 Tn = tex2D(
	ToonSamp,
	In.ToonTex);
	
	OutPut = Dc * Tn * Color;
	
	
	
	return OutPut;
}

float4 psEdge(VS_OUTPUT1 In) : COLOR
{
	return float4(0, 0, 0, 1);
}

//=================================================================================================
//
// テクニック
//
technique Toon
{
	// 階調ライティング描画
    pass p0
    {
		CullMode = CCW;

		VertexShader = compile vs_2_0 vsToon();
		PixelShader  = compile ps_2_0 psToon();
    }
	// エッジ描画
	pass p1
    {
		CullMode = CW;
		
		VertexShader = compile vs_2_0 vsEdge();
		PixelShader  = compile ps_2_0 psEdge();
    }
}

