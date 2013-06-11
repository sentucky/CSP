#include"CHitTestTankToWall.h"

#include"CTank.h"

#include"CTaskList.h"
#include"CTaskMng.h"
#include"CObjMng.h"
#include"CObjBase.h"
#include"CListMng.h"
#include"CListItem.h"
#include"StageData.h"

CListMng<CObjBase*>* CHitTestTankToWall::_pTankList = NULL;
const CStageData*			 CHitTestTankToWall::_StageData = NULL;
CHitTestTankToWall::CHitTestTankToWall()
	:_pHitTestTask(NULL)
{
}

CHitTestTankToWall::~CHitTestTankToWall()
{
	disableTask();
}

CHitTestTankToWall::CHitTestTankToWall(const CHitTestTankToWall& src)
	:_pHitTestTask(NULL)
{
	enableTask();
}

void CHitTestTankToWall::enableTask()
{
	CTaskMng::push<CHitTestTankToWall>(
		TASKKEY::HITTEST_TANKTOWALL(),
		this,
		&CHitTestTankToWall::hitTest,
		&_pHitTestTask);
}

void CHitTestTankToWall::disableTask()
{
	CTaskMng::erase(&_pHitTestTask);
}

void CHitTestTankToWall::hitTest()
{
	CListItem<CObjBase*>* run = _pTankList->begin();	
	const CListItem<CObjBase*>* end = _pTankList->end();
	CTank* pTank = NULL;
	D3DXVECTOR3 NewV(0,0,0);

	while(run != end)
	{
		pTank = static_cast<CTank*>(run->getInst());


		if(pTank->getDestroyed())
		{
			run = run->next();
			continue;
		}

		//	—§‚Á‚Ä‚¢‚éêŠ‚ð’m‚é
		const float tx = pTank->getMatBottom()->_41;
		const float ty = pTank->getMatBottom()->_43;
		const float tx2 = tx + pTank->getMoveVec()->x;
		const float ty2 = ty + pTank->getMoveVec()->z;

		uint x,y;
		_StageData->step(&x,&y,tx,ty);


		//	•Ç‚Ìî•ñ‚ðŽæ“¾
		RECT WallFlg;
		_StageData->wallFlg(&WallFlg,x,y);

		const TILE tile[MAX_DATA][MAX_DATA];
		_StageData->getTile(tile);

		/*
		float hitX;
		float hitY;
		//*/
		const float f = 500.0f / 16.0f * 0.5f;

		const float top		= tile[x][y].posY + f - 1.0f;
		const float left	= tile[x][y].posX - f + 1.0f;
		const float bottom	= tile[x][y+1].posY +  f + 1.0f;
		const float right	= tile[x+1][y].posX -  f - 1.0f;



		NewV.x = NewV.y = NewV.z = 0;
		//	top
		if(WallFlg.top)
		{
			if(top < ty)
			{
				pTank->setPos(tx,top );
				NewV.x = pTank->getMoveVec()->x;
				NewV.z = -pTank->getMoveVec()->z;
				pTank->setMoveVec(NewV);
			}
		}
		//	left
		if(WallFlg.left)
		{
			if(left > tx)
			{
				pTank->setPos(left,ty);
				NewV.x = -pTank->getMoveVec()->x;
				NewV.z = pTank->getMoveVec()->z;
				pTank->setMoveVec(NewV);
			}
		}
		//	bottom
		if(WallFlg.bottom)
		{
			if( bottom >= ty2 && bottom <= ty)
			{
				pTank->setPos(tx,bottom);
				NewV.x = pTank->getMoveVec()->x;
				NewV.z = -pTank->getMoveVec()->z;
				pTank->setMoveVec(NewV);
			}
		}
		//	right
		if(WallFlg.right)
		{
			if( right <= tx2 && right >= tx)
			{
				pTank->setPos(right,ty);
				NewV.x = -pTank->getMoveVec()->x;
				NewV.z = pTank->getMoveVec()->z;
				pTank->setMoveVec(NewV);
			}
		}

		//	“–‚½‚Á‚Ä‚¢‚é‚©Šm”F
		pTank->hitTestWall();

		run = run->next();
	}
}
