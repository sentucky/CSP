/***********************************************************************/
/*! @file  common.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___COMMON_HEADER___
#define ___COMMON_HEADER___	//!<インクルードガード

#include"d3d9.h"
#include"d3dx9.h"
#include"commonfunc.h"
#include"commonstruct.h"
#include<vector>
#include<map>
#include<list>


/***********************************************************************/
//	型定義
/***********************************************************************/
typedef signed	 int	sint;
typedef signed	 short	sshort;
typedef signed	 long	slong;

typedef unsigned int	uint;
typedef unsigned short	ushort;
typedef unsigned long	ulong;

typedef char*	FILEPATH;

typedef std::vector<sint> vector_sint;
typedef std::vector<uint> vector_uint;



#ifdef _DEBUG
//	メモリリークチェッカー
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

#endif

#endif
//EOF