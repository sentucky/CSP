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
	D3DXVECTOR3		_MoveVec;			///<	�ړ��x�N�g��
	D3DXVECTOR3		_Dir;
	D3DXMATRIXA16	_WMat;			///<	�{�g���̃}�g���N�X

	float			_fSpeedMove;		///<	�ړ����x
	float			_fSpeedTurn;		///<	���񑬓x
};

#endif