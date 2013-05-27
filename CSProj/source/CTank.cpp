/***********************************************************************/
/*! @file  CTank.cpp
 *  @brief タンク
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"const.h"
//...タスク
#include"CTaskBase.h"
#include"CTaskList.h"
#include"CTank.h"
#include"CTaskMng.h"
//...パラメタ
#include"CMesh.h"
//...別オブジェクト
#include"CShell.h"
//...思考
#include"CTankIntInter.h"
#include"CTankIntPlayer.h"
//...ファクトリ
#include"CFactory.h"
#include"CObjMng.h"

#ifdef _DEBUG
#include"CFont.h"
#include"CInputCommon.h"
#endif

/***********************************************************************/
/*! @brief コンストラクタ
 * 
 *  @param[in] pMeshTop 	タンクの機体上部のモデル
 *  @param[in] pMeshBottom	タンクの機体下部のモデル
 *  @param[in] unIntType	タンクの思考タイプ
 *  @param[in] fSpeed 		移動速度
 *  @param[in] fTurnSpeed 	旋回速度
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
/*! @brief デストラクタ
 */
/***********************************************************************/
CTank::~CTank()
{
	disableTask();
	SAFE_DELETE(_pShellProto);
	release();
}

/***********************************************************************/
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] src コピーするオブジェクト
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
	//	マトリクス初期化
	D3DXMatrixIdentity(&_matTop);
	D3DXMatrixIdentity(&_matBottom);
	_matTop._42 += 0.5f;

	//	思考設定
	switch(_unIntType)
	{
	case 0:_pIntelligence = new CTankIntPlayer(this);break;
	case 1:break;
	}

	//	タスク有効化
	enableTask();

	//	弾の無効化
	_pShellProto->disableTask();
}

/***********************************************************************/
/*! @brief 解放処理
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
/*! @brief	思考更新
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
/*! @brief 描画処理
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
/*! @brief 姿勢系処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::pause()
{
	intMove();				//	思考がらみの移動処理
	calcDir();
}

/***********************************************************************/
/*! @brief 移動処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::move()
{
	calcActiveMoveVec();	//	能動的移動ベクトル計算

	//	移動加算さん
	_matBottom._41 += _MoveVec.x;
	_matBottom._42 += _MoveVec.y;
	_matBottom._43 += _MoveVec.z;
	_matTop._41 = _matBottom._41;
	_matTop._42 = _matBottom._42;
	_matTop._43 = _matBottom._43;
}


/***********************************************************************/
/*! @brief 移動フラグからの処理
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
/*! @brief 発砲フラグからの処理
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
/*! @brief 向き計算
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
/*! @brief ボトムの向き計算
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::calcDirBottom()
{
	float x,y,z;
	
	//	移動方向の左右確認
	static D3DXVECTOR2 v1,v2;

	v1.x = _BottomDir.x;
	v1.y = _BottomDir.z;
	v2.x = _MoveVec.x;
	v2.y = _MoveVec.z;

	float fCross = D3DXVec2CCW(&v1,&v2);	//	外積
	float fDot;

	//	左右判定
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
/*! @brief ボトムを回転
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
/*! @brief 移動ベクトルを計算
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
/*! @brief 移動ベクトルを計算
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::calcActiveMoveVec()
{
	//	姿勢からベクトルを計算
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
/*!	@brift	ボトムのマトリクス取得
 *	@retval	D3DXMATRIXA16* マトリクス
 */
/***********************************************************************/
D3DXMATRIXA16* CTank::getMatBottom()
{
	return &_matBottom;
}
	
/***********************************************************************/
/*! @brief タスクの有効化
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
/*! @brief タスクの無効化
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