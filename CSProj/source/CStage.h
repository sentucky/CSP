/***********************************************************************/
/*! @file  CStage.h
 *  @brief �X�e�[�W�I�u�W�F�N�g
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSTAGE___
#define ___CSTAGE___	///<	�C���N���[�h�K�[�h

/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CObjBase.h"


/***********************************************************************/
//	��s�錾
/***********************************************************************/
class CMesh;
class CTaskList;

/***********************************************************************/
/*!
 *	@class	CStage
 *	@brift	�X�e�[�W�I�u�W�F�N�g
 */
/***********************************************************************/
class CStage:public CObjBase
{
public:
	CStage(
		const char* StageDataPath,
		CMesh* pMesh
		);
	~CStage();
	CStage(const CStage& src);
	void release();
	void enableTask();
	void disableTask();
	void draw();
private:
	const char*		_StageFilePath;

	CTaskList*		_pTaskDraw;	///<	�`��֐�
	CMesh*			_Mesh;		///<	���b�V��
	D3DXMATRIXA16	_matW;		///<	�}�g���N�X
};

#endif