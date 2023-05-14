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
#include "stage_select.h"
#include "input_keyboard.h"
#include "camera.h"
#include "utility.h"
#include "motion.h"
#include "objectX.h"
#include "move.h"
#include "itemObj.h"
#include "mini_game_basis.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NOM_SPEED (1.0f)		// ���x
#define MIN_SPEED (0.09f)		// �Œᑬ�x
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
	m_nCntRimit = 0;		// �ߋ��Ɏc��鎞�Ԃ𐔂���
	m_bFuture = false;		//�����ɂ��邩�ǂ���
	m_bMiniGame = false;	// �~�j�Q�[�������ǂ���
	m_pMyItem = nullptr;
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
	// �e�N���X�̏�����
	CMotionModel3D::Init(pos);

	if (m_pMove == nullptr)
	{// �ړ�
		m_pMove = new CMove;
		assert(m_pMove != nullptr);
	}

	// �ړ����̏�����
	m_pMove->SetMoving(NOM_SPEED, MAX_SPEED, MIN_SPEED, NOM_FRICTION);
	m_nParentParts = 3;

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
	CMotionModel3D::Uninit();

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
	// ���[�V�������̎擾
	CMotion *pMotion = CMotionModel3D::GetMotion();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	// �ߋ��ʒu�̍X�V
	SetPosOld(pos);

	// �ړ�
	pos += Move();

	// �ʒu�̐ݒ�
	SetPos(pos);

	// ��]
	Rotate();

	// ���[�v
	Warp();

	if (CInputKeyboard::Trigger(DIK_F))
	{// �A�C�e���̕ێ��̉���
		Drop();
	}

	//�����蔻��
	Collision();

	if (pMotion != nullptr
		&& !pMotion->GetMotion())
	{// �j���[�g�������[�V�����̐ݒ�
		m_EAction = NEUTRAL_ACTION;
		pMotion->SetNumMotion(m_EAction);
	}

	// �e�N���X�̍X�V
	CMotionModel3D::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CPlayer::Draw()
{
	// �e�N���X�̕`��
	CMotionModel3D::Draw();
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

	// ���[�V�������̎擾
	CMotion *pMotion = CMotionModel3D::GetMotion();

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

		//-----------------------------------
		// �J�������̎擾
		//-----------------------------------
		CCamera* pCamera = nullptr;
		switch (CApplication::GetMode())
		{//���[�h���Ƃ̏���
		 //�Q�[����ʂȂ�
		case CApplication::MODE_GAME:
			pCamera = CGame::GetCamera(0);
			break;

			//�X�e�[�W�I����ʂȂ�
		case CApplication::MODE_STAGESELECT:
			pCamera = CApplication::GetStage()->GetCamera();
			break;

		default:
			break;
		}

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

		if (m_EAction == NEUTRAL_ACTION)
		{// �ړ�
			m_EAction = MOVE_ACTION;

			if (pMotion != nullptr)
			{
				pMotion->SetNumMotion(m_EAction);
			}
		}
	}

	// �ړ����̌v�Z
 	m_pMove->Moving(move);

	// �ړ����̎擾
	D3DXVECTOR3 moveing = m_pMove->GetMove();
	float fLength = m_pMove->GetMoveLength();

	if (fLength <= 0.0f
		&& pMotion != nullptr
		&& m_EAction == MOVE_ACTION)
	{
		m_EAction = NEUTRAL_ACTION;
		pMotion->SetNumMotion(m_EAction);
	}

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

//=============================================================================
// ���[�v
// Author : �����P��
// �T�v : ���݂̏��(�ߋ��E����)�ɍ��킹�Ďw��̈ʒu�܂Ń��[�v����
//=============================================================================
void CPlayer::Warp()
{
	//-----------------------------
	// �ϐ��錾
	//-----------------------------
	D3DXVECTOR3 pos = GetPos();	//�ʒu���擾
	int nTimeRimit = 300;		//�ߋ��Ɏc��鎞�Ԃ̌��E

	//-----------------------------
	// �^�C�����~�b�g�̏���
	//-----------------------------
	if (!m_bFuture)
	{//�ߋ��ɂ���Ȃ�
		//���Ԃ𐔂���
		m_nCntRimit++;

		if (m_nCntRimit >= nTimeRimit)
		{//���Ԃ����E�n�𒴂�����
			//�����ɑ���
			m_bFuture = true;

			//�ʒu���X�V
			pos.y = 0.0f;
			SetPos(pos);

			//���Ԃ�������
			m_nCntRimit = 0;
		}
	}

	//-----------------------------
	// �L�[���������Ƃ��̏���
	// (�I�u�W�F�N�g�ɐG�ꂽ���ɂ���\��)
	//-----------------------------
	if (CInputKeyboard::Trigger(DIK_0))
	{//0�L�[���������Ƃ�
		//-----------------------------
		// �ʒu�̕ύX
		//-----------------------------
		if (m_bFuture)
		{//�����ɂ���Ȃ�
			//�v���C���[�̈ʒu��ύX
			pos.y = 300.0f;
		}
		else
		{//�ߋ��ɂ���Ȃ�
			pos.y = 0.0f;
		}

		//�ʒu���X�V
		SetPos(pos);

		//���݂̎����؂�ւ�
		m_bFuture = !m_bFuture;
	}
}

//=============================================================================
// �����蔻��̏���
// �T�v : �����蔻��̏������܂Ƃ߂��֐�
//=============================================================================
void CPlayer::Collision()
{
	//-----------------------------------
	// �I�u�W�F�N�g�Ƃ̓����蔻��
	//-----------------------------------
	{
		// ���[�V�������̎擾
		CMotion *pMotion = CMotionModel3D::GetMotion();

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = GetPosOld();
		D3DXVECTOR3 size(20.0f, 20.0f, 20.0f);
		D3DXVECTOR3 targetPos(0.0f, 0.0f, 0.0f);
		CObjectX *pObject = nullptr;

		//--------------------------------
		// �I�u�W�F�N�g�̈ʒu���擾
		//--------------------------------
		switch (CApplication::GetMode())
		{//���[�h���Ƃ̏���

		 //----------------------------
		 // �Q�[����ʂȂ�
		 //----------------------------
		case CApplication::MODE_GAME:
			targetPos = CGame::GetObjectX()->GetPosition();

			//--------------------------------
			// �����蔻��
			//--------------------------------
			if (CUtility::Collision(pos, posOld, size
				, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
			{// �Փ˔��肪�s��ꂽ�B
				if (m_bMiniGame)
				{
					//�~�j�Q�[���̐���
					CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTUNPUSH);
					m_bMiniGame = false;
				}
			}
			else
			{
				m_bMiniGame = true;
			}
			break;

		//----------------------------
		// �X�e�[�W�I����ʂȂ�
		//----------------------------
		case CApplication::MODE_STAGESELECT:
			pObject = CApplication::GetStage()->GetObjectX();
			targetPos = pObject->GetPosition();
			break;

		default:
			break;
		}

		//--------------------------------
		// �����蔻��
		//--------------------------------
		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
			&& pObject->GetObjType() == CObject::OBJTYPE_ITEM)
		{// �Փ˔��肪�s��ꂽ�B
			if (m_pMyItem == nullptr
				&& CInputKeyboard::Trigger(DIK_H))
			{// �A�C�e�����������Ă��Ȃ�
				CModel3D *pParts = (CModel3D*)pMotion->GetParts(m_nParentParts);
				m_pMyItem = (CItemObj*)pObject;
				m_pMyItem->SetParent(pParts);
			}
		}

		//�ʒu�̍X�V
		SetPos(pos);
	}
}

//=============================================================================
// �A�C�e���̕ێ�����
// Author : �������l
// �T�v : �A�C�e���̕ێ�����������
//=============================================================================
void CPlayer::Drop()
{
	if (m_pMyItem != nullptr)
	{
		m_pMyItem->SetParent();
		m_pMyItem = nullptr;
	}
}
