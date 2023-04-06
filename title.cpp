//===================================================
//
// �^�C�g���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bg.h"

//===========================
// �R���X�g���N�^
//===========================
CTitle::CTitle()
{
	m_pBg = nullptr;	//�w�i
}

//===========================
// �f�X�g���N�^
//===========================
CTitle::~CTitle()
{

}

//===========================
// ������
//===========================
HRESULT CTitle::Init()
{
	//�w�i�̐���
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_TITLE);
	}

	//BGM�̍Đ�
	//CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// �I��
//===========================
void CTitle::Uninit()
{
	////BGM�̒�~
	//CSound::StopSound();
}

//===========================
// �X�V
//===========================
void CTitle::Update()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//�Q�[����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);

		//SE�̍Đ�
		//CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
}