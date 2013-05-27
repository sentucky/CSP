float4x4 WVP;	//	���W�ϊ��̍s��

//	�ʏ�e�N�X�`��
texture DecalTex;
sampler DecalSamp = sampler_state{
	Texture = <DecalTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//	�T���v���[�I�u�W�F�N�g
struct VS_OUTPUT{
	float4 Pos	:POSITION;
	float2 Tex	:TEXCOORD0;
};

//	���_�V�F�[�_
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

//	�s�N�Z���V�F�[�_
float4 psMain(VS_OUTPUT In):COLOR{
	return tex2D(DecalSamp,In.Tex);
}

//	�e�N�j�b�N
technique Hlsl{
	pass p0
	{
		VertexShader = compile vs_2_0 vsMain();
		PixelShader	 = compile ps_2_0 psMain();
	}
}