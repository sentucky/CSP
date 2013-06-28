/***********************************************************************/
/*! @file  CFont.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"CFont.h"
#include<stdio.h>

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CFont::CFont()
{
	init();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CFont::~CFont()
{
	release();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CFont::init()
{
	_Color = D3DCOLOR_XRGB(255,255,255);

	_LogFont.Height = 20;
	_LogFont.Width = 10;
	_LogFont.Weight = FW_NORMAL;
	_LogFont.MipLevels = 0;
	_LogFont.Italic = FALSE;
	_LogFont.CharSet = 0;
	_LogFont.OutputPrecision = 0;
	_LogFont.Quality = DEFAULT_QUALITY;
	_LogFont.PitchAndFamily = DEFAULT_PITCH || FF_DONTCARE;
	lstrcpy( _LogFont.FaceName,"ゴシック");

	D3DXCreateFontIndirect(D3DDEVICE, &_LogFont, &_pFont);
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] Height 
 *  @param[in,out] Width 
 *  @param[in,out] Weight 
 *  @retval void
 */
/***********************************************************************/
void CFont::init(
		INT               Height,
		UINT              Width,
		UINT              Weight
)
{
	/*
		_LogFont.Height				= Height;
		_LogFont.Width				= Width;
		_LogFont.Weight				= FW_NORMAL;
		_LogFont.MipLevels			= 0;
		_LogFont.Italic				= FALSE;
		_LogFont.CharSet			= 0;
		_LogFont.OutputPrecision	= 0;
		_LogFont.Quality			= DEFAULT_QUALITY;
		_LogFont.PitchAndFamily		= DEFAULT_PITCH || FF_DONTCARE;
		lstrcpy( _LogFont.FaceName,"ゴシック");

		D3DXCreateFontIndirect(D3DDEVICE, &_LogFont, &_pFont);
		*/
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CFont::release()
{
	_pFont->Release();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] charpStr[MAX_PATH] 
 *  @param[in,out] rect 
 *  @retval void
 */
/***********************************************************************/
void CFont::DrawStr(char pStr[MAX_PATH], RECT& rect)
{

	_pFont->DrawText(
		NULL,
		pStr,
		-1,
		&rect,
		DT_LEFT | DT_NOCLIP,
		_Color
		);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] charpStr[MAX_PATH] 
 *  @param[in,out] nNum 
 *  @param[in,out] rect 
 *  @retval void
 */
/***********************************************************************/
void CFont::DrawInt(char pStr[MAX_PATH], int nNum, RECT& rect)
{
	char pStr2[MAX_PATH] = {0,};
	sprintf_s(pStr2,"%s:%04d",pStr,nNum);
/*
	_pFont->DrawText(
		NULL,
		pStr2,
		-1,
		&rect,
		DT_LEFT | DT_NOCLIP,
		_Color
		);
		*/
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] charpStr[MAX_PATH] 
 *  @param[in,out] fNum 
 *  @param[in,out] rect 
 *  @retval void
 */
/***********************************************************************/
void CFont::DrawFloat(char pStr[MAX_PATH], float fNum, RECT& rect)
{
	/*
	char pStr2[MAX_PATH] = {0,};
	sprintf_s(pStr2,"%s:%04f",pStr,fNum);

	_pFont->DrawText(
		NULL,
		pStr2,
		-1,
		&rect,
		DT_LEFT | DT_NOCLIP,
		_Color
		);
		*/
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] charpStr[MAX_PATH] 
 *  @param[in,out] lNum 
 *  @param[in,out] rect 
 *  @retval void
 */
/***********************************************************************/
void CFont::DrawLong(char pStr[MAX_PATH], long lNum, RECT& rect)
{
	/*
	char pStr2[MAX_PATH] = {0,};
	sprintf_s(pStr2,"%s:%d",pStr,lNum);

	_pFont->DrawText(
		NULL,
		pStr2,
		-1,
		&rect,
		DT_LEFT | DT_NOCLIP,
		_Color
		);
		*/
}
