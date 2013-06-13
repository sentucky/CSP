#include"CAnimeSprite.h"

#include"CTexture.h"


CAnimeSprite::CAnimeSprite(CTexture* pTexture,const char* FilePath)
	:CSprite(pTexture),
	_AnimeParam(FilePath)
{
}

CAnimeSprite::~CAnimeSprite()
{
}

void CAnimeSprite::update()
{
	const uint before = _AnimeParam.getCat();

	_AnimeParam.update();

	if(before != _AnimeParam.getCat())
	{
		RECTEX& UV = _AnimeParam.getUV();

		_UV = UV;
	}
}



const uint CAnimeSprite::animeState()
{
	return _AnimeParam.getState();
}


