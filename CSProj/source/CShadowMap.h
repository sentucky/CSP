#ifndef ___CSHADOWMAP___
#define ___CSHADOWMAP___
#if 0

#include"CEffectBase.h"

#include"CDevice.h"
class CMesh;


class CShadowMap:public CEffectBase
{
public:
	CShadowMap(const char FXFilePath[MAX_PATH]);
	~CShadowMap();
	CShadowMap(const CShadowMap& src);

private:
	void create();
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);
	void drawDepth(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix);

	D3DXHALDE _techniqueHandle;	//
	D3DXHALDE _wvpHandle;		//���[���h�r���[�v���W�F�N�V����
	D3DXHALDE _wlpHandle;		//���C�g�
	D3DXHALDE _wlpbHandle;		//
	D3DXHALDE _colorHandle;		//
	D3DXHALDE _lightDirHandle;	//
	D3DXHALDE _DecaleTexHandle;	//
	D3DXHALDE _ShadowTexHandle;	//
};

#endif
#endif