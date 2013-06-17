/***********************************************************************/
/*! @file  CShell.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___BULLET___
#define ___BULLET___

class CTaskList;
class CMesh;
class CTank;
class CStageData;

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
				CMesh*	Mesh,
				const int power
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

	//
	void hitTestTank(CTank* pTank);	///<	��ԂƂ̏Փ�
	void hitTestWall();

	//	�Q�b�^
	D3DXVECTOR3& getTrajectory();
	D3DXVECTOR3& getMoveVector();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const D3DXMATRIXA16* 
	 */
	/***********************************************************************/
	const D3DXMATRIXA16* getMatW(){return &_matW;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const CTank* 
	 */
	/***********************************************************************/
	const CTank* getOwner(){
		return _Owner;
	}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const int 
	 */
	/***********************************************************************/
	const int	getPower(){return _Power;}

	void moveVector(const D3DXVECTOR3* MoveVec);

	//	�Z�b�^
	void setPos(const D3DXMATRIXA16*	pos);
	void setPos(const D3DXVECTOR3*		pos);
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] pTank 
	 *  @retval void
	 */
	/***********************************************************************/
	void setOwner(CTank* pTank){
		_Owner = pTank;
	}

private:
	D3DXMATRIXA16	_matW;			///<	���[���h�}�g���N�X
	D3DXVECTOR3		_OldPos;		///<	�����W
	D3DXVECTOR3		_Trajectory;	///<	�O���x�N�g��
	D3DXVECTOR3		_MoveVector;	///<	�ړ��x�N�g��
	CMesh*			_pMesh;			///<	���b�V��
	float			_MoveSpeed;		///<	�ړ����x
	int				_Power;			///<	�З�
	const int		_nMaxLife;		///<	���C�t
	int				_nLife;			////<
	CTank*			_Owner;			///<	���˂������

	//	�^�X�N
	CTaskList*		_TaskListDraw;			///<	�`��^�X�N
	CTaskList*		_TaskListMove;			///<	�ړ��^�X�N
	CTaskList*		_TaskListCheckAlive;	///<	�����m�F�^�X�N
	CTaskList*		_TaskListExplosion;		///<	�����^�X�N

	static CStageData* _StageData;

#ifdef _DEBUG
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const float 
	 */
	/***********************************************************************/
	const float getRad(){return _fRad;}
	float _fRad;
#endif

};

#endif