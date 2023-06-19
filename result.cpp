//===================================================
//
// ���U���g�̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "result.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "sound.h"
#include "bg.h"
#include "fade.h"
#include "ranking.h"
#include "debug_proc.h"

//===========================
// �R���X�g���N�^
//===========================
CResult::CResult()
{
	m_pBg = nullptr;	//�w�i
	m_pRanking = nullptr;
}

//===========================
// �f�X�g���N�^
//===========================
CResult::~CResult()
{
	
}

//===========================
// ������
//===========================
HRESULT CResult::Init()
{
	{
		//�w�i�̐���
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_RESULT);
		m_pBg->SetTexture(CTexture::TEXTURE_RESULT);
	}

	//BGM�̍Đ�
	//CSound::PlaySound(CSound::SOUND_LABEL_RESULT);

	//�����L���O�̐���
	m_pRanking = CRanking::Create();

	return S_OK;
}

//===========================
// �I��
//===========================
void CResult::Uninit()
{
	//BGM�̒�~
	//CSound::StopSound();
}

//===========================
// �X�V
//===========================
void CResult::Update()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//�^�C�g����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_TITLE);

		//SE�̍Đ�
		//CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}

	CDebugProc::Print("���U���g���");
}