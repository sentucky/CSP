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


	void fire();					///<	���C
	void turn();					///<	��]
	void draw();					///<	�`��
	void cooldown();				///<	���M(�D��x��

	void rotationy(const float fY);

	void setTankBottom(CTankBottom* pTankBottom){_Bottom = pTankBottom;}
	void setOwner(CTank* pTank){_Owner = pTank;}
	void setPos(const float x, const float y,const float z);
	void setIntelligence(CTankIntInter* pIntelligence);
private:
	CTank*			_Owner;			
	CTankBottom*	_Bottom;
	CTankIntInter*	_pTankIntelligence;	///<	�v�l
	CMesh*			_pMesh;				///<	���b�V��
	CShell*			_pProtoShell;		///<	�C�e�̌��^
	D3DXVECTOR3		_TopDir;			///<	�C���̌����x�N�g��
	D3DXMATRIXA16	_WMat;				///<	���[���h�}�g���N�X
	int				_CntCool;			///<	�N�[���^�C���J�E���^
};

#endif