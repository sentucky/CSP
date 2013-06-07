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

#include"StageData.h"

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

const CStageData* CTank::_StageData = NULL;

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
	_pTankTop = new CTankTop(this,pMeshTop,NULL,pShellProto);
	_pTankBottom = new CTankBottom(pMeshBottom,fMoveSpeed,fTurnSpeed);
	debugMesh = NULL;
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
//	Cnt--;
	if(debugMesh != 0)
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

	_pTankTop->setOwner(this);
	_pTankTop->setTankBottom(_pTankBottom);

	//	タスク有効化
	enableTask();

#ifdef _DEBUG
	debugMesh = NULL;
	D3DXCreateSphere(D3DDEVICE,_fRadius,10,5,&debugMesh,NULL);
	Cnt++;
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

	D3DDEVICE->SetRenderState(D3DRS_FILLMODE ,2);

	if(debugMesh != NULL)
		debugMesh->DrawSubset(0);
	static BOOL flg = TRUE;
	uint x;
	uint y;
	_StageData->step(&x,&y,_pTankBottom->getWMat()->_41,_pTankBottom->getWMat()->_43);
	FONT->DrawInt("step",x,RECTEX(0,32,0,0));
	FONT->DrawInt("step",y,RECTEX(100,32,0,0));
//	if(flg)
	{
		FONT->DrawFloat("TPOS",_pTankBottom->getWMat()->_41,RECTEX(0,48,0,0));
		FONT->DrawFloat("TPOS",_pTankBottom->getWMat()->_43,RECTEX(0,64,0,0));
	}
	TILE tile[16][16];
	_StageData->getTile(tile);

	RECT a;
	_StageData->wallFlg(&a,x,y);
	int a3 = 0;
	a3 = a.top * 1000 + a.left * 100 + a.bottom * 10 + a.right;
	FONT->DrawInt("FLGS",a3,RECTEX(0,112,0,0));

	flg ^= TRUE;
	FONT->DrawFloat("VecX",_pTankBottom->getMoveVec()->x,RECTEX(0,80,0,0));
	FONT->DrawFloat("VecZ",_pTankBottom->getMoveVec()->z,RECTEX(0,96,0,0));
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
void CTank::hitTestTank( CTank* pTank)
{
	if(pTank == this)
		return;

	D3DXVECTOR3 v1ref[2];
	const D3DXVECTOR3* v1 = _pTankBottom->getMoveVec();
	const D3DXVECTOR3* v2 = pTank->getMoveVec();
	const D3DXVECTOR3* vBak;

	const D3DXMATRIXA16* pmatW1 = _pTankBottom->getWMat();
	const D3DXMATRIXA16* pmatW2 = pTank->getMatBottom();

	D3DXVECTOR3 pos1(pmatW1->_41,pmatW1->_42,pmatW1->_43);
	D3DXVECTOR3 pos2(pmatW2->_41,pmatW2->_42,pmatW2->_43);

	D3DXVECTOR3 v3 = pos1 - pos2;

	D3DXVec3Normalize(&v3,&v3);

	float f = (sqrt(v1->x * v1->x + v1->z * v1->z) + sqrt(v2->x * v2->x + v2->z * v2->z))*0.5f;
	v1ref[0] = v3 * f;
	v1ref[1] = -v3 * f;

	/*
	//for(uint Cnt = 0; Cnt < 2; ++Cnt)
	{
//		commonfunc::repulsion(&v1ref[Cnt].x,v1->x,v2->x,100,100,1.0F,1.0F);
//		commonfunc::repulsion(&v1ref[Cnt].z,v1->z,v2->z,100,100,1.0F,1.0F);
//*
		CalcParticleColliAfterPos(
			&pos1,
			&pos2,
			v1,
			v2,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			&v1ref[0],
			&v1ref[1]
		);
//	
//		v1ref[Cnt].y = 0;
//		vBak = v1;
//		v1 = v2;
//		v2 = vBak;
	}
*/
	_pTankBottom->setMoveVec(v1ref[0]);
	pTank->setMoveVec(v1ref[1]);
}

void CTank::hitTestShell(CShell* pShell)
{
	_DeleteFlg = TRUE;
}

