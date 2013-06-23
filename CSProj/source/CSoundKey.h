#ifndef ___SOUNDKEY___
#define ___SOUNDKEY___

#include"common.h"

class SOUNDKEY
{
public:
	static const uint BGM1();
	static const uint COLLITANKTOTANK();
	static const uint ENGILE();
	static const uint FIRE();
	static const uint HITSHELL();
	static const uint FANFARE();
	static const uint START();

	static const uint SUM();
};

class SOUNDPATH
{
public:
	static char* BGM1();
	static char* COLLITANKTOTANK();
	static char* ENGILE();
	static char* FIRE();
	static char* HITSHELL();
	static char* FANFARE();
	static char* START();
};

#endif