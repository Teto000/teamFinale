//=============================================================================
//
// �v���C���[�N���X(player.h)
// Author : �������l
// �T�v : �v���C���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "player.h"
#include "game.h"
#include "input_keyboard.h"
#include "camera.h"
#include "utility.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NOM_SPEED (1.0f)		// ���x
#define MIN_SPEED (0.0f)		// �Œᑬ�x
#define MAX_SPEED (10.0f)		// �ō����x
#define NOM_FRICTION (0.1f)		// ���C�W��

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���f���𐶐�����
//=============================================================================
CPlayer * CPlayer::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CPlayer *pPlayer = nullptr;

	// �������̉��
	pPlayer = new CPlayer;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pPlayer != nullptr);

	// ���l�̏�����
	pPlayer->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �C���X�^���X��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CPlayer::CPlayer()
{
	m_pMove = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	if (m_pMove == nullptr)
	{// �ړ�
		m_pMove = new CMove;
		assert(m_pMove != nullptr);
	}

	// �ړ����̏�����
	m_pMove->SetMoving(NOM_SPEED, MAX_SPEED, MIN_SPEED, NOM_FRICTION);

	// �e�N���X�̏�����
	CObjectX::Init(pos);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CPlayer::Uninit()
{
	if (m_pMove != nullptr)
	{// �I������
	 // �������̉��
		delete m_pMove;
		m_pMove = nullptr;
	}

	// �e�N���X�̏I��
	CObjectX::Uninit();

	// �I�u�W�F�N�g3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CPlayer::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	// �ߋ��ʒu�̍X�V
	m_posOld = pos;

	// �ړ�
	pos += Move();

	// �ʒu�̐ݒ�
	SetPos(pos);

	// ��]
	Rotate();

	// �e�N���X�̍X�V
	CObjectX::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CPlayer::Draw()
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : �ړ��L�[����͂ŁA�w������ւ̈ړ��x�N�g����Ԃ�
//=============================================================================
D3DXVECTOR3 CPlayer::Move()
{
	// �ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if ((CInputKeyboard::Press(DIK_W)
		|| CInputKeyboard::Press(DIK_A)
		|| CInputKeyboard::Press(DIK_D)
		|| CInputKeyboard::Press(DIK_S)))
	{// �ړ��L�[�������ꂽ
		if (CInputKeyboard::Press(DIK_W))
		{// [W]�L�[�������ꂽ��
			if (CInputKeyboard::Press(DIK_A))
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.25f;
			}
			else if (CInputKeyboard::Press(DIK_D))
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (CInputKeyboard::Press(DIK_S))
		{// [S]�L�[�������ꂽ��
			if (CInputKeyboard::Press(DIK_A))
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.75f;
			}
			else if (CInputKeyboard::Press(DIK_D))
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�Vq
				m_rotDest.y = D3DX_PI;
			}
		}
		else if (CInputKeyboard::Press(DIK_A))
		{// [A]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotDest.y = D3DX_PI * -0.5f;
		}
		else if (CInputKeyboard::Press(DIK_D))
		{// [D]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotDest.y = D3DX_PI * 0.5f;
		}

		// �J�������̎擾
		CCamera *pCamera = CGame::GetCamera(0);

		// �ړ������̎Z�o
		m_rotDest.y += pCamera->GetRot().y;

		// �ړ������̐��K��
		m_rotDest.y = CUtility::GetNorRot(m_rotDest.y);

		// �ړ��ʂ̌v�Z
		move = D3DXVECTOR3(sinf(m_rotDest.y), 0.0f, cosf(m_rotDest.y));

		// �p�x�̐��K��
		m_rotDest.y -= D3DX_PI;

		// �ړ������̐��K��
		m_rotDest.y = CUtility::GetNorRot(m_rotDest.y);
	}

	// �ړ����̌v�Z
 	m_pMove->Moving(move);

	// �ړ����̎擾
	D3DXVECTOR3 moveing = m_pMove->GetMove();

	// �����̎擾
	D3DXVECTOR3 rot = GetRot();

	// �ړI�̌����̕␳
	if (m_rotDest.y - rot.y >= D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y <= -D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y += D3DX_PI * 2;
	}

	return moveing;
}

//=============================================================================
// ��]
// Author : �������l
// �T�v : �ړI�̌����܂ŉ�]����
//=============================================================================
void CPlayer::Rotate()
{
	// �����̎擾
	D3DXVECTOR3 rot = GetRot();
	float fFriction = 0.5f;

	// �����̍X�V
	rot.y += (m_rotDest.y - rot.y) * fFriction;

	// �����̐��K��
	rot.y = CUtility::GetNorRot(rot.y);

	// �����̐ݒ�
	SetRot(rot);
}
