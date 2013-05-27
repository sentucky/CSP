#ifndef ___PIN___
#define ___PIN___
#include"CObjBase.h"

class CMesh;
class CTaskList;

/*!
 *	@class	CPin
 *	@brift	�s��
 */

class CPin:public CObjBase
{
public:
	CPin(CMesh* pPinMesh);
	~CPin();
	CPin(const CPin& src);

	void enableTask();	//	�^�X�N�L����
	void disableTask();	//	�^�X�N������

	//	���X�g�o�^�^�X�N
	void draw();		//	�`��
	void move();		//	�X�V

private:
	CTaskList* _pTaskDraw;
	CTaskList* _pTaskUpdate;

	CMesh*			_pMesh;
	D3DXMATRIXA16	_matW;
};

#endif