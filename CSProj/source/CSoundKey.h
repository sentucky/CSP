#ifndef ___SOUNDKEY___
#define ___SOUNDKEY___

#include"common.h"

class SOUNDKEY
{
public:
	static const uint GAMEBGM();
	static const uint LOSEBGM();
	static const uint TITLEBGM();
	static const uint COLLISION();
	static const uint FANFARE();
	static const uint MOVE();
	static const uint FIRE();
	static const uint SIREN();


	static const uint SUM();
};

class SOUNDPATH
{
public:
	static char* GAMEBGM();
	static char* LOSEBGM();
	static char* TITLEBGM();
	static char* COLLISION();
	static char* FANFARE();
	static char* MOVE();
	static char* FIRE();
	static char* SIREN();
};

#endif