/***********************************************************************/
/*! @file  CTankIntInter.h
 *  @brief �^���N�v�l�C���^�[�t�F�[�X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTASKINTINTER___
#define ___CTASKINTINTER___	///<	�C���N���[�h�K�[�h


/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"common.h"

/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CTank;
class CStageData;

/***********************************************************************/
//	�萔
/***********************************************************************/
/*! @brift �������*/
enum eTANK_MOVE
{
	TMV_1 = 1,
	TMV_2,
	TMV_3,
	TMV_4,
	TMV_5,
	TMV_6,
	TMV_7,
	TMV_8,
	TMV_9,
};


/***********************************************************************/
/*!	@class CTankIntInter
 *	@brift �^���N�v�l�C���^�[�t�F�[�X
 */
/***********************************************************************/
class CTankIntInter
{
public:
	CTankIntInter(CTank*);					///<	�R���X�g���N�^
	virtual ~CTankIntInter();				///<	�f�X�g���N�^
	
	virtual void update() = 0;				///<	�X�V�֐�

protected:
	void myStep();						//	�����m�F
public:

	const BOOL getFireFlg();				///<	���C�t���O�̎擾
	const uint getMoveFlg();				///<	�ړ������t���O�̎擾
	const D3DXVECTOR3* getTargetPoint();	///<	�C�������������擾
	static void setStageData(const CStageData* StageData);	//	�X�e�[�W�f�[�^�̐ݒ�
protected:
	BOOL	_FireFlg;					///<	���C�t���O
	uint	_MoveDir;					///<	�ړ������t���O
	CTank*	_pMyTank;					///<	�v�l�����f�������
	D3DXVECTOR3			_TargetPoint;	///<	�^�[�Q�b�g�̍��W
	static CTank*		_pPlayerTank;	///<	�v���C���[�^���N�̃|�C���^
	static const CStageData*	_StageData;		///<	�X�e�[�W�f�[�^
};


#endif