/***********************************************************************/
/*! @file  CMeshFactory.cpp
 *  @brief �V���O���g��
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CMeshFactory.h"


CMeshFactory::CMeshFactory(){}
/***********************************************************************/
/*! @brief �f�X�g���N�^
 * 
 *  @retval  
 */
/***********************************************************************/
CMeshFactory::~CMeshFactory(){
	release();
	_vectorMesh.clear();
}


/***********************************************************************/
/*! @brief ���b�V����n��
 * 
 *  @param[in] unMeshKeyName ���b�V���t�@�C���p�X
 *  @retval CMesh* 
 */
/***********************************************************************/
CMesh* CMeshFactory::create(const uint unMeshKeyName)
{
	//	���o�^������
#ifdef _DEBUG
	if(_vectorMesh[unMeshKeyName] == NULL)
	{
		MessageAlert("����Ȗ��O�̃��b�V���Ȃ��ł�","error from CModelFactory::create");
		return NULL;
	}

	const uint SUMMESH = _vectorMesh.size();

	if(unMeshKeyName >= SUMMESH)
	{
		MessageAlert("�e�ʂ�����Ă��܂���","error from CModelFactory::create");
		return NULL;
	}

#endif
	return new CMesh(*_vectorMesh[unMeshKeyName]);
}


/***********************************************************************/
/*! @brief ���b�V���̓o�^
 * 
 *  @param[in] unKeyName		���b�V���̌ʔԍ�
 *  @param[in] pszMeshFilePath	���b�V���t�@�C���p�X
 *  @retval BOOL 
 */
/***********************************************************************/
void CMeshFactory::registMesh(const uint unKeyName,const char*pszMeshFilePath)
{
	//	�ϐ��錾
	const uint SUMMESH = _vectorMesh.size();

	//	�d���`�F�b�N
	//----�L�[�l�[���̏d���`�F�b�N
	if(_vectorMesh[unKeyName] != NULL)
	{
#ifdef _DEBUG
		MessageAlert("�o�^�ςݔԍ�","error from CMeshFactory::registMesh");
#endif
		return;
	}
	//----�t�@�C���p�X�̏d���`�F�b�N
	for(uint unCnt = 0; unCnt < SUMMESH;++unCnt)
	{
		if(_vectorMesh[unCnt] == NULL)
		{
			continue;
		}
		if(_vectorMesh[unCnt]->_szMeshFileName == pszMeshFilePath)
		{
#ifdef _DEBUG
		MessageAlert("�t�@�C���p�X���d�����Ă��܂�","error from CMeshFactory::registMesh");
#endif
			return;
		}
	}
	//	�o�^����
	_vectorMesh[unKeyName] = new CMesh(pszMeshFilePath);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CMeshFactory::release()
{
	const uint SUMMESH = _vectorMesh.size();
	for(uint unCnt = 0; unCnt < SUMMESH; ++unCnt)
	{
		SAFE_DELETE(_vectorMesh[unCnt]);
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @param[in] unReserveSize 
 *  @retval void
 */
/***********************************************************************/
void CMeshFactory::reserve(const uint unReserveSize)
{
	_vectorMesh.reserve(unReserveSize);
	_vectorMesh.resize(unReserveSize);
}

//EOF