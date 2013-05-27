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
	_pShellProto	( pShellProto	),
	_MeshTop		( pMeshTop		),
	_MeshBottom		( pMeshBottom	),
	_TopDir			( 0,0,0			),
	_BottomDir		( 0,0,0			),
	_fNormalMoveSpeed(fMoveSpeed	),
	_fMoveSpeed		( fMoveSpeed	),
	_fTurnSpeed		( fTurnSpeed	),
	_pIntelligence	( NULL			),
	_unIntType		( unIntType		)
{
	D3DXMatrixIdentity(&_matTop);
	D3DXMatrixIdentity(&_matBottom);
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CTank::~CTank()
{
	disableTask();
	SAFE_DELETE(_pShellProto);
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
	_pShellProto		( new CShell(*src._pShellProto)	),
	_MeshTop			( new CMesh(*src._MeshTop)		),
	_MeshBottom			( new CMesh(*src._MeshBottom)	),
	_TopDir				( 0,0,1.0f						),
	_BottomDir			( 0,0,1.0f						),
	_fNormalMoveSpeed	( src._fNormalMoveSpeed			),
	_fMoveSpeed			( src._fMoveSpeed				),
	_fTurnSpeed			( src._fTurnSpeed				),
	_pIntelligence		( NULL							),
	_unIntType			( src._unIntType				)
{
	//	�}�g���N�X������
	D3DXMatrixIdentity(&_matTop);
	D3DXMatrixIdentity(&_matBottom);
	_matTop._42 += 0.5f;

	//	�v�l�ݒ�
	switch(_unIntType)
	{
	case 0:_pIntelligence = new CTankIntPlayer(this);break;
	case 1:break;
	}

	//	�^�X�N�L����
	enableTask();

	//	�e�̖�����
	_pShellProto->disableTask();
}

/***********************************************************************/
/*! @brief �������
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::release()
{
	SAFE_DELETE(_MeshTop);
	SAFE_DELETE(_MeshBottom);
	SAFE_DELETE(_pIntelligence);
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
	intFire();
}

/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::draw()
{
	_MeshTop->draw(&_matTop);

	_MeshBottom->draw(&_matBottom) ;
#ifdef _DEBUG
	FONT->DrawFloat("X",_matBottom._41,RECTEX(0,48,0,0));
	FONT->DrawFloat("X",_matBottom._43,RECTEX(0,64,0,0));
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
	intMove();				//	�v�l����݂̈ړ�����
	calcDir();
}

/***********************************************************************/
/*! @brief �ړ�����
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::move()
{
	calcActiveMoveVec();	//	�\���I�ړ��x�N�g���v�Z

	//	�ړ����Z����
	_matBottom._41 += _MoveVec.x;
	_matBottom._42 += _MoveVec.y;
	_matBottom._43 += _MoveVec.z;
	_matTop._41 = _matBottom._41;
	_matTop._42 = _matBottom._42;
	_matTop._43 = _matBottom._43;
}


/***********************************************************************/
/*! @brief �ړ��t���O����̏���
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::intMove()
{
	uint unMoveDir = _pIntelligence->getMoveFlg();
	_MoveVec.y = 0;
	switch(unMoveDir % 3)
	{
	case 1:_MoveVec.x = -1.0f;	break;
	case 2:_MoveVec.x = 0.0f;	break;
	case 0:_MoveVec.x = 1.0f;	break;
	}
	switch((unMoveDir -1 ) / 3)
	{
	case 0:_MoveVec.z = -1.0f;	break;
	case 1:_MoveVec.z = 0.0f;	break;
	case 2:_MoveVec.z = 1.0f;	break;
	}
}

/***********************************************************************/
/*! @brief ���C�t���O����̏���
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::intFire()
{
	if(_pIntelligence->getFireFlg())
	{
		CShell* pShell = NULL;
		OBJMNG->push_back(pShell = new CShell(*_pShellProto));
		pShell->setMoveVector(&_TopDir);
		pShell->setPos(&_matTop);
	}
}


/***********************************************************************/
/*! @brief �����v�Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::calcDir()
{
	float x,y,z;

	x = _matTop._41;
	y = _matTop._42;
	z = _matTop._43;

	calcDirBottom();
	turnTop();
}

/***********************************************************************/
/*! @brief �{�g���̌����v�Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::calcDirBottom()
{
	float x,y,z;
	
	//	�ړ������̍��E�m�F
	static D3DXVECTOR2 v1,v2;

	v1.x = _BottomDir.x;
	v1.y = _BottomDir.z;
	v2.x = _MoveVec.x;
	v2.y = _MoveVec.z;

	float fCross = D3DXVec2CCW(&v1,&v2);	//	�O��
	float fDot;

	//	���E����
	if(fCross > 0)
	{
		turnBottom(_fTurnSpeed);
	}
	else if(fCross < 0)
	{
		turnBottom(-_fTurnSpeed);
	}
	else
	{
		fDot = D3DXVec3Dot(&_BottomDir,&_MoveVec);
		
		if(fDot < 0)
		{
			turnBottom(_fTurnSpeed);
		}
	}

	x = _matBottom._41;
	y = _matBottom._42;
	z = _matBottom._43;

	static const D3DXVECTOR3 XV(0.0f,0.0f,1.0f);
	
	D3DXVec3Normalize(&_BottomDir,&_BottomDir);

	_matBottom._41 = _matBottom._42 = _matBottom._43 = 0;

	D3DXMatrixRotationY(&_matBottom,-atan2f(_BottomDir.z,_BottomDir.x) + 0.5F*3.1415f);

	_matBottom._41 = x;
	_matBottom._42 = y;
	_matBottom._43 = z;
}


/***********************************************************************/
/*! @brief �{�g������]
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::turnBottom(const float fTurnSpeed)
{
	const float x = _BottomDir.x * cosf(fTurnSpeed) + (-_BottomDir.z * sin(fTurnSpeed));
	const float z = _BottomDir.z * cosf(fTurnSpeed) + _BottomDir.x * sin(fTurnSpeed);
	_BottomDir.x = x;
	_BottomDir.z = z;
}


/***********************************************************************/
/*! @brief �ړ��x�N�g�����v�Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::turnTop()
{
	D3DXVECTOR3 p1;
	D3DXVECTOR2 cr;
	MOUSE.mousePoint3D(&p1,0);

	_TopDir.x = cr.x = p1.x - _matTop._41;
	_TopDir.z = cr.y = p1.z - _matTop._43;

	D3DXVec2Normalize(&cr,&cr);

	D3DXMatrixRotationY(&_matTop,-atan2f(cr.y,cr.x) + 0.5F*3.1415f);
}


/***********************************************************************/
/*! @brief �ړ��x�N�g�����v�Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::calcActiveMoveVec()
{
	//	�p������x�N�g�����v�Z
	if(_pIntelligence->getMoveFlg() != TMV_5)
	{
		_MoveVec = _BottomDir;
	}
	else
	{
		_MoveVec.x = _MoveVec.y = _MoveVec.z = 0;
	}
	_MoveVec *= _fMoveSpeed;
}

/***********************************************************************/
/*!	@brift	�{�g���̃}�g���N�X�擾
 *	@retval	D3DXMATRIXA16* �}�g���N�X
 */
/***********************************************************************/
D3DXMATRIXA16* CTank::getMatBottom()
{
	return &_matBottom;
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
}