/***********************************************************************/
/*! @file  const.cpp
 *  @brief íËêî
 *  
 *  @author êÏå¥Å@óCâÓ
 *  @date 
 */
/***********************************************************************/
#include"const.h"

const char* STAGEPATH::NO_01(){return "data/stage/stageData00.dat";}

#ifdef _DEBUG
const char* MESHPATH::RING(){			return "data/model/donuts.x";		}
#endif
const char* MESHPATH::DOME(){			return "data/model/karidome.x";}
const char* MESHPATH::SHELL01(){		return "data/model/tama.x";		}
const char* MESHPATH::SHELL02(){		return "data/model/pin.x";		}
const char* MESHPATH::SHELL03(){		return "data/model/pin.x";		}
const char* MESHPATH::PIN(){			return "data/model/pin.x";		}
const char* MESHPATH::YUKA(){			return "data/model/nanase_pose.x";		}
const char* MESHPATH::STAGE01(){		return "data/model/land2.x";		}
const char* MESHPATH::TANK01_TOP(){		return "data/model/ziki_Lv1_up.x";		}
const char* MESHPATH::TANK02_TOP(){		return "data/model/tekki_lv1_up.x";		}
const char* MESHPATH::TANK03_TOP(){		return "data/model/tank03_top.x";		}
const char* MESHPATH::TANK04_TOP(){		return "data/model/tank04_top.x";		}
const char* MESHPATH::TANK01_BOTTOM(){	return "data/model/ziki_Lv1_down.x";	}
const char* MESHPATH::TANK02_BOTTOM(){	return "data/model/tekki_lv1_down.x";	}
const char* MESHPATH::TANK03_BOTTOM(){	return "data/model/tank03_bottom.x";	}
const char* MESHPATH::TANK04_BOTTOM(){	return "data/model/tank04_bottom.x";	}




enum eMESHKEY
{
	MESH_PIN,			//
	MESH_DOME,			//
	MESH_SHELL01,		//
	MESH_SHELL02,		//
	MESH_SHELL03,		//
	MESH_YUKA,			//
#ifdef _DEBUG
	MESH_RING,			//
#endif
	MESH_STAGE01,		//
	MESH_TANK01_TOP,	//
	MESH_TANK02_TOP,	//
	MESH_TANK03_TOP,	//
	MESH_TANK04_TOP,	//
	MESH_TANK01_BOTTOM,	//
	MESH_TANK02_BOTTOM,	//
	MESH_TANK03_BOTTOM,	//
	MESH_TANK04_BOTTOM,	//
	MESH_SUM,			//
};

#ifdef _DEBUG
const uint MESHKEY::RING()			{	return MESH_RING;			}
#endif
const uint MESHKEY::DOME()			{	return MESH_DOME;			}
const uint MESHKEY::SHELL01()		{	return MESH_SHELL01;		}
const uint MESHKEY::PIN()			{	return MESH_PIN;			}
const uint MESHKEY::YUKA()			{	return MESH_YUKA;			}
const uint MESHKEY::STAGE01()		{	return MESH_STAGE01;		}
const uint MESHKEY::TANK01_TOP()	{	return MESH_TANK01_TOP;		}
const uint MESHKEY::TANK02_TOP()	{	return MESH_TANK02_TOP;		}
const uint MESHKEY::TANK03_TOP()	{	return MESH_TANK03_TOP;		}
const uint MESHKEY::TANK04_TOP()	{	return MESH_TANK04_TOP;		}
const uint MESHKEY::TANK01_BOTTOM()	{	return MESH_TANK01_BOTTOM;	}
const uint MESHKEY::TANK02_BOTTOM()	{	return MESH_TANK02_BOTTOM;	}
const uint MESHKEY::TANK03_BOTTOM()	{	return MESH_TANK03_BOTTOM;	}
const uint MESHKEY::TANK04_BOTTOM()	{	return MESH_TANK04_BOTTOM;	}
const uint MESHKEY::SUM()			{	return MESH_SUM;			}

const char* EFFECTPATH::NONE(){return "a";}
const char* EFFECTPATH::TOON(){return "A";}


enum eTID
{
	TID_STARTCAMMOVE,			//
	TID_SYSTEMPARAM,			//
	TID_TANKSETPSET,			//
	TID_COCKPIT,				//
	TID_INTELLIGENCE,			//
	TID_RAP,					//
	TID_FIRE,					//
	TID_PAUSE,					//
	TID_CALCACTIVEMOVE,			//
	TID_HITTEST_TANK_AND_TANK,	//
	TID_HITTEST_TANK_TO_SHELL,	//
	TID_HITTEST_WALL,			//
	TID_MOVE,					//
	TID_FOLLOW,					//	ÉJÉÅÉâí«îˆ
	TID_RANKING,				//
	TID_EXPLOSION,				//
	TID_CHECKALIVE,				//
	TID_SUM,					//
	TID_DRAW,					//
};

const uint TASKKEY::TANKSETPSET()			{return TID_TANKSETPSET;			}
const uint TASKKEY::STARTCAMMOVE()			{return TID_STARTCAMMOVE;			}
const uint TASKKEY::SYSTEMPARAM()			{return TID_SYSTEMPARAM;			}
const uint TASKKEY::COCKPIT()				{return TID_COCKPIT;				}
const uint TASKKEY::RANKING()				{return TID_RANKING;				}
const uint TASKKEY::RAP()					{return TID_RAP;					}
const uint TASKKEY::HITTEST_TANKADNTANK()	{return TID_HITTEST_TANK_AND_TANK;	}
const uint TASKKEY::HITTEST_TANKTOSHELL()	{return TID_HITTEST_TANK_TO_SHELL;	}
const uint TASKKEY::HITTEST_TANKTOWALL()	{return TID_HITTEST_WALL;			}
const uint TASKKEY::CALCACTIVEMOVE()		{return TID_CALCACTIVEMOVE;			}
const uint TASKKEY::CHECKALIVE()			{return TID_CHECKALIVE;				}
const uint TASKKEY::INTELLIGENCE()			{return TID_INTELLIGENCE;			}
const uint TASKKEY::UPDATECAMERA()			{return TID_FOLLOW;					}
const uint TASKKEY::EXPLOSION()				{return TID_EXPLOSION;				}
const uint TASKKEY::FIRE()					{return TID_FIRE;					}
const uint TASKKEY::PAUSE()					{return TID_PAUSE;					}
const uint TASKKEY::MOVE()					{return TID_MOVE;					}
const uint TASKKEY::DRAW()					{return TID_DRAW;					}
const uint TASKKEY::SUM()					{return TID_SUM;					}

