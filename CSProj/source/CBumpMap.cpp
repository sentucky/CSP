#include"CBumpMap.h"
#include"CCamera.h"
#include"CScreen.h"

const char* CBumpMap::_params[CBumpMap::SUM_HANDLES] =
{
	"LIGHTDIR",
	"CAMERAPOSITION",
	"WORLD",
	"VIEW",
	"PROJECTION",
	"WORLDVIEW",
	
	"VIEWPROJECTION",
	"WORLDVIEWPROJECTION",

	"MATERIALAMBIENT",
	"MATERIALDIFFUSE",
	"MATERIALSPECULAR",
	"MATERIALPOWER",
	"MATERIALTEXTURE",
	"MATERIALTEXTUREVALID",
	"NORMALMAP",
};

CBumpMap::CBumpMap(char FXFilePath[MAX_PATH])
	:CEffectBase(FXFilePath),
	_HandleNormalMap(0),
	_HandleTex(0)
{
	release();
}

CBumpMap::~CBumpMap()
{
	release();
}

void CBumpMap::release()
{
	CEffectBase::release();
	memset(_Handles,0,sizeof(_Handles));
	memset(&_Desc,0,sizeof(_Desc));
}

BOOL CBumpMap::create()
{
	release();

	LPD3DXBUFFER error = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		D3DDEVICE,
		_FxPath,
		NULL,
		NULL,
		0,
		NULL,
		&_Effect,
		&error);

	if(FAILED(hr))
	{
		MessageAlert((char*)error->GetBufferPointer(),"error from CBumpMat::create");
		SAFE_RELEASE(error);
		return FALSE;
	}

	_Effect->GetDesc(&_Desc);

	for(uint Cnt = 0; Cnt < SUM_HANDLES; ++Cnt){
		_Handles[Cnt] = _Effect->GetParameterBySemantic(NULL,_params[Cnt]);
	}


	if (_Effect) {
		//	if (_Effect && _Handles[H_PROJ]) 
		{
			_Effect->SetMatrix(_Handles[H_PROJ], CSCREEN->getMatProj());
		}
		//if (_Handles[H_VIEW]) 
		{
			_Effect->SetMatrix(_Handles[H_VIEW], CCamera::getMatView());
		}
		if (_Handles[H_VP]) {
			_Effect->SetMatrix(_Handles[H_VP], &(*CCamera::getMatView() * *CSCREEN->getMatProj()));
		}
	}

	_Effect->SetTechnique(_Effect->GetTechniqueByName("TBump"));
	SAFE_RELEASE(error);
	return TRUE;
}

BOOL CBumpMap::cloneCreate()
{
	return TRUE;
}


void CBumpMap::setMaterial(D3DMATERIAL9* pMaterial)
{
	if (_Effect == NULL || pMaterial == NULL) {
		return;
	}
	if (_Handles[H_AMBI]) {
		_Effect->SetVector(_Handles[H_AMBI], (LPD3DXVECTOR4)&pMaterial->Ambient);
	}
	if (_Handles[H_DIFF]) {
		_Effect->SetVector(_Handles[H_DIFF], (LPD3DXVECTOR4)&pMaterial->Diffuse);
	}
	if (_Handles[H_SPEC]) {
		_Effect->SetVector(_Handles[H_SPEC], (LPD3DXVECTOR4)&pMaterial->Specular);
	}
	if (_Handles[H_POW]) {
		_Effect->SetFloat(_Handles[H_POW], pMaterial->Power);
	}
}


void CBumpMap::setWorldMatrix( D3DXMATRIXA16* pMatrix)
{
	if (_Effect)
	{
		if(_Handles[H_WORLD])
		{
			_Effect->SetMatrix(_Handles[H_WORLD], pMatrix);
		}
		if(_Handles[H_WV])
		{
			_Effect->SetMatrix(_Handles[H_WV], &(*pMatrix * *CCamera::getMatView()));
		}
		if(_Handles[H_WVP])
		{
			_Effect->SetMatrix(_Handles[H_WVP], &(*pMatrix * *CCamera::getMatView() * *CSCREEN->getMatProj()));
		}

	}
}

void CBumpMap::setLightDir(const D3DXVECTOR3*const LightDir)
{
	if (_Effect && LightDir) {
		_Effect->SetVector(
			_Handles[H_LIGHTDIR],
			&D3DXVECTOR4(LightDir->x,LightDir->y,LightDir->z,1.0f)
			);
	}
}


void CBumpMap::setCameraPos(LPD3DXVECTOR3 pCameraPos)
{
	if (_Effect && pCameraPos) {
		_Effect->SetVector(_Handles[H_CAMERA],
			&D3DXVECTOR4(pCameraPos->x, pCameraPos->y, pCameraPos->z, 1.0f));
	}
}

void CBumpMap::setTex(LPDIRECT3DTEXTURE9 tex)
{
	if(_Effect)
	{
		if(_Handles[H_TEX])
		{
			_Effect->SetTexture(_Handles[H_TEX],tex);
		}
	}
}


void CBumpMap::setBumpTex(LPDIRECT3DTEXTURE9 pTex,LPDIRECT3DTEXTURE9 pNormalTex)
{
	if(_Effect)
	{
		if(_Handles[H_TEX])
		{
			_Effect->SetTexture(_Handles[H_TEX],pTex);
		}
		if(_Handles[H_BUMPTEX])
		{
			_Effect->SetTexture(_Handles[H_BUMPTEX],pNormalTex);		
		}
		if (_Handles[H_BTEX]) {
			_Effect->SetBool(_Handles[H_BTEX], pTex != NULL);
		}
	}
}