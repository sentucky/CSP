#ifndef ___CANIMEPARAM___
#define ___CANIMEPARAM___

#include"common.h"

class ANIMEPATH;

struct FrameData
{
	uint	FrameCnt;
	RECTEX	UV;
};

enum ANIME_STATE
{
	PLAY,
	STOP,
	PLAY_LOOP,
};

class CAnimeParam
{
public:
	CAnimeParam(ANIMEPATH& APath);
	~CAnimeParam();
	void update();

	const uint getCat()		{return _Cat;}
	const uint getState()	{return _State;}
	RECTEX& getUV()			{return _frameData[_Cat].UV;}

	void setCat(const uint Cat);
	void setState(const uint State){_State = State;}
private:
	FrameData* _frameData;
	uint _Cat;
	uint _Cnt;
	uint _State;
	uint _MaxCat;
};

#endif