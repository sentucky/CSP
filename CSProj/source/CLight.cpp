/***********************************************************************/
/*! @file  CLight.cpp
 *  @brief ���C�g�N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	CLight.h
//	�T�v			���C�g�N���X
//	�����		�쌴�C��
//	�X�V����		
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CLight.h"	//���C�g�N���X�w�b�_
#include"CDevice.h"	//�f�o�C�X�N���X�w�b�_

/***********************************************************************/
//	�ÓI�����o������
/***********************************************************************/
int CLight::_nSumId = 0;
bool CLight::_bRegistorState[sc_nMaxRegistor];

/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CLight::CLight()
{
	//---�l�̏�����---//
	if(_nSumId > sc_nMaxRegistor)
	{//	�o�^���E���𒴂��Ă����Ƃ��A�o�^�ł��Ȃ�
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
/*! @brief �f�X�g���N�^
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
/*! @brief ����������
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::init()
{
	D3DMATERIAL9 mtrlInitializer;
	ZeroMemory( &_Light, sizeof(D3DLIGHT9));	//�������̗�N���A
	ZeroMemory( &mtrlInitializer, sizeof(D3DMATERIAL9));	//�������̗�N���A
	_Light.Type = D3DLIGHT_DIRECTIONAL;		//���C�g�^�C�v�̐ݒ�
	_Light.Diffuse.r = 1.0f;					//�f�B�t���[�Y�F��
	_Light.Diffuse.g = 1.0f;					//			�@ ��
	_Light.Diffuse.b = 1.0f;					//			�@ ��
	_Light.Diffuse.a = 1.0f;					//			�@ �A���t�@
	_Light.Direction.x = 0.0f;					//���̌���X
	_Light.Direction.y = -1.0f;					//       Y
	_Light.Direction.z = 0.0f;					//		 Z
	_Light.Position.y = 0.0f;					//�����_X
	_Light.Position.x = 0.0f;					//      Y
	_Light.Position.z = 0.0f;					//		Z
	_Light.Range = 1000.0f;					//���̓͂�����
	_Light.Attenuation0 = 0.0f;
	_Light.Attenuation1 = 1.0f;
	_Light.Attenuation2 = 0.0f;
	_Light.Phi   = D3DX_PI;
	_Light.Theta = D3DX_PI;	//0 �` phi
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
/*! @brief ���C�g�̗L����
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::activeLight()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = D3DDEVICE;
	//---���C�g�̗L����---//
	hr = pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
	if(FAILED(hr))
	{
		MessageBox(NULL, "���C�g�L�������G���[","",MB_OK);
		exit(1);
	}
	
	pDevice->SetLight( _nId, &_Light);	//���C�g�̐ݒu
	pDevice->SetRenderState(D3DRS_AMBIENT , 0x00444444 );	//����ŏƂ炷
	pDevice = NULL;
}


/***********************************************************************/
/*! @brief ���C�g���擾
 * 
 *  @retval D3DLIGHT9* 
 */
/***********************************************************************/
D3DLIGHT9* CLight::getLight()
{
	return &_Light;
}

/***********************************************************************/
/*! @brief ���C�g�^�C�v�ݒ�
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
/*! @brief �f�B�t���[�Y�F�ݒ�
 * 
 *  @param[in] fR 
 *  @param[in] fG 
 *  @param[in] fB 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffRGBA(const float fR,const float fG,const float fB,const float fA)	//��
{
	_Light.Diffuse.r = fR;
	_Light.Diffuse.g = fG;
	_Light.Diffuse.b = fB;
	_Light.Diffuse.a = fA;
}

/***********************************************************************/
/*! @brief �f�B�t���[�Y�F�Ԑݒ�
 * 
 *  @param[in] fR 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffR(const float fR)	//��
{
	_Light.Diffuse.r = fR;
}

/***********************************************************************/
/*! @brief �f�B�t���[�Y�F�ΐݒ�
 * 
 *  @param[in] fG 
 *  @retval void
 */
/***********************************************************************/
void CLight::setDiffG(const float fG)	//��
{
	_Light.Diffuse.g = fG;
}

/***********************************************************************/
/*! @brief �f�B�t���[�Y�F�ݒ�
 * 
 *  @param[in] fB 
 *  @retval void setDiffA 
 */
/***********************************************************************/
void CLight::setDiffB(const float fB)	//��
{
	_Light.Diffuse.b = fB;
}

/***********************************************************************/
/*! @brief �f�B�t���[�Y�F�A���t�@�ݒ�
 * 
 *  @param[in] fA 
 *  @retval void setDiffA 
 */
/***********************************************************************/
void CLight::setDiffA(const float fA)	//��
{
	_Light.Diffuse.a = fA;
}

/***********************************************************************/
/*! @brief ���C�g�x�N�g���̐ݒ�
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
/*! @brief ���̓͂�������ݒ�
 * 
 *  @param[in] fRange 
 *  @retval void
 */
/***********************************************************************/
void CLight::setRange(const float fRange)	//���̓͂������ݒ�
{
	_Light.Range = fRange;
}

/***********************************************************************/
/*! @brief ���C�g������
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::lightON()
{
	D3DDEVICE->LightEnable( _nId , TRUE);		//���������
}

/***********************************************************************/
/*! @brief ���C�g������
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::lightOFF()
{
	D3DDEVICE->LightEnable( _nId , FALSE);		//�����
}

/***********************************************************************/
/*! @brief ���C�g�̍��W��ݒ�
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
/*! @brief ���C�g��ݒ�
 * 
 *  @retval void
 */
/***********************************************************************/
void CLight::setLight()
{
	D3DDEVICE->SetLight(_nId, &_Light);
}

/***********************************************************************/
/*! @brief �������̐ݒ�
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
/*! @brief �|�C���g���C�g�̐ݒ�
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
/*! @brief �f�B���N�V���i�����C�g�̐ݒ�
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
/*! @brief �X�|�b�g���C�g�̐ݒ�
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