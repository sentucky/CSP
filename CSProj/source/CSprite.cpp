/***********************************************************************/
/*! @file  CSprite.cpp
 *  @brief �X�v���C�g
 *  
 *  @author �쌴�@�C��
 *  @date	2013/5/11	�R�s�[�R���X�g���N�^�̏C��
 */
/***********************************************************************/
/***********************************************************************/
//	�C���N���[�h
/***********************************************************************/
#include"CSprite.h"
#include"CScreen.h"
#include"common.h"
#include"CAnimeParam.h"
#include"CCamera.h"

/***********************************************************************/
//	�}�N����`
/***********************************************************************/
#define D3DCOLORA(a) ( a & 0xff << 24)
#define D3DCOLORR(a) ( a & 0xff << 16)
#define D3DCOLORG(a) ( a & 0xff <<  8)
#define D3DCOLORB(a) ( a & 0xff )

/***********************************************************************/
/*! @brief �R���X�g���N�^
 * 
 *  @param[in] pTexture 
 */
/***********************************************************************/
CSprite::CSprite(CTexture* pTexture)
	:_pTexture		(pTexture						),
	 _pD3DSprite	(NULL							),	
	 _vecCenter		(D3DXVECTOR3(0,0,0)				),		
	 _UV(RECTEX		(0,0,0,0)						),			
	 _colorRevision	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)	),
	 _bDrawFlg		(TRUE							),
	 _AnimeParam	(NULL							)
{
	_pTexture = pTexture;	//�e�N�X�`���̓o�^
	create();
}

/***********************************************************************/
/*! @brief �R�s�[�R���X�g���N�^
 * 
 *  @param[in] copy 
 */
/***********************************************************************/
CSprite::CSprite(const CSprite& copy)
	:_pTexture		( copy._pTexture		),
	_pD3DSprite		( NULL					),	
	 _vecCenter		( copy._vecCenter		),		
	 _UV			( copy._UV				),			
	 _colorRevision	( copy._colorRevision	),
	 _bDrawFlg		( TRUE					),
	 _AnimeParam	( NULL					)
{
	create();
}
	
/***********************************************************************/
/*! @brief �f�X�g���N�^
 */
/***********************************************************************/
CSprite::~CSprite()
{
	if(_pTexture != NULL)
	{//�e�N�X�`�����ݒ肳��Ă����Ƃ�
		_pTexture = NULL;
	}
	SAFE_RELEASE(_pD3DSprite);
	SAFE_DELETE(_AnimeParam);
}

/***********************************************************************/
/*! @brief ������
 * 
 *  @retval void
 */
/***********************************************************************/
void CSprite::init()
{
	_pTexture = NULL;		//�e�N�X�`��
	_pD3DSprite =NULL;		//�X�v���C�g
	_bDrawFlg = TRUE;
	_vecCenter = D3DXVECTOR3(0,0,0);
	_UV = RECTEX(0,0,0,0);
	setColorRevision(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));	//�F�␳
}


/***********************************************************************/
/*! @brief �X�v���C�g�쐬
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CSprite::create()
{
	/////////////////////////
	//	��������
	if(_pTexture == NULL)
	{
		return 0;	//�������Ȃ�
	}

	HRESULT hr;	//�������ʔ���
	
	hr = D3DXCreateSprite(D3DDEVICE, &_pD3DSprite);

	if(FAILED(hr))
	{
		MessageAlert("�X�v���C�g�̍쐬�Ɏ��s���܂���","error from CSprite::Create");
		return hr;
	}

	//	UV���W�̎擾
	_UV.right = _pTexture->getSrcInfoRef().Width;
	_UV.bottom = _pTexture->getSrcInfoRef().Height;

	//	���S���W�̐ݒ�
	_vecCenter.x = (float)_UV.right * 0.5f;	
	_vecCenter.y = (float)_UV.bottom * 0.5f;
	return hr;
}

/***********************************************************************/
/*! @brief ���S���W�v�Z
 * 
 *  @retval void
 */
/***********************************************************************/
void CSprite::calcCenter()
{
/*	if(_AnimeParam != NULL)
	{
		_vecCenter.x = (float)(_UV.right - _UV.left) * 0.5f + _AnimeParam->getUV().left;
		_vecCenter.y = (float)(_UV.bottom - _UV.top) * 0.5f + _AnimeParam->getUV().top;
		return;
	}*/
	_vecCenter.x = (float)(_UV.right - _UV.left) * 0.5f;
	_vecCenter.y = (float)(_UV.bottom - _UV.top) * 0.5f;
}

