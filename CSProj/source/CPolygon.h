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
 *	@brift	�|���S���̃N���X
 */
/***********************************************************************/
class CPolygon
{
public:
	/***********************************************************************/
	///<@brift	���_�^�C�v
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
	D3DXVECTOR3 pos;		///<	���W
	D3DXVECTOR3 Tangent;	///<
	D3DXVECTOR3 NormalVec;	///<	�@��
	D3DXVECTOR2 UV;			///<	uv���W
};
public:
	/***********************************************************************/
	//	Decl�̐ݒ�
	/***********************************************************************/
	class VtxDecl
	{
	public:
		/***********************************************************************/
		//	�R���X�g���N�^�E�f�X�g���N�^
		/***********************************************************************/
		VtxDecl();
		~VtxDecl();


		/***********************************************************************/
		//	�֐�
		/***********************************************************************/
		void init();
		void release();

		//	�Q�b�^
		D3DVERTEXELEMENT9*	getDecl(uint VtxBufType){return DeclAry_[VtxBufType];}
		const uint			getVtxBufSize(uint VtxBufType){return VtxBufSize_[VtxBufType];}
	private:
		/***********************************************************************/
		//	�ÓI�ϐ�
		/***********************************************************************/
		static D3DVERTEXELEMENT9	*(DeclAry_[VBT_SUM]);
		static uint					VtxBufSize_[VBT_SUM];
		static int					SumInst_;
	};
	/***********************************************************************/
	//	�R���X�g���N�^�E�f�X�g���N�^
	/***********************************************************************/
	CPolygon();
	~CPolygon();
	
	
	/***********************************************************************/
	//	�֐�
	/***********************************************************************/
	void release();

	HRESULT setVtxBufType(uint VtxBufType,uint NumVtx);
	HRESULT createVtxBuf(uint BufLen,uint NumVtx);

	void draw();
	HRESULT LockVtx(void**);
	HRESULT UnLockVtx();
	//	�Z�b�^
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
	//	�ϐ�
	/***********************************************************************/
	IDirect3DVertexDeclaration9*	decl_;			///<���_�f�R���[�V�����iFVF�j
	IDirect3DVertexBuffer9*			VtxBuf_;		///<���_�o�b�t�@
	uint							CurVtxType_;	///<���݂̒��_�`��

	/***********************************************************************/
	//	�ÓI�ϐ�
	/***********************************************************************/
	static LPDIRECT3DDEVICE9		Device_;		///<�f�o�C�X
	static VtxDecl					VtxDeclInfo_;




};

#endif