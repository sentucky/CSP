/***********************************************************************/
/*! @file  CSystemparam.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CSystemparam.h"

#include"const.h"
#include"ObjKey.h"
#include"TextureKey.h"

#include"CTank.h"
#include"CFollowCamera.h"
#include"CStartCamWork.h"

#include"CObjMng.h"
#include"CTaskMng.h"
#include"CTaskList.h"
#include"CSpriteFactory.h"
#include"CSprite.h"


#include<algorithm>


int CSystemparam::_MaxGoalCount = 300;

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSystemparam::CSystemparam()
	:CObjBase(OBJGROUPKEY::GAMESYSTEM()),
	_flgRaceResult(0),
	_flgEnd(FALSE),
	_Sprite(NULL),
	_playerTank(NULL),
	_TaskList(NULL),
	_TaskEndCount(NULL),
	_TaskEndCheck(NULL),
	_TaskStartCheck(NULL),
	_TaskDrawResult(NULL),
	_TaskDrawStart(NULL),
	_goalCount(_MaxGoalCount)
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSystemparam::~CSystemparam()
{
	disableTask();
	SAFE_DELETE(_Sprite);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] src 
 *  @retval  
 */
/***********************************************************************/
CSystemparam::CSystemparam(const CSystemparam& src)
	:CObjBase(OBJGROUPKEY::GAMESYSTEM()),
	_flgRaceResult(0),
	_flgEnd(FALSE),
	_Sprite(NULL),
	_playerTank(NULL),
	_TaskEndCount(NULL),
	_TaskList(NULL),
	_TaskEndCheck(NULL),
	_TaskStartCheck(NULL),
	_TaskDrawResult(NULL),
	_TaskDrawStart(NULL),
	_goalCount(_MaxGoalCount)
{
	TankList = OBJMNG->getList(OBJGROUPKEY::TANK());
	D3DXMatrixIdentity(&_spriteMatrix);
	_spriteMatrix._41 = 400;
	_spriteMatrix._42 = 320;
	enableTask();
	_Sprite = SPRITEFACTORY->create(TEXKEY::READY());
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::enableTask()
{
	CTaskMng::push<CSystemparam>(
		TASKKEY::RANKING(),
		this,
		&CSystemparam::Ranking,
		&_TaskList);
	CTaskMng::push<CSystemparam>(
		TASKKEY::SYSTEMPARAM(),
		this,
		&CSystemparam::endcheck,
		&_TaskEndCheck);
	CTaskMng::push<CSystemparam>(
		TASKKEY::DRAW(),
		this,
		&CSystemparam::drawStart,
		&_TaskDrawStart);
	CTaskMng::push<CSystemparam>(
		TASKKEY::SYSTEMPARAM(),
		this,
		&CSystemparam::startcheck,
		&_TaskStartCheck);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::disableTask()
{
	CTaskMng::erase(&_TaskList);
	CTaskMng::erase(&_TaskEndCount);
	CTaskMng::erase(&_TaskEndCheck);
	CTaskMng::erase(&_TaskStartCheck);
	CTaskMng::erase(&_TaskDrawResult);
	CTaskMng::erase(&_TaskDrawStart);
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::endCount()
{
	--_goalCount;

	_flgEnd = _goalCount <= 0 ? TRUE : FALSE;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::endcheck()
{
	CListMng<CObjBase*>*TankList = OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>* pItem = TankList->begin();
	const CListItem<CObjBase*>* pEnd = TankList->end();

	CTank* pTank;
	if(!endcheckGoal(&pTank,pItem,pEnd) && !endcheckDestroy(&pTank,pItem,TankList->size()))
	{
		return;
	}


	_FollowCamera->setTank(pTank);
	_FollowCamera->setNAtToEye(1.0f,0.5f,1.0f);

	//	ÉåÅ[ÉXèIóπ
	pItem = TankList->begin();
	while(pItem != pEnd)
	{
		pTank = static_cast<CTank*>(pItem->getInst());

		pTank->raceEnd();

		pItem = pItem->next();
	}
	CTaskMng::push<CSystemparam>(
		TASKKEY::DRAW(),
		this,
		&CSystemparam::drawResult,
		&_TaskDrawResult);

	CTaskMng::push(TASKKEY::SYSTEMPARAM(),
		this,
		&CSystemparam::endCount,
		&_TaskEndCount);

	CTaskMng::erase(&_TaskEndCheck);
	SAFE_DELETE(_Sprite);
	if(_flgRaceResult == 1)	_Sprite = SPRITEFACTORY->create(TEXKEY::VICTORY());
	else					_Sprite = SPRITEFACTORY->create(TEXKEY::LOSE());
	

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::Ranking()
{
	memset(_Ranking,0,sizeof(_Ranking));


	CListItem<CObjBase*>* run = TankList->begin();
	CListItem<CObjBase*>* end = TankList->end();

	uint n = 0;

	CTank* pTank;

	while(run != end)
	{
	 	pTank = static_cast<CTank*>(run->getInst());
		if(!pTank->getDestroyed())
		{
			_Ranking[n] = pTank;
			n++;
		}
		run = run->next();
	}


	std::sort(_Ranking,_Ranking + n,CTank::lower);

	const uint Sum = n;

	for(n = 0; n < Sum; n++)
	{
		_Ranking[n]->setRank(n);
	}
}

void CSystemparam::drawResult()
{
	_Sprite->draw(0,&_spriteMatrix);
}

void CSystemparam::drawStart()
{	
	_Sprite->draw(
		0,
		&_spriteMatrix
		);
}

void CSystemparam::switchGame()
{
	_FollowCamera->enableTask();
	_FollowCamera->update();

	//	êÌé‘ÇìÆÇ©ÇπÇÈÇÊÇ§Ç…Ç∑ÇÈ
	CListMng<CObjBase*>*TankList =  OBJMNG->getList(OBJGROUPKEY::TANK());
	CListItem<CObjBase*>* pItem = TankList->begin();
	CListItem<CObjBase*>* pEnd = TankList->end();
	CTank* pTank;

	while(1)
	{
		pTank = static_cast<CTank*>(pItem->getInst());
		pTank->enableTask();
		pItem = pItem->next();
		if(pItem == pEnd)
		{
			break;
		}
	}
}

BOOL CSystemparam::endcheckGoal(CTank** GoalTank,CListItem<CObjBase*>* begin,const CListItem<CObjBase*>* end)
{
	CTank* pTank;

	static const uint MaxSize = 1024;
	CTank* pTankGoals[MaxSize]={0,};
	uint sumGoals = 0;

	CListItem<CObjBase*>* pItem = begin;
	//	ÉSÅ[ÉãÇµÇΩêÌé‘ÇíTÇ∑
	while(pItem != end)
	{
		pTank = static_cast<CTank*>(pItem->getInst());


		if(pTank->getFlgGoal() == TRUE )
		{
			pTankGoals[sumGoals] = pTank;
			if(pTank->getTankType() == CTank::TYPE_PLAYER)
			{
				_flgRaceResult = 1;
				*GoalTank = pTank;
				SAFE_DELETE(_Sprite);
				_Sprite = SPRITEFACTORY->create(TEXKEY::VICTORY());
				return TRUE;
			}
			++sumGoals;
			if(sumGoals > MaxSize)
			{
				break;
			}
		}

		pItem = pItem->next();

	}

	if(sumGoals > 0)
	{//	ÉSÅ[ÉãÇµÇΩÉ^ÉìÉNÇ†ÇË
		_flgRaceResult = 2;
		*GoalTank = pTankGoals[0];
		SAFE_DELETE(_Sprite);
		_Sprite = SPRITEFACTORY->create(TEXKEY::LOSE());
		return TRUE;
	}
	return FALSE;
}


BOOL CSystemparam::endcheckDestroy(CTank** DestroyerTank,CListItem<CObjBase*>* begin,const uint sumTanks)
{
	//	é©ã@Ç™åÇîjÇ≥ÇÍÇƒÇ¢ÇΩÇÁèIóπ
	if(_playerTank->getDestroyed())
	{
		_flgRaceResult = 2;
		*DestroyerTank = _playerTank;
		SAFE_DELETE(_Sprite);
		_Sprite = SPRITEFACTORY->create(TEXKEY::LOSE());
		return TRUE;
	}
	if(sumTanks <= 1)
	{
		if(sumTanks == 0)
		{///	ìØéûåÇîj
			SAFE_DELETE(_Sprite);
			_Sprite = SPRITEFACTORY->create(TEXKEY::LOSE());
			_flgRaceResult = 2;
		}
		else
		{
			*DestroyerTank = static_cast<CTank*>(begin->getInst());
			SAFE_DELETE(_Sprite);
			_Sprite = SPRITEFACTORY->create(TEXKEY::VICTORY());
			_flgRaceResult = 1;
		}
		return TRUE;
	}
	return FALSE;
}

void CSystemparam::startcheck()
{
	if(_CamStart == NULL)
	{
		--_startCount;
		if(_startCount <= 0)
		{
			CTaskMng::erase(&_TaskDrawStart);
			CTaskMng::erase(&_TaskStartCheck);
			
			CListItem<CObjBase*>* run = TankList->begin();
			CListItem<CObjBase*>* end = TankList->end();

			uint n = 0;

			CTank* pTank;

			while(run != end)
			{
				static_cast<CTank*>(run->getInst())->enableTask();
				run = run->next();
			}

		}
	}
	else if(_CamStart->getDeleteFlg() == TRUE)
	{
		_CamStart = NULL;
		switchGame();
		SAFE_DELETE(_Sprite);
		_Sprite = SPRITEFACTORY->create(TEXKEY::GO());
		_startCount = MaxStartCount;
	}
}