/***********************************************************************/
/*! @file  CTank.cpp
 *  @brief �^���N
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#include"const.h"
//...�^�X�N
#include"CTaskBase.h"
#include"CTaskList.h"
#include"CTank.h"
#include"CTaskMng.h"
//...�p�����^
#include"CMesh.h"
#include"CTankTop.h"
#include"CTankBottom.h"

//...�ʃI�u�W�F�N�g
#include"CShell.h"
//...�v�l
#include"CTankIntInter.h"
#include"CTankIntPlayer.h"
//...�t�@�N�g��
#include"CFactory.h"
#include"CObjMng.h"

#ifdef _DEBUG
#include"CCamera.h"
#include"CScreen.h"
#include"CFont.h"
#include"CInputCommon.h"
#include"CTankIntDummy.h"
#endif

#ifdef _DEBUG
LPD3DXMESH debugMesh = NULL;
int			Cnt = 0;
#endif

/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] pMeshTop 	�^���N�̋@�̏㕔�̃��f��
 *  @param[in] pMeshBottom	�^���N�̋@�̉����̃��f��
 *  @param[in] unIntType	�^���N�̎v�l�^�C�v
 *  @param[in] fSpeed 		�ړ����x
 *  @param[in] fTurnSpeed 	���񑬓x
 */