/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @param[in] SpriteType	�`��̃I�v�V����
 *  @param[in] vec3Pos		���W
 *  @param[in] vec3Rot		��]��
 *  @param[in] vec3Scale	�g�嗦
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXVECTOR3* vec3Pos,const D3DXVECTOR3* vec3Rot,const D3DXVECTOR3* vec3Scale)
{
	/////////////////////////
	//	��������
	if(_pTexture == NULL)
	{
		return;	//�������Ȃ�
	}
	
	/////////////////////////
	//	�ϐ��錾
	D3DXMATRIXA16 rot;		//��]�}�g���N�X
	D3DXMATRIXA16 scale;	//�T�C�Y�}�g���N�X
	D3DXMATRIXA16 pos;		//���W�}�g���N�X
	D3DXMATRIXA16 posRot;	//��]�p���W�}�g���N�X
	D3DXMATRIXA16 matWorld;	//���[���h���W�}�g���N�X


	////////////////////////////
	//	��������
	//...�}�g���N�X�̏�����
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixIdentity( &rot );
	D3DXMatrixIdentity( &scale );
	D3DXMatrixIdentity( &pos );
	D3DXMatrixIdentity( &posRot );


	////////////////////////////
	//	���W�ϊ�
	D3DDEVICE->SetFVF(FVF_VERTEX_2D);

	if(vec3Scale != 0)
	{
		D3DXMatrixScaling( &scale, vec3Scale->x, vec3Scale->y, 0.0f );	//�X�P�[���g��k������
		matWorld *= scale;
	}
	if(vec3Rot != 0)
	{//��]����
		D3DXMatrixRotationYawPitchRoll(&rot,D3DXToRadian(vec3Rot->y),D3DXToRadian(vec3Rot->x),D3DXToRadian(vec3Rot->z));	
		matWorld *= rot;
	}
	
	if(vec3Pos != 0)
	{
		D3DXMatrixTranslation( &pos, vec3Pos->x, vec3Pos->y, vec3Pos->z );	//�ړ�����
		matWorld *= pos;
	}


	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);		//�����_�����O
	_pD3DSprite->SetTransform(&matWorld);
	D3DDEVICE->SetTransform(D3DTS_WORLD, &matWorld);					//���[���h���W�ϊ�
	_pD3DSprite->Begin(SpriteType );	//�`��J�n
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,0, _colorRevision);
	_pD3DSprite->End();	//�`��I��
}


/***********************************************************************/
/*! @brief �`�揈��
 * 
 *  @param[in] SpriteType	�`��I�v�V���� 
 *  @param[in] pmatWorld	���[���h�}�g���N�X
 *  @param[in] pmatView		�r���[�}�g���N�Xw
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXMATRIXA16* pmatWorld, const D3DXMATRIXA16* pmatView)
{
	/////////////////////////
	//	��������
	if(_pTexture == NULL)
	{
		return;	//�������Ȃ�
	}

	////////////////////////////
	//	���W�ϊ�
	//*
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getMatProj());	//�r���[���W�ϊ�
	
	if(pmatView != NULL)
	{
		D3DDEVICE->SetTransform(D3DTS_VIEW, pmatView);					//�J�������W�ϊ�
	}
	D3DDEVICE->SetTransform(D3DTS_WORLD, pmatWorld);					//���[���h���W�ϊ�

	//*/
	////////////////////////////
	//	�`�揈��
	calcCenter();

	D3DDEVICE->SetFVF(FVF_VERTEX_2D);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);			//	�����_�����O

	_pD3DSprite->SetWorldViewLH(pmatWorld,pmatView);

	_pD3DSprite->Begin(SpriteType | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);	//	�`��J�n
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,NULL, _colorRevision);
	_pD3DSprite->End();	//�`��I��
}

/***********************************************************************/
/*! @brief 2D�p�`��
 * 
 *  @param[in] SpriteType 
 *  @param[in] pmatWorld 
 *  @retval void
 */
/***********************************************************************/
void CSprite::draw(DWORD SpriteType,const D3DXMATRIXA16* pmatWorld)
{
	/////////////////////////
	//	��������
	if(_pTexture == NULL)
	{
		return;	//�������Ȃ�
	}

	////////////////////////////
	//	���W�ϊ�
	/*
	D3DDEVICE->SetTransform(D3DTS_PROJECTION,CSCREEN->getMatProj());	//�r���[���W�ϊ�
	D3DDEVICE->SetTransform(D3DTS_WORLD, pmatWorld);					//���[���h���W�ϊ�
	*/
	//calcCenter();

	////////////////////////////
	//	�`�揈��
	D3DDEVICE->SetFVF(FVF_VERTEX_2D);
	D3DDEVICE->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);					//�����_�����O
	_pD3DSprite->SetTransform(pmatWorld);
	D3DDEVICE->SetTransform(D3DTS_WORLD, pmatWorld);					//���[���h���W�ϊ�
	_pD3DSprite->Begin(SpriteType | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);			//�`��J�n
	_pD3DSprite->Draw(_pTexture->getTexture(), &_UV, &_vecCenter,NULL, _colorRevision);
	_pD3DSprite->End();	//�`��I��
}


