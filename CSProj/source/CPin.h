/***********************************************************************/
/*! @file  CPin.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___PIN___
#define ___PIN___
#include"CObjBase.h"

class CMesh;
class CTaskList;

/*!
 *	@class	CPin
 *	@brift	ピン
 */

class CPin:public CObjBase
{
public:
	CPin(CMesh* pPinMesh);
	~CPin();
	CPin(const CPin& src);

	void enableTask();	///<	タスク有効化
	void disableTask();	///<	タスク無効化

	//	リスト登録タスク
	void draw();		///<	描画
	void move();		///<	更新
	void setPos(const float x,const float y,const float z)
	{
		_matW._41 = x;
		_matW._42 = y;
		_matW._43 = z;
	}
private:
	CTaskList* _pTaskDraw;
	CTaskList* _pTaskUpdate;

	CMesh*			_pMesh;
	D3DXMATRIXA16	_matW;
};

#endif