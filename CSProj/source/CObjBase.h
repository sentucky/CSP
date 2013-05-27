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
	CObjBase();
	virtual ~CObjBase();

	virtual void enableTask()	= 0;		///<	タスク有効化
	virtual void disableTask()	= 0;		///<	タスク無効化
	const BOOL getDeleteFlg();				///<	削除フラグ取得
protected:
	BOOL _DeleteFlg;						///<	削除フラグ
};



#endif