/***********************************************************************/
/*! @file  const.cpp
 *  @brief 定数
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"const.h"

const char* STAGEPATH::NO_01(){return "data/stage/stageData00.dat";}

const char* MESHPATH::SHELL01(){		return "data/model/pin.x";		}
const char* MESHPATH::SHELL02(){		return "data/model/pin.x";		}
const char* MESHPATH::SHELL03(){		return "data/model/pin.x";		}
const char* MESHPATH::PIN(){			return "data/model/pin.x";		}
const char* MESHPATH::YUKA(){			return "data/model/nanase_pose.x";		}
const char* MESHPATH::STAGE01(){		return "data/model/stage01.x";			}
const char* MESHPATH::TANK01_TOP(){		return "data/model/tank01_top.x";		}
const char* MESHPATH::TANK02_TOP(){		return "data/model/tank02_top.x";		}
const char* MESHPATH::TANK03_TOP(){		return "data/model/tank03_top.x";		}
const char* MESHPATH::TANK04_TOP(){		return "data/model/tank04_top.x";		}
const char* MESHPATH::TANK01_BOTTOM(){	return "data/model/tank01_bottom.x";	}
const char* MESHPATH::TANK02_BOTTOM(){	return "data/model/tank02_bottom.x";	}
const char* MESHPATH::TANK03_BOTTOM(){	return "data/model/tank03_bottom.x";	}
const char* MESHPATH::TANK04_BOTTOM(){	return "data/model/tank04_bottom.x";	}




enum eMESHKEY
{
	MESH_PIN,			//
	MESH_SHELL01,		//
	MESH_SHELL02,		//
	MESH_SHELL03,		//
	MESH_YUKA,			//
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


const uint MESHKEY::SHELL01(){		return MESH_SHELL01;		}
const uint MESHKEY::PIN(){			return MESH_PIN;			}
const uint MESHKEY::YUKA(){			return MESH_YUKA;			}
const uint MESHKEY::STAGE01(){		return MESH_STAGE01;		}
const uint MESHKEY::TANK01_TOP(){	return MESH_TANK01_TOP;		}
const uint MESHKEY::TANK02_TOP(){	return MESH_TANK02_TOP;		}
const uint MESHKEY::TANK03_TOP(){	return MESH_TANK03_TOP;		}
const uint MESHKEY::TANK04_TOP(){	return MESH_TANK04_TOP;		}
const uint MESHKEY::TANK01_BOTTOM(){return MESH_TANK01_BOTTOM;	}
const uint MESHKEY::TANK02_BOTTOM(){return MESH_TANK02_BOTTOM;	}
const uint MESHKEY::TANK03_BOTTOM(){return MESH_TANK03_BOTTOM;	}
const uint MESHKEY::TANK04_BOTTOM(){return MESH_TANK04_BOTTOM;	}
const uint MESHKEY::SUM(){			return MESH_SUM;			}

const char* EFFECTPATH::NONE(){return "a";}
const char* EFFECTPATH::TOON(){return "A";}


enum eTID
{
	TID_INTELLIGENCE,			//
	TID_RAP,					//
	TID_FIRE,					//
	TID_PAUSE,					//
	TID_CALCACTIVEMOVE,			//
	TID_HITTEST_TANK_AND_TANK,	//
	TID_HITTEST_TANK_TO_SHELL,	//0
	TID_HITTEST_WALL,			//
	TID_MOVE,					//
	TID_EXPLOSION,				//
	TID_FOLLOW,					//	カメラ追尾
	TID_CHECKALIVE,				//
	TID_SUM,					//
	TID_DRAW,					//
};

const uint TASKKEY::RAP(){return TID_RAP;}
const uint TASKKEY::HITTEST_TANKADNTANK(){return TID_HITTEST_TANK_AND_TANK;}
const uint TASKKEY::HITTEST_TANKTOSHELL(){return TID_HITTEST_TANK_TO_SHELL;}
const uint TASKKEY::HITTEST_TANKTOWALL(){return TID_HITTEST_WALL;}
const uint TASKKEY::CALCACTIVEMOVE(){return TID_CALCACTIVEMOVE;}
const uint TASKKEY::CHECKALIVE(){return TID_CHECKALIVE;}
const uint TASKKEY::INTELLIGENCE(){return TID_INTELLIGENCE;}
const uint TASKKEY::UPDATECAMERA(){return TID_FOLLOW;}
const uint TASKKEY::EXPLOSION(){return TID_EXPLOSION;}
const uint TASKKEY::FIRE(){return TID_FIRE;}
const uint TASKKEY::PAUSE(){return TID_PAUSE;}
const uint TASKKEY::MOVE(){return TID_MOVE;}
const uint TASKKEY::DRAW(){return TID_DRAW;}
const uint TASKKEY::SUM(){return TID_SUM;}


enum eOBJID
{
	OID_HITTESTTOT,
	OID_HITTESTTOS,
	OID_HITTESTTOW,
	OID_SHELL01,	//
	OID_SHELL02,	//
	OID_SHELL03,	//
	OID_PIN,		//
	OID_STAGE01,	//
	OID_TANK01,		//
	OID_TANK02,		//
	OID_TANK03,		//
	OID_TANK04,		//
	OID_FOLLOW,		//
	OID_NUM,
#ifdef _DEBUG
	OID_TANKDUMMY,
#endif
	OID_SUM,		//
};

#ifdef _DEBUG
const uint OBJKEY::TANKDUMMY(){return OID_TANKDUMMY;}
#endif
const uint OBJKEY::HITTESTTTOT(){return OID_HITTESTTOT;}	///<	@brift	あたり判定
const uint OBJKEY::HITTESTTTOS(){return OID_HITTESTTOS;}	///<	@brift	あたり判定
const uint OBJKEY::HITTESTTTOW(){return OID_HITTESTTOW;}	///<	@brift	あたり判定
const uint OBJKEY::SHELL01(){return OID_SHELL01;}	///<	
const uint OBJKEY::SHELL02(){return OID_SHELL02;}	///<	
const uint OBJKEY::SHELL03(){return OID_SHELL03;}	///<	
const uint OBJKEY::PIN()	{return OID_PIN;	}	///<	
const uint OBJKEY::TANK01()	{return OID_TANK01;	}	///<	@brift	タンク01オブジェキー
const uint OBJKEY::TANK02()	{return OID_TANK02;	}	///<	@brift	タンク02オブジェキー
const uint OBJKEY::TANK03()	{return OID_TANK03;	}	///<	@brift	タンク03オブジェキー
const uint OBJKEY::TANK04()	{return OID_TANK04;	}	///<	@brift	タンク04オブジェキー
const uint OBJKEY::STAGE01(){return OID_STAGE01;}	///<	@brift	ステージオブジェキー
const uint OBJKEY::FOLLOW()	{return OID_FOLLOW;	}	///<	@brift	追尾カメラオブジェキー
const uint OBJKEY::NUM()	{return OID_NUM;	}	///<	@brift	数字
const uint OBJKEY::SUM()	{return OID_SUM;	}	///<	@brift	オブジェキー最大数

enum eOBJGROUPKEY
{
	OGK_HITTEST,//
	OGK_SHELL,	//
	OGK_PIN,	//
	OGK_STAGE,	//
	OGK_TANK,	//
	OGK_FOLLOW,	//
	OGK_NUM,	//
	OGK_SUM,	//
};

const uint OBJGROUPKEY::TANK()		{return OGK_TANK;	}
const uint OBJGROUPKEY::HITTEST()	{return OGK_HITTEST;}
const uint OBJGROUPKEY::SHELL()		{return OGK_SHELL;	}
const uint OBJGROUPKEY::STAGE()		{return OGK_STAGE;	}
const uint OBJGROUPKEY::FOLLOW()	{return OGK_FOLLOW;	}
const uint OBJGROUPKEY::PIN()		{return OGK_PIN;	}
const uint OBJGROUPKEY::NUM()		{return OGK_NUM;	}
const uint OBJGROUPKEY::SUM()		{return OGK_SUM;	}
