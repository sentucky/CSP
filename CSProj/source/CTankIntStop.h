#ifndef ___CTANKINTSTOP___
#define ___CTANKINTSOTP___

//	�v�l��~

#include"CTankIntInter.h"

class CTankIntStop:public CTankIntInter
{
public:
	CTankIntStop(CTank* Tank):CTankIntInter(Tank){}					///<	�R���X�g���N�^
	~CTankIntStop(){};				///<	�f�X�g���N�^
	
	void update(){};				///<	�X�V�֐�};
};

#endif