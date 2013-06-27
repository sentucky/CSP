#include"CSoundKey.h"

enum eSOUNDKEY
{
	SOUND_GAMEBGM,
	SOUND_LOSEBGM,	
	SOUND_TITLEBGM,	
	SOUND_COLLISION,
	SOUND_FANFARE,	
	SOUND_MOVE,		
	SOUND_FIRE,		
	SOUND_SIREN,

	SOUND_SUM,
};


const uint SOUNDKEY::GAMEBGM()	{ return 	SOUND_GAMEBGM;	}
const uint SOUNDKEY::LOSEBGM()	{ return 	SOUND_LOSEBGM;	}
const uint SOUNDKEY::TITLEBGM()	{ return 	SOUND_TITLEBGM;	}
const uint SOUNDKEY::COLLISION(){ return 	SOUND_COLLISION;}
const uint SOUNDKEY::FANFARE()	{ return 	SOUND_FANFARE;	}
const uint SOUNDKEY::MOVE()		{ return 	SOUND_MOVE;		}
const uint SOUNDKEY::FIRE()		{ return 	SOUND_FIRE;		}
const uint SOUNDKEY::SIREN()	{ return 	SOUND_SIREN;	}
const uint SOUNDKEY::SUM()		{ return 	SOUND_SUM;		}

char* SOUNDPATH::GAMEBGM()	{ return "data/sound/BGM/gamebgm.wav";	}
char* SOUNDPATH::LOSEBGM()	{ return "data/sound/BGM/losebgm.wav";	}
char* SOUNDPATH::TITLEBGM()	{ return "data/sound/BGM/titlebgm.wav";	}
char* SOUNDPATH::COLLISION(){ return "data/sound/SE/collision/01.wav";	}
char* SOUNDPATH::FANFARE()	{ return "data/sound/SE/fanfare/01.wav";}
char* SOUNDPATH::MOVE()		{ return "data/sound/SE/move.wav";		}
char* SOUNDPATH::FIRE()		{ return "data/sound/SE/fire/01.wav";	}
char* SOUNDPATH::SIREN()	{ return "data/sound/SE/siren.wav";		}

