/***********************************************************************/
/*! @file  CMeshFactory.h
 *  @brief ���b�V���t�@�N�g��
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h�K�[�h
/***********************************************************************/
#pragma once
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CMesh.h"
#include"commonfunc.h"
#include"CSingleton.h"
#include<vector>

/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define MESHFACTORY	CMeshFactory::getInst()


/***********************************************************************/
//	�N���X��`
/***********************************************************************/
class CMeshFactory:public CSingleton<CMeshFactory>
{
	//	�t�����h�o�^
	friend class CSingleton<CMeshFactory>;
private:
	CMeshFactory();						///<	�R���X�g���N�^
	CMeshFactory(const CMeshFactory&);	///<	�R�s�[�R���X�g���N�^
	~CMeshFactory();					///<	�f�X�g���N�^

public:
	CMesh* create(const uint nMeshKeyName);	///<	���b�V���쐬
	void registMesh(const uint unKeyName,const char*pszMeshFilePath);	///<	���b�V���o�^
	void release();							///<	�������
	void reserve(const uint unReserveSize);	///<	�e�ʗ\��


private:
	typedef std::vector<CMesh*> vector_mesh;
	vector_mesh _vectorMesh;					//!< ���b�V���̌��^������x�N�^
};
//EOF