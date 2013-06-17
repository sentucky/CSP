/***********************************************************************/
/*! @file  CAnimeParam.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CANIMEPARAM___
#define ___CANIMEPARAM___

#include"common.h"

class ANIMEPATH;

struct FrameData
{
	uint	FrameCnt;
	RECTEX	UV;
};

enum ANIME_STATE
{
	PLAY,
	STOP,
	PLAY_LOOP,
};

class CAnimeParam
{
public:
	CAnimeParam(ANIMEPATH& APath);
	~CAnimeParam();
	void update();

	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const uint 
	 */
	/***********************************************************************/
	const uint getCat()		{return _Cat;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval const uint 
	 */
	/***********************************************************************/
	const uint getState()	{return _State;}
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @retval RECTEX& 
	 */
	/***********************************************************************/
	RECTEX& getUV()			{return _frameData[_Cat].UV;}

	void setCat(const uint Cat);
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] State 
	 *  @retval void
	 */
	/***********************************************************************/
	void setState(const uint State){_State = State;}
private:
	FrameData* _frameData;
	uint _Cat;
	uint _Cnt;
	uint _State;
	uint _MaxCat;
};

#endif