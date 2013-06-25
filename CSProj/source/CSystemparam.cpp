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

#include"CObjMng.h"
#include"CTaskMng.h"
#include"CTaskList.h"
#include"CSpriteFactory.h"
#include"CSprite.h"

#include<algorithm>


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSystemparam::CSystemparam()
	:CObjBase(OBJGROUPKEY::GAMESYSTEM()),
	_flgRaceResult(0),
	_Sprite(NULL),
	_playerTank(NULL),
	_TaskList(NULL),
	_TaskEndCheck(NULL),
	_TaskDrawResult(NULL)
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
	_Sprite(NULL),
	_playerTank(NULL),
	_TaskList(NULL),
	_TaskEndCheck(NULL),
	_TaskDrawResult(NULL)
{
	TankList = OBJMNG->getList(OBJGROUPKEY::TANK());
	enableTask();
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
		&CSystemparam::run,
		&_TaskList);
	CTaskMng::push<CSystemparam>(
		TASKKEY::SYSTEMPARAM(),
		this,
		&CSystemparam::endcheck,
		&_TaskEndCheck);
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
	CTaskMng::erase(&_TaskEndCheck);
	CTaskMng::erase(&_TaskDrawResult);
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


	_Camera->setTank(pTank);
	_Camera->setNAtToEye(1.0f,0.5f,1.0f);

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

	CTaskMng::erase(&_TaskEndCheck);
	if(_flgRaceResult == 1)	_Sprite = SPRITEFACTORY->create(TEXKEY::WIN());
	else					_Sprite = SPRITEFACTORY->create(TEXKEY::LOSE());
	

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSystemparam::run()
{
	const uint size = TankList->size();

	CTank* pArray[512] = {0,};


	CListItem<CObjBase*>* run = TankList->begin();

	uint n;

	for(n = 0; n < size; n++)
	{
		pArray[n] = static_cast<CTank*>(run->getInst());
		run = run->next();
	}

	std::sort(pArray,pArray + size,CTank::lower);

	for(n = 0; n < size; n++)
	{
		pArray[n]->setRank(n+1);
	}
}

void CSystemparam::drawResult()
{
	D3DXVECTOR3 _pos(400,320,0);
	D3DXVECTOR3 _scale(1,1,1);
	D3DXVECTOR3 _rot(0,0,0);
	_Sprite->draw(0,&_pos,&_rot,&_scale);
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

	//	ÉSÅ[ÉãÇµÇΩêÌé‘ÇÃíÜÇ…éûä˙Ç™Ç†ÇÍÇŒÇªÇÃéûÇÃèàóù
	if(sumGoals > 0)
	{//	ÉSÅ[ÉãÇµÇΩÉ^ÉìÉNÇ†ÇË
		_flgRaceResult = 2;
		*GoalTank = pTankGoals[0];
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
		return TRUE;
	}
	if(sumTanks <= 1)
	{
		if(sumTanks == 0)
		{///	ìØéûåÇîj
			_flgRaceResult = 2;
		}
		else
		{
			*DestroyerTank = static_cast<CTank*>(begin->getInst());
			_flgRaceResult = 1;
		}
		return TRUE;
	}
	return FALSE;
}
