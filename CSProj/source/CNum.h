/***********************************************************************/
/*! @file  CNum.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CNUM___
#define ___CNUM___

class CSprite;
class CTaskList;

#include"common.h"
#include"CObjBase.h"


enum eDRAWMODE
{
	POINT_RIGHT,
	POINT_LEFT,
};

class CNum:public CObjBase
{
public:
	CNum();
	~CNum();
	CNum(const CNum& src);

	void enableTask();
	void disableTask();
private:
	void releaseSprite();
public:
	void draw();
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] DrawMode 
	 *  @retval void
	 */
	/***********************************************************************/
	void setDrawMode(uint DrawMode){_DrawMode = DrawMode;}

private:
	void DMR();
	void DML();

public:
	void addNum(const int num);
	void setNum(const int num);
	void transPos(const float x, const float y, const float z);
	void setPos(D3DXVECTOR3& pos);

private:
	CTaskList* _TaskDraw;

	int		_Num;
	float	_xlen;

	D3DXVECTOR3 _Pos;
	D3DXVECTOR3 _Rot;
	D3DXVECTOR3 _Scale;
	CSprite* _NumSprite[10];

	uint _DrawMode;
	BOOL _flgProto;

};


#endif