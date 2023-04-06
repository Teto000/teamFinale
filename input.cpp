//===================================================
//
// ���͏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CInputKeyboard *CInput::m_pInputKeybord = nullptr;	//�L�[�{�[�h
CInputJoypad *CInput::m_pInputJoypad = nullptr;		//�W���C�p�b�h

//===========================
// �R���X�g���N�^
//===========================
CInput::CInput()
{

}

//===========================
// �f�X�g���N�^
//===========================
CInput::~CInput()
{

}

//===========================
// �S�Ă̓��͂̏�����
//===========================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeybord->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�h������
	m_pInputJoypad->Init();

	return S_OK;
}

//===========================
// �S�Ă̓��͂̏I��
//===========================
void CInput::Uninit()
{
	// �L�[�{�[�h�̏I������
	m_pInputKeybord->Uninit();

	// �W���C�p�b�h�I������
	m_pInputJoypad->Uninit();
}

//===========================
// �S�Ă̓��͂̍X�V
//===========================
void CInput::Update()
{
	// �L�[�{�[�h�̍X�V����
	m_pInputKeybord->Update();

	// �W���C�p�b�h�X�V����
	m_pInputJoypad->Update();
}