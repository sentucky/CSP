/***********************************************************************/
/*! @file  CTaskIntInter.cpp
 *  @brief �^���N�v�l�C���^�[�t�F�[�X
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#include"CTankIntInter.h"
#include"CTank.h"

CTank* CTankIntInter::_pPlayerTank = NULL;	//	�v���C���[�^���N�̃|�C���^


/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CTankIntInter::CTankIntInter(CTank* pMyTank)
	:_FireFlg(FALSE),
	_MoveDir(TMV_5),
	_pMyTank(pMyTank),
	_TargetPoint(0,0,0)
{

}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTankIntInter::~CTankIntInter()
{
}

/***********************************************************************/
/*! @brief FireFlg�̎擾
 * 
 *  @retval const BOOL 
 */
/***********************************************************************/
const BOOL CTankIntInter::getFireFlg(){return _FireFlg;}

/***********************************************************************/
/*! @brief MoveDir�̎擾
 * 
 *  @retval const uint 
 */
/***********************************************************************/
const uint CTankIntInter::getMoveFlg(){return _MoveDir;}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3* CTankIntInter::getTargetPoint()
{
	return &_TargetPoint;
}