float4x4 WVP;	//	座標変換の行列

//	通常テクスチャ
texture DecalTex;
sampler DecalSamp = sampler_state{
	Texture = <DecalTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//	サンプラーオブジェクト
struct VS_OUTPUT{
	float4 Pos	:POSITION;
	float2 Tex	:TEXCOORD0;
};

//	頂点シェーダ
VS_OUTPUT vsMain(
	float4 Pos	:POSITION,
	float2 Tex	:TEXCOORD
	)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	Out.Pos = mul(Pos,WVP);
	Out.Tex = Tex;
	
	return Out;
}

//	ピクセルシェーダ
float4 psMain(VS_OUTPUT In):COLOR{
	return tex2D(DecalSamp,In.Tex);
}

//	テクニック
technique Hlsl{
	pass p0
	{
		VertexShader = compile vs_2_0 vsMain();
		PixelShader	 = compile ps_2_0 psMain();
	}
}