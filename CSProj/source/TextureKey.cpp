#include"TextureKey.h"

enum eTEXKEY{
	TEX_STARTSELECT,
	TEX_START,
	TEX_REDTY,
	TEX_GO,
	TEX_EXIT,

	TEX_WIN,
	TEX_LOSE,
	TEX_FADEMASK,
	TEX_BACK_BUTTON,
	TEX_TITLE_BG,
	TEX_TITLE_STR,
	TEX_TITLE_BUTTON01,
	TEX_TITLE_BUTTON02,
	TEX_TITLE_BUTTON03,
	TEX_SELECT_BG,
	TEX_SELECT_COURSE1,
	TEX_SELECT_COURSE2,
	TEX_SELECT_COURSE3,
	TEX_TILE01,
	TEX_TILE02,
	TEX_TILE03,
	TEX_TILE04,
	TEX_TILE05,
	TEX_TILE06,
	TEX_NUM_B0,
	TEX_NUM_B1,
	TEX_NUM_B2,
	TEX_NUM_B3,
	TEX_NUM_B4,
	TEX_NUM_B5,
	TEX_NUM_B6,
	TEX_NUM_B7,
	TEX_NUM_B8,
	TEX_NUM_B9,
	TEX_NUM_W0,
	TEX_NUM_W1,
	TEX_NUM_W2,
	TEX_NUM_W3,
	TEX_NUM_W4,
	TEX_NUM_W5,
	TEX_NUM_W6,
	TEX_NUM_W7,
	TEX_NUM_W8,
	TEX_NUM_W9,
	TEX_ANIMETEST,
	TEX_SUM,		//
};

const uint TEXKEY::STARTSELECT()	{	return TEX_WIN;		}
const uint TEXKEY::START()			{	return TEX_WIN;		}
const uint TEXKEY::REDY()			{	return TEX_WIN;		}
const uint TEXKEY::GO()				{	return TEX_WIN;		}
const uint TEXKEY::EXIT()			{	return TEX_WIN;		}

const uint TEXKEY::WIN()		{	return TEX_WIN;		}
const uint TEXKEY::LOSE()		{	return TEX_LOSE;		}
const uint TEXKEY::FADEMASK()		{	return TEX_FADEMASK;		}
const uint TEXKEY::BACK_BUTTON()	{	return TEX_BACK_BUTTON;		}
const uint TEXKEY::TITLE_BG()		{	return TEX_TITLE_BG;		}
const uint TEXKEY::TITLE_STR()		{	return TEX_TITLE_STR;		}
const uint TEXKEY::TITLE_BUTTON01()	{	return TEX_TITLE_BUTTON01;	}
const uint TEXKEY::TITLE_BUTTON02()	{	return TEX_TITLE_BUTTON02;	}
const uint TEXKEY::TITLE_BUTTON03()	{	return TEX_TITLE_BUTTON03;	}
const uint TEXKEY::SELECT_BG()		{	return TEX_SELECT_BG;		}
const uint TEXKEY::SELECT_COURSE1()	{	return TEX_SELECT_COURSE1;	}
const uint TEXKEY::SELECT_COURSE2()	{	return TEX_SELECT_COURSE2;	}
const uint TEXKEY::SELECT_COURSE3()	{	return TEX_SELECT_COURSE3;	}
const uint TEXKEY::TILE01()			{	return TEX_TILE01;			}
const uint TEXKEY::TILE02()			{	return TEX_TILE02;			}
const uint TEXKEY::TILE03()			{	return TEX_TILE03;			}
const uint TEXKEY::TILE04()			{	return TEX_TILE04;			}
const uint TEXKEY::NUM_B0()			{	return TEX_NUM_B0;			}
const uint TEXKEY::NUM_B1()			{	return TEX_NUM_B1;			}
const uint TEXKEY::NUM_B2()			{	return TEX_NUM_B2;			}
const uint TEXKEY::NUM_B3()			{	return TEX_NUM_B3;			}
const uint TEXKEY::NUM_B4()			{	return TEX_NUM_B4;			}
const uint TEXKEY::NUM_B5()			{	return TEX_NUM_B5;			}
const uint TEXKEY::NUM_B6()			{	return TEX_NUM_B6;			}
const uint TEXKEY::NUM_B7()			{	return TEX_NUM_B7;			}
const uint TEXKEY::NUM_B8()			{	return TEX_NUM_B8;			}
const uint TEXKEY::NUM_B9()			{	return TEX_NUM_B9;			}
const uint TEXKEY::NUM_W0()			{	return TEX_NUM_W0;			}
const uint TEXKEY::NUM_W1()			{	return TEX_NUM_W1;			}
const uint TEXKEY::NUM_W2()			{	return TEX_NUM_W2;			}
const uint TEXKEY::NUM_W3()			{	return TEX_NUM_W3;			}
const uint TEXKEY::NUM_W4()			{	return TEX_NUM_W4;			}
const uint TEXKEY::NUM_W5()			{	return TEX_NUM_W5;			}
const uint TEXKEY::NUM_W6()			{	return TEX_NUM_W6;			}
const uint TEXKEY::NUM_W7()			{	return TEX_NUM_W7;			}
const uint TEXKEY::NUM_W8()			{	return TEX_NUM_W8;			}
const uint TEXKEY::NUM_W9()			{	return TEX_NUM_W9;			}
const uint TEXKEY::ANIMETEST()		{	return TEX_ANIMETEST;		}
const uint TEXKEY::SUM()			{	return TEX_SUM;				}


