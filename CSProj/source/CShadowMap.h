/***********************************************************************/
/*! @file  CShadowMap.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#ifndef ___CSHADOWMAP___
#define ___CSHADOWMAP___
#if 1

#include"CEffectBase.h"

#include"CDevice.h"
#include"d3dx9.h"

class CMesh;
#include"d3dx9effect.h"

class CShadowMap:public CEffectBase
{
public:
	CShadowMap(
		const char path[MAX_PATH],
		const char FXFilePath[MAX_PATH]);
	~CShadowMap();
	CShadowMap(const CShadowMap& src);


private:
	void create();
	void draw(CMesh* pMesh, const D3DXMATRIXA16* matWorld);
	void draw1(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix);
	void draw2(CMesh* pMesh,const D3DXMATRIXA16* matWorld, const D3DXMATRIXA16* lightVpMatrix);

	D3DXHANDLE _techniqueHandle;	///<
	D3DXHANDLE _wvpHandle;			///<���[���h�r���[�v���W�F�N�V����
	D3DXHANDLE _wlpHandle;			///<���C�g�
	D3DXHANDLE _wlpbHandle;			///<
	D3DXHANDLE _colorHandle;		///<
	D3DXHANDLE _lightDirHandle;		///<
	D3DXHANDLE _DecaleTexHandle;	///<
	D3DXHANDLE _ShadowTexHandle;	///<


	LPDIRECT3DTEXTURE9 _ShadowTex;						//!< �e�e�N�X�`��
	LPDIRECT3DSURFACE9 shadowSurf_;						//!< �e�e�N�X�`���쐬�p�̃T�[�t�F�X
	LPDIRECT3DSURFACE9 shadowTexZ_;						//!< �e�e�N�X�`���쐬�p��Z�o�b�t�@

public:
	D3DXMATRIXA16 landMat;
	CMesh* _pMeshLand;
};

#endif
#endif