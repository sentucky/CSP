/***********************************************************************/
/*! @file  const.cpp
 *  @brief 定数
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#include"const.h"

const char* MESHPATH::SHELL01(){		return "data/model/pin.x";		}
const char* MESHPATH::SHELL02(){		return "data/model/pin.x";		}
const char* MESHPATH::SHELL03(){		return "data/model/pin.x";		}
const char* MESHPATH::PIN(){			return "data/model/pin.x";		}
const char* MESHPATH::YUKA(){			return "data/model/nanase_pose.x";		}
const char* MESHPATH::STAGE01(){		return "data/model/stage01.x";			}
const char* MESHPATH::TANK01_TOP(){		return "data/model/tank01_top.x";		}
const char* MESHPATH::TANK02_TOP(){		return "data/model/tank01_top.x";		}
const char* MESHPATH::TANK03_TOP(){		return "data/model/tank01_top.x";		}
const char* MESHPATH::TANK01_BOTTOM(){	return "data/model/tank01_bottom.x";	}
const char* MESHPATH::TANK02_BOTTOM(){	return "data/model/tank01_bottom.x";	}
const char* MESHPATH::TANK03_BOTTOM(){	return "data/model/tank01_bottom.x";	}



const char* TEXPATH::FADEMASK(){		return "data/texture/fademask.jpg";			}

enum eTEXKEY{
	TEX_FADEMASK,	//
	TEX_SUM,		//
};
const uint TEXKEY::FADEMASK()	{	return TEX_FADEMASK;	}
const uint TEXKEY::SUM()		{	return TEX_SUM;		}



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
	MESH_TANK01_BOTTOM,	//
	MESH_TANK02_BOTTOM,	//
	MESH_TANK03_BOTTOM,	//
	MESH_SUM,			//
};


const uint MESHKEY::SHELL01(){		return MESH_SHELL01;		}
const uint MESHKEY::PIN(){			return MESH_PIN;			}
const uint MESHKEY::YUKA(){			return MESH_YUKA;			}
const uint MESHKEY::STAGE01(){		return MESH_STAGE01;		}
const uint MESHKEY::TANK01_TOP(){	return MESH_TANK01_TOP;		}
const uint MESHKEY::TANK01_BOTTOM(){return MESH_TANK01_BOTTOM;	}
const uint MESHKEY::SUM(){			return MESH_SUM;			}

const char* EFFECTPATH::NONE(){return "a";}
const char* EFFECTPATH::TOON(){return "A";}


enum eTID
{
	TID_HITTEST_WALL,			//
	TID_HITTEST_TANK_AND_TANK,	//
	TID_HITTEST_TANK_AND_SHELL,	//
	TID_INTELLIGENCE,			//
	TID_PAUSE,					//
	TID_FIRE,					//
	TID_MOVE,					//
	TID_EXPLOSION,				//
	TID_FOLLOW,					//	カメラ追尾
	TID_CHECKALIVE,				//
	TID_SUM,					//
	TID_DRAW,					//
};


const uint TASKID::CHECKALIVE(){return TID_CHECKALIVE;}
const uint TASKID::INTELLIGENCE(){return TID_INTELLIGENCE;}
const uint TASKID::UPDATECAMERA(){return TID_FOLLOW;}
const uint TASKID::EXPLOSION(){return TID_EXPLOSION;}
const uint TASKID::FIRE(){return TID_FIRE;}
const uint TASKID::PAUSE(){return TID_PAUSE;}
const uint TASKID::MOVE(){return TID_MOVE;}
const uint TASKID::DRAW(){return TID_DRAW;}
const uint TASKID::SUM(){return TID_SUM;}


enum eOBJID
{
	OID_SHELL01,	//
	OID_SHELL02,	//
	OID_SHELL03,	//
	OID_PIN,		//
	OID_STAGE01,	//
	OID_TANK01,		//
	OID_TANK02,		//
	OID_TANK03,		//
	OID_FOLLOW,		//
	OID_SUM,		//
};

const uint OBJKEY::SHELL01(){return OID_SHELL01;}	///<	
const uint OBJKEY::SHELL02(){return OID_SHELL02;}	///<	
const uint OBJKEY::SHELL03(){return OID_SHELL03;}	///<	
const uint OBJKEY::PIN()	{return OID_PIN;	}	///<	
const uint OBJKEY::TANK01()	{return OID_TANK01;	}	///<	@brift	タンク01オブジェキー
const uint OBJKEY::TANK02()	{return OID_TANK02;	}	///<	@brift	タンク01オブジェキー
const uint OBJKEY::TANK03()	{return OID_TANK03;	}	///<	@brift	タンク01オブジェキー
const uint OBJKEY::STAGE01(){return OID_STAGE01;}	///<	@brift	ステージオブジェキー
const uint OBJKEY::FOLLOW()	{return OID_FOLLOW;	}	///<	@brift	追尾カメラオブジェキー
const uint OBJKEY::SUM()	{return OID_SUM;	}	///<	@brift	オブジェキー最大数


