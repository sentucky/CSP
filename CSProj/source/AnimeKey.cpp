#include"AnimeKey.h"



ANIMEPATH::ANIMEPATH(const char* path):Path(path){}


ANIMEPATH ANIMEPATH::TEST()	{	return ANIMEPATH("data/animeparam/data2.dat");	}
ANIMEPATH ANIMEPATH::SMOKE()	{	return ANIMEPATH("data/animeparam/kemuri.dat");	}
ANIMEPATH ANIMEPATH::SPARK()	{	return ANIMEPATH("data/animeparam/hibana.dat");	}
ANIMEPATH ANIMEPATH::BARN()	{	return ANIMEPATH("data/animeparam/burn.dat");}
ANIMEPATH ANIMEPATH::TANK()	{	return ANIMEPATH("data/animeparam/tank.dat");}

