/***********************************************************************/
/*! @file  CSceneTestSpace.cpp
 *  @brief テスト空間
 *  
 *  @author 川原　佑介
 *  @date 
 */
/***********************************************************************/
#ifndef _HOGEHOGE
#include"CSceneTestSpace.h"
#include"const.h"
#include"CSpriteFactory.h"
#include"CMeshFactory.h"
#include"Rect.h"
#include"CBumpMap.h"

#include"CCamera.h"
#include"CLight.h"
#include"CScreen.h"
#include"CFactory.h"
#include"CFont.h"

#include"CSound.h"
#include"TextureKey.h"
#include"CSoundKey.h"

#include"CAnimeParam.h"
#include"AnimeKey.h"
#include"CSprite.h"

#include"CNum.h"

#include"CMesh.h"

CMesh *TestMesh[2] = {NULL,};
CLight* pLight;
CCamera* pCamera;
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
CAnimeParam* aparam = NULL;
CSprite *pSprite = NULL;
CNum* pNum;
CNum* pNum2;

#include"CMeshFactory.h"
#include"Rect.h"

float dis;
float rad;

CMesh*		pMesh;
CLight*		light;

CBumpMap* pmap;
CRect* rect;
CTexture* tex;
CTexture* btex;
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
	pSprite = SPRITEFACTORY->create(TEXKEY::ANIMETEST());
	pSprite->createAnimeParam(ANIMEPATH::TEST());
	pSprite->getAnimeParam()->setState(ANIME_STATE::PLAY_LOOP);
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
//	*/

