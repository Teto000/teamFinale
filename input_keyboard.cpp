//===================================================
//
// �L�[�{�[�h�̏���
// Author : Sato Teruto
//
//===================================================

//---------------------------
// �C���N���[�h
//---------------------------
#include <d3dx9.h>
#include "input_keyboard.h"

//---------------------------
// �ÓI�����o�ϐ��錾
//---------------------------
CInputKeyboard::Keyboard CInputKeyboard::m_Keyboard = {};

//===========================================
// �R���X�g���N�^
//===========================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_Keyboard, 0, sizeof(m_Keyboard));
}

//===========================================
// �f�X�g���N�^
//===========================================
CInputKeyboard::~CInputKeyboard()
{

}

//===========================================
// �L�[�{�[�h�̏���������
//===========================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_Keyboard.pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_Keyboard.pInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard.pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_Keyboard.pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_Keyboard.pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_Keyboard.pDevKeyboard->Acquire();

	return S_OK;
}

//===========================================
// �L�[�{�[�h�̏I������
//===========================================
void CInputKeyboard::Uninit(void)
{
	// ���̓f�o�C�X�i�L�[�{�[�h�j�̕���
	if (m_Keyboard.pDevKeyboard != NULL)
	{
		m_Keyboard.pDevKeyboard->Unacquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_Keyboard.pDevKeyboard->Release();
		m_Keyboard.pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_Keyboard.pInput != NULL)
	{
		m_Keyboard.pInput->Release();
		m_Keyboard.pInput = NULL;
	}
}

//===========================================
// �L�[�{�[�h�̍X�V����
//===========================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_Keyboard.pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_Keyboard.aKeyStateTrigger[nCntKey] = ~m_Keyboard.aKeyState[nCntKey] & aKeyState[nCntKey];		// �L�[�{�[�h�̃g���K�[����ۑ�
			m_Keyboard.aKeyStateRelease[nCntKey] = m_Keyboard.aKeyState[nCntKey] & ~aKeyState[nCntKey];		// �L�[�{�[�h�̃����[�X����ۑ�
			m_Keyboard.aKeyState[nCntKey] = aKeyState[nCntKey];										// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_Keyboard.pDevKeyboard->Acquire();			// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//===========================================
// �L�[�{�[�h�̃v���X�����擾
//===========================================
bool CInputKeyboard::Press(int nKey)
{
	return (m_Keyboard.aKeyState[nKey] & 0x80) != 0;
}

//===========================================
// �L�[�{�[�h�̃g���K�[�����擾
//===========================================
bool CInputKeyboard::Trigger(int nKey)
{
	return (m_Keyboard.aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===========================================
// �L�[�{�[�h�̃����[�X�����擾
//===========================================
bool CInputKeyboard::Release(int nKey)
{
	return (m_Keyboard.aKeyStateRelease[nKey] & 0x80) != 0;
}

//===========================================
// �L�[�{�[�h�̑S�L�[�v���X�����擾
//===========================================
bool CInputKeyboard::AllPress(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (CInputKeyboard::Press(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//===========================================
// �L�[�{�[�h�̑S�L�[�g���K�[�����擾
//===========================================
bool CInputKeyboard::AllTrigger(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (CInputKeyboard::Trigger(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//===========================================
// �L�[�{�[�h�̑S�L�[�����[�X�����擾
//===========================================
bool CInputKeyboard::AllRelease(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (CInputKeyboard::Release(nCntKey))
		{
			return true;
		}
	}

	return false;
}