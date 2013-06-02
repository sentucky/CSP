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
	*pv1Out = (m1 - (e1 * e2) * m2) * v1  / (m1 + m2) + (1 + e1 * e2) * m2 * v2 / (m1 + m2);
}