#include"TextureKey.h"

enum eTEXKEY{
	TEX_FADEMASK,	//
	TEX_TITLE_BG,
	TEX_TITLE_BUTTON01,
	TEX_TITLE_BUTTON02,
	TEX_TITLE_BUTTON03,
	TEX_TILE01,
	TEX_TILE02,
	TEX_TILE03,
	TEX_TILE04,
	TEX_TILE05,
	TEX_TILE06,
	TEX_NUM0,
	TEX_NUM1,
	TEX_NUM2,
	TEX_NUM3,
	TEX_NUM4,
	TEX_NUM5,
	TEX_NUM6,
	TEX_NUM7,
	TEX_NUM8,
	TEX_NUM9,
	TEX_ANIMETEST,
	TEX_SUM,		//
};


const uint TEXKEY::FADEMASK()		{	return TEX_FADEMASK;		}
const uint TEXKEY::TITLE_BG()		{	return TEX_TITLE_BG;		}
const uint TEXKEY::TITLE_BUTTON01()	{	return TEX_TITLE_BUTTON01;	}
const uint TEXKEY::TITLE_BUTTON02()	{	return TEX_TITLE_BUTTON02;	}
const uint TEXKEY::TITLE_BUTTON03()	{	return TEX_TITLE_BUTTON03;	}
const uint TEXKEY::TILE01()			{	return TEX_TILE01;			}
const uint TEXKEY::TILE02()			{	return TEX_TILE02;			}
const uint TEXKEY::TILE03()			{	return TEX_TILE03;			}
const uint TEXKEY::TILE04()			{	return TEX_TILE04;			}
const uint TEXKEY::TILE05()			{	return TEX_TILE05;			}
const uint TEXKEY::TILE06()			{	return TEX_TILE06;			}
const uint TEXKEY::NUM0()			{	return TEX_NUM0;			}
const uint TEXKEY::NUM1()			{	return TEX_NUM1;			}
const uint TEXKEY::NUM2()			{	return TEX_NUM2;			}
const uint TEXKEY::NUM3()			{	return TEX_NUM3;			}
const uint TEXKEY::NUM4()			{	return TEX_NUM4;			}
const uint TEXKEY::NUM5()			{	return TEX_NUM5;			}
const uint TEXKEY::NUM6()			{	return TEX_NUM6;			}
const uint TEXKEY::NUM7()			{	return TEX_NUM7;			}
const uint TEXKEY::NUM8()			{	return TEX_NUM8;			}
const uint TEXKEY::NUM9()			{	return TEX_NUM9;			}
const uint TEXKEY::ANIMETEST()		{	return TEX_ANIMETEST;		}
const uint TEXKEY::SUM()			{	return TEX_SUM;				}


const char* TEXPATH::FADEMASK()			{return "data/texture/fademask.jpg";		}
const char* TEXPATH::TITLE_BG()			{return "data/texture/title_bg.jpg";		}
const char* TEXPATH::TITLE_BUTTON01()	{return "data/texture/title_button01.jpg";	}
const char* TEXPATH::TITLE_BUTTON02()	{return "data/texture/title_button02.jpg";	}
const char* TEXPATH::TITLE_BUTTON03()	{return "data/texture/title_button03.jpg";	}
const char* TEXPATH::TILE01()			{return "data/Stage/001.jpg";				}
const char* TEXPATH::TILE02()			{return "data/Stage/004.jpg";				}
const char* TEXPATH::TILE03()			{return "data/Stage/005.jpg";				}
const char* TEXPATH::TILE04()			{return "data/Stage/006.jpg";				}
const char* TEXPATH::TILE05()			{return "data/Stage/002.jpg";				}
const char* TEXPATH::TILE06()			{return "data/Stage/003.jpg";				}
const char* TEXPATH::NUM0()				{return "data/texture/num0.png";			}
const char* TEXPATH::NUM1()				{return "data/texture/num1.png";			}
const char* TEXPATH::NUM2()				{return "data/texture/num2.png";			}
const char* TEXPATH::NUM3()				{return "data/texture/num3.png";			}
const char* TEXPATH::NUM4()				{return "data/texture/num4.png";			}
const char* TEXPATH::NUM5()				{return "data/texture/num5.png";			}
const char* TEXPATH::NUM6()				{return "data/texture/num6.png";			}
const char* TEXPATH::NUM7()				{return "data/texture/num7.png";			}
const char* TEXPATH::NUM8()				{return "data/texture/num8.png";			}
const char* TEXPATH::NUM9()				{return "data/texture/num9.png";			}
const char* TEXPATH::ANIMETEST()		{return "data/texture/animeTextTex.png";	}