/***********************************************************************/
/*! @file  CTankTop.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANKTOP___
#define ___CTANKTOP___

#include"common.h"

class CMesh;
class CTankBottom;
class CTankIntInter;
class CShell;
class CTank;

class CTankTop
{
public:
	CTankTop(
		CTank*			pOwner,
		CMesh*			pMesh,
		CTankIntInter*	pTankIntInter,
		CShell*			pProtoShell
		);
	~CTankTop();
	CTankTop::CTankTop(
		const CTankTop& src
	);


	void fire();					///<	発砲
	void turn();					///<	回転
	void draw();					///<	描画
	void cooldown();				///<	放熱(優先度低

	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] pTankBottom 
	 *  @retval void
	 */
	/***********************************************************************/
	void setTankBottom(CTankBottom* pTankBottom){_Bottom = pTankBottom;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] pTank 
	 *  @retval void
	 */
	/***********************************************************************/
	void setOwner(CTank* pTank){_Owner = pTank;}
	void setPos(const float x, const float y,const float z);
	void setIntelligence(CTankIntInter* pIntelligence);
private:
	CTank*			_Owner;			
	CTankBottom*	_Bottom;
	CTankIntInter*	_pTankIntelligence;	///<	思考
	CMesh*			_pMesh;				///<	メッシュ
	CShell*			_pProtoShell;		///<	砲弾の原型
	D3DXVECTOR3		_TopDir;			///<	砲塔の向きベクトル
	D3DXMATRIXA16	_WMat;				///<	ワールドマトリクス
	int				_CntCool;			///<	クールタイムカウンタ
};

#endif