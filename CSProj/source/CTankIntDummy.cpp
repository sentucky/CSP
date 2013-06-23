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


float debug,debug2,debug3,debug4,debug5;
float p;
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
	
	CTankIntDummy::root();
	Debug();
	
}
/***********************************************************************/
/*! @brief ���[�g�ɏ]���֐�
 * 
 *  @retval void
 */
/***********************************************************************/
void CTankIntDummy::root(){
	
	static D3DXVECTOR2 i;// ���݈ʒu����ړI�i�r�|�C���g�܂ł̃x�N�g��
	static D3DXVECTOR2 o;// �O�i�r�|�C���g����ړI�i�r�|�C���g�܂ł̃x�N�g��
	static D3DXVECTOR2 a;
	static D3DXVECTOR2 b;
	// ���݈ʒu����ړI�i�r�|�C���g�܂�
	
	i.x = CTankIntDummy::_StageData->getRoot()[_point].x - CTankIntDummy::_pMyTank->getMatBottom()->_41;
	i.y = CTankIntDummy::_StageData->getRoot()[_point].y - CTankIntDummy::_pMyTank->getMatBottom()->_43;
	//�O�i�r�|�C���g����ړI�i�r�|�C���g�܂�
	o.x = CTankIntDummy::_StageData->getRoot()[_point].x - CTankIntDummy::_StageData->getRoot()[_point-1].x;
	o.y = CTankIntDummy::_StageData->getRoot()[_point].y - CTankIntDummy::_StageData->getRoot()[_point-1].y;
	
	// ���퉻
	D3DXVec2Normalize(&a,&i);
	D3DXVec2Normalize(&b,&o);

	float k = D3DXVec2Dot(&a,&b);
	debug = k;
	debug2 =  CTankIntDummy::_StageData->getRoot()[_point].x;
	debug3 =  CTankIntDummy::_StageData->getRoot()[_point].y;
	debug4 = CTankIntDummy::_pMyTank->getMatBottom()->_41;
	debug5 = CTankIntDummy::_pMyTank->getMatBottom()->_43;
	
	p = CTankIntDummy::_StageData->getRootNum();
	
	if(k<0){
		if( _point >= CTankIntDummy::_StageData->getRootNum()-1 ){
			_point = 0;	// �i�r�|�C���g���Z�b�g
		}else{
			_point++;	// ���̃|�C���g��
		}
	}
	_MoveDir = D3DXVECTOR2(a.x,a.y);	// �i�r�|�C���g�ֈړ�
	
	
}

// �f�o�b�O�o��
void CTankIntDummy::Debug(){
	FONT->DrawFloat("navipointNormalize:",debug,RECTEX(0,16,0,0));
	FONT->DrawFloat("navipointX:",debug2,RECTEX(0,32,0,0));
	FONT->DrawFloat("Y:",debug3,RECTEX(250,32,0,0));
	FONT->DrawFloat("enemyX:",debug4,RECTEX(0,176,0,0));
	FONT->DrawFloat("enemyy:",debug5,RECTEX(0,192,0,0));
	FONT->DrawFloat("pointnum:",p,RECTEX(0,300,0,0));

}