void CSprite::createAnimeParam(ANIMEPATH& AnimePath)
{
	_AnimeParam = new CAnimeParam(AnimePath);
	_UV = _AnimeParam->getUV();
//	calcCenter();
}

void CSprite::updateAnime()
{
	if(_AnimeParam == NULL)
		return;

	_AnimeParam->update();
	_UV = _AnimeParam->getUV();
//	calcCenter();
}

void CSprite::setCatAnime(const uint Cat)
{
	_AnimeParam->setCat(Cat);
//	calcCenter();
}
void CSprite::setStateAniem(const uint State)
{
	_AnimeParam->setState(State);
//	calcCenter();
}


/***********************************************************************/
/*! @brief �e�N�X�`���ݒ�
 * 
 *  @param[in] pTexture 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setTexture(CTexture* pTexture)
{
	_pTexture = pTexture;
	create();
}


/***********************************************************************/
/*! @brief ���S���W�̐ݒ�
 * 
 *  @param[in] x 
 *  @param[in] y 
 *  @param[in] z 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setCenter(float x, float y, float z)
{
	_vecCenter.x = x;
	_vecCenter.y = y;
	_vecCenter.z = z;
}
/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pos 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setCenter(D3DXVECTOR3* pos)
{
	_vecCenter = *pos;
}



/***********************************************************************/
/*! @brief UV���W�̐ݒ�
 * 
 *  @param[in] lLeft 
 *  @param[in] lTop 
 *  @param[in] lRight 
 *  @param[in] lBottom 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setUV(long lLeft,long lTop,long lRight,long lBottom)
{
	_UV.left = lLeft;		//���[�̐ݒ�
	_UV.top  = lTop;		//��[�̐ݒ�
	_UV.right = lRight;		//�E�[�̐ݒ�
	_UV.bottom = lBottom;	//���[�̐ݒ�
}


/***********************************************************************/
/*! @brief UV���W�̐ݒ�
 * 
 *  @param[in] rect 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setUV(RECT& rect)
{
	_UV = rect;
}

/***********************************************************************/
/*! @brief �F�␳�̐ݒ�
 * 
 *  @param[in] colorRevision 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevision(D3DXCOLOR& colorRevision)
{
	_colorRevision = colorRevision;
}


/***********************************************************************/
/*! @brief �F�␳�̐ݒ�
 * 
 *  @param[in] fR 
 *  @param[in] fG 
 *  @param[in] fB 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevision(
	const float fR,
	const float fG,
	const float fB,
	const float fA
	)
{
	_colorRevision = D3DXCOLOR(fR,fG,fB,fA);
}
/***********************************************************************/
/*! @brief �F�␳�Ԏw��
 * 
 *  @param[in] fR 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionR(const float fR)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fR);
	_colorRevision &= 0xff00ffff;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief �F�␳�Ύw��
 * 
 *  @param[in] fG 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionG(const float fG)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fG);
	_colorRevision &= 0xffff00ff;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief �F�␳�w��
 * 
 *  @param[in] fB 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionB(const float fB)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fB);
	_colorRevision &= 0xffffff00;
	_colorRevision |= D3DCOLORR(unRVal);
}
/***********************************************************************/
/*! @brief �F�␳�A���t�@�w��
 * 
 *  @param[in] fA 
 *  @retval void
 */
/***********************************************************************/
void CSprite::setColorRevisionA(const float fA)
{
	uint unRVal = static_cast<int>(static_cast<float>(0xff) * fA);
	_colorRevision &= 0x00ffffff;
	_colorRevision |= D3DCOLORR(unRVal);
}

/***********************************************************************/
/*! @brief �F�␳�l�擾
 * 
 *  @retval D3DCOLOR 
 */
/***********************************************************************/
D3DCOLOR CSprite::getColorRevision()
{
	return _colorRevision;
}

const RECTEX*	CSprite::getUV()
{
	return &_UV;
}

/***********************************************************************/
/*! @brief �e�N�X�`�����擾
 * 
 *  @retval const D3DXIMAGE_INFO* 
 */
/***********************************************************************/
const D3DXIMAGE_INFO* CSprite::getTextureInfo()
{
	return &_pTexture->getSrcInfoRef();
}


//	EOF