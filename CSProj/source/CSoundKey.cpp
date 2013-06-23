#include"CSoundKey.h"

enum eSOUNDKEY
{
	SOUND_BGM1,
	SOUND_ENGINE,
	SOUDN_COLLITANKTOTANK,
	SOUND_FIRE,
	SOUND_HITSHELL,
	SOUND_FANFARE,
	SOUND_START,
	SOUND_SUM,
};
const uint SOUNDKEY::BGM1()				{ return SOUND_BGM1;			}
const uint SOUNDKEY::COLLITANKTOTANK()	{ return SOUDN_COLLITANKTOTANK;	}
const uint SOUNDKEY::ENGILE()			{ return SOUND_ENGINE;			}
const uint SOUNDKEY::FIRE()				{ return SOUND_FIRE;			}
const uint SOUNDKEY::HITSHELL()			{ return SOUND_HITSHELL;		}
const uint SOUNDKEY::FANFARE()			{ return SOUND_FANFARE;			}
const uint SOUNDKEY::START()			{ return SOUND_START;			}
const uint SOUNDKEY::SUM()				{ return SOUND_SUM;				}

char* SOUNDPATH::BGM1()				{ return "data/sound/bgm1.wav";}
char* SOUNDPATH::COLLITANKTOTANK()	{ return "data/sound/collitanktotank.wav";	}
char* SOUNDPATH::ENGILE()			{ return "data/sound/engine.wav";			}
char* SOUNDPATH::FIRE()				{ return "data/sound/fire.wav";				}
char* SOUNDPATH::HITSHELL()			{ return "data/sound/hitshell.wav";			}
char* SOUNDPATH::FANFARE()			{ return "data/sound/fanfare.wav";			}
char* SOUNDPATH::START()			{ return "data/sound/start.wav";			}
