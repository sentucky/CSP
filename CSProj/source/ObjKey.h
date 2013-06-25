#ifndef ___OBJKEY___
#define ___OBJKEY___

#include"ObjKey.h"
#include"const.h"

class OBJKEY
{
public:
	static const uint GOALCHECK();
	static const uint COCKPIT();
	static const uint SYSTEMPARAM();
	static const uint HITTESTTTOT();
	static const uint HITTESTTTOS();
	static const uint HITTESTTTOW();
	static const uint SHELL01();
	static const uint SHELL02();
	static const uint SHELL03();
	static const uint PIN();
	static const uint TANKDUMMY();
	static const uint TANK01();
	static const uint TANK02();
	static const uint TANK03();
	static const uint TANK04();
	static const uint STAGE01();
	static const uint STARTCAMERA();
	static const uint FOLLOWCAMERA();
	static const uint NUM();
	static const uint SUM();
};


class OBJGROUPKEY
{
public:
	static const uint GAMESYSTEM();
	static const uint COCKPIT();
	static const uint TANK();
	static const uint HITTEST();
	static const uint SHELL();
	static const uint STAGE();
	static const uint CAMERA();
	static const uint PIN();
	static const uint NUM();
	static const uint SUM();
};

#endif