/***********************************************************************/
/*! @file  CTankBottom.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANKBOTTOM___
#define ___CTANKBOTTOM___

#include"const.h"

class CMesh;
class CTankIntInter;
template<class T>
class CListMng;

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
	void clacMove(const uint rank);
	void rotateMatrix(float fTurnSpeed);

	const D3DXMATRIXA16* getWMat();


	const D3DXVECTOR3  getPos();
	const D3DXVECTOR3* getMoveVec();
	void setIntelligence(CTankIntInter* pIntelligence);
	void setMoveVec( D3DXVECTOR3& MoveVec );
	void setMoveVec( const D3DXVECTOR3 *MoveVec );
	void setPos(const float x,const float y);
private:
	CMesh*			_pMesh;
	CTankIntInter*	_pIntelligence;
	D3DXVECTOR3		_MoveVec;			///<	移動ベクトル
	D3DXVECTOR3		_MoveDir;			///<	移動方向
	D3DXVECTOR3		_Dir;
	D3DXMATRIXA16	_WMat;			///<	ボトムのマトリクス
	float			_fSpeedMove;		///<	移動速度
	float			_fSpeedTurn;		///<	旋回速度
	static const	float	_fDeceleration;		///<	減速率
};

#endif