#ifndef ___ANIMEKEY___
#define ___ANIMEKEY___

#include"common.h"

#include <cstdio>

class ANIMEKEY
{
private:
	ANIMEKEY(const uint n);
public:
	static ANIMEKEY& TEST();

	const uint operator=(ANIMEKEY& src);
private:
	const uint Key;
};

class ANIMEPATH
{
public:
	ANIMEPATH(const char* path);
	static ANIMEPATH& TEST();

	const char* getPath(){return Path;}
private:
	const char* Path;
};

#endif