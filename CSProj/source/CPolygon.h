/***********************************************************************/
/*! @file  CPolygon.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CPOLYGON___
#define ___CPOLYGON___

#include"common.h"



/***********************************************************************/
/*!	@class	CPolygon
 *	@brift	ポリゴンのクラス
 */
/***********************************************************************/
class CPolygon
{
public:
	/***********************************************************************/
	///<@brift	頂点タイプ
	/***********************************************************************/
	enum eVERTEXBUFFER_TYPE{
		VBT_POS_TAN_NOR_UV,
		VBT_SUM,
		VBT_NONE,
		VBT_EX,
//		VBT_POS_COR_UV,
	};

	struct VB_PTNU
{
	D3DXVECTOR3 pos;		///<	座標
	D3DXVECTOR3 Tangent;	///<
	D3DXVECTOR3 NormalVec;	///<	法線
	D3DXVECTOR2 UV;			///<	uv座標
};
public:
	/***********************************************************************/
	//	Declの設定
	/***********************************************************************/
	class VtxDecl
	{
	public:
		/***********************************************************************/
		//	コンストラクタ・デストラクタ
		/***********************************************************************/
		VtxDecl();
		~VtxDecl();


		/***********************************************************************/
		//	関数
		/***********************************************************************/
		void init();
		void release();

		//	ゲッタ
		D3DVERTEXELEMENT9*	getDecl(uint VtxBufType){return DeclAry_[VtxBufType];}
		const uint			getVtxBufSize(uint VtxBufType){return VtxBufSize_[VtxBufType];}
	private:
		/***********************************************************************/
		//	静的変数
		/***********************************************************************/
		static D3DVERTEXELEMENT9	*(DeclAry_[VBT_SUM]);
		static uint					VtxBufSize_[VBT_SUM];
		static int					SumInst_;
	};
	/***********************************************************************/
	//	コンストラクタ・デストラクタ
	/***********************************************************************/
	CPolygon();
	~CPolygon();
	
	
	/***********************************************************************/
	//	関数
	/***********************************************************************/
	void release();

	HRESULT setVtxBufType(uint VtxBufType,uint NumVtx);
	HRESULT createVtxBuf(uint BufLen,uint NumVtx);

	void draw();
	HRESULT LockVtx(void**);
	HRESULT UnLockVtx();
	//	セッタ
	static void setDevice(LPDIRECT3DDEVICE9 Device){Device_ = Device;}

	HRESULT setPos(const D3DXVECTOR3* Pos,kuint VtxNum);
	HRESULT setPos(kfloat x, kfloat y, kfloat z, kuint VtxNum);
	HRESULT setUV(const D3DXVECTOR2* UV, kuint VtxNum);
	HRESULT setUV(kfloat x,kfloat y, kuint VtxNum);
	HRESULT setNormal(const D3DXVECTOR3* NormalVector, kuint VtxNum);
	HRESULT setNormal(kfloat x, kfloat y, kfloat z, kuint VtxNum);
	HRESULT setTangent(const D3DXVECTOR3* Tangent, kuint VtxNum);
	HRESULT setTangent(kfloat x, kfloat y, kfloat z, kuint VtxNum);
	HRESULT setVtxBuf(void* VtxBuf,kuint VtxBufType,kuint VtxNum);

private:
	/***********************************************************************/
	//	変数
	/***********************************************************************/
	IDirect3DVertexDeclaration9*	decl_;			///<頂点デコレーション（FVF）
	IDirect3DVertexBuffer9*			VtxBuf_;		///<頂点バッファ
	uint							CurVtxType_;	///<現在の頂点形式

	/***********************************************************************/
	//	静的変数
	/***********************************************************************/
	static LPDIRECT3DDEVICE9		Device_;		///<デバイス
	static VtxDecl					VtxDeclInfo_;




};

#endif