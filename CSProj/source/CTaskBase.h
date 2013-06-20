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

	virtual void run() = 0;		//!<	ˆ—ŠÖ”
	const uint getID();
private:
	const	uint			_unTaskID;		//!<	ƒ^ƒXƒN”Ô†
};

#endif