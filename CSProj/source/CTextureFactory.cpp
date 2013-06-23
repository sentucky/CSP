/***********************************************************************/
/*! @file  CTextureFactory.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	�F
//	�T�v			�F
//	�����		�F
//	�X�V����		�F
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CTextureFactory.h"
#include"commonfunc.h"

/***********************************************************************/
//	�R���X�g���N�^
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTextureFactory::CTextureFactory()
{
}
/***********************************************************************/
//	�f�X�g���N�^
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CTextureFactory::~CTextureFactory()
{
	const uint SUMTEXTURE = _vecTexture.size();

	for(uint unCnt = 0; unCnt != SUMTEXTURE; ++unCnt)
	{//	�}�b�v�̐擪����I�[�܂ō폜
		SAFE_DELETE(_vecTexture[unCnt]);
	}
	_vecTexture.clear();	//�}�b�v�v�f�̉��
}
/***********************************************************************/
//	�����o�֐���`
/***********************************************************************/
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] unReserveSize 
 *  @retval void
 */
/***********************************************************************/
void CTextureFactory::reserve(const uint unReserveSize)
{
	_vecTexture.reserve(unReserveSize);
	_vecTexture.resize(unReserveSize);
}

//===================================================================
//	�T�v
//		�e�N�X�`���̓o�^
//	����	
//		char*				�L�[�l�[��
//		char*				�t�@�C���p�X
//	�߂�l
//		BOOL				�o�^�̗L�����ʃt���O
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @param[in,out] pszTextureFilePath 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CTextureFactory::registTexture(const uint nId,const char* pszTextureFilePath)
{
	/////////////////////////
	//	�ϐ��錾
	vec_texture::iterator itr;	//�e�N�X�`���}�X�^�C�e���[�^
	

	/////////////////////////
	//	�d���`�F�b�N
	//----�t�@�C���p�X�̏d���`�F�b�N
	uint SUMTEXTURE = _vecTexture.size();

	if(SUMTEXTURE <= nId)
	{
#ifdef DEBUG
		char szErrorMessage[MAX_PATH];
		sprintf(szErrorMessage,"�e�N�X�`���i�[�z��̗e�ʕs���ł��B\n�e�ʂ�ǉ����܂�",pszTextureFilePath);
		MessageAlert(szErrorMessage,"error from CTextureFatory::registTexture");
#endif
		reserve(nId);
	}

#ifdef DEBUG
	for(uint unCnt = 0; unCnt < SUMTEXTURE; ++unCnt)
	{
		if(_vecTexture[unCnt] == NULL)
		{
			continue;
		}
		if(_vecTexture[unCnt]->getFilePath() == pszTextureFilePath)
		{
			char szErrorMessage[MAX_PATH];
			sprintf(szErrorMessage,"�e�N�X�`���t�@�C��\"%s\"�͊��ɓo�^����Ă��܂�",pszTextureFilePath);
			MessageAlert(szErrorMessage,"error from CTextureFatory::registTexture");
			return FALSE;
		}
	}
#endif
	/////////////////////////
	//	�o�^����
	_vecTexture[nId] = new CTexture(pszTextureFilePath);
	return TRUE;
}


//===================================================================
//	�T�v
//		�e�N�X�`���̉��
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @retval BOOL 
 */
/***********************************************************************/
BOOL CTextureFactory::releaseTexture(const uint nId)
{
	if(_vecTexture[nId] == NULL)
	{
#ifdef DEBUG
		MessageAlert("�w�肳�ꂽ�e�N�X�`���͓o�^����Ă��܂���","error from releaseTexture");
#endif
		return FALSE;
	}

	const uint SUMTEXTURE = _vecTexture.size();

	if(nId >= SUMTEXTURE)
	{
#ifdef DEBUG
		MessageAlert("�e�ʂ𒴂��Ă��܂�","error from releaseTexture");
		return FALSE;
#endif
	}

	SAFE_DELETE(_vecTexture[nId]);
	return TRUE;
}

//===================================================================
//	�T�v
//		�e�N�X�`���̎擾
//	����	
//		char*				�L�[�l�[��
//	�߂�l
//		texture*			�e�N�X�`���|�C���^
//===================================================================
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] nId 
 *  @retval CTexture* 
 */
/***********************************************************************/
CTexture* CTextureFactory::getTexture(const uint nId)
{
	/////////////////////////
	//	�m�F����
	//----�L�[�l�[���̗L��
	if(_vecTexture[nId] == NULL)
	{
#ifdef DEBUG
		char szErrorMessage[MAX_PATH];
		sprintf_s(szErrorMessage,"�e�N�X�`���t�@�N�g���[�L�[\"%d\"��������܂���",nId);
		MessageAlert(szErrorMessage,"error from CTextureFatory::getTexture");
#endif
		return NULL;
	}

	return _vecTexture[nId];
}
//EOF