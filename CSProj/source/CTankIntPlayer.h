/***********************************************************************/
/*! @file  CTankIntPlayer.h
 *  @brief �^���N�@�v���C���[�v�l
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANKINTPLAYER___
#define ___CTANKINTPLAYER___	///<	�C���N���[�h�K�[�h


/***********************************************************************/
//	�C���N���[�h�K�[�h
/***********************************************************************/
#include"CTankIntInter.h"
#include"CListItem.h"

class CTank;
class CObjBase;


/***********************************************************************/
/*!	@class	CTankIntPlayer
 *	@brift	�^���N�̃v���C���[�v�l�N���X
 */
/***********************************************************************/
class CTankIntPlayer:public CTankIntInter
{
public:
	CTankIntPlayer(CTank* pPlayerTank);	//	�R���X�g���N�^
	~CTankIntPlayer();	//	�f�X�g���N�^
private:
	void update();	//	�t���O�̍X�V
	void moveSight();	//	�Ə��ړ�
	
	CListItem<CObjBase*>*  _pList;
	
};

#endif