/***********************************************************************/
CTank::CTank(
	CMesh* pMeshTop,
	CMesh* pMeshBottom,
	uint   unIntType,
	CShell* pShellProto,
	const float fMoveSpeed,
	const float fTurnSpeed
	)
	:_pTaskDraw		( NULL			),
	_pTaskPause		( NULL			),
	_pTaskMove		( NULL			),
	_pTaskIntelligence( NULL		),
	_pTaskFire		( NULL			),
	_pTankTop		( NULL			),
	_pTankBottom	( NULL			),
	_pIntelligence	( NULL			),
	_fRadius		( 1.0f			),
	_unIntType		( unIntType		)
{
	_pTankTop = new CTankTop(pMeshTop,NULL,pShellProto);
	_pTankBottom = new CTankBottom(pMeshBottom,fMoveSpeed,fTurnSpeed);
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTank::~CTank()
{
	disableTask();
	SAFE_DELETE(_pTankTop);
	SAFE_DELETE(_pTankBottom);
	release();
#ifdef _DEBUG
	Cnt--;
	if(Cnt == 0)
	{
		debugMesh->Release();
		debugMesh = NULL;
	}
#endif
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] src �R�s�[����I�u�W�F�N�g
 */
/***********************************************************************/
CTank::CTank(const CTank& src)
	:_pTaskDraw			( NULL								),
	_pTaskPause			( NULL								),
	_pTaskMove			( NULL								),
	_pTaskIntelligence	( NULL								),
	_pTaskFire			( NULL								),
	_pTankTop			( new CTankTop(*src._pTankTop)		),
	_pTankBottom		( new CTankBottom(*src._pTankBottom)),
	_pIntelligence		( NULL								),
	_fRadius			( src._fRadius							),
	_unIntType			( src._unIntType					)
{

	//	�v�l�ݒ�
	switch(_unIntType)
	{
	case  0:_pIntelligence = new CTankIntPlayer(this);	break;
#ifdef _DEBUG
	case -1:_pIntelligence = new CTankIntDummy(this);	break;
#endif
	}
	_pTankTop->setIntelligence(_pIntelligence);
	_pTankBottom->setIntelligence(_pIntelligence);

	//	�^�X�N�L����
	enableTask();

#ifdef _DEBUG
	if(Cnt == 0)
	{
		D3DXCreateSphere(D3DDEVICE,_fRadius,10,5,&debugMesh,NULL);
		Cnt++;
	}
#endif
}

/***********************************************************************/
/*! @brief �������
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::release()
{
	SAFE_DELETE(_pIntelligence	);
	SAFE_DELETE(_pTankTop		);
	SAFE_DELETE(_pTankBottom	);
}

/***********************************************************************/
/*! @brief �^�X�N�̗L����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::enableTask()
{
	CTaskMng::push<CTank>(TASKKEY::DRAW(),			this,&CTank::draw,	&_pTaskDraw			);
	CTaskMng::push<CTank>(TASKKEY::PAUSE(),			this,&CTank::pause,	&_pTaskPause		);
	CTaskMng::push<CTank>(TASKKEY::MOVE(),			this,&CTank::move,	&_pTaskMove			);
	CTaskMng::push<CTank>(TASKKEY::INTELLIGENCE(),	this,&CTank::intelligence,	&_pTaskIntelligence	);
	CTaskMng::push<CTank>(TASKKEY::FIRE(),			this,&CTank::fire,	&_pTaskFire);

}

/***********************************************************************/
/*! @brief �^�X�N�̖�����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::disableTask()
{
	CTaskMng::erase(&_pTaskDraw);
	CTaskMng::erase(&_pTaskPause);
	CTaskMng::erase(&_pTaskMove);
	CTaskMng::erase(&_pTaskIntelligence);
	CTaskMng::erase(&_pTaskFire);
}

/***********************************************************************/
/*! @brief	�v�l�X�V
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::intelligence()
{
	_pIntelligence->update();
}

/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::draw()
{
	_pTankTop->draw();
	_pTankBottom->draw();

#ifdef _DEBUG
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//�r���[���W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatView());			//�J�������W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_WORLD,this->_pTankBottom->getWMat());						//���[���h���W�ϊ�

//	D3DDEVICE->SetRenderState(D3DRS_FILLMODE ,2);

//	debugMesh->DrawSubset(0);
	static BOOL flg = TRUE;
	if(flg)
	{
		FONT->DrawFloat("MVecX",_pTankBottom->getMoveVec()->x,RECTEX(0,48,0,0));
		FONT->DrawFloat("MVecZ",_pTankBottom->getMoveVec()->z,RECTEX(0,64,0,0));
	}
	flg ^= TRUE;
	FONT->DrawInt("X",MOUSE.getPointWindow().x,RECTEX(0,80,0,0));
	FONT->DrawInt("X",MOUSE.getPointWindow().y,RECTEX(0,96,0,0));
#endif
}

/***********************************************************************/
/*! @brief �p���n����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::pause()
{
	_pTankTop->turn();
	_pTankBottom->turn();
}

/***********************************************************************/
/*! @brief �ړ�����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::move()
{
	_pTankBottom->move();

	//	�ړ����Z����
	const D3DXMATRIXA16* pMatTank = _pTankBottom->getWMat();
	_pTankTop->setPos(
		pMatTank->_41,
		pMatTank->_42 + 0.5f,
		pMatTank->_43
		);
}


/***********************************************************************/
/*! @brief ���C����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::fire()
{
	_pTankTop->fire();
}



/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pTank 
 *  @retval void
 */
/***********************************************************************/
void CTank::hitTank( CTank* pTank)
{
	if(pTank == this)
		return;

	D3DXVECTOR3 v1ref[2];
	const D3DXVECTOR3* v1 = _pTankBottom->getMoveVec();
	const D3DXVECTOR3* v2 = pTank->getMoveVec();
	const D3DXVECTOR3* vBak;

	for(uint Cnt = 0; Cnt < 2; ++Cnt)
	{
		commonfunc::repulsion(&v1ref[Cnt].x,v1->x,v2->x,100,100,1.0F,1.0F);
		commonfunc::repulsion(&v1ref[Cnt].z,v1->z,v2->z,100,100,1.0F,1.0F);
		v1ref[Cnt].y = 0;
		vBak = v1;
		v1 = v2;
		v2 = vBak;
	}

	_pTankBottom->setMoveVec(v1ref[0]);
	pTank->setMoveVec(v1ref[1]);
}

/***********************************************************************/
/*!	@brift	�{�g���̃}�g���N�X�擾
 *	@retval	D3DXMATRIXA16* �}�g���N�X
 */
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXMATRIXA16* 
 */
/***********************************************************************/
const D3DXMATRIXA16* CTank::getMatBottom()
{
	return _pTankBottom->getWMat();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval const D3DXVECTOR3* 
 */
/***********************************************************************/
const D3DXVECTOR3* CTank::getMoveVec()
{
	return _pTankBottom->getMoveVec();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval const float 
 */
/***********************************************************************/
const float CTank::getRadius()
{
	return _fRadius;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval const float 
 */
/***********************************************************************/
const float	CTank::getMass()
{
	return _fMass;
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] MoveVec 
 *  @retval void
 */
/***********************************************************************/
void CTank::setMoveVec( D3DXVECTOR3& MoveVec )
{
	_pTankBottom->setMoveVec(MoveVec);
	_pTankBottom->setMoveVec(MoveVec);
	_pTankBottom->setMoveVec(MoveVec);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] MoveVec 
 *  @retval void
 */
/***********************************************************************/
void CTank::setMoveVec( const D3DXVECTOR3 *MoveVec )
{
	_pTankBottom->setMoveVec(MoveVec);
	_pTankBottom->setMoveVec(MoveVec);
	_pTankBottom->setMoveVec(MoveVec);
}