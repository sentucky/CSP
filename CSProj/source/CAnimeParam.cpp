#include"CAnimeParam.h"
#include"AnimeKey.h"

CAnimeParam::CAnimeParam(ANIMEPATH& key)
	:_frameData(NULL),
	_Cat(0),
	_Cnt(0),
	_State(STOP),
	_MaxCat(0)
{
	FILE* fp;
	const char* szkey = key.getPath();
	fp = fopen(szkey,"rb");

	const uint MAXCAT = 256;

	fread(&_MaxCat,sizeof(int),1,fp);
	if(_MaxCat > MAXCAT)
	{
		MessageAlert("‘ƒJƒbƒg”‚ª‘½‚·‚¬‚Ü‚·\n256ˆÈ‰º‚É‚µ‚Ä‚­‚¾‚³‚¢","error form CAnimeParam::CAnimeParam");
		fclose(fp);
		return;
	}
	_frameData = new FrameData[_MaxCat];
	fread(_frameData,sizeof(FrameData),_MaxCat,fp);

	fclose(fp);
}
CAnimeParam::~CAnimeParam()
{
	SAFE_DELETE_ARRAY(_frameData);
}
void CAnimeParam::update()
{
	if(_State == STOP)
		return;

	if(_Cnt > _frameData[_Cat].FrameCnt)
	{
		++_Cat;
		if(_Cat >= _MaxCat)
		{
			if(_State == PLAY_LOOP)
			{
				_Cat = 0;
				_Cnt = 0;
			}
			else
			{
				_State = STOP;
			};
		}
		_Cnt = 0;
		return;
	}
	++_Cnt;
}	
void CAnimeParam::setCat(const uint Cat)
{
	_Cat = Cat;
}