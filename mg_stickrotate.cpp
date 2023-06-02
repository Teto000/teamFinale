//===================================================
//
// �X�e�B�b�N��]�Q�[������
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "mg_stickrotate.h"
#include "application.h"
#include "renderer.h"

#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object2D.h"
#include "game.h"

#include "itemObj.h"
#include "player.h"

//=======================
// �R���X�g���N�^
//=======================
CStickRotate::CStickRotate()
{

}

//=======================
// �f�X�g���N�^
//=======================
CStickRotate::~CStickRotate()
{

}

//=======================
// ������
//=======================
HRESULT CStickRotate::Init(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J���[�ϐ�
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	

	//�{�^���A�ŉ摜
	pObj2D = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D->SetSize(500.0f, 300.0f);
	pObj2D->SetTexture(CTexture::TEXTURE_JOYPAD);
	pObj2D->SetColor(m_col);
	pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

	//�A�j���[�V�����p�ϐ�
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//�����J�E���g�p�ϐ�
	m_nStickCount = 0;		//�J�E���g��

	m_bStick = false;

	return S_OK;
}

//=======================
// �I��
//=======================
void CStickRotate::Uninit()
{

}

//=======================
// �X�V
//=======================
void CStickRotate::Update()
{
	CInputJoypad *pJoypad = CInput::GetJoypad();

	if (pObj2D != nullptr)
	{
		//�J�E���^�[�����Z
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10�t���[���o��
		 //�e�N�X�`���̃A�j���[�V����
			pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//�p�^�[��No.���X�V����
			m_nPatternAnim++;
		}

		//�ړ��ʂƖړI�̊p�x�̌v�Z
		if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
		{//W�L�[�������ꂽ�ꍇ
			if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				m_stick = STICK_UPLEFT;

				if (m_stickold != STICK_UPLEFT)
				{
					m_nStickCount++;
				}
			}
			else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
			{//D�L�[�������ꂽ�ꍇ
				m_stick = STICK_UPRIGHT;

				if (m_stickold != STICK_UPRIGHT)
				{
					m_nStickCount++;
				}
			}
			else
			{//W�L�[�����������ꂽ�ꍇ
				m_stick = STICK_UP;

				if (m_stickold != STICK_UP)
				{
					m_nStickCount++;
				}
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
		{//S�L�[�������ꂽ�ꍇ
			if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				m_stick = STICK_DOWNLEFT;

				if (m_stickold != STICK_DOWNLEFT)
				{
					m_nStickCount++;
				}
			}
			else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.5f)
			{//D�L�[�������ꂽ�ꍇ
				m_stick = STICK_DOWNRIGHT;

				if (m_stickold != STICK_DOWNRIGHT)
				{
					m_nStickCount++;
				}
			}
			else
			{//S�L�[�����������ꂽ�ꍇ
				m_stick = STICK_DOWN;

				if (m_stickold != STICK_DOWN)
				{
					m_nStickCount++;
				}
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//D�L�[���������ꂽ�ꍇ
			m_stick = STICK_RIGHT;

			if (m_stickold != STICK_RIGHT)
			{
				m_nStickCount++;
			}
		}
		else if (pJoypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//A�L�[���������ꂽ�ꍇ
			m_stick = STICK_LEFT;

			if (m_stickold != STICK_LEFT)
			{
				m_nStickCount++;
			}
		}

#ifdef _DEBUG
		if (CInputKeyboard::Trigger(DIK_N))
		{//N�L�[�����ꂽ��I��
			m_nStickCount = 45;
		}
#endif // !_DEBUG

		m_stickold = m_stick;

		if (m_nStickCount >= 45)
		{
			m_nStickCount = 0;
			m_stick = STICK_UP;
			m_stickold = STICK_UP;

			//�I�u�W�F�N�g�j��
			pObj2D->Uninit();
			pObj2D = nullptr;
		}
	}
}

//=======================
// �`��
//=======================
void CStickRotate::Draw()
{

}

//=======================
// ����
// �����F�ʒu
//=======================
CStickRotate *CStickRotate::Create(D3DXVECTOR3 pos)
{
	CStickRotate *pStickGame = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pStickGame = new CStickRotate;	//����

	if (pStickGame != nullptr)
	{//NULL�`�F�b�N

	 //������
		pStickGame->Init(D3DXVECTOR3(pos));
		pStickGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pStickGame;
}
