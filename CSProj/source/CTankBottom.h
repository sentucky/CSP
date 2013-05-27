#ifndef ___CTANKBOTTOM___
#define ___CTANKBOTTOM___

#include"const.h"

class CMesh;
class CTankIntInter;

class CTankBottom
{
public:
	CTankBottom(
	CMesh* pMesh,
	const float fSpeedMove,
	const float fSpeedTurn
	);
	~CTankBottom();
	CTankBottom(const CTankBottom& src);

	void draw();
	void move();
	void turn();
	void rotateMatrix(float fTurnSpeed);
	const D3DXMATRIXA16* getWMat();

	void setIntelligence(CTankIntInter* pIntelligence);
private:
	CMesh*			_pMesh;
	CTankIntInter*	_pIntelligence;
	D3DXVECTOR3		_MoveVec;			///<	移動ベクトル
	D3DXVECTOR3		_Dir;
	D3DXMATRIXA16	_WMat;			///<	ボトムのマトリクス

	float			_fSpeedMove;		///<	移動速度
	float			_fSpeedTurn;		///<	旋回速度
};

#endif