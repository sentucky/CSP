/***********************************************************************/
/*! @file  CObjBase.h
 *  @brief �I�u�W�F�N�g���N���X
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

	virtual void enableTask()	= 0;		///<	�^�X�N�L����
	virtual void disableTask()	= 0;		///<	�^�X�N������
	const BOOL getDeleteFlg();				///<	�폜�t���O�擾
	const uint getID(){return _GroupID;}
protected:
	const uint _GroupID;
	BOOL _DeleteFlg;						///<	�폜�t���O
};



#endif