#ifndef ___CBUMPMAP___
#define ___CBUMPMAP___

#include"CEffectBase.h"
#include"CDevice.h"
#include"d3dx9effect.h"

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
	CBumpMap(char FXFilePath[MAX_PATH]);
	~CBumpMap();
	

	void release();

	BOOL create();
	BOOL cloneCreate();


	void setMaterial(D3DMATERIAL9* pMaterial);
	void setTexture(LPDIRECT3DTEXTURE9 pTexture);

	void setWorldMatrix( D3DXMATRIXA16* pMatrix);

	void setCameraPos(LPD3DXVECTOR3 pCameraPos);

	void setHandle(uint HandleID, D3DXHANDLE Handle){*(_Handles + HandleID) =  Handle;};
	void setBumpTex(LPDIRECT3DTEXTURE9 Tex, LPDIRECT3DTEXTURE9 NormalTex);
private:
	D3DXHANDLE		_Handles[SUM_HANDLES];
	D3DXHANDLE		_HandleNormalMap;
	D3DXHANDLE		_HandleTex;

	D3DXEFFECT_DESC _Desc;


	static const char* _params[SUM_HANDLES];
};



#endif