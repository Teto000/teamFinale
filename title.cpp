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
#include "mode.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bg.h"

//===========================
// �R���X�g���N�^
//===========================
CTitle::CTitle()
{
	m_pBg[0] = {};	//�w�i
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
		m_pBg[0] = CBg::Create(pos, CBg::BGTYPE_TITLE);
		m_pBg[0]->SetTexture(CTexture::TEXTURE_TITLE_BG);

		D3DXVECTOR3 LogoPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
		m_pBg[1] = CBg::Create(LogoPos, CBg::BGTYPE_TITLE);
		m_pBg[1]->SetTexture(CTexture::TEXTURE_TITLE);
		m_pBg[1]->SetSize(1000.0f, 600.0f);

		D3DXVECTOR3 EnterPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f);
		m_pBg[2] = CBg::Create(EnterPos, CBg::BGTYPE_TITLE);
		m_pBg[2]->SetTexture(CTexture::TEXTURE_PRESSENTER);
		m_pBg[2]->SetSize(300.0f, 300.0f);

		m_bScale = false;
		m_fScale = 500.0f;
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

	// ���݂��̑I�������I������Ă���ꍇ
	if (m_bScale == false)
	{// �������g�債�Ă���ꍇ
		m_fScale += 5.0f;
		if (m_fScale > 600.0f)
		{// ���������̒l�܂Ŋg�債���ꍇ
			m_bScale = true;	// �������k��������
		}
	}
	else
	{// �������k�����Ă���ꍇ
		m_fScale -= 5.0f;
		if (m_fScale < 400.0f)
		{// ���������̒l�܂ŏk�������ꍇ
			m_bScale = false;	// �������g�傳����
		}
	}

	m_pBg[2]->SetSize(m_fScale, m_fScale);

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