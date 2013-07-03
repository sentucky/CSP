#ifndef ___CBUMPMAP___
#define ___CBUMPMAP___

#include"CEffectBase.h"
#include"CDevice.h"

class CBumpMap:public CEffectBase
{
public:
	enum eBUMP_HANDLE{
		H_CAMERA,
		H_WORLD,
		H_VIEW,
		H_PROJ,
		H_WV,
		H_VP,
		H_WVP,
		H_AMBI,
		H_DIFF,
		H_SPEC,
		H_POW,
		H_TEX,
		H_BTEX,	//	バンプテクスチャ
		SUM_HANDLES,
	};
public:
	CBumpMap();
	~CBumpMap();
	
	void create();
	void release();

	void setMaterial();

	void setHandle(uint HandleID, D3DXHANDLE Handle){*(_Handles + HandleID) = Handle;};
	void setTexture(LPDIRECT3DTEXTURE9 Tex, LPDIRECT3DTEXTURE9 NormalTex);
	void begin();
	void end();
private:
	D3DXHANDLE		_Handles[SUM_HANDLES];
	D3DXEFFECT_DECL _Decl;
};



#endif