const char* TEXPATH::WIN()				{return "data/texture/win.bmp";		}
const char* TEXPATH::LOSE()				{return "data/texture/lose.bmp";		}
const char* TEXPATH::FADEMASK()			{return "data/texture/fademask.jpg";		}
const char* TEXPATH::BACK_BUTTON()		{return "data/texture/back_button.jpg";		}
const char* TEXPATH::TITLE_BG()			{return "data/texture/title_bg.jpg";		}
const char* TEXPATH::TITLE_STR()		{return "data/texture/title_str.png";		}
const char* TEXPATH::TITLE_BUTTON01()	{return "data/texture/title_button01.jpg";	}
const char* TEXPATH::TITLE_BUTTON02()	{return "data/texture/title_button02.jpg";	}
const char* TEXPATH::TITLE_BUTTON03()	{return "data/texture/title_button03.jpg";	}
const char* TEXPATH::SELECT_BG()		{return "data/texture/select_bg.jpg";		}
const char* TEXPATH::SELECT_COURSE1()	{return "data/texture/select_course1.jpg";	}
const char* TEXPATH::SELECT_COURSE2()	{return "data/texture/select_course2.jpg";	}
const char* TEXPATH::SELECT_COURSE3()	{return "data/texture/select_course3.jpg";	}
const char* TEXPATH::TILE01()			{return "data/Stage/001.jpg";				}
const char* TEXPATH::TILE02()			{return "data/Stage/004.jpg";				}
const char* TEXPATH::TILE03()			{return "data/Stage/005.jpg";				}
const char* TEXPATH::TILE04()			{return "data/Stage/006.jpg";				}
const char* TEXPATH::NUM_B0()				{return "data/texture/num/b_0.png";		}
const char* TEXPATH::NUM_B1()				{return "data/texture/num/b_1.png";		}
const char* TEXPATH::NUM_B2()				{return "data/texture/num/b_2.png";		}
const char* TEXPATH::NUM_B3()				{return "data/texture/num/b_3.png";		}
const char* TEXPATH::NUM_B4()				{return "data/texture/num/b_4.png";		}
const char* TEXPATH::NUM_B5()				{return "data/texture/num/b_5.png";		}
const char* TEXPATH::NUM_B6()				{return "data/texture/num/b_6.png";		}
const char* TEXPATH::NUM_B7()				{return "data/texture/num/b_7.png";		}
const char* TEXPATH::NUM_B8()				{return "data/texture/num/b_8.png";		}
const char* TEXPATH::NUM_B9()				{return "data/texture/num/b_9.png";		}
const char* TEXPATH::NUM_W0()				{return "data/texture/num/b_0.png";		}
const char* TEXPATH::NUM_W1()				{return "data/texture/num/w_1.png";		}
const char* TEXPATH::NUM_W2()				{return "data/texture/num/w_2.png";		}
const char* TEXPATH::NUM_W3()				{return "data/texture/num/w_3.png";		}
const char* TEXPATH::NUM_W4()				{return "data/texture/num/w_4.png";		}
const char* TEXPATH::NUM_W5()				{return "data/texture/num/w_5.png";		}
const char* TEXPATH::NUM_W6()				{return "data/texture/num/w_6.png";		}
const char* TEXPATH::NUM_W7()				{return "data/texture/num/w_7.png";		}
const char* TEXPATH::NUM_W8()				{return "data/texture/num/w_8.png";		}
const char* TEXPATH::NUM_W9()				{return "data/texture/num/w_9.png";		}
const char* TEXPATH::ANIMETEST()		{return "data/texture/animeTextTex.png";	}