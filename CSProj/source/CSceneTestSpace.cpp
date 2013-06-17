/***********************************************************************/
/*! @file  CSceneTestSpace.cpp
 *  @brief �e�X�g���
 *  
 *  @author �쌴�@�C��
 *  @date 
 */
/***********************************************************************/
#include"CSceneTestSpace.h"
#include"const.h"
#include"CSpriteFactory.h"
#include"CMeshFactory.h"

#include"CCamera.h"
#include"CLight.h"
#include"CScreen.h"
#include"CEffect.h"
#include"CEffectToon.h"
#include"CFactory.h"
#include"CFont.h"

#include"CSound.h"
#include"TextureKey.h"
#include"CSoundKey.h"

#include"CAnimeParam.h"
#include"AnimeKey.h"
#include"CSprite.h"

#include"CNum.h"

CMesh *TestMesh[2] = {NULL,};
CLight* pLight;
CCamera* pCamera;
CSprite* pSprite;
CEffectBase* pEffect;
CEffectBase* pEffect2;

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneTestSpace::CSceneTestSpace()
{
	release();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CSceneTestSpace::~CSceneTestSpace()
{
	release();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
D3DXVECTOR4 v4lD(1.0f,1.0f,1.0f,1.0f);
/***********************************************************************/
/*! @namespace stest
 *  @brief 
 * 
 */
/***********************************************************************/
namespace stest
{
CAnimeParam* aparam = NULL;
CSprite *pSprite = NULL;
CNum* pNum;
CNum* pNum2;
}
/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::init()
{

	release();
	/*
	MESHFACTORY->registMesh(MESHKEY::YUKA(),MESHPATH::YUKA());
	TestMesh[0] = MESHFACTORY->create(MESHKEY::YUKA());
	TestMesh[1] = MESHFACTORY->create(MESHKEY::YUKA());
	pCamera = new CCamera;

	pCamera->setEyeZ(-30);
	pCamera->update();


	CLight* pLight;
	pLight  = new CLight;
	pLight->setDirectionalLight(
		COLORVALUE(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR3(0,-1.0f,0)
		);

	pEffect = new CEffectToon;
	
	//pEffectToon->setlightDir(&v4lD);

	TestMesh[0]->setEffect(pEffect);

	pEffect2 = new CEffect(
		"data/fx/Hlsl.fx",
		"Hsls",
		"DecalTex",
		"WVP");

	TestMesh[1]->setEffect(pEffect2);

	pLight->lightON();
	*/

//	CSOUND->LoadSoundFile()

	CSOUND->Init();
	stest::pNum = static_cast<CNum*>(OBJFACTORY->create(OBJKEY::NUM()));
	stest::pNum2 = static_cast<CNum*>(OBJFACTORY->create(OBJKEY::NUM()));
	
	stest::pNum2->setPos(D3DXVECTOR3(800,64,0));
	stest::pNum2->setDrawMode(0);
	stest::aparam = new CAnimeParam(ANIMEPATH::TEST());
	stest::aparam->setState(PLAY_LOOP);
	stest::pSprite = SPRITEFACTORY->create(TEXKEY::ANIMETEST());
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::update()
{
	CHECK_UPDATE;
	/*
	D3DXVECTOR3 Eye = pCamera->getEye();
	if(GetAsyncKeyState('S'))
	{
		pCamera->setEyeZ(Eye.z - 0.5f);
	}
	else if(GetAsyncKeyState('W'))
	{
		pCamera->setEyeZ(Eye.z + 0.5f);
	}
	if(GetAsyncKeyState('E'))
	{
		pCamera->setEyeY(Eye.y - 0.5f);
	}
	else if(GetAsyncKeyState('R'))
	{
		pCamera->setEyeY(Eye.y + 0.5f);
	}

	
	*/
	stest::aparam->update();
	stest::pSprite->setUV(stest::aparam->getUV());

	
	if(GetAsyncKeyState('Y'))
	{
		stest::pNum->addNum(10);
		stest::pNum2->addNum(10);
	}
	else if(GetAsyncKeyState('U'))
	{
		stest::pNum->addNum(10);
		stest::pNum2->addNum(10);
	}

	//pCamera->update();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::draw()
{
	CHECK_DRAW;
	stest::pSprite->draw(
		0,
		&D3DXVECTOR3(400,320,0),
		&D3DXVECTOR3(0,0,0),
		&D3DXVECTOR3(1,1,0));

	stest::pNum->draw();
	stest::pNum2->draw();
	/*
	D3DXVECTOR3 vec(0,0,-1);

	static D3DXMATRIXA16 mat[2];
	static float rot = 0;
	D3DXMatrixIdentity(&mat[0]);
	D3DXMatrixIdentity(&mat[1]);

	D3DXMatrixRotationY(&mat[0],rot);
	D3DXMatrixRotationY(&mat[1],rot);

//	mat[0]._41 -= 2;
	mat[1]._41 += 4;

	rot += 0.01f;

	rot = rot >= 360.0f ? 0.0f : rot;

	RECTEX rect(0,0,0,0);

	CSCREEN->update();
	D3DXVec3TransformCoord(&vec,&vec,&mat[0]);
	

	FONT->DrawFloat("x",vec.x,RECTEX(0,0,0,0));
	FONT->DrawFloat("y",vec.y,RECTEX(0,16,0,0));
	FONT->DrawFloat("z",vec.z,RECTEX(0,32,0,0));

	TestMesh[0]->draw(
		&mat[0]
		);
	TestMesh[1]->draw(
		&mat[1]
		);
		*/
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::release()
{
	SAFE_DELETE(stest::aparam);
	SAFE_DELETE(stest::pSprite);
	SAFE_DELETE(stest::pNum);
	SAFE_DELETE(stest::pNum2);
	/*
	SAFE_DELETE(TestMesh[0]);
	SAFE_DELETE(TestMesh[1]);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pLight);
	SAFE_DELETE(pSprite);
	SAFE_DELETE(pEffect);
	SAFE_DELETE(pEffect2);
	*/
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval CSceneBase * 
 */
/***********************************************************************/
CSceneBase * CSceneTestSpace::nextScene()
{
	return this;
}