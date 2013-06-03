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
#include"CTankTop.h"
#include"CTankBottom.h"

//...別オブジェクト
#include"CShell.h"
//...思考
#include"CTankIntInter.h"
#include"CTankIntPlayer.h"
//...ファクトリ
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
/*! @brief デストラクタ
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
/*! @brief コピーコンストラクタ
 * 
 *  @param[in] src コピーするオブジェクト
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

	//	思考設定
	switch(_unIntType)
	{
	case  0:_pIntelligence = new CTankIntPlayer(this);	break;
#ifdef _DEBUG
	case -1:_pIntelligence = new CTankIntDummy(this);	break;
#endif
	}
	_pTankTop->setIntelligence(_pIntelligence);
	_pTankBottom->setIntelligence(_pIntelligence);

	//	タスク有効化
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
/*! @brief 解放処理
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
/*! @brief タスクの有効化
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
	CTaskMng::erase(&_pTaskFire);
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
}

/***********************************************************************/
/*! @brief 描画処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::draw()
{
	_pTankTop->draw();
	_pTankBottom->draw();

#ifdef _DEBUG
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//ビュー座標変換
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatView());			//カメラ座標変換
	D3DDEVICE->SetTransform(D3DTS_WORLD,this->_pTankBottom->getWMat());						//ワールド座標変換

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
/*! @brief 姿勢系処理
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
/*! @brief 移動処理
 * 
 *  @retval void
 */
/***********************************************************************/
void CTank::move()
{
	_pTankBottom->move();

	//	移動加算さん
	const D3DXMATRIXA16* pMatTank = _pTankBottom->getWMat();
	_pTankTop->setPos(
		pMatTank->_41,
		pMatTank->_42 + 0.5f,
		pMatTank->_43
		);
}


/***********************************************************************/
/*! @brief 発砲処理
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
/*!	@brift	ボトムのマトリクス取得
 *	@retval	D3DXMATRIXA16* マトリクス
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