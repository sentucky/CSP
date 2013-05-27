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


	void fire();					//	���C
	void turn();					//	��]
	void draw();					//	�`��
	void cooldown();				//	���M(�D��x��

	void setPos(const float x, const float y,const float z);
	void setIntelligence(CTankIntInter* pIntelligence);
private:
	CTankIntInter*	_pTankIntelligence;	///<	�v�l
	CMesh*			_pMesh;			///<	���b�V��
	CShell*			_pProtoShell;	///<	�C�e�̌��^
	D3DXVECTOR3		_TopDir;		///<	�C���̌����x�N�g��
	D3DXMATRIXA16	_WMat;			///<	���[���h�}�g���N�X

	int				_CntCool;		///<	�N�[���^�C���J�E���^
};

#endif