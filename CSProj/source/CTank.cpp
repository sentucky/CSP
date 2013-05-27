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
#include"CFont.h"
#include"CInputCommon.h"
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
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] src �R�s�[����I�u�W�F�N�g
 */
/***********************************************************************/
CTank::CTank(const CTank& src)
	:_pTaskDraw			( NULL			),
	_pTaskPause			( NULL			),
	_pTaskMove			( NULL			),
	_pTaskIntelligence	( NULL			),
	_pTaskFire			( NULL			),
	_pTankTop			( new CTankTop(*src._pTankTop)			),
	_pTankBottom		( new CTankBottom(*src._pTankBottom)	),
	_pIntelligence		( NULL							),
	_unIntType			( src._unIntType				)
{

	//	�v�l�ݒ�
	switch(_unIntType)
	{
	case 0:_pIntelligence = new CTankIntPlayer(this);break;
	case 1:break;
	}
	_pTankTop->setIntelligence(_pIntelligence);
	_pTankBottom->setIntelligence(_pIntelligence);

	//	�^�X�N�L����
	enableTask();

}

/***********************************************************************/
/*! @brief �������
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::release()
{
	SAFE_DELETE(_pIntelligence);
	SAFE_DELETE(_pTankTop);
	SAFE_DELETE(_pTankBottom);
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
	FONT->DrawFloat("X",_pTankBottom->getWMat()->_41,RECTEX(0,48,0,0));
	FONT->DrawFloat("Y",_pTankBottom->getWMat()->_42,RECTEX(0,64,0,0));
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
/*!	@brift	�{�g���̃}�g���N�X�擾
 *	@retval	D3DXMATRIXA16* �}�g���N�X
 */
/***********************************************************************/
const D3DXMATRIXA16* CTank::getMatBottom()
{
	return _pTankBottom->getWMat();
}
	
/***********************************************************************/
/*! @brief �^�X�N�̗L����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::enableTask()
{
	CTaskMng::push<CTank>(TASKID::DRAW(),			this,&CTank::draw,	&_pTaskDraw			);
	CTaskMng::push<CTank>(TASKID::PAUSE(),			this,&CTank::pause,	&_pTaskPause		);
	CTaskMng::push<CTank>(TASKID::MOVE(),			this,&CTank::move,	&_pTaskMove			);
	CTaskMng::push<CTank>(TASKID::INTELLIGENCE(),	this,&CTank::intelligence,	&_pTaskIntelligence	);
	CTaskMng::push<CTank>(TASKID::FIRE(),			this,&CTank::fire,	&_pTaskFire);

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