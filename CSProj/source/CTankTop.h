#ifndef ___CTANKTOP___
#define ___CTANKTOP___

#include"common.h"

class CMesh;
class CTankIntInter;
class CShell;

class CTankTop
{
public:
	CTankTop(
		CMesh*			pMesh,
		CTankIntInter*	pTankIntInter,
		CShell*			pProtoShell
		);
	~CTankTop();
	CTankTop::CTankTop(
		const CTankTop& src
	);


	void fire();					//	発砲
	void turn();					//	回転
	void draw();					//	描画
	void cooldown();				//	放熱(優先度低

	void setPos(const float x, const float y,const float z);
	void setIntelligence(CTankIntInter* pIntelligence);
private:
	CTankIntInter*	_pTankIntelligence;	///<	思考
	CMesh*			_pMesh;			///<	メッシュ
	CShell*			_pProtoShell;	///<	砲弾の原型
	D3DXVECTOR3		_TopDir;		///<	砲塔の向きベクトル
	D3DXMATRIXA16	_WMat;			///<	ワールドマトリクス

	int				_CntCool;		///<	クールタイムカウンタ
};

#endif