/***********************************************************************/
/*! @file  CLight.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	CLight.h
//	�T�v			���C�g�N���X�w�b�_
//	�����		�쌴�C��
//	�X�V����		
/***********************************************************************/
//===================================================================
//	�C���N���[�h�K�[�h
//===================================================================
#pragma once
//===================================================================
//	�C���N���[�h
//===================================================================
#include"d3d9.h"
#include"d3dx9.h"
#include"common.h"

//===================================================================
//	�C�����C���֐�
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] a 
 *  @param[in,out] r 
 *  @param[in,out] g 
 *  @param[in,out] b 
 *  @retval inline D3DCOLORVALUE 
 */
/***********************************************************************/
inline D3DCOLORVALUE COLORVALUE(float a, float r, float g, float b)
{
	/////////////////////////
	//	�ϐ��錾
	D3DCOLORVALUE ColorValue;	///<�F�̒l�i�[

	/////////////////////////
	//	�F�l�̐ݒ�
	ColorValue.a = a;
	ColorValue.r = r;
	ColorValue.g = g;
	ColorValue.b = b;

	/////////////////////////
	//	�F�l�̐ݒ�
	return ColorValue;
}
//===================================================================
//	�񋓒�`
//===================================================================
//---------------------------
//	�T�v
//		�A�e�j���G�[�V�����ԍ�
//---------------------------
typedef enum
{
	ATT_0 = 0,
	ATT_1 = 1,
	ATT_2 = 2,
}eATTENUATIONID;

//===================================================================
//	�N���X��`
//===================================================================
class CLight
{
public:
	/////////////////////////
	//	�R���X�g���N�^
	CLight(	);


	/////////////////////////
	//	�f�X�g���N�^
	~CLight();

public:
	/////////////////////////
	//	�����o�֐�
	void init();		///<������
	void update();		///<�X�V
	void release();		///<���

	void activeLight();								///<���C�g�̗L����
	void setLightType(const D3DLIGHTTYPE sType);	///<���C�g�^�C�v�̐ݒ�

	static D3DCOLORVALUE COLORVALUE();

	D3DLIGHT9* getLight();

	//...�f�B�t���[�Y�F�ݒ�
	void setDiffR(float fR);	///<��
	void setDiffG(float fG);	///<��
	void setDiffB(float fB);	///<��
	void setDiffA(float fA);	///<��
	void setDiffRGBA(float fR,float fG,float fB,float fA);	///<�ԗΐ�

	void setLight();
	void setPos(D3DXVECTOR3& vec3Pos);				///<�����̍��W
	void setDirection(D3DXVECTOR3& vec3Direction);	///<���̃x�N�g���ݒ�
	void setRange(const float fRange);					///<���̓͂������ݒ�
	void setAttenuation(const eATTENUATIONID eNo,const float fAttenuation);
	void setInsideCorn(const float fTheta);	///<
	void setOutsideCorn(const float fPhi);
	void setCornFallout(const float fFallout);
	void setupLight();	///<���C�g�̐ݒu
	void lightON();		///<�����������
	void lightOFF();	///<�����������

	void setPointLight(
		D3DCOLORVALUE& DiffColor,
		D3DXVECTOR3& vec3Direct,
		float fRange,
		float fAtt0,
		float fAtt1,
		float fAtt2
		);
	void setDirectionalLight(D3DCOLORVALUE& DiffColor, D3DXVECTOR3& vec3Direct);
	void setSpotLight(
		D3DCOLORVALUE& DiffColor, 
		D3DXVECTOR3& vec3Direct,
		const float fRange,
		D3DXVECTOR3& _vec3Pos,
		const float fAtt1, 
		const float fAtt3,
		const float fAtt2,
		const float fInsideCorn,
		const float fOutsideCornm,
		const float fCornFallout
		);

private:
	////////////////////////
	//	�����o�ϐ�
	static const int	sc_nMaxRegistor = 10;				///<�ő�o�^�\��
	D3DLIGHT9			_Light;								///<���C�g�\����
	DWORD				_nId;								///<���g��ID
	static bool			_bRegistorState[sc_nMaxRegistor];	///<�o�^����Ă���ID�̃��X�g
	static int			_nSumId;							///<�o�^ID�̐�
};


//EOF