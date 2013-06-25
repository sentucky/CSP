#include"ObjKey.h"


enum eOBJID
{
	OID_COCKPIT,
	OID_SYSTEMPARAM,
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
	OID_STARTCAMERA,
	OID_NUM,
	OID_TANKDUMMY,
	OID_SUM,		//
};

const uint OBJKEY::TANKDUMMY()		{return OID_TANKDUMMY;	}

const uint OBJKEY::COCKPIT()		{return OID_COCKPIT;	}
const uint OBJKEY::SYSTEMPARAM()	{return OID_SYSTEMPARAM;}
const uint OBJKEY::HITTESTTTOT()	{return OID_HITTESTTOT;	}	///<	@brift	あたり判定
const uint OBJKEY::HITTESTTTOS()	{return OID_HITTESTTOS;	}	///<	@brift	あたり判定
const uint OBJKEY::HITTESTTTOW()	{return OID_HITTESTTOW;	}	///<	@brift	あたり判定
const uint OBJKEY::SHELL01()		{return OID_SHELL01;	}	///<	
const uint OBJKEY::SHELL02()		{return OID_SHELL02;	}	///<	
const uint OBJKEY::SHELL03()		{return OID_SHELL03;	}	///<	
const uint OBJKEY::PIN()			{return OID_PIN;		}	///<	
const uint OBJKEY::TANK01()			{return OID_TANK01;		}	///<	@brift	タンク01オブジェキー
const uint OBJKEY::TANK02()			{return OID_TANK02;		}	///<	@brift	タンク02オブジェキー
const uint OBJKEY::TANK03()			{return OID_TANK03;		}	///<	@brift	タンク03オブジェキー
const uint OBJKEY::TANK04()			{return OID_TANK04;		}	///<	@brift	タンク04オブジェキー
const uint OBJKEY::STAGE01()		{return OID_STAGE01;	}	///<	@brift	ステージオブジェキー
const uint OBJKEY::STARTCAMERA()	{return OID_STARTCAMERA;}
const uint OBJKEY::FOLLOWCAMERA()	{return OID_FOLLOW;		}	///<	@brift	追尾カメラオブジェキー
const uint OBJKEY::NUM()			{return OID_NUM;		}	///<	@brift	数字
const uint OBJKEY::SUM()			{return OID_SUM;		}	///<	@brift	オブジェキー最大数

enum eOBJGROUPKEY
{
	OGK_GAMESYSTEM,
	OGK_COCKPIT,
	OGK_HITTEST,//
	OGK_SHELL,	//
	OGK_PIN,	//
	OGK_STAGE,	//
	OGK_TANK,	//
	OGK_CAMERA,	//
	OGK_NUM,	//
	OGK_SUM,	//
};

const uint OBJGROUPKEY::GAMESYSTEM(){return OGK_GAMESYSTEM;}
const uint OBJGROUPKEY::COCKPIT()	{return OGK_COCKPIT;}
const uint OBJGROUPKEY::TANK()		{return OGK_TANK;	}
const uint OBJGROUPKEY::HITTEST()	{return OGK_HITTEST;}
const uint OBJGROUPKEY::SHELL()		{return OGK_SHELL;	}
const uint OBJGROUPKEY::STAGE()		{return OGK_STAGE;	}
const uint OBJGROUPKEY::CAMERA()	{return OGK_CAMERA;	}
const uint OBJGROUPKEY::PIN()		{return OGK_PIN;	}
const uint OBJGROUPKEY::NUM()		{return OGK_NUM;	}
const uint OBJGROUPKEY::SUM()		{return OGK_SUM;	}
