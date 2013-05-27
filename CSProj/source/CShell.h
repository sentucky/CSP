#ifndef ___BULLET___
#define ___BULLET___

class CTaskList;
class CMesh;

#include"CObjBase.h"

/*!
 *	@class CShell
 *	@brift �C�e
 */
class CShell:public CObjBase
{
public:
	//	�R���X�g���N�^
	CShell(
		const	int		MaxLife,
				float	MoveSpeed,
				CMesh*	Mesh
		);
	//	�f�X�g���N�^
	~CShell();
	//	�R�s�[�R���X�g���N�^
	CShell(const CShell& src);

	//	�^�X�N�̗L�����E������
	void enableTask();
	void disableTask();
	
	//	�^�X�N�n
	void draw();
	void move();
	void checkAlive();
	void explosion();

	//	�Q�b�^
	D3DXVECTOR3& getTrajectory();
	D3DXVECTOR3& getMoveVector();

	//	�Z�b�^
	void setMoveVector(const D3DXVECTOR3* MoveVec);
	void setPos(const D3DXMATRIXA16*	pos);
	void setPos(const D3DXVECTOR3*		pos);

private:
	D3DXMATRIXA16	_matW;			///<	���[���h�}�g���N�X
	D3DXVECTOR3		_OldPos;		///<	�����W
	D3DXVECTOR3		_Trajectory;	///<	�O���x�N�g��
	D3DXVECTOR3		_MoveVector;	///<	�ړ��x�N�g��
	CMesh*			_pMesh;			///<	���b�V��
	float			_MoveSpeed;		///<	�ړ����x
	const int		_nMaxLife;		///<	���C�t�ő�l
	int				_nLife;			///<	���݃��C�t

	//	�^�X�N
	CTaskList*		_TaskListDraw;			///<	�`��^�X�N
	CTaskList*		_TaskListMove;			///<	�ړ��^�X�N
	CTaskList*		_TaskListCheckAlive;	///<	�����m�F�^�X�N
	CTaskList*		_TaskListExplosion;		///<	�����^�X�N

};

#endif