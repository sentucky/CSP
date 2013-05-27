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
class CTankTop;
class CTankBottom;
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
	void fire();				///<	���C


private:


	void turnTop();

public:
	void enableTask();			///<	�^�X�N�L����
	void disableTask();			///<	�^�X�N������

	const D3DXMATRIXA16* getMatBottom();	//	�{�g���̃}�g���N�X�擾
private:
	CTaskList*		_pTaskDraw;
	CTaskList*		_pTaskPause;
	CTaskList*		_pTaskMove;
	CTaskList*		_pTaskIntelligence;
	CTaskList*		_pTaskFire;
	CTankTop*		_pTankTop;			///<	��Ԃ̏㕔
	CTankBottom*	_pTankBottom;		///<	��Ԃ̉���

	CTankIntInter*	_pIntelligence;		///<	�v�l

	uint			_unIntType;			///<	�v�l�^�C�v
};
#endif