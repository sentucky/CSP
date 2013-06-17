/***********************************************************************/
/*! @file  CSound.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
//================================================================================
// CSound.h
//
// �T�E���h�N���X											
//--------------------------------------------------------------------------------
// �X�V����
//	2011/1/4
//		�쐬�J�n
//================================================================================
//================================================================================
// �}�N����`
//================================================================================
#ifndef __CSOUND_H__
#define __CSOUND_H__

#define CSOUNDMAP		std::map<std::string,LPDIRECTSOUNDBUFFER>
#define CSOUNDMAPITR	std::map<std::string,LPDIRECTSOUNDBUFFER>::iterator
#define CSOUNDPAIR		std::pair<std::string,LPDIRECTSOUNDBUFFER>

#define CSOUND CSound::getInst()

//================================================================================
// �C���N���[�h
//================================================================================
//#include <map>
//#include <string>
//#include "main.h"
#include "CSingleton.h"
#include <dsound.h>
#include<vector>

typedef std::vector<LPDIRECTSOUNDBUFFER> CSOUNDVECTOR;
typedef std::vector<LPDIRECTSOUNDBUFFER>::iterator CSOUNDVECYORITR;

#pragma comment ( lib, "dsound.lib" )
//================================================================================
// �N���X��`
//================================================================================
class CSound : public CSingleton<CSound>
{
	friend class CSingleton<CSound>;

public:
	//===========================
	// �����o�֐� - ���J
	//===========================
	//�f�X�g���N�^
	~CSound();

	//������
	HRESULT Init();
	//�I��
	void Uninit();

	//WAV�T�E���h�f�[�^�̓ǂݍ���
	HRESULT LoadSoundFile(const uint keyName, char* fileName);

	//�T�E���h�f�[�^�̎擾
	LPDIRECTSOUNDBUFFER GetSound(const uint Key);

	void reserve(const uint size);

private:
	//===========================
	// �����o�֐� - ����J
	//===========================
	//�R���X�g���N�^
	CSound();
	//===========================
	// �����o�ϐ� - ����J
	//===========================
	LPDIRECTSOUND8		_pDSound;			///<�T�E���h�f�o�C�X
	LPDIRECTSOUNDBUFFER _pDSoundPrimary;	///<�v���C�}���o�b�t�@
	CSOUNDVECTOR		_soundVector;			///<�Z�J���_���o�b�t�@�̃x�N�^
};

#endif		//__CSOUND_H