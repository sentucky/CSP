/***********************************************************************/
/*! @file  CCamera.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

/***********************************************************************/
//	�C���N���[�h��
/***********************************************************************/
#include<d3dx9.h>
#include<d3d9.h>
#include"common.h"
#include"CCamera.h"


/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CCamera
{

public:
	explicit CCamera();			///<	�R���X�g���N�^
	CCamera(const CCamera&);	///<	�R�s�[�R���X�g���N�^
	virtual ~CCamera();			///<	�f�X�g���N�^

public:
	static const D3DXMATRIXA16* getMatView();	///<	�r���[�}�g���N�X�̎擾
	static void init();							///<	������
	static void update();						///<	�X�V
	static void setEyeX(const float fX);		///<	���_���W�w�ݒ�
	static void setEyeY(const float fY);		///<	���_���W�x�ݒ�
	static void setEyeZ(const float fZ);		///<	���_���W�y�ݒ�
	static void setEye(D3DXVECTOR3& vec3Eye);	///<	���_���W�ݒ�
	static void setAt(D3DXVECTOR3& vec3At);		///<	�����_���W�ݒ�
	static void setUp(D3DXVECTOR3& vec3Up);		///<	�A�b�v�x�N�g���ݒ�
	static D3DXVECTOR3& getEye();				///<	���_���W�擾	
	static D3DXVECTOR3& getAt();				///<	�����_���W�擾
	static D3DXVECTOR3& getUp();				///<	�A�b�v�x�N�g���擾
	static D3DXMATRIXA16& position();			///<	���W�}�g���N�X�擾

protected:
	static D3DXVECTOR3 _vec3Eye;	//!<	�J�������W
	static D3DXVECTOR3 _vec3At;		//!<	�����_
	static D3DXVECTOR3 _vec3Up;		//!<	�A�b�v�x�N�g��
	static D3DXMATRIXA16 _matView;	//!<	�r���[�}�g���N�X
	static D3DXMATRIXA16 _matPose;	//!<	�p���}�g���N�X
	static bool  _bUpdateFlg;		//!<	�X�V�t���O
	static float _fZOffset;			//!<	�J�����̉��s���̃I�t�Z�b�g
	static float _fZRotDef;			//!<	�J�����y���ł̉�]����
	static float _fAngle;			//!<	�ړ�����]�P��
};
//EOF