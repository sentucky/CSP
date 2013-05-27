//-------------------------------------------------------------------------------------------------
/** 
 * @file	ShadowMap.fx
 * @brief	�V���h�E�}�b�v�T���v��
 *
 * @author	Koichi Kusano
 * @version 1.0
 *
 * Copyright (C) 2010 Koichi Kusano, Inc. All rights reserved.
 */

//=================================================================================================
//
// �O���[�o���ϐ�
//
float4x4 WVP;								// �J�����ʒu��F���W�ϊ��̍s��(���[�J���`�ˉe���)
float4 Color;								// ���b�V���̐F
float4 LightDir;							// ���̈ʒu�i���[�J�����W�n�j

const float EdgeThickness = 0.01f;			// �֊s�̏���

//=================================================================================================
//
// �e�N�X�`��
//
// �ʏ�̃e�N�X�`��
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

// �g�D�[���p�̃e�N�X�`��
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
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
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
// ���_�V�F�[�_
//
VS_OUTPUT0 vsToon(
	float4 Pos      : POSITION,								// ���[�J���ʒu���W
	float4 Normal   : NORMAL,								// �@���x�N�g��
	float2 Texcoord : TEXCOORD0								// UV���W
)
{
    VS_OUTPUT0 Out = (VS_OUTPUT0)0;							// �o�̓f�[�^

	Out.Pos = mul(Pos,WVP);
	
	float3 N = Normal.xyz;
	float3 L = -LightDir.xyz;
	
	
	
	Out.DecalTex = Texcoord;


	Out.ToonTex.x = Out.ToonTex.y = max(0,dot(N,-L));

 	return Out;
}

VS_OUTPUT1 vsEdge(
	float4 Pos      : POSITION,								// ���[�J���ʒu���W
	float4 Normal   : NORMAL,								// �@���x�N�g��
	float2 Texcoord : TEXCOORD0								// UV���W
)
{
    VS_OUTPUT1 Out = (VS_OUTPUT1)0;							// �o�̓f�[�^

    Out.Pos = Pos + Normal * EdgeThickness;
    Out.Pos = mul(Out.Pos,WVP);

 	return Out;
}

//=================================================================================================
//
// �s�N�Z���V�F�[�_�[
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
// �e�N�j�b�N
//
technique Toon
{
	// �K�����C�e�B���O�`��
    pass p0
    {
		CullMode = CCW;

		VertexShader = compile vs_2_0 vsToon();
		PixelShader  = compile ps_2_0 psToon();
    }
	// �G�b�W�`��
	pass p1
    {
		CullMode = CW;
		
		VertexShader = compile vs_2_0 vsEdge();
		PixelShader  = compile ps_2_0 psEdge();
    }
}

