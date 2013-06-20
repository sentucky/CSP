/***********************************************************************/
/*! @file  CObjBase.h
 *  @brief オブジェクト基底クラス
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___COBJBASE___
#define ___COBJBASE___

#include"common.h"

class CObjBase
{
public:
	CObjBase(const uint _GroupID);
	virtual ~CObjBase();
	CObjBase(const CObjBase& src);

	virtual void enableTask()	= 0;		///<	タスク有効化
	virtual void disableTask()	= 0;		///<	タスク無効化
	const BOOL getDeleteFlg();				///<	削除フラグ取得
	const uint getID(){return _GroupID;}
protected:
	const uint _GroupID;
	BOOL _DeleteFlg;						///<	削除フラグ
};



#endif