/***********************************************************************/
/*! @file  CTank.h
 *  @brief �^�X�N�N���X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANK___
#define ___CTANK___	///<	�C���N���[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CObjBase.h"
#include <dsound.h>



/***********************************************************************/
//	��s�錾
/***********************************************************************/
template<class T>
class CListItem;
class CTaskBase;
class CTaskList;
class CMesh;
class CTankIntInter;
class CShell;
class CTankTop;
class CTankBottom;
class CStageData;
/***********************************************************************/
/*!
 *	@class CTank
 *	@brift �^���N�N���X
 */
/***********************************************************************/
class CTank:public CObjBase
{
public:
	CTank(
		CMesh* pMeshTop,		///<	�g�b�v���b�V��
		CMesh* pMeshBottom,		///<	�{�g�����b�V��
		uint   unThisType,		///<	�C���e���W�F���X
		CShell* pShellProto,
		const float fMoveSpeed,	///<	���x
		const float fTurnSpeed,	///<	���񑬓x
		const int	Life		///<
		);
	~CTank();					///<	�f�X�g���N�^
	CTank(const CTank& src);	///<	�R�s�[�R���X�g���N�^

private:
	void release();				///<	�������
public:
	//	�^�X�N
	void draw();				///<	�`�揈��
	void intelligence();		///<	�v�l�X�V
	void pause();				///<	�p���̍X�V
	void move();				///<	�ړ�����
	void fire();				///<	���C
	void calcMove();			///<	�ړ��ʌv�Z
	void eRap();				///<	�G���b�v
	void pRap();				///<	���@���b�v

	//	�ďo��
	void hitTestTank(CTank* pTank);		///<	�����蔻��
	void hitTestShell(CShell* pShell);	///<	�e�Ƃ̂����蔻��㏈��
	void hitTestWall();					///<	�ǂƂ̂����蔻��̏���

private:
	void turnTop();				///<	�㕔�̉�]
	void destroyed();			///<	��j��

public:
	void enableTask();			///<	�^�X�N�L����
	void disableTask();			///<	�^�X�N������

	const D3DXMATRIXA16*	getMatBottom();	///<	�{�g���̃}�g���N�X�擾
	const D3DXVECTOR3*		getMoveVec();	///<	�ړ��x�N�g��
	const float				getRadius();	///<	���a�̎擾
	const BOOL				getDestroyed(){return _Destroyed;}	///<	��j��t���O�擾

	void setMoveVec( D3DXVECTOR3& MoveVec );
	void setMoveVec( const D3DXVECTOR3 *MoveVec );
	void setPos(const float x,const float z);

	static void setStageData(const CStageData* pStageData){	_StageData = pStageData;}
	static void setSoundFire(const LPDIRECTSOUNDBUFFER SoundFire){ _SoundFire = SoundFire;}

private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTaskList*		_pTaskCalcAM;
	CTaskList*		_pTaskRap;

	CTankTop*		_pTankTop;			///<	��Ԃ̏㕔
	CTankBottom*	_pTankBottom;		///<	��Ԃ̉���

	CTankIntInter*	_pIntelligence;		///<	�v�l

	float			_fRadius;			///<	���a
	uint			_unThisType;		///<	�^�C�v

	int				_life;				///<	�ϋv��

	int				_radiate;			///<	���M��
	int				_MaxRadiateTime;	///<	���M���Ԃ̍ő�l

	BOOL			_Destroyed;			///<	�j�󔻒�t���O
	BOOL			_GoalFlg;			///<	�S�[���t���O

	uint			_TankType;			///<	�^���N�̌^

	static const uint TYPE_PLAYER = 0;
	static const uint TYPE_ENEMY01 = -1;

	static LPDIRECTSOUNDBUFFER _SoundFire;

#ifdef _DEBUG
LPD3DXMESH debugMesh;;
#endif

	static const CStageData* _StageData;
};
#endif