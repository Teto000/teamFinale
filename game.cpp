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
#include "player.h"
#include "mini_game_basis.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
bool		CGame::m_bFinish = false;				//�Q�[���I���t���O
CCamera*	CGame::m_pCamera[nMaxCamera] = {};		//�J����
CTime*		CGame::m_pTime = nullptr;				//�^�C�}�[
CSky*		CGame::m_pSky = nullptr;				//��
CMeshField*	CGame::m_pMeshField = nullptr;			//�n��

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{
	m_pPlayer = nullptr;	//�v���C���[
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

	//------------------------
	// �J�����̐���
	//------------------------
	m_pCamera[0] = CCamera::Create((DWORD)0.0f, (DWORD)0.0f
								, (DWORD)(SCREEN_WIDTH / 2)
								, (DWORD)SCREEN_HEIGHT);

	m_pCamera[1] = CCamera::Create((DWORD)(SCREEN_WIDTH/ 2), (DWORD)0.0f
								, (DWORD)(SCREEN_WIDTH / 2)
								, (DWORD)SCREEN_HEIGHT);

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create();

	//��̐���
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//�^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));

	// �v���C���[�̐ݒ�
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

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

	//---------------------
	// �J�����̏I��
	//---------------------
	for (int i = 0; i < nMaxCamera; i++)
	{
		if (m_pCamera[i] != nullptr)
		{
			m_pCamera[i]->Uninit();
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
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
	for (int i = 0; i < nMaxCamera; i++)
	{
		if (m_pCamera[i] != nullptr)
		{
			m_pCamera[i]->Update();
		}
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

		//��ʃT�C�Y���g��
		for (int i = 0; i < nMaxCamera; i++)
		{
			m_pCamera[i]->SetViewSize(0, 0, 1280, 720);
		}
	}

	if (CInputKeyboard::Trigger(DIK_T))
	{//T�L�[����������
		//�~�j�Q�[���̐���
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTUNPUSH);
	}

	if (CInputKeyboard::Trigger(DIK_L))
	{//L�L�[����������
		//�~�j�Q�[���̐���
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTONMASH);
	}
}