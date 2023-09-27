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
#include "camera.h"
#include "meshfield.h"

//===========================
// �R���X�g���N�^
//===========================
CResult::CResult()
{
	m_pBg[0] = nullptr;	//�w�i
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
		m_pBg[0] = CBg::Create(pos, CBg::BGTYPE_RESULT);
		m_pBg[0]->SetTexture(CTexture::TEXTURE_RESULT);

		m_pBg[1] = CBg::Create(pos, CBg::BGTYPE_RESULT);
		m_pBg[1]->SetTexture(CTexture::TEXTURE_NONE);
		m_pBg[1]->SetSize(800.0f, 650.0f);
		m_pBg[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		m_pBg[2] = CBg::Create(D3DXVECTOR3(pos.x,pos.y - 275.0f,pos.z), CBg::BGTYPE_RESULT);
		m_pBg[2]->SetTexture(CTexture::TEXTURE_RANKING);
		m_pBg[2]->SetSize(500.0f, 300.0f);
	}

	//-------------------------------------
	// �X�R�A���X�V���ꂽ��l��ۑ�
	//-------------------------------------
	for (int i = 0; i < CApplication::GetMaxStage(); i++)
	{//�X�e�[�W�̍ő吔����
		int nScore = CApplication::GetStageScore(i);	//����̃X�R�A
		int nMaxScore = CApplication::GetMaxScore(i);	//�ő�̃X�R�A

		if (nScore >= nMaxScore)
		{//�X�R�A���X�V���ꂽ��
			//����̃X�R�A���ő�ɂ���
			CApplication::SetMaxScore(i, nScore);
		}

		//����̃X�R�A�̒l�����Z�b�g
		//CApplication::ResetStageScore(i);
	}

	//BGM�̍Đ�
	CSound::PlaySound(CSound::SOUND_LABEL_RESULT);

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
	CSound::StopSound();
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
		CMode::GetFade()->SetFade(CMode::MODE_TITLE);

		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}

	CDebugProc::Print("���U���g���");
}