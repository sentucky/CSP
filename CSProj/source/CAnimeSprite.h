#ifndef ___CANIMESPRITE___
#define ___CANIMESPRITE___

#include"CSprite.h"
#include"CAnimeParam.h"

class CTexture;

class CAnimeSprite:public CSprite
{
public:
	CAnimeSprite(CTexture* pTexture,const char* FilePath);
	CAnimeSprite(const CAnimeSprite& src);
	~CAnimeSprite();
	const uint animeState();
private:
	void update();
	CAnimeParam _AnimeParam;
};







#endif 

