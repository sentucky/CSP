/***********************************************************************/
/*! @file  CFont.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

/***********************************************************************/
//	�w�b�_�t�@�C��
/***********************************************************************/
#include<d3dx9.h>
#include<d3d9.h>
#include"CSingleton.h"
#include"CDevice.h"
#include"commonstruct.h"

/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define FONT CFont::getInst()	//	�C���X�^���X�̎擾


class CFont:public CSingleton<CFont>
{
	friend class CSingleton<CFont>;
private:
	explicit CFont();
	~CFont();
public:
	void init();	///<	������
	void init(INT Height,UINT Width,UINT Weight);	///<	������������
	void release();									///<	�J��
	void DrawStr(char	pStr[MAX_PATH],RECT& rect);	///<	������`��
	void DrawInt(char	pStr[MAX_PATH], int		nNum, RECT& rect);	///<	�����`��
	void DrawFloat(char pStr[MAX_PATH], float	fNum, RECT& rect);	///<	�����`��
	void DrawLong(char	pStr[MAX_PATH], long	lNum, RECT& rect);	///<	32�r�b�g�����`��
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] color 
	 *  @retval void
	 */
	/***********************************************************************/
	void setColor(D3DCOLOR color){_Color = color;}					///<	�`��F�ݒ�

	//++++++++++++++++++++++++++++++++++++
	//	�����o�ϐ�
	//++++++++++++++++++++++++++++++++++++
private:
	LPD3DXFONT _pFont;		///<	�`��t�H���g
	D3DXFONT_DESC _LogFont;	
	D3DCOLOR _Color;		///<	�`��F
};

