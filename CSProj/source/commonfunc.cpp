/***********************************************************************/
/*! @file  commonfunc.cpp
 *  @brief
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"commonfunc.h"

/***********************************************************************/
//	�O���[�o���֐���`
/***********************************************************************/
/***********************************************************************/
/*! @brief ���W�ϊ�
 * 
 *  @param[out] matWorld	���W�ϊ��}�g���N�X�|�C���^
 *  @param[in] refvec3Pos	�ړ��x�N�g���̎Q��
 *  @param[in] refvec3Rot	�����Ƃ̉�]�ʂ̎Q��
 *  @param[in] refvec3Scale �g�嗦�̎Q��
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
	//	�ϐ��錾
	D3DXMATRIXA16 rot;		//��]�}�g���N�X
	D3DXMATRIXA16 scale;	//�T�C�Y�}�g���N�X
	D3DXMATRIXA16 pos;		//���W�}�g���N�X
	

	////////////////////////////
	//	���W�ϊ�
	//---�g�嗦
	D3DXMatrixScaling(
		&scale,
		refvec3Scale.x,
		refvec3Scale.y,
		refvec3Scale.z
		);

	//---��]
	D3DXMatrixRotationYawPitchRoll(
		&rot,
		D3DXToRadian(refvec3Rot.y),
		D3DXToRadian(refvec3Rot.x),
		D3DXToRadian(refvec3Rot.z)
		);
	
	//---���W
	D3DXMatrixTranslation( 
		&pos,
		refvec3Pos.x,
		refvec3Pos.y,
		refvec3Pos.z
		);

	//---�}�g���N�X�̂������킹
	*matWorld *= scale;	//�g�嗦
	*matWorld *= rot;	//��]
	*matWorld *= pos;	//���W

}


/***********************************************************************/
/*! @brief �d�͉���
 * 
 *  @param[in] fElTime �o�ߎ���
 *  @retval float �����ړ���
 */
/***********************************************************************/
float gravAcc(float fElTime)
{
	return 0.5f * grvityacc * fElTime * fElTime;
}


