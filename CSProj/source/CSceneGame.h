/***********************************************************************/
/*! @file  CSceneGame.h
 *  @brief �Q�[�������̏���
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSCENEGAME___
#define ___CSCENEGAME___	///<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CSceneBase.h"

/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CCamera;
class CStage;
class CObjMng;
class CFollowCamera;
template<class T>
class CListItem;
class CObjBase;
class CSystemparam;
/***********************************************************************/
/*!	@class CSceneGame
 *	@brift �Q�[�������̏���
 */
/***********************************************************************/
class CSceneGame:public CSceneBase
{
public:
	CSceneGame();				///<	�R���X�g���N�^
	~CSceneGame();				///<	�f�X�g���N�^

private:
	void init();				///<	����������
	void update();				///<	�X�V����
	void draw();				///<	�`�揈��
	void release();				///<	�������
	CSceneBase* nextScene();	///<	�V�[���؂�ւ�

	void standby(CStage* pStage);	///<	����

	void switchGStart();
	void switchGMain();
	void switchGEnd();


	uint Phase;
private:
	CCamera* _pCamera;	///<	�J�����N���X�|�C���^
	CFollowCamera* _FollowCamera;
	CListItem<CObjBase*>* _CamStart;
	CSystemparam* _SysPara;
};

#endif