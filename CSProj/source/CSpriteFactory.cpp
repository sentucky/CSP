/***********************************************************************/
/*! @file  CSpriteFactory.cpp
 *  @brief	�X�v���C�g�t�@�N�g��
 *  
 *  @author �쌴�@�C��
 *  @date	
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CSpriteFactory.h"
#include"CSprite.h"
#include"common.h"

/***********************************************************************/
/*! @brief �R���X�g���N�^
 */
/***********************************************************************/
CSpriteFactory::CSpriteFactory()
{
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] constCSpriteFactory& 
 *  @retval  
 */
/***********************************************************************/
CSpriteFactory::CSpriteFactory(const CSpriteFactory&)
{
}

/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CSpriteFactory::~CSpriteFactory()
{
}

/***********************************************************************/
/*! @brief �X�v���C�g�쐬
 * 
 *  @param[in] nId 
 *  @retval CSprite* 
 */
/***********************************************************************/
CSprite* CSpriteFactory::create(const int nId)
{
	//	�ϐ��錾
	CTexture*	pTex = NULL;

	//	�e�N�X�`���L�[�`�F�b�N
	pTex =  TEXTUREFACTORY->getTexture( nId);
#ifdef DEBUG
	if(NULL == pTex)
	{
		MessageAlert("����Ȗ��O�̃e�N�X�`���Ȃ��ł�","erorr from CSpriteFactory::create");
		return NULL;
	}
#endif
	return 	new CSprite(pTex);
}


/***********************************************************************/
/*! @brief �e�N�X�`���o�^
 * 
 *  @param[in] nId 
 *  @param[in] constcharszTextureFilePath[MAX_PATH] 
 *  @retval const BOOL 
 */
/***********************************************************************/
const BOOL CSpriteFactory::registTexture(
	const int nId,
	const char szTexFilePath[MAX_PATH]
)
{
	return TEXTUREFACTORY->registTexture( nId,szTexFilePath);
}

//EOF