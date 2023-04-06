//===================================================
//
// �W���C�p�b�h�̏���
// Author : Koduna Hirohito
// Author : Sato Teruto
//
//===================================================

//---------------------------
// �C���N���[�h
//---------------------------
#include <assert.h>
#include <d3dx9.h>
#include "input_joypad.h"

//---------------------------
// �ÓI�����o�ϐ��錾
//---------------------------
CInputJoypad::Joypad CInputJoypad::m_Joypad = {};


//===========================================
// �R���X�g���N�^
//===========================================
CInputJoypad::CInputJoypad()
{
	memset(&m_Joypad, 0, sizeof(m_Joypad));
}

//===========================================
// �f�X�g���N�^
//===========================================
CInputJoypad::~CInputJoypad()
{

}


//===========================================
// �W���C�p�b�h�̏���������
//===========================================
HRESULT CInputJoypad::Init()
{
	// XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		// �������[�̃N���A
		memset(&m_Joypad.JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_Joypad.JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		// �W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&m_Joypad.JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		// �U������p�̏�����
		m_Joypad.nStrength[nCnt] = 0;
		m_Joypad.nTime[nCnt] = 0;
	}

	return S_OK;
}

//===========================================
// �W���C�p�b�h�̏I������
//===========================================
void CInputJoypad::Uninit(void)
{
	// XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//===========================================
// �W���C�p�b�h�̍X�V����
//===========================================
void CInputJoypad::Update(void)
{
	XINPUT_STATE JoyKeyState;		// �W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		// �W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState) == ERROR_SUCCESS)
		{
			// �g���K�[����ۑ�
			m_Joypad.JoyKeyStateTrigger[nCnt].Gamepad.wButtons = ~m_Joypad.JoyKeyState[nCnt].Gamepad.wButtons & JoyKeyState.Gamepad.wButtons;

			// �����[�X����ۑ�
			m_Joypad.JoyKeyStateRelease[nCnt].Gamepad.wButtons = m_Joypad.JoyKeyState[nCnt].Gamepad.wButtons & ~JoyKeyState.Gamepad.wButtons;

			// �v���X����ۑ�
			m_Joypad.JoyKeyState[nCnt] = JoyKeyState;

			// �X�e�B�b�N�̃g���K�[�̍X�V
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_UP, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_DOWN, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_LEFT, nCnt);
			UpdateStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_RIGHT, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_UP, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_DOWN, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_LEFT, nCnt);
			UpdateStickTrigger(JOYKEY_RIGHT_STICK, JOYKEY_RIGHT, nCnt);

			m_Joypad.bUseJoyPad[nCnt] = true; // �g�p�󋵂̍X�V
		}
		else
		{
			m_Joypad.bUseJoyPad[nCnt] = false;	// �g�p�󋵂̍X�V
		}

		// �W���C�p�b�h�̐U��
		m_Joypad.JoyMoter[nCnt].wLeftMotorSpeed = m_Joypad.nStrength[nCnt];
		m_Joypad.JoyMoter[nCnt].wRightMotorSpeed = m_Joypad.nStrength[nCnt];
		XInputSetState(nCnt, &m_Joypad.JoyMoter[nCnt]);

		if (m_Joypad.nTime[nCnt] > 0)
		{
			m_Joypad.nTime[nCnt]--;
		}
		else
		{
			m_Joypad.nStrength[nCnt] = 0;
			m_Joypad.nTime[nCnt] = 0;
		}
	}
}

