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
	CObjBase();
	virtual ~CObjBase();

	virtual void enableTask()	= 0;		///<	�^�X�N�L����
	virtual void disableTask()	= 0;		///<	�^�X�N������
	const BOOL getDeleteFlg();				///<	�폜�t���O�擾
protected:
	BOOL _DeleteFlg;						///<	�폜�t���O
};



#endif