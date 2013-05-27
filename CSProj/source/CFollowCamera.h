#ifndef ___CFOLLOWCAMERA___
#define ___CFOLLOWCAMERA___

#include"CObjBase.h"

class CCamera;
class CTaskList;
class CTank;

/*!	@class
 *	@brift	追尾カメラ
 */
class CFollowCamera:public CObjBase
{
public:
	CFollowCamera();
	~CFollowCamera();
	CFollowCamera(const CFollowCamera& src);

	void enableTask();
	void disableTask();

	void update();	//	視点、注視点の更新

	void setTank(CTank* pTank);

private:
	float		_fDistance;		///<	距離
	D3DXVECTOR3	_NAtToEye;		///<	注視点から視点の単位ベクトル
	CTank*		_pTank;			///<

	CTaskList*	_pUpdate;	///<	ビューの更新
};

#endif