//===========================================
// �X�e�B�b�N�̃g���K�[�̍X�V
//===========================================
void CInputJoypad::UpdateStickTrigger(CInputJoypad::JOYKEY Stick, CInputJoypad::JOYKEY Key, int nPlayer)
{
	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fDeadZone = 0.0f;
	int nStick = 0;

	switch (Stick)
	{// �X�e�B�b�N�̎��
	case CInputJoypad::JOYKEY_LEFT_STICK:
		stick = D3DXVECTOR3((float)(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLX), (float)(-m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		nStick = 0;
		break;

	case CInputJoypad::JOYKEY_RIGHT_STICK:
		stick = D3DXVECTOR3((float)(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRX), (float)(-m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		nStick = 1;
		break;

	default:
		assert(false);
		break;
	}

	switch (Key)
	{// �X�������
	case CInputJoypad::JOYKEY_UP:		// ��
		if (m_Joypad.bLean[nPlayer][nStick][0])
		{// �X����
			m_Joypad.bStick[nPlayer][nStick][0] = true;
			m_Joypad.bLean[nPlayer][nStick][0] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.y >= -fDeadZone)
			{// �X���ĂȂ�
				m_Joypad.bStick[nPlayer][nStick][0] = false;
			}
		}
		break;

	case CInputJoypad::JOYKEY_DOWN:	// ��
		if (m_Joypad.bLean[nPlayer][nStick][1])
		{// �X����
			m_Joypad.bStick[nPlayer][nStick][1] = true;
			m_Joypad.bLean[nPlayer][nStick][1] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.y <= fDeadZone)
			{// �X���ĂȂ�
				m_Joypad.bStick[nPlayer][nStick][1] = false;
			}
		}
		break;

	case CInputJoypad::JOYKEY_LEFT:	// ��
		if (m_Joypad.bLean[nPlayer][nStick][2])
		{// �X����
			m_Joypad.bStick[nPlayer][nStick][2] = true;
			m_Joypad.bLean[nPlayer][nStick][2] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.x >= -fDeadZone)
			{// �X���ĂȂ�
				m_Joypad.bStick[nPlayer][nStick][2] = false;
			}
		}
		break;

	case CInputJoypad::JOYKEY_RIGHT:	// �E
		if (m_Joypad.bLean[nPlayer][nStick][3])
		{// �X����
			m_Joypad.bStick[nPlayer][nStick][3] = true;
			m_Joypad.bLean[nPlayer][nStick][3] = false;
		}
		else
		{// �X���ĂȂ�
			if (stick.x <= fDeadZone)
			{// �X���ĂȂ�
				m_Joypad.bStick[nPlayer][nStick][3] = false;
			}
		}
		break;

	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �W���C�p�b�h�̃v���X����(�v���C���[�w�肠��)
//--------------------------------------------------
bool CInputJoypad::IdxPress(CInputJoypad::JOYKEY Key, int nPlayer)
{
	return (m_Joypad.JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃g���K�[����(�v���C���[�w�肠��)
//--------------------------------------------------
bool CInputJoypad::IdxTrigger(CInputJoypad::JOYKEY Key, int nPlayer)
{
	bool a = (m_Joypad.JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
	return a;
}

//--------------------------------------------------
// �W���C�p�b�h�̃����[�X����(�v���C���[�w�肠��)
//--------------------------------------------------
bool CInputJoypad::IdxRelease(CInputJoypad::JOYKEY Key, int nPlayer)
{
	bool a = (m_Joypad.JoyKeyStateRelease[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
	return a;
}

//--------------------------------------------------
// �W���C�p�b�h�̃v���X����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool CInputJoypad::Press(CInputJoypad::JOYKEY Key)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if (CInputJoypad::IdxPress(Key, nPlayer))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃g���K�[����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool CInputJoypad::Trigger(CInputJoypad::JOYKEY Key)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if (CInputJoypad::IdxTrigger((CInputJoypad::JOYKEY)Key, nPlayer))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃����[�X����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool CInputJoypad::Release(CInputJoypad::JOYKEY Key)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if (CInputJoypad::IdxRelease((CInputJoypad::JOYKEY)Key, nPlayer))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̑S�L�[�v���X����
//--------------------------------------------------
bool CInputJoypad::AllPress(void)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (CInputJoypad::IdxPress((CInputJoypad::JOYKEY)nCntKey, nPlayer))
			{
				return true;
			}
		}
	}
	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̑S�L�[�g���K�[����
//--------------------------------------------------
bool CInputJoypad::AllTrigger(void)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (CInputJoypad::IdxTrigger((CInputJoypad::JOYKEY)nCntKey, nPlayer))
			{
				return true;
			}
		}
	}
	return false;
}


//--------------------------------------------------
// �W���C�p�b�g�i�X�e�B�b�N�v���X�j����
//--------------------------------------------------
D3DXVECTOR3 CInputJoypad::Stick(CInputJoypad::JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case CInputJoypad::JOYKEY_LEFT_STICK:
		m_Joypad.JoyStickPos[nPlayer] = D3DXVECTOR3(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case CInputJoypad::JOYKEY_RIGHT_STICK:
		m_Joypad.JoyStickPos[nPlayer] = D3DXVECTOR3(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_Joypad.JoyStickPos[nPlayer];
}

//--------------------------------------------------
// �W���C�p�b�g�i�g���K�[�y�_���j����
//--------------------------------------------------
int CInputJoypad::TriggerPedal(CInputJoypad::JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;

	switch (Key)
	{
	case CInputJoypad::JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_Joypad.JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case CInputJoypad::JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_Joypad.JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//--------------------------------------------------
// �R���g���[���[�̐U������
//--------------------------------------------------
void CInputJoypad::Vibration(int nTime, WORD nStrength, int nPlayer)
{
	m_Joypad.nTime[nPlayer] = nTime;				// �U����������
	m_Joypad.nStrength[nPlayer] = nStrength;		// �U���̋���
}

//--------------------------------------------------
// �W���C�p�b�h�̎g�p����Ă��邩�Ԃ�����
//--------------------------------------------------
bool CInputJoypad::IsJoyPadUse(int nPlayer)
{
	return m_Joypad.bUseJoyPad[nPlayer];
}

//--------------------------------------------------
// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w��Ȃ�)
//--------------------------------------------------
bool CInputJoypad::StickTrigger(CInputJoypad::JOYKEY Stick, CInputJoypad::JOYKEY Key)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (IdxStickTrigger(Stick, Key, i))
		{// �N�����w��̃X�e�B�b�N���w��̕����ɓ|����
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w�肠��)
//--------------------------------------------------
bool CInputJoypad::IdxStickTrigger(CInputJoypad::JOYKEY Stick, CInputJoypad::JOYKEY Key, int nPlayer)
{
	D3DXVECTOR3 stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fDeadZone = 0.0f;
	int nStick = 0;

	switch (Stick)
	{// �X�e�B�b�N�̎��
	case CInputJoypad::JOYKEY_LEFT_STICK:
		stick = D3DXVECTOR3((float)(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLX), (float)(-m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbLY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		nStick = 0;
		break;

	case CInputJoypad::JOYKEY_RIGHT_STICK:
		stick = D3DXVECTOR3((float)(m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRX), (float)(-m_Joypad.JoyKeyState[nPlayer].Gamepad.sThumbRY), 0.0f);
		fDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		nStick = 1;
		break;

	default:
		assert(false);
		break;
	}

	switch (Key)
	{// �X�������
	case CInputJoypad::JOYKEY_UP:		// ��
		if (!m_Joypad.bStick[nPlayer][nStick][0])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.y < -fDeadZone)
			{// ���X�e�B�b�N���X����
				m_Joypad.bLean[nPlayer][nStick][0] = true;
				return true;
			}
		}
		break;

	case CInputJoypad::JOYKEY_DOWN:	// ��
		if (!m_Joypad.bStick[nPlayer][nStick][1])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.y > fDeadZone)
			{// ���X�e�B�b�N���X����
				m_Joypad.bLean[nPlayer][nStick][1] = true;
				return true;
			}
		}
		break;

	case CInputJoypad::JOYKEY_LEFT:	// ��
		if (!m_Joypad.bStick[nPlayer][nStick][2])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.x < -fDeadZone)
			{// ���X�e�B�b�N���X����
				m_Joypad.bLean[nPlayer][nStick][2] = true;
				return true;
			}
		}
		break;

	case CInputJoypad::JOYKEY_RIGHT:	// �E
		if (!m_Joypad.bStick[nPlayer][nStick][3])
		{// ���X�e�B�b�N���X���ĂȂ�
			if (stick.x > fDeadZone)
			{// ���X�e�B�b�N���X����
				m_Joypad.bLean[nPlayer][nStick][3] = true;
				return true;
			}
		}
		break;

	default:
		assert(false);
		break;
	}

	return false;
}