//	CSOUND->LoadSoundFile()
	/*
	CSOUND->Init();
	stest::pNum = static_cast<CNum*>(OBJFACTORY->create(OBJKEY::NUM()));
	stest::pNum2 = static_cast<CNum*>(OBJFACTORY->create(OBJKEY::NUM()));
	
	stest::pNum2->setPos(D3DXVECTOR3(800,64,0));
	stest::pNum2->setDrawMode(0);
	stest::aparam = new CAnimeParam(ANIMEPATH::TEST());
	stest::aparam->setState(PLAY_LOOP);
	stest::pSprite = SPRITEFACTORY->create(TEXKEY::ANIMETEST());
//*	
	CCamera::init();
	Shadow = new CShadowMap("0","data/fx/shadowmap.fx");

	Shadow->_pMeshLand=MESHFACTORY->create(MESHKEY::STAGE01());
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixScaling(&mat,0.1f,0.1f,0.1f);
	//*
	mat._41 = -100;
	mat._42 = 80;
	mat._43 = -100;
	
	Shadow->landMat = mat;

	CCamera::setEye(D3DXVECTOR3(0,200,-300));

	pMesh = MESHFACTORY->create(MESHKEY::RING());


//	light = new CLight;
//	light->activeLight();
//	light->lightON();
*/
	CCamera::setEye(D3DXVECTOR3(0,0,-7.5f));

	pmap = new CBumpMap("data/fx/bump.fx");
	pmap->create();
	rect = new CRect;
	tex  = TEXTUREFACTORY->getTexture(TEXKEY::TILESTRAIGHT());
	btex  = TEXTUREFACTORY->getTexture(TEXKEY::TILESTRAIGHT_BUMP());
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
	//pSprite->updateAnime();
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

	
	//*/
	/*
	stest::aparam->update();
	stest::pSprite->setUV(stest::aparam->getUV());
	/*
	
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
	
//	light->update();
*/


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
//		pCamera->setEyeY(Eye.y - 0.5f);
	}
	else if(GetAsyncKeyState('R'))
	{
//		pCamera->setEyeY(Eye.y + 0.5f);
	}


	CCamera::update();
	/*
	D3DXVECTOR3 eye = CCamera::getEye();
	int move = 100;
	if(GetAsyncKeyState('W'))
	{
		eye.z+=move;
	}
	else if(GetAsyncKeyState('S'))
	{
		eye.z-=move;
	}

	if(GetAsyncKeyState('A'))
	{
		eye.x-=move;
	}
	else if(GetAsyncKeyState('D'))
	{
		eye.x+=move;
	}

	if(GetAsyncKeyState('Q'))
	{
		eye.y-=move;
	}
	else if(GetAsyncKeyState('E'))
	{
		eye.y+=move;
	}
	CCamera::setEye(eye);
	//*/
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::draw()
{/*
	CHECK_DRAW;
	pSprite->draw(
		0,
		&D3DXVECTOR3(400,320,0),
		&D3DXVECTOR3(0,0,0),
		&D3DXVECTOR3(1,1,1)
		);
	/*
	stest::pSprite->draw(
		0,
		&D3DXVECTOR3(400,320,0),
		&D3DXVECTOR3(0,0,0),
		&D3DXVECTOR3(1,1,0));

	stest::pNum->draw();
	stest::pNum2->draw();
	//*
	D3DXMATRIXA16 MAT;
	D3DXMatrixIdentity(&MAT);
	D3DXMatrixScaling(&MAT,0.1f,0.1f,0.1f);
	
	MAT._42 = 200;
	pMesh->setEffect(Shadow);

	pMesh->draw(&MAT);
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


	D3DMATERIAL9 mate;
	{
		mate.Ambient.a = mate.Ambient.r = mate.Ambient.g = mate.Ambient.b = 1.0f;
		mate.Diffuse = mate.Ambient;
		mate.Emissive.r = mate.Emissive.g = mate.Emissive.b = 0;
		mate.Specular.r = mate.Specular.g = mate.Specular.b = 0;
		mate.Emissive.a = 1.0f;
		mate.Power = 0.5f;
	}
	pmap->setMaterial(&mate);

	rect->SetSize(4.0f,4.0f);
	rect->SetTexture(tex->getTexture());
	rect->SetUV(0,D3DXVECTOR2(0,0));
	rect->SetUV(1,D3DXVECTOR2(0,1));
	rect->SetUV(2,D3DXVECTOR2(1,0));
	rect->SetUV(3,D3DXVECTOR2(1,1));


	CMesh* pmesh = MESHFACTORY->create(MESHKEY::TANK01_BOTTOM_1());

	static float rot = 90.0;
	static float rot2 = 0.0;
	static float rot3 = 0.0;
	if(GetAsyncKeyState('T'))
	{
		rot+=0.1f;
	}
	else if(GetAsyncKeyState('Y'))
	{
		rot-=0.1f;
	}
	if(GetAsyncKeyState('G'))
	{
		rot3+=0.1f;
	}
	else if(GetAsyncKeyState('H'))
	{
		rot3-=0.1f;
	}
	if(GetAsyncKeyState('B'))
	{
		rot2+=0.1f;
	}
	else if(GetAsyncKeyState('N'))
	{
		rot2-=0.1f;
	}
	D3DXMATRIXA16 mat2;
	D3DXMatrixIdentity(&mat2);
	D3DXMatrixRotationYawPitchRoll(&mat2,rot,rot2,rot3);

	pmap->setWorldMatrix(&mat2);

	D3DDEVICE->SetFVF(FVF_VERTEX_3D);	// 頂点フォーマットの設定
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getMatProj());	//ビュー座標変換
	D3DDEVICE->SetTransform(D3DTS_VIEW, CCamera::getMatView());			//カメラ座標変換
	D3DDEVICE->SetTransform(D3DTS_WORLD,&mat2);							//ワールド座標変換

	CCamera::setAt(D3DXVECTOR3(0,0,0));
	CCamera::setUp(D3DXVECTOR3(0,1,0));


	D3DDEVICE->SetRenderState(D3DRS_ZENABLE,FALSE);
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DDEVICE->SetTexture(0,tex->getTexture());

	ID3DXMesh* mesh = NULL;
	D3DXCreatePolygon(D3DDEVICE,4.0f,4,&mesh,NULL);

		// 法線が無い場合は強制的に追加
	if ((mesh->GetFVF() & D3DFVF_NORMAL) == 0) 
	{
		LPD3DXMESH pMeshTmp = mesh;
		pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(), pMeshTmp->GetFVF() | D3DFVF_NORMAL,
			D3DDEVICE, &mesh);
		SAFE_RELEASE(pMeshTmp);
		D3DXComputeNormals(mesh, NULL);
	}
	//法線の強制追加
	D3DVERTEXELEMENT9 m_vtxElem[] =
    {
        {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
        {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
        {0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
        D3DDECL_END()
    };

	
    LPDIRECT3DVERTEXDECLARATION9 m_pVtxDecl;
	D3DDEVICE->CreateVertexDeclaration(m_vtxElem, &m_pVtxDecl);

	LPD3DXMESH pCloneMesh;
	if (SUCCEEDED(mesh->CloneMesh(D3DXMESH_MANAGED,m_vtxElem, D3DDEVICE, &pCloneMesh)) )
	{
		mesh->Release();
		mesh = pCloneMesh;
		D3DXComputeTangent(mesh, 0, 0, D3DX_DEFAULT, FALSE, NULL);
	}     

	LPDIRECT3DTEXTURE9 tex2;
	D3DXCreateTexture(
		D3DDEVICE,
		256,
		256,
		D3DX_DEFAULT ,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		_D3DPOOL::D3DPOOL_DEFAULT,
		&tex2);
	


	D3DXVECTOR3 pos = CCamera::getEye();
	pmap->setCameraPos(&pos);
	pmap->setBumpTex(tex->getTexture(),btex->getTexture());
	
	static D3DXVECTOR3 lv = D3DXVECTOR3(1,1,1);

	D3DXVec3Normalize(&lv,&lv);
	pmap->setLightDir(&lv);

	uint teq;
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,FALSE);	

	rect->SetSize(4.0f,4.0f);
	if(teq = pmap->begin(0))
	{
		for(int i = 0; i < teq; i++)
		{
			pmap->beginPass(i);
//			for(DWORD j = 0; j < 4; j++)
			{
				pmap->setMaterial(&mate);
				pmap->commitChanges();
//				mesh->DrawSubset(0);
				rect->DrawBump();
//				pmesh->getMesh()->DrawSubset(j);				
			}

			pmap->endPass();
		}
		pmap->end();
	}
	mesh->Release();
	D3DDEVICE->SetRenderState(D3DRS_ZENABLE,TRUE);		
	D3DDEVICE->SetRenderState(D3DRS_LIGHTING,TRUE);	
	delete pmesh;
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneTestSpace::release()
{
	delete pSprite;
	/*
	SAFE_DELETE(stest::aparam);
	SAFE_DELETE(stest::pSprite);
	SAFE_DELETE(stest::pNum);
	SAFE_DELETE(stest::pNum2);
	
	SAFE_DELETE(pMesh);
	SAFE_DELETE(light);
	
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

#endif