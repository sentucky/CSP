/***********************************************************************/
/*! @file  CTaskBase.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTASKBASE___
#define ___CTASKBASE___

#include"common.h"

class CTaskBase
{
public:
	CTaskBase(const uint unTaskID);
	virtual ~CTaskBase();
private:
	CTaskBase(const CTaskBase& copy);
	void operator =(const CTaskBase& src);

public:

	virtual void run() = 0;		//!<	処理関数
	const uint getTaskID();
private:
	const	uint			_unTaskID;		//!<	タスク番号
};

#endif