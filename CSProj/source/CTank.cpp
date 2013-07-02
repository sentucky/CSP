/***********************************************************************/
/*! @file  CTank.cpp
 *  @brief �^���N
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#include"CTank.h"

#include"const.h"
#include"ObjKey.h"
//...�^�X�N
#include"CTaskBase.h"
#include"CTaskList.h"
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
#include"CTankIntStop.h"
//...�t�@�N�g��
#include"CFactory.h"
#include"CObjMng.h"

#include"StageData.h"
#include"Rect.h"
#include"CFollowCamera.h"
#include"CSound.h"
#include"CSoundKey.h"
#include"CTankIntDummy.h"
#include"CSprite.h"
#include"CSpriteFactory.h"
#include"TextureKey.h"
#include"CAnimeParam.h"
#include"AnimeKey.h"

#ifdef _DEBUG
#include"CCamera.h"
#include"CScreen.h"
#include"CFont.h"
#include"CInputCommon.h"
#include"CTextureFactory.h"
#endif

#ifdef _DEBUG
LPD3DXMESH debugMesh = NULL;
#endif

CTank* CTank::_Player = NULL;
const CStageData* CTank::_StageData = NULL;
LPDIRECTSOUNDBUFFER CTank::_SoundFire	= NULL;


void billboard(D3DXMATRIXA16* Out,const D3DXMATRIXA16* In)
{
		//	�t�r���[�̍쐬
		D3DXMATRIXA16 trance;
		D3DXMatrixIdentity(&trance);
		trance._41 = In->_41;
		trance._42 = In->_42;
		trance._43 = In->_43;

		D3DXMATRIXA16 scale;
		D3DXMatrixIdentity(&scale);
		scale._11 = In->_11;
		scale._22 = In->_22;
		scale._33 = In->_33;


		D3DXMATRIXA16 inv;
		D3DXMatrixIdentity(&inv);
		D3DXMatrixInverse(&inv,0,CCamera::getMatView());
		inv._41 = inv._42 = inv._43 = 0;


		D3DXMatrixIdentity(Out);
		*Out = inv * trance;
}




/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] pMeshTop 	�^���N�̋@�̏㕔�̃��f��
 *  @param[in] pMeshBottom	�^���N�̋@�̉����̃��f��
 *  @param[in] unThisType	�^���N�̎v�l�^�C�v
 *  @param[in] fSpeed 		�ړ����x
 *  @param[in] fTurnSpeed 	���񑬓x
 */
