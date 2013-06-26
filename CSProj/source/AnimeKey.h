/***********************************************************************/
/*! @file  AnimeKey.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___ANIMEKEY___
#define ___ANIMEKEY___

#include"common.h"

#include <cstdio>


class ANIMEPATH
{
public:
	ANIMEPATH(const char* path);
	static ANIMEPATH& TEST();
	static ANIMEPATH& SMOKE();
	static ANIMEPATH& SPARK();
	static ANIMEPATH& BARN();

	const char* getPath(){return Path;}
private:
	const char* Path;
};

#endif