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
#include"StageData.h"

		CTank*			CTankIntInter::_pPlayerTank = NULL;	//	�v���C���[�^���N�̃|�C���^
const	CStageData*		CTankIntInter::_StageData	= NULL;	//	�X�e�[�W�f�[�^

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


void CTankIntInter::myStep()
{
	/*
	//....�񕪒T���Ŏ����������Ă���ꏊ��T��
	const TILE **pT = _StageData->getTile();
	uint x = 8;
	uint z = 8;

	float ary[17]={0};

	for(uint Cnt = 0; Cnt < 16; Cnt+=1)
	{
		ary[Cnt] = ary[16];

		ary[16] += 500.0f / 16;
	}

	float tX = _pMyTank->getMatBottom()->_41;
	float tZ = _pMyTank->getMatBottom()->_43;

	uint ud = 8;

	while(1)
	{
		ud /= 2;
		if(ary[x] <= tX && ary[x + 1] > tX )
		{
			break;
		}
		else if(ary[x] < tX)
		{
		}
		else
		{
		}
	}
	*/
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

void CTankIntInter::setStageData(const CStageData* StageData)
{
	_StageData = StageData;
}
