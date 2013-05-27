/***********************************************************************/
/*! @file  CTankIntPlayer.h
 *  @brief タンク　プレイヤー思考
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef ___CTANKINTPLAYER___
#define ___CTANKINTPLAYER___	///<	インクルードガード


/***********************************************************************/
//	インクルードガード
/***********************************************************************/
#include"CTankIntInter.h"
#include"CListItem.h"

class CTank;
class CObjBase;


/***********************************************************************/
/*!	@class	CTankIntPlayer
 *	@brift	タンクのプレイヤー思考クラス
 */
/***********************************************************************/
class CTankIntPlayer:public CTankIntInter
{
public:
	CTankIntPlayer(CTank* pPlayerTank);	//	コンストラクタ
	~CTankIntPlayer();	//	デストラクタ
private:
	void update();	//	フラグの更新
	void moveSight();	//	照準移動
	
	CListItem<CObjBase*>*  _pList;
	
};

#endif