void CTank::hitTestWall()
{

	//	立っている場所を知る
	uint x;
	uint y;
	uint x2;
	uint y2;
	float tx = _pTankBottom->getWMat()->_41;
	float ty = _pTankBottom->getWMat()->_43;
	float tx2 = tx + _pTankBottom->getMoveVec()->x;
	float ty2 = ty + _pTankBottom->getMoveVec()->z;
	_StageData->step(&x,&y,tx,ty);

	_StageData->step(&x2,&y2,tx,ty);


	//	壁の情報を取得
	RECT WallFlg;
	_StageData->wallFlg(&WallFlg,x,y);

	const TILE tile[MAX_DATA][MAX_DATA];
	_StageData->getTile(tile);

	float hitX;
	float hitY;

	const float top		= tile[x][y].posY + 15.0f;
	const float left	= tile[x][y].posX - 15.0f;
	const float bottom	= tile[x][y+1].posY +  17.0f;
	const float right	= tile[x+1][y].posX -  17.0f;



	bool flg;

	D3DXVECTOR3 NewV;
	NewV.x = 0;
	NewV.y = 0;
	NewV.z = 0;

	const float ref = 2.0f;

	//	top
	if(WallFlg.top)
	{
		/*
		flg = LineToLine(
			&hitX,
			&hitY,
			tile[x][y].posX,tile[x][y].posY,
			tile[x+1][y].posX,tile[x+1][y].posY,
			tx,ty,
			tx + _pTankBottom->getMoveVec()->x,
			ty + _pTankBottom->getMoveVec()->z);
			*/
		
		if(top < ty)
		{
			_pTankBottom->setPos(tx,top );
			NewV.x = _pTankBottom->getMoveVec()->x;
			NewV.z = -_pTankBottom->getMoveVec()->z;
			_pTankBottom->setMoveVec(NewV);
		}
	}
	//	left
	if(WallFlg.left)
	{
		/*
		flg = LineToLine(
			&hitX,
			&hitY,
			tile[x][y].posX,tile[x][y].posY,
			tile[x][y+1].posX,tile[x][y+1].posY,
			tx,ty,
			tx + _pTankBottom->getMoveVec()->x,
			ty + _pTankBottom->getMoveVec()->z);
			*/

		if(left > tx)
		{
			_pTankBottom->setPos(left,ty);
			NewV.x = -_pTankBottom->getMoveVec()->x;
			NewV.z = _pTankBottom->getMoveVec()->z;
			_pTankBottom->setMoveVec(NewV);
		}
	}
	//	bottom
	if(WallFlg.bottom)
	{
		/*
		flg = LineToLine(
			&hitX,
			&hitY,
			tile[x][y+1].posX,tile[x][y+1].posY,
			tile[x+1][y+1].posX,tile[x+1][y+1].posY,
			tx,ty,
			tx + _pTankBottom->getMoveVec()->x,
			ty + _pTankBottom->getMoveVec()->z);*/
		if( bottom >= ty2 && bottom <= ty)
		{
			_pTankBottom->setPos(tx,bottom);
			NewV.x = _pTankBottom->getMoveVec()->x;
			NewV.z = -_pTankBottom->getMoveVec()->z;
			_pTankBottom->setMoveVec(NewV);
		}
	}
	//	right
	if(WallFlg.right)
	{
		/*
		flg = LineToLine(
			&hitX,
			&hitY,
			tile[x+1][y].posX,tile[x+1][y].posY,
			tile[x+1][y+1].posX,tile[x+1][y+1].posY,
			tx,ty,
			tx + _pTankBottom->getMoveVec()->x,
			ty + _pTankBottom->getMoveVec()->z);	
			*/
		if( right <= tx2 && right >= tx)
		{
			_pTankBottom->setPos(right,ty);
			NewV.x = -_pTankBottom->getMoveVec()->x;
			NewV.z = _pTankBottom->getMoveVec()->z;
			_pTankBottom->setMoveVec(NewV);
		}
	}
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
}


void CTank::setPos(const float x,const float z)
{
	_pTankBottom->setPos(x,z);
}