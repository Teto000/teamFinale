//===================================================
//
// �Q�[���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "debug_proc.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "time.h"
#include "sky.h"
#include "meshfield.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
bool		CGame::m_bFinish = false;		//�Q�[���I���t���O
CCamera*	CGame::m_pCamera = nullptr;		//�J����
CTime*		CGame::m_pTime = nullptr;		//�^�C�}�[
CSky*		CGame::m_pSky = nullptr;		//��
CMeshField*	CGame::m_pMeshField = nullptr;	//�n��

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{

}

//===========================
// �f�X�g���N�^
//===========================
CGame::~CGame()
{

}

//===========================
// ������
//===========================
HRESULT CGame::Init()
{
	//�����l�̐ݒ�
	m_bFinish = false;	//�Q�[�����I�����Ă��Ȃ����

	//�J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create();

	//��̐���
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//�^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));

	//BGM�̍Đ�
	//CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{
	//BGM�̒�~
	//CSound::StopSound();

	//�J�����̏I��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CGame::Update()
{
	//----------------------------
	// �J�����̍X�V
	//----------------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//�Q�[���I���t���O�𗧂Ă�
		m_bFinish = true;

		//���U���g��ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
	}
}