/***********************************************************************/
CTank::CTank(
	CMesh* pMeshTop,
	CMesh* pMeshBottom,
	uint   unThisType,
	CShell* pShellProto,
	const float fMoveSpeed,
	const float fTurnSpeed,
	const int	Life

	)
	:CObjBase			( OBJGROUPKEY::TANK()),
	_pTaskDraw			( NULL			),
	_pTaskPause			( NULL			),
	_pTaskMove			( NULL			),
	_pTaskIntelligence	( NULL			),
	_pTaskFire			( NULL			),
	_pTaskCalcAM		( NULL			),
	_pTaskRap			( NULL			),
	_pTaskDestroyed		( NULL			),
	_pTaskStepReset		( NULL			),
	_pTankTop			( NULL			),
	_pTankBottom		( NULL			),
	_pIntelligence		( NULL			),
	_fRadius			( 0.75f			),
	_unThisType			( unThisType	),
	_life				( Life			),
	_Maxlife			( Life			),
	_radiate			( 0				),
	_MaxRadiateTime		( 15			),
	_deldelayCount		( 0				),
	_Destroyed			( FALSE			),
	_FlgGoal			( FALSE			),
	_lap				(-1				),
	_lapVal				(0				),
	_Rank				(0				),
	_CurStep			(),
	_SpriteExpload		(NULL			),
	_expflag			(false			),
	_effectMatrix		(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
{
	_pTankTop = new CTankTop(this,pMeshTop,NULL,pShellProto);
	_pTankBottom = new CTankBottom(pMeshBottom,fMoveSpeed,fTurnSpeed);
#ifdef _DEBUG
	debugMesh = NULL;
#endif
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
	SAFE_DELETE(_SpriteExpload);
	release();
#ifdef _DEBUG
	if(debugMesh != 0)
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
	:CObjBase			(src._GroupID						),
	_pTaskDraw			( NULL								),
	_pTaskPause			( NULL								),
	_pTaskMove			( NULL								),
	_pTaskIntelligence	( NULL								),
	_pTaskFire			( NULL								),
	_pTaskCalcAM		( NULL								),
	_pTaskRap			( NULL								),
	_pTaskDestroyed		( NULL								),
	_pTaskStepReset		( NULL								),
	_pTankTop			( new CTankTop(*src._pTankTop)		),
	_pTankBottom		( new CTankBottom(*src._pTankBottom)),
	_pIntelligence		( NULL								),
	_fRadius			( src._fRadius						),
	_unThisType			( src._unThisType					),
	_life				( src._life							),
	_Maxlife			( src._Maxlife						),
	_radiate			(0									),
	_MaxRadiateTime		(src._MaxRadiateTime				),
	_deldelayCount		( 0									),
	_Destroyed			( FALSE								),
	_FlgGoal			( FALSE								),
	_lap				(-1									),
	_lapVal				(0									),
	_Rank				(0									),
	_CurStep			(									),
	_SpriteExpload		(NULL								),
	_expflag			(false								),
	_effectMatrix		(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	)
{
	//	�v�l�ݒ�
	switch(_unThisType)
	{
	case  TYPE_PLAYER:
		_pIntelligence = new CTankIntPlayer(this);
		break;
	case TYPE_ENEMY01:
		_pIntelligence = new CTankIntDummy(this);	
		break;
	}

	_pTankTop->setIntelligence(_pIntelligence);
	_pTankBottom->setIntelligence(_pIntelligence);

	_pTankTop->setOwner(this);
	_pTankTop->setTankBottom(_pTankBottom);

	//	�^�X�N�L����
//	enableTask();
	CTaskMng::push<CTank>(TASKKEY::DRAW(),			this,&CTank::draw,	&_pTaskDraw			);

	_Panel		= NULL;
	_prevPanel	= NULL;

	memset(&_CurStep,0,sizeof(_CurStep));

	_SpriteExpload = SPRITEFACTORY->create(TEXKEY::TANK_EXPLOAD());
	_SpriteExpload->createAnimeParam(ANIMEPATH::BARN());
	_SpriteExpload->setCatAnime(0);
	_SpriteExpload->updateAnime();

	D3DXMatrixIdentity(&_effectMatrix);

	CTaskMng::push<CTank>(TASKKEY::TANKSETPSET(),	this,&CTank::stepReset,		&_pTaskStepReset	);
#ifdef _DEBUG
	debugMesh = NULL;
	D3DXCreateSphere(D3DDEVICE,_fRadius,10,5,&debugMesh,NULL);
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
	CTaskMng::push<CTank>(TASKKEY::PAUSE(),			this,&CTank::pause,			&_pTaskPause		);
	CTaskMng::push<CTank>(TASKKEY::MOVE(),			this,&CTank::move,			&_pTaskMove			);
	CTaskMng::push<CTank>(TASKKEY::INTELLIGENCE(),	this,&CTank::intelligence,	&_pTaskIntelligence	);
	CTaskMng::push<CTank>(TASKKEY::FIRE(),			this,&CTank::fire,			&_pTaskFire);
	CTaskMng::push<CTank>(TASKKEY::CALCACTIVEMOVE(),this,&CTank::calcMove,		&_pTaskCalcAM);
	CTaskMng::push<CTank>(TASKKEY::RAP(),			this,&CTank::pRap,			&_pTaskRap);
	CTaskMng::push<CTank>(TASKKEY::TANKSETPSET(),	this,&CTank::stepReset,		&_pTaskStepReset	);
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
	CTaskMng::erase(&_pTaskCalcAM);
	CTaskMng::erase(&_pTaskRap);
	CTaskMng::erase(&_pTaskDestroyed);
	CTaskMng::erase(&_pTaskStepReset);
}

const bool CTank::lower(const CTank* A,const CTank* B)
{
	return A->_lapVal > B->_lapVal;
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
	int x,y;
	int playerx, playery;

	//	�אڃ^�C���ȓ��ɂȂ���Ε`�悵�Ȃ�
	x = YOUSO(_pTankBottom->getWMat()->_41);
	y = YOUSO(_pTankBottom->getWMat()->_43);
	playerx = YOUSO(CCamera::getAt().x);
	playery = YOUSO(CCamera::getAt().z);
	if(abs(x - playerx) > 1 || abs(y - playery) > 1)
	{
		return;
	}

	_pTankTop->draw();
	_pTankBottom->draw();

	if(_expflag)
	{
		drawDestroyed();
	}

#ifdef _DEBUG
	if(_unThisType == 0)
	{
		FONT->DrawFloat("lapval,",this->_lapVal,RECTEX(400,0,0,0));
		FONT->DrawInt("lap,",this->_lap,RECTEX(400,16,0,0));
	}

	/*
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getProjPtr());	//�r���[���W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatViewOUSO());		//�J�������W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_WORLD,this->_pTankBottom->getWMat());	//���[���h���W�ϊ�
//	D3DDEVICE->SetRenderState(D3DRS_FILLMODE ,2);
	debugMesh->DrawSubset(0);
	*/

	static BOOL flg = TRUE;

	FONT->DrawInt("step",x,RECTEX(0,32,0,0));
	FONT->DrawInt("step",y,RECTEX(100,32,0,0));


	OUTPUT tile[16][16];
	_StageData->getTile(tile);

	RECT a;
	_StageData->wallFlg(&a,x,y);
	int a3 = 0;
	a3 = a.top * 1000 + a.left * 100 + a.bottom * 10 + a.right;
	FONT->DrawInt("FLGS",a3,RECTEX(0,112,0,0));

	flg ^= TRUE;
	FONT->DrawFloat("VecX",_pTankBottom->getMoveVec()->x,RECTEX(0,80,0,0));
	FONT->DrawFloat("VecZ",_pTankBottom->getMoveVec()->z,RECTEX(0,96,0,0));
	FONT->DrawInt("RadiateTime",_radiate,RECTEX(0,112+16,0,0));
	FONT->DrawInt("roottile",_StageData->step2(_pTankBottom->getWMat()->_41,_pTankBottom->getWMat()->_43)->root,RECTEX(0,500,0,0));

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
	const D3DXVECTOR3* movevec = _pTankBottom->getMoveVec();
	if( movevec->x + movevec->z > 10)
		CSOUND->GetSound(SOUNDKEY::MOVE())->Play(0,0,0);

	_pTankBottom->move();

	//	�ړ����Z����/
	const D3DXMATRIXA16* pMatTank = _pTankBottom->getWMat();

	_pTankTop->setPos(
		pMatTank->_41,
		pMatTank->_42,
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
	//	���M
	if(_radiate > 0 )
	{
		--_radiate;
	}

	//	���C
	if(_pIntelligence->getFireFlg() && _radiate <= 0)
	{
		_pTankTop->fire();
		_radiate = _MaxRadiateTime;
		_SoundFire->Play(0,0,0);
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::calcMove()
{
	_pTankBottom->clacMove(_Rank + 1);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::pRap()				///<	���@���b�v
{
	const OUTPUT* StData = _StageData->getStartTile();
	const OUTPUT* ScData = _StageData->getSecondTile();
	const OUTPUT* LaData = _StageData->getLastTile();
	const D3DXVECTOR3 pos = _pTankBottom->getPos();
	int rootNum = _StageData->getRootTileNum();

	_Panel = _StageData->step2(pos.x,pos.z);
	
	if (!_prevPanel){
		_prevPanel = (OUTPUT*)_Panel;
	}

	//�p�l���ړ�
	if (_Panel != _prevPanel){
		
		//�p�^�[���P����
		if (_Panel == StData && _prevPanel == LaData){
			_lap++;
		}

		//�p�^�[���Q�t��
		if (_Panel == LaData && _prevPanel == StData){
			_lap--;
		}
		_prevPanel = _Panel;
	}

	int i,j;
	
	OUTPUT* p;
	OUTPUT* f;
	OUTPUT* s;
	for (i = -1 ; i < 2 ; i++){
		for (j = -1 ; j < 2 ; j++){
			p = _StageData->step2(pos.x + (i * (500.0f / 16.0f)),pos.z + (j * (500.0f / 16.0f)));
			if(_Panel->root - p->root == -1)f = p;
			else if(_Panel->root - p->root == (rootNum - 1))f = p;
			else if(_Panel->root - p->root == 1)s = p;
			else if(_Panel->root - p->root == -(rootNum - 1))s = p;
		}
	}

	float flen = (pos.x - f->posX) * (pos.x - f->posX) + (pos.z - f->posY) * (pos.z - f->posY);
	float slen = (pos.x - s->posX) * (pos.x - s->posX) + (pos.z - s->posY) * (pos.z - s->posY);

	if (flen < slen){
		s = f;
		p = _Panel;
	}
	else {
		p = s;
		s = _Panel;
	}

	
	float t = (pos.x - p->posX) * (s->posX - p->posX) + (pos.z - p->posY) * (s->posY - p->posY);
	t /= ((s->posX - p->posX) * (s->posX - p->posX) + (s->posY - p->posY) * (s->posY - p->posY));

	_lapVal = (float)(_lap * rootNum) + p->root + t;

	if (p->root == rootNum - 1 && _Panel->no == 3)
		_lapVal -= rootNum;

	if(_lap > 3)
	{
		_FlgGoal = TRUE;
	}
}


/***********************************************************************/
/*! @brief �폜���o
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::destroyed()
{
	_expflag = true;

	float count;
	count = _deldelayCount;

	_SpriteExpload->setCatAnime(6 - int(6 * (_deldelayCount / 60.0f)));
	_SpriteExpload->updateAnime();

	--_deldelayCount;

	if(_deldelayCount < 0)
	{
		CTaskMng::erase(&_pTaskDestroyed);
		SAFE_DELETE(_pIntelligence);
		_pIntelligence = new CTankIntStop(this);
		if(_unThisType != TYPE_PLAYER)
			_DeleteFlg = TRUE;
		_expflag = false;
	}
}

/***********************************************************************/
/*! @brief ������̎擾
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::stepReset()
{
	_CurStep[0] = YOUSO(_pTankBottom->getWMat()->_41);
	_CurStep[1] = YOUSO(_pTankBottom->getWMat()->_43);
}


/***********************************************************************/
/*! @brief ��ԂƂ̂����蔻��
 * 
 *  @param[in] pTank 
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
	const D3DXMATRIXA16* pmatW1 = _pTankBottom->getWMat();
	const D3DXMATRIXA16* pmatW2 = pTank->getMatBottom();

	/*
	D3DXVECTOR3 pos1(pmatW1->_41,pmatW1->_42,pmatW1->_43);
	D3DXVECTOR3 pos2(pmatW2->_41,pmatW2->_42,pmatW2->_43);

//	D3DXVec3Normalize(&v3,&v3);

	/*

	float f = sqrt(v1->x * v1->x + v1->z * v1->z + v2->x * v2->x + v2->z * v2->z) *0.5f;

	v1ref[0] =  v3 * f;
	v1ref[1] = -v3 * f;

	_pTankBottom->setMoveVec(v1ref[0]);
	pTank->setMoveVec(v1ref[1]);

	*/
	D3DXVECTOR3 vIn;

	//	�\�ʂ܂ŉ����߂�
	//	�������甼�a�����������l = �߂荞�ݓx
	//*
	float distance = (pmatW1->_41 - pmatW2->_41) * (pmatW1->_41 - pmatW2->_41) + (pmatW1->_43 - pmatW2->_43) * (pmatW1->_43 - pmatW2->_43);
	distance = sqrt(distance);

	//���̂P�̗�������
	float tx = pmatW1->_41 - pmatW2->_41;
	float ty = pmatW1->_43 - pmatW2->_43;

	float t = _fRadius + pTank->getRadius() - distance;

	tx = tx >= 0 ? 1.0f : -1.0f;
	ty = ty >= 0 ? 1.0f : -1.0f;

	tx *= t * 0.5f;
	ty *= t * 0.5f;
	//*
	setPos(pmatW1->_41 + tx ,pmatW1->_43 + ty);
	pTank->setPos(pmatW2->_41 + -tx ,pmatW2->_43 + -ty);
	//*/
	float vox1,voy1;
	float vox2,voy2;
	
	commonfunc::repulsion(&vox1,v1->x,v2->x,1,1,1,1);
	commonfunc::repulsion(&voy1,v1->z,v2->z,1,1,1,1);

	commonfunc::repulsion(&vox2,v2->x,v1->x,1,1,1,1);
	commonfunc::repulsion(&voy2,v2->z,v1->z,1,1,1,1);

	vIn.y = 0;
	vIn.x = vox1;
	vIn.z = voy1;
	setMoveVec(vIn);

	vIn.x = vox2;
	vIn.z = voy2;
	pTank->setMoveVec(vIn);
}


/***********************************************************************/
/*! @brief �e�Ƃ̂����蔻��
 * 
 *  @param[in] pShell	�e 
 *  @retval void
 */
/***********************************************************************/
void CTank::hitTestShell(CShell* pShell)
{
	//	���C�t���Z
	_life -= pShell->getPower();

	//	�ϋv�؂�Ŕj��
	if(_life <= 0)
	{
		//_DeleteFlg = TRUE;
		_Destroyed = TRUE;

		SAFE_DELETE(_pIntelligence);
		_pIntelligence = new CTankIntStop(this);
		CTaskMng::erase(&_pTaskPause);
		CTaskMng::erase(&_pTaskFire);
		CTaskMng::erase(&_pTaskRap);
		CTaskMng::push<CTank>(TASKKEY::EXPLOSION(),this,&CTank::destroyed,&_pTaskDestroyed);
		_deldelayCount = _maxdeldelayCount;
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::hitTestWall()
{
}


/***********************************************************************/
/*!	@brift	���[�X�I��������
 *	@retval	void
 */
/***********************************************************************/
void CTank::raceEnd()
{
	CTaskMng::erase(&_pTaskRap);
	CTaskMng::erase(&_pTaskFire);
	if(_unThisType == TYPE_PLAYER)
	{
		SAFE_DELETE(_pIntelligence);
		_pIntelligence = new CTankIntDummy(this);
	}
}

/***********************************************************************/
/*!	@brift	��j�󎞉��o
 *	@retval	void
 */
/***********************************************************************/
void CTank::drawDestroyed()
{
		//�������o
		/*
		D3DDEVICE->SetTransform(D3DTS_WORLD, &_effectMatrix);
		D3DDEVICE->SetRenderState(D3DRS_ZENABLE,FALSE);	
		D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);	
		
		CRect rect;
		rect.SetSize(4.0f, 4.0f);

		rect.SetTexture( (TEXTUREFACTORY->getTexture(TEXKEY::TANK_EXPLOAD()))->getTexture());
		rect.SetUV(0,D3DXVECTOR2(_SpriteExpload->getAnimeParam()->getUV().left / 384.0f , _SpriteExpload->getAnimeParam()->getUV().top / 64.0f  ));
		rect.SetUV(1,D3DXVECTOR2(_SpriteExpload->getAnimeParam()->getUV().right / 384.0f, _SpriteExpload->getAnimeParam()->getUV().top / 64.0f  ));
		rect.SetUV(2,D3DXVECTOR2(_SpriteExpload->getAnimeParam()->getUV().left / 384.0f , _SpriteExpload->getAnimeParam()->getUV().bottom/ 64.0f));
		rect.SetUV(3,D3DXVECTOR2(_SpriteExpload->getAnimeParam()->getUV().right / 384.0f, _SpriteExpload->getAnimeParam()->getUV().bottom/ 64.0f));

		rect.Draw();
		*/

		D3DXMATRIXA16 scale;
		D3DXMATRIXA16 mat2;
		D3DXMatrixIdentity(&scale);
		D3DXMatrixScaling(&scale,1.0f / 16.0f,1.0f / 16.0f,1.0f / 16.0f);
		D3DXMatrixIdentity(&mat2);

		billboard(&mat2,_pTankBottom->getWMat());

		D3DXMATRIXA16 rot;
		D3DXMatrixIdentity(&rot);
		D3DXMatrixRotationZ(&rot,D3DXToRadian(180.0f));

		D3DXMATRIXA16 trance = mat2;
		mat2._41 = mat2._42 = mat2._43 = 0;
		mat2 *= scale;
		mat2._41 = trance._41;
		mat2._42 = trance._42 + 1.0f;
		mat2._43 = trance._43;
		_SpriteExpload->draw(D3DXSPRITE_ALPHABLEND,&mat2,CCamera::getMatView());
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


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
void CTank::setPos(const float x,const float z)
{
	_pTankBottom->setPos(x,z);
	const D3DXMATRIXA16* pMatTank = _pTankBottom->getWMat();
	_pTankTop->setPos(
		pMatTank->_41,
		pMatTank->_42,
		pMatTank->_43
		);
}

void CTank::rotationY(const float fY)
{
	_pTankBottom->rotationsetY(fY);
	_pTankTop->rotationy(fY);
}
