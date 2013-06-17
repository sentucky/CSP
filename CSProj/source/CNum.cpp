#include"CNum.h"

#include"TextureKey.h"

#include"CSprite.h"
#include"CSpriteFactory.h"

#include"CTaskList.h"
#include"CTaskMng.h"


//	�ÓI�����o������
CSprite* CNum::_NumSprite[10] = {0,};

CNum::CNum()
	:_TaskDraw(NULL),
	_Num(0),
	_xlen(0),
	_Pos(0,0,0),
	_Rot(0,0,0),
	_Scale(1,1,1),
	_DrawMode(POINT_LEFT),
	_flgProto(TRUE)
{
	ZeroMemory(_NumSprite,sizeof(_NumSprite));

#ifdef _DEBUG
	static int checker = 0;
	if(checker > 0 )
		MessageAlert("�Ԉ�����g�������Ă܂�","warning from CNum::CNum");

	checker++;
#endif
	if(_NumSprite[0] == 0)
	{
		CSpriteFactory* Factory = SPRITEFACTORY;
		_NumSprite[0] = Factory->create(TEXKEY::NUM0());
		_NumSprite[1] = Factory->create(TEXKEY::NUM1());
		_NumSprite[2] = Factory->create(TEXKEY::NUM2());
		_NumSprite[3] = Factory->create(TEXKEY::NUM3());
		_NumSprite[4] = Factory->create(TEXKEY::NUM4());
		_NumSprite[5] = Factory->create(TEXKEY::NUM5());
		_NumSprite[6] = Factory->create(TEXKEY::NUM6());
		_NumSprite[7] = Factory->create(TEXKEY::NUM7());
		_NumSprite[8] = Factory->create(TEXKEY::NUM8());
		_NumSprite[9] = Factory->create(TEXKEY::NUM9());
		_xlen = static_cast<float>(_NumSprite[0]->getTextureInfo()->Width);
		for(int i = 0; i < 10;++i)
		{
			_NumSprite[i]->setCenter(0,0,0);
		}
	}
}

CNum::~CNum()
{
	releaseSprite();
}

CNum::CNum(const CNum& src)
	:_TaskDraw(NULL),
	_Num(0),
	_xlen(src._xlen),
	_Pos(0,0,0),
	_Rot(0,0,0),
	_Scale(1,1,1),
	_DrawMode(POINT_LEFT),
	_flgProto(TRUE)
{

}


void CNum::releaseSprite()
{
	if(_flgProto == TRUE)
		for(int i = 0; i < 10; ++i)
			SAFE_DELETE(_NumSprite[i]);
}

void CNum::enableTask()
{
	CTaskMng::push<CNum>(
		TASKKEY::DRAW(),
		this,
		&CNum::draw,
		&_TaskDraw);
}

void CNum::disableTask()
{
	CTaskMng::erase(&_TaskDraw);
}

void CNum::draw()
{
	switch(_DrawMode)
	{
	case POINT_RIGHT:
		DMR();
		break;
	case POINT_LEFT:
		DML();
		break;
	}
}


void CNum::DMR()
{
	const float BakX = _Pos.x;
	_Pos.x -= _xlen;
	if(_Num == 0)
	{
		_NumSprite[0]->draw(
			0,
			&_Pos,
			&_Rot,
			&_Scale);
	}
	else
	{
		int work = _Num;

		for(int i = 0; i < 10; ++i)
		{
			_NumSprite[work % 10]->draw(
				0,
				&_Pos,
				&_Rot,
				&_Scale);


			work /= 10;
			if(work == 0)
				break;
			_Pos.x -= _xlen;
		}
	}
	_Pos.x = BakX;
}

void CNum::DML()
{
	if(_Num == 0)
	{
		_NumSprite[0]->draw(
			0,
			&_Pos,
			&_Rot,
			&_Scale);
		return;
	}
	else
	{
		int work = _Num;
		const float BakX = _Pos.x;

		int keta = 0;
		for(int n = 10; work / n > 0; n *= 10)
		{
			++keta;
		}
		_Pos.x += keta * _xlen;
		for(int i = 0; i < 10; ++i)
		{
			_NumSprite[work % 10]->draw(
				0,
				&_Pos,
				&_Rot,
				&_Scale);

			_Pos.x -= _xlen;


			work /= 10;
			if(work == 0)
				break;
		}
		_Pos.x = BakX;
	}
}

void CNum::addNum(const int num)
{
	_Num += num;
	_Num = _Num >= 0 ? _Num : 0;
}

void CNum::setNum(const int num)
{
	_Num = num;
	_Num = _Num >= 0 ? _Num : 0;
}


void CNum::transPos(const float x, const float y, const float z)
{
	_Pos.x += x;
	_Pos.y += y;
	_Pos.z += z;
}

void CNum::setPos(D3DXVECTOR3& pos)
{
	_Pos.x = pos.x;
	_Pos.y = pos.y;
	_Pos.z = pos.z;
}