/***********************************************************************/
/*! @brief �����̎擾
 * 
 *  @param[in] nBetween 
 *  @retval uint �����̕�
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
/*! @brief �A���[�g�̃��b�Z�[�W�{�b�N�X��\�����邾��
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
/*! @brief ���Ƌ��̂����蔻��
 * 
 *  @param[in] vec3PosA �I�u�W�F�N�g�`�̈ʒu�x�N�g��
 *  @param[in] fARadius �I�u�W�F�N�g�`�̔��a
 *  @param[in] vec3PosB �I�u�W�F�N�g�a�̈ʒu�x�N�g��
 *  @param[in] fBRadius �I�u�W�F�N�g�a�̔��a
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindBall(D3DXVECTOR3& vec3PosA,float fARadius,D3DXVECTOR3& vec3PosB,float fBRadius)
{
	////////////////////////////
	//	�ϐ��錾
	float fX;
	float fY;
	float fZ;
	float fDistance;


	////////////////////////////
	//	��̃I�u�W�F�N�g�̋������v�Z
	fX = (vec3PosA.x - vec3PosB.x) * (vec3PosA.x - vec3PosB.x);
	fY = (vec3PosA.y - vec3PosB.y) * (vec3PosA.y - vec3PosB.y);
	fZ = (vec3PosA.z - vec3PosB.z) * (vec3PosA.z - vec3PosB.z);


	////////////////////////////
	//	���̂ƐڐG���鋗���̌v�Z
	fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);

	////////////////////////////
	//	�ڐG����
	if(	fX + fY + fZ <=  fDistance)
	{
		return TRUE;
	}
	return FALSE;
}


/***********************************************************************/
/*! @brief ���Ƌ��̂����蔻��
 * 
 *  @param[in] matPosA	�I�u�W�F�N�g�`�̃}�g���N�X
 *  @param[in] fARadius �I�u�W�F�N�g�`�̔��a
 *  @param[in] matPosB	�I�u�W�F�N�g�a�̃}�g���N�X
 *  @param[in] fBRadius �I�u�W�F�N�g�a�̔��a
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL bindBall(D3DXMATRIXA16& matPosA,float fARadius,D3DXMATRIXA16& matPosB,float fBRadius)
{
	////////////////////////////
	//	��̃I�u�W�F�N�g�̋������v�Z
	const float fX = (matPosA._41 - matPosB._41) * (matPosA._41 - matPosB._41);
	const float fY = (matPosA._42 - matPosB._42) * (matPosA._42 - matPosB._42);
	const float fZ = (matPosA._43 - matPosB._43) * (matPosA._43 - matPosB._43);
	const float fDistance = (fARadius + fBRadius) * (fARadius + fBRadius);
	//���ƃv���C���[�̂����蔻��
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

	//	�Q�_�̋����v�Z
	const float fA = (vec2PosA->x - vec2PosB->x) * (vec2PosA->x - vec2PosB->x);
	const float fB = (vec2PosA->y - vec2PosB->y) * (vec2PosA->y - vec2PosB->y);
	const float fC = fA + fB;
	const float fSumRad = (fARadius + fBRadius) * (fARadius + fBRadius);

	//���ƃv���C���[�̂����蔻��
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
	if(	pvec2PosA->x < pvec2PosB->x		//	���[
		&&	pvec2PosA->x + pRectSizeA->right > pvec2PosB->x	//�E�[
		&&	pvec2PosA->y < pvec2PosB->y	//	��[
		&&	pvec2PosA->y + pRectSizeA->bottom > pvec2PosB->y
		)
	{
		return TRUE;
	}

	return FALSE;
}


/***********************************************************************/
/*! @brief �Փˌ�̉^���v�Z
 * 
 *  @param[out] pv1Out �I�u�W�F�N�g�P�̏Փˌ�̈ړ���
 *  @param[in] v1	   �I�u�W�F�N�g�P�̈ړ���
 *  @param[in] v2	   �I�u�W�F�N�g�Q�̈ړ���
 *  @param[in] m1	   �I�u�W�F�N�g�P�̎���
 *  @param[in] m2	   �I�u�W�F�N�g�Q�̎���
 *  @param[in] e1	   �I�u�W�F�N�g�P���������W��
 *  @param[in] e2	   �I�u�W�F�N�g�Q���������W��
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
		MessageAlert("e1�ɕs���Ȓl�����͂���Ă��܂�","error from repulsion");
	}
	if(e2 > 1 || 0 > e2)
	{
		MessageAlert("e2�ɕs���Ȓl�����͂���Ă��܂�","error from repulsion");
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
   FLOAT TotalWeight = weight_A + weight_B; // ���ʂ̍��v
   FLOAT RefRate = (1 + res_A * res_B); // ������
   D3DXVECTOR3 C = *pColliPos_B - *pColliPos_A; // �Փˎ��x�N�g��
   D3DXVec3Normalize(&C, &C);
   FLOAT Dot = D3DXVec3Dot( &(*pVelo_A-*pVelo_B), &C ); // ���ώZ�o
   D3DXVECTOR3 ConstVec = RefRate*Dot/TotalWeight * C; // �萔�x�N�g��
   
   // �Փˌ㑬�x�x�N�g���̎Z�o
   *pOut_velo_A = -weight_B * ConstVec + *pVelo_A;
   *pOut_velo_B = weight_A * ConstVec + *pVelo_B;
}

//�����蔻��N���X
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
	float* hitX,	//	��_
	float* hitY,	//	��_
	float x1,		//	�n�_
	float y1,		//	�n�_
	float x2,		//	�I�_
	float y2,		//	�I�_
	float centerX,	//	�~�̒��S�_��
	float centerY,	//	�~�̒��S�_��
	float radius	//	�~�̔��a
){
	//�_�P�Ƃ̔���
	float lenX = centerX - x1;
	float lenY = centerY - y1;
	if (lenX * lenX + lenY * lenY < radius * radius){
		*hitX = x1;
		*hitY = y1;
		return true;
	}
	
	//�_�Q�Ƃ̔���
	lenX = centerX - x2;
	lenY = centerY - y2;
	if (lenX * lenX + lenY * lenY < radius * radius){
		*hitX = x2;
		*hitY = y2;
		return true;
	}
	
	//���Ƃ̔���
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

//���Ɛ�
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
	float* hitX,//	��_
	float* hitY,//	��_
	float x1,	//	�n�_1
	float y1,	//	�n�_1
	float x2,	//	�I�_1
	float y2,	//	�I�_1
	float x3,	//	�n�_2
	float y3,	//	�n�_2
	float x4,	//	�I�_2
	float y4	//	�I�_2
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