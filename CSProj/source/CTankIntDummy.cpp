/***********************************************************************/
/*! @file  CTankIntDummy.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CTankIntDummy.h"

#include"CTank.h"
#include"StageData.h"
#include"CObjMng.h"
#include"ObjKey.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(CTank* pTank)
	:CTankIntInter(pTank)
{
	_pMyTank = pTank;
	_point = 1;
	_MoveDir = D3DXVECTOR2(0,1);
	_pointError = (rand()%POINT_ERROR_NUM) - POINT_ERROR_NUM / 2;	// �덷�ݒ�

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::~CTankIntDummy()
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CTankIntDummy::CTankIntDummy(const CTankIntDummy& src)
	:CTankIntInter(src._pMyTank)
{

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::update()
{
	
	root();
	shot();
	
}
/***********************************************************************/
/*! @brief ���[�g�ɏ]���֐�
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::root(){
	
	static D3DXVECTOR2 TanktoNaviPoint;			// ���݈ʒu����ړI�i�r�|�C���g�܂ł̃x�N�g��
	static D3DXVECTOR2 NaviToNavi;				// �O�i�r�|�C���g����ړI�i�r�|�C���g�܂ł̃x�N�g��
	static D3DXVECTOR2 TtoNUnitVec;				// ���݈ʒu����ړI�i�r�|�C���g�܂ł̒P�ʃx�N�g��
	static D3DXVECTOR2 NtoNUnitVec;				// �O�i�r�|�C���g����ړI�i�r�|�C���g�܂ł̒P�ʃx�N�g��
	static float dot;
	// ���݈ʒu����ړI�i�r�|�C���g�܂�
	
	TanktoNaviPoint.x = (CTankIntDummy::_StageData->getRoot()[_point].x + _pointError) - CTankIntDummy::_pMyTank->getMatBottom()->_41;
	TanktoNaviPoint.y = (CTankIntDummy::_StageData->getRoot()[_point].y + _pointError) - CTankIntDummy::_pMyTank->getMatBottom()->_43;
	//�O�i�r�|�C���g����ړI�i�r�|�C���g�܂�
	NaviToNavi.x = (CTankIntDummy::_StageData->getRoot()[_point].x + _pointError) - (CTankIntDummy::_StageData->getRoot()[_point-1].x + _pointError);
	NaviToNavi.y = (CTankIntDummy::_StageData->getRoot()[_point].y + _pointError) - (CTankIntDummy::_StageData->getRoot()[_point-1].y + _pointError);
	
	// ���퉻
	D3DXVec2Normalize(&TtoNUnitVec,&TanktoNaviPoint);
	D3DXVec2Normalize(&NtoNUnitVec,&NaviToNavi);

	dot = D3DXVec2Dot(&TtoNUnitVec,&NtoNUnitVec);
	
	if(dot<0){
		if( _point >= CTankIntDummy::_StageData->getRootNum()-1 ){
			_point = 0;	// �i�r�|�C���g���Z�b�g
		}else{
			_point++;	// ���̃|�C���g��
			}
		_pointError = (rand()%POINT_ERROR_NUM) - POINT_ERROR_NUM / 2;
	}
	_MoveDir = D3DXVECTOR2(TtoNUnitVec.x,TtoNUnitVec.y);	// �i�r�|�C���g�ֈړ�
	
}

/***********************************************************************/
/*! @brief �߂��̓G�����֐�
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::shot(){
	static int aimNum;
//	return;
	// �ˌ�����
	if(getRand(SHOT_PROB) == 1){	// ���m��
		
		// �_���G�̃i���o�[�ݒ�
		if(rand()%2){aimNum = 1;}else{aimNum = -1;}	

		const uint myRank = CTankIntDummy::CTankIntInter::_pMyTank->getRank();
		
		if(myRank + aimNum < 0 || ((*CTankIntDummy::_Ranking)[myRank + aimNum]) == NULL ||  myRank +aimNum > OBJMNG->getList(OBJGROUPKEY::TANK())->size())
			return;
		
		// �e��������
		CTankIntDummy::_TargetPoint.x =
			(*CTankIntDummy::_Ranking)[myRank + aimNum ]->getMatBottom()->_41;
		CTankIntDummy::_TargetPoint.z =
			(*CTankIntDummy::_Ranking)[myRank + aimNum ]->getMatBottom()->_43;
		// ����
		CTankIntDummy::_FireFlg = true;
		
	}

}