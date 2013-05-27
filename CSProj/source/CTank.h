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
		uint   unIntType,		///<	�C���e���W�F���X
		CShell* pShellProto,
		const float fMoveSpeed,	///<	���x
		const float fTurnSpeed	//	���񑬓x
		);
	~CTank();					///<	�f�X�g���N�^
	CTank(const CTank& src);	///<	�R�s�[�R���X�g���N�^

private:
	void release();				///<	�������
public:
	void draw();				///<	�`�揈��
	void intelligence();		///<	�v�l�X�V
	void pause();				///<	�p���̍X�V
	void move();				///<	�ړ�����


private:
	void intFire();				///<
	void intMove();				///<	

	void calcDir();				///<	�����̍X�V
	void calcDirBottom();		///<	�{�g���̌����v�Z
	void calcActiveMoveVec();	///<	�\���I�ړ��x�N�g���v�Z


	void turnBottom(const float fTurnSpeed);
	void turnTop();

public:
	void enableTask();			///<	�^�X�N�L����
	void disableTask();			///<	�^�X�N������

	D3DXMATRIXA16* getMatBottom();	//	�{�g���̃}�g���N�X�擾
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;

	CMesh*			_MeshTop;			///<	�g�b�v���b�V��
	CMesh*			_MeshBottom;		///<	�{�g�����b�V��



	D3DXVECTOR3		_TopDir;			///<	�g�b�v�̉�]�p
	D3DXVECTOR3		_BottomDir;			///<	�{�g���̉�]�p

	D3DXVECTOR3		_MoveVec;			///<	�ړ��x�N�g��

	D3DXMATRIXA16	_matTop;			///<	�g�b�v�̃}�g���N�X
	D3DXMATRIXA16	_matBottom;			///<	�{�g���̃}�g���N�X
	
	float			_fNormalMoveSpeed;	///<	�P�ʈړ����x
	float			_fMoveSpeed;		///<	�ړ����x
	float			_fTurnSpeed;		///<	���񑬓x

	CTankIntInter*	_pIntelligence;		///<	�v�l
	CShell*			_pShellProto;		///<	�C�e

	uint			_unIntType;			///<	�v�l�^�C�v
};
#endif