/***********************************************************************/
/*! @file  CTexture.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	�t�@�C����	
//	�T�v			
//	�����		
//	�X�V����		
/***********************************************************************/
//===================================================================
//	�C���N���[�h�K�[�h
//===================================================================
#pragma once
//===================================================================
//	�C���N���[�h
//===================================================================
#include<d3dx9.h>
#include<d3d9.h>
#include"CDevice.h"
#include"commonfunc.h"
//===================================================================
//	�N���X��`
//===================================================================
class CTexture
{
	//===========================================
	//	�t�����h�N���X
	//===========================================
	friend class CTextureFactory;	///<�e�N�X�`���t�@�N�g���[
	FRIEND_DELETE
	FRIEND_RELEASE

	//===========================================
	//	�R���X�g���N�^	
	//===========================================
private:
	CTexture(const char* pszFilePath);

	//===========================================
	//	�f�X�g���N�^		
	//===========================================
	~CTexture();

	//===========================================
	//	�����o�֐�		
	//===========================================
private:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const char* 
	 */
	/***********************************************************************/
	const char*				 getFilePath()const{return _pszFilePath;}
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval D3DXIMAGE_INFO 
	 */
	/***********************************************************************/
	D3DXIMAGE_INFO			 getSrcInfoRef()const{return _srcInfo;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const LPDIRECT3DTEXTURE9 
	 */
	/***********************************************************************/
	const LPDIRECT3DTEXTURE9 getTexture()const{return _texture;};
	void setFilePath(const char* pszFilePath);

	//===========================================
	//	�����o�ϐ�		
	//===========================================
private:
	const char*			_pszFilePath;
	LPDIRECT3DTEXTURE9	_texture;
	D3DXIMAGE_INFO		_srcInfo;
};
//EOF