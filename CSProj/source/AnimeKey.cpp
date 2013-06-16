#include"AnimeKey.h"

enum eANIMEKEY
{
	ANIMEKEY_TEST,
	ANIMEKEY_SUM
};



ANIMEKEY::ANIMEKEY(const uint n):Key(n){}

ANIMEKEY& ANIMEKEY::TEST()
{
	static ANIMEKEY Param(ANIMEKEY_TEST);
	return Param;
}

const uint ANIMEKEY::operator=(ANIMEKEY& src){return src.Key;}

ANIMEPATH::ANIMEPATH(const char* path):Path(path){}


ANIMEPATH& ANIMEPATH::TEST()
{
	static ANIMEPATH Param("data/animeparam/data2.dat");
	return Param;
}

