#ifndef ___CFOLLOWCAMERA___
#define ___CFOLLOWCAMERA___

#include"CObjBase.h"

class CCamera;
class CTaskList;
class CTank;

/*!	@class
 *	@brift	�ǔ��J����
 */
class CFollowCamera:public CObjBase
{
public:
	CFollowCamera();
	~CFollowCamera();
	CFollowCamera(const CFollowCamera& src);

	void enableTask();
	void disableTask();

	void update();	//	���_�A�����_�̍X�V

	void setTank(CTank* pTank);

private:
	float		_fDistance;		///<	����
	D3DXVECTOR3	_NAtToEye;		///<	�����_���王�_�̒P�ʃx�N�g��
	CTank*		_pTank;			///<

	CTaskList*	_pUpdate;	///<	�r���[�̍X�V
};

#endif