/***********************************************************************/
/*! @file  CTaskList.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTASKLIST___
#define ___CTASKLIST___

#include"CListItem.h"

class CTaskBase;

class CTaskList:public CListItem<CTaskBase*>
{
};

#endif
