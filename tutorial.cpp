//===================================================
//
// �`���[�g���A���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "tutorial.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "mode.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bg.h"

//===========================
// �R���X�g���N�^
//===========================
CTutorial::CTutorial()
{
	m_pBg = nullptr;	//�w�i
}

//===========================
// �f�X�g���N�^
//===========================
CTutorial::~CTutorial()
{

}

//===========================
// ������
//===========================
HRESULT CTutorial::Init()
{
	//�w�i�̐���
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_TITLE);
		m_pBg->SetTexture(CTexture::TEXTURE_TUTORIAL);
	}

	return S_OK;
}

//===========================
// �I��
//===========================
void CTutorial::Uninit()
{
	////BGM�̒�~
	//CSound::StopSound();
}

//===========================
// �X�V
//===========================
void CTutorial::Update()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//�Q�[����ʂɈڍs
		CMode::GetFade()->SetFade(CMode::MODE_GAME);

		//SE�̍Đ�
		//CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
}