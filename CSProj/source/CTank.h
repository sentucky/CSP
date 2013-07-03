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
#include"StageData.h"
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
		CMesh* pMeshTop,		///< �g�b�v���b�V��
		CMesh* pMeshBottom,		///< �{�g�����b�V��
		CMesh* pMeshBottom2,	///< �{�g�����b�V���Q
		uint   unThisType,		///< �C���e���W�F���X
		CShell* pShellProto,	///< 
		const float fMoveSpeed,	///< ���x
		const float fTurnSpeed,	///< ���񑬓x
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
	void pRap();				///<	���@���b�v
	void destroyed();			///<	��j��
	void stepReset();			///<	�������X�V

	//	�ďo��
	void hitTestTank(CTank* pTank);		///<	�����蔻��
	void hitTestShell(CShell* pShell);	///<	�e�Ƃ̂����蔻��㏈��
	void hitTestWall();					///<	�ǂƂ̂����蔻��̏���
	void raceEnd();				///<	���[�X�I��������
private:
	void turnTop();				///<	�㕔�̉�]
	void drawDestroyed();		///<	��j�󎞂̕`�揈��

public:
	void enableTask();			///<	�^�X�N�L����
	void disableTask();			///<	�^�X�N������

	static const bool lower(const CTank* A,const CTank* B);
	void rotationY(const float fY);	




	///	�Q�b�^
	CTankBottom*				getTankBottom()	{return _pTankBottom;}
	const D3DXMATRIXA16*	getMatBottom();	///<	�{�g���̃}�g���N�X�擾
	const D3DXVECTOR3*		getMoveVec();	///<	�ړ��x�N�g��
	const float				getRadius();	///<	���a�̎擾
	const BOOL				getDestroyed()		{return _Destroyed;		}	///<	��j��t���O�擾
	const BOOL				getFlgGoal()		{return _FlgGoal;		}
	const uint				getThisType()		{return _unThisType;	}
	const float				getlapVal()			{return _lapVal;		}
	const int				getlap()			{return _lap;			}
	const int				getradiate()		{return _radiate;		}
	const int				getMaxradiateTime()	{return _MaxRadiateTime;}
	const int				getlife()			{return _life;			}
	const int				getmaxlife()		{return _Maxlife;		}
	const uint				getRank()			{return _Rank;			}
	const uint*				getCurStep()		{return _CurStep;		}
	const uint				getTankType()		{return _unThisType;	}
	const CTankIntInter*	getIntelligence()	{return _pIntelligence;	}		// �{�s�擾

	///	�Z�b�^
	void setMoveVec( D3DXVECTOR3& MoveVec );
	void setMoveVec( const D3DXVECTOR3 *MoveVec );
	void setPos(const float x,const float z);
	void setRank(const uint Rank){_Rank = Rank;}

	static void setTankPlayer(CTank* Player){_Player = Player;};
	static void setStageData(const CStageData* pStageData		){	_StageData = pStageData;}
	static void setSoundFire(const LPDIRECTSOUNDBUFFER SoundFire){ _SoundFire = SoundFire;}
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTaskList*		_pTaskCalcAM;
	CTaskList*		_pTaskRap;
	CTaskList*		_pTaskDestroyed;
	CTaskList*		_pTaskStepReset;

	CTankTop*		_pTankTop;			///<	��Ԃ̏㕔
	CTankBottom*	_pTankBottom;		///<	��Ԃ̉���
	CTankIntInter*	_pIntelligence;		///<	�v�l

	float			_fRadius;			///<	���a
	BOOL			_Destroyed;			///<	�j�󔻒�t���O
	BOOL			_FlgGoal;			///<	�S�[���t���O
	uint			_unThisType;		///<	�^�C�v
	float			_lapVal;			//	�i�s���
	int				_lap;				//	���b�v��	
	int				_radiate;			///<	���M��
	int				_MaxRadiateTime;	///<	���M���Ԃ̍ő�l
	int				_life;				///<	�ϋv��
	const int		_Maxlife;			///<	�ϋv��
	uint			_Rank;				///<	�����N
	uint			_CurStep[2];		///<	���݂̑����^�C��

	int				_deldelayCount;	
	OUTPUT*         _Panel;				//
	OUTPUT*         _prevPanel;			//


	CSprite*		_SpriteExpload;
	D3DXMATRIXA16	_effectMatrix;
	bool			_expflag;

	static CTank* _Player;

public:
	static const uint TYPE_PLAYER = 0;
	static const uint TYPE_ENEMY01 = -1;
private:
	static LPDIRECTSOUNDBUFFER _SoundFire;
	static const int _maxdeldelayCount = 60;
	static const CStageData* _StageData;

#ifdef _DEBUG
LPD3DXMESH debugMesh;
#endif
};
#endif