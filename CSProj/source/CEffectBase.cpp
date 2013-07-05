/***********************************************************************/
/*! @file  CEffectBase.cpp
 *  @brief エフェクトベース
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
/***********************************************************************/
//	インクルード
/***********************************************************************/
#include"CEffectBase.h"
#include"CDevice.h"

CEffectBase::CEffectBase(
	char FXFilePath[MAX_PATH]
):	_FxPath	(FXFilePath),
	_Effect	(NULL)
{
}

CEffectBase::~CEffectBase()
{
}

CEffectBase::CEffectBase(
	const CEffectBase& src
	)
	:_FxPath	(src._FxPath),
	_Effect		(NULL		)
{
	src._Effect->CloneEffect(D3DDEVICE,&_Effect);
}

void CEffectBase::release()
{
	_FxPath = NULL;
	SAFE_RELEASE(_Effect);
}

uint CEffectBase::begin(uint Technique)
{
	if(_Effect == NULL)
	{
		return 0;
	}

	uint MaxPath = 0;
	D3DXHANDLE TechHandle = _Effect->GetTechnique(Technique);
	_Effect->SetTechnique(TechHandle);
	if (FAILED(_Effect->Begin(&MaxPath, 0))) {
		MaxPath = 0;
	}
	return MaxPath;
}

void CEffectBase::end()
{
	_Effect->End();
}

BOOL CEffectBase::beginPass(uint Pass)
{
	if(_Effect == NULL)
		return FALSE;

	return SUCCEEDED(_Effect->BeginPass(Pass));
}

void CEffectBase::endPass()
{
	if(_Effect == NULL)
		return;

	_Effect->EndPass();
}


void CEffectBase::commitChanges()
{
	if(_Effect != NULL)_Effect->CommitChanges();
}