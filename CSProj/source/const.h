/***********************************************************************/
/*! @file  const.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CONST___
#define ___CONST___

#include"common.h"

class STAGEPATH
{
public:
	static const char* NO_01();
};

class MESHPATH
{
public:
	static const char* SHELL01();
	static const char* SHELL02();
	static const char* SHELL03();
	static const char* PIN();
	static const char* YUKA();
	static const char* STAGE01();
	static const char* TANK01_TOP();
	static const char* TANK02_TOP();
	static const char* TANK03_TOP();
	static const char* TANK04_TOP();
	static const char* TANK01_BOTTOM();
	static const char* TANK02_BOTTOM();
	static const char* TANK03_BOTTOM();
	static const char* TANK04_BOTTOM();
};

class TEXPATH
{
public:
	static const char* FADEMASK();
	static const char* TILE01();
	static const char* TILE02();
	static const char* TILE03();
	static const char* TILE04();
	static const char* TILE05();
	static const char* TILE06();
};

class TEXKEY
{
public:
	static const uint FADEMASK();
	static const uint TILE01();
	static const uint TILE02();
	static const uint TILE03();
	static const uint TILE04();
	static const uint TILE05();
	static const uint TILE06();
	static const uint SUM();
};

class MESHKEY
{
public:
	
	static const uint YUKA();
	static const uint STAGE01();
	static const uint TANK01_TOP();
	static const uint TANK02_TOP();
	static const uint TANK03_TOP();
	static const uint TANK04_TOP();
	static const uint TANK01_BOTTOM();
	static const uint TANK02_BOTTOM();
	static const uint TANK03_BOTTOM();
	static const uint TANK04_BOTTOM();
	static const uint PIN();
	static const uint SHELL01();
	static const uint SHELL02();
	static const uint SHELL03();
	static const uint SUM();
};

class EFFECTPATH
{
public:
	static const char* NONE();
	static const char* TOON();
};


class TASKKEY
{
public:
	static const uint HITTEST_TANKADNTANK();
	static const uint HITTEST_TANKANDSHELL();
	static const uint HITTEST_TANKANDWALL();

	static const uint CHECKALIVE();
	static const uint INTELLIGENCE();
	static const uint UPDATECAMERA();
	static const uint EXPLOSION();
	static const uint FIRE();
	static const uint PAUSE();
	static const uint MOVE();
	static const uint DRAW();
	static const uint SUM();
};




class OBJKEY
{
public:
	static const uint HITTEST();
	static const uint SHELL01();
	static const uint SHELL02();
	static const uint SHELL03();
	static const uint PIN();
#ifdef _DEBUG
	static const uint TANKDUMMY();
#endif
	static const uint TANK01();
	static const uint TANK02();
	static const uint TANK03();
	static const uint TANK04();
	static const uint STAGE01();
	static const uint FOLLOW();
	static const uint SUM();
};

class OBJGROUPKEY
{
public:
	static const uint TANK();
	static const uint HITTEST();
	static const uint SHELL();
	static const uint STAGE();
	static const uint FOLLOW();
	static const uint PIN();
	static const uint SUM();
};

#endif