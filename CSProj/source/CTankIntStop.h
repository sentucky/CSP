#ifndef ___CTANKINTSTOP___
#define ___CTANKINTSOTP___

//	思考停止

#include"CTankIntInter.h"

class CTankIntStop:public CTankIntInter
{
public:
	CTankIntStop(CTank* Tank):CTankIntInter(Tank){}					///<	コンストラクタ
	~CTankIntStop(){};				///<	デストラクタ
	
	void update(){};				///<	更新関数};
};

#endif