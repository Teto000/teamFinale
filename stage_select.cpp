//===================================================
//
// �X�e�[�W�I������
// Author : Sato Teruto
//
//===================================================

//----------------------------------
// �C���N���[�h
//----------------------------------
#include "stage_select.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "fade.h"
#include "camera.h"
#include "meshfield.h"
#include "objectX.h"
#include "player.h"

//==================================
// �R���X�g���N�^
//==================================
CStageSelect::CStageSelect()
{
	m_pCamera = nullptr;	//�J����
	m_pMeshField = nullptr;	//���b�V���t�B�[���h(�n��)
	m_pObjectX = nullptr;	//�I�u�W�F�N�gX
	m_pPlayer = nullptr;	//�v���C���[
}

//=================================
// �f�X�g���N�^
//=================================
CStageSelect::~CStageSelect()
{
}

//==================================
// ����������
//==================================
HRESULT CStageSelect::Init()
{
	//------------------------
	// �J�����̐���
	//------------------------
	m_pCamera = CCamera::Create(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//------------------------
	// �n�ʂ̐���
	//------------------------
	m_pMeshField = CMeshField::Create();

	//------------------------
	// �v���C���[�̐���
	//------------------------
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

	//------------------------
	// �I�u�W�F�N�g�̐���(��)
	//------------------------
	m_pObjectX = CObjectX::Create();
	m_pObjectX->SetType(1);

	return S_OK;
}

//==================================
// �I������
//==================================
void CStageSelect::Uninit()
{
	//-----------------------
	// �J�����̏I��
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==================================
// �X�V����
//==================================
void CStageSelect::Update()
{
	//-----------------------
	// �J�����̍X�V����
	//-----------------------
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
		//�Q�[����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);
	}
}