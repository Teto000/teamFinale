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
#include <vector>

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
#include "collision_rectangle3D.h"

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
	m_nNumber = 0;			// �v���C���[�ԍ�
	m_bFuture = false;		// �����ɂ��邩�ǂ���
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

	//----------------------------
	// �ړ�
	//----------------------------
	switch (m_nNumber)
	{
	case 0:
		pos += Move(DIK_W, DIK_S, DIK_A, DIK_D);
		break;

	case 1:
		pos += Move(DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT);
		break;

	default:
		break;
	}

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

	// �����蔻��̎擾
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->Collision(CObject::OBJTYPE_NONE, true);

	// ���������I�u�W�F�N�g�̃��X�g���擾
	std::vector<CObject*> apCollidedObj = pCollision->GetCollidedObj();

	if (apCollidedObj.size() > 0)
	{// ���������I�u�W�F�N�g�Ƃ̏���
		for (int nCntObj = 0; nCntObj < apCollidedObj.size(); nCntObj++)
		{
			CObject *pCollidedObj = apCollidedObj.at(nCntObj);

			if (pCollidedObj->GetObjType() == CObject::OBJTYPE_ITEM
				&& CInputKeyboard::Trigger(DIK_H))
			{// �A�C�e����ێ����Ă��炷�A�A�C�e���I�u�W�F�N�g�ɐG��Ă����ꍇ�擾
				Retention((CItemObj*)pCollidedObj);
			}
		}
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

void CPlayer::SetMiniGame(bool bMiniGame)
{
	m_bMiniGame = bMiniGame;
}

//=============================================================================
// �A�C�e���̎擾����
// Author : �������l
// �T�v : �������A�C�e���������Ă��Ȃ�������A�A�C�e�����擾����
//=============================================================================
void CPlayer::Retention(CItemObj * pItem)
{
	// ���[�V�������̎擾
	CMotion *pMotion = CMotionModel3D::GetMotion();

	if (m_pMyItem == nullptr)
	{// �A�C�e�����������Ă��Ȃ�
		CModel3D *pParts = (CModel3D*)pMotion->GetParts(m_nParentParts);
		m_pMyItem = pItem;
		m_pMyItem->SetParent(pParts);
	}
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : �ړ��L�[����͂ŁA�w������ւ̈ړ��x�N�g����Ԃ�
// ���� : �㉺���E�L�[
//=============================================================================
D3DXVECTOR3 CPlayer::Move(int nUpKey, int nDownKey, int nLeftKey, int nRightKey)
{
	// �ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���[�V�������̎擾
	CMotion *pMotion = CMotionModel3D::GetMotion();

	if (!m_bMiniGame
		&& (CInputKeyboard::Press(nUpKey)
			|| CInputKeyboard::Press(nLeftKey)
			|| CInputKeyboard::Press(nRightKey)
			|| CInputKeyboard::Press(nDownKey)))
	{// �ړ��L�[�������ꂽ
		if (CInputKeyboard::Press(nUpKey))
		{// [W]�L�[�������ꂽ��
			if (CInputKeyboard::Press(nLeftKey))
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.25f;
			}
			else if (CInputKeyboard::Press(nRightKey))
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (CInputKeyboard::Press(nDownKey))
		{// [S]�L�[�������ꂽ��
			if (CInputKeyboard::Press(nLeftKey))
			{// [A]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * -0.75f;
			}
			else if (CInputKeyboard::Press(nRightKey))
			{// [D]�L�[�������ꂽ��
			 // �ړ������̍X�V
				m_rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// �ړ������̍X�Vq
				m_rotDest.y = D3DX_PI;
			}
		}
		else if (CInputKeyboard::Press(nLeftKey))
		{// [A]�L�[�������ꂽ��
		 // �ړ������̍X�V
			m_rotDest.y = D3DX_PI * -0.5f;
		}
		else if (CInputKeyboard::Press(nRightKey))
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
			pCamera = CGame::GetCamera();
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

		if (pMotion != nullptr
			&& m_EAction == NEUTRAL_ACTION)
		{// �ړ�
			m_EAction = MOVE_ACTION;
			pMotion->SetNumMotion(m_EAction);
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
			pObject = CApplication::GetGame()->GetObjectX();
			targetPos = pObject->GetPosition();

			//--------------------------------
			// �����蔻��
			//--------------------------------
			if (CUtility::Collision(pos, posOld, size
				, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
			{// �Փ˔��肪�s��ꂽ�B
				if (!m_bMiniGame)
				{
					//�~�j�Q�[���̐���
					CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTUNPUSH);
					m_bMiniGame = true;
				}

				//---------------------------------
				// �I�u�W�F�N�g�̌����ڂ�ύX����
				//---------------------------------
				if (CInputKeyboard::Trigger(DIK_Z))
				{//Z�L�[�������ꂽ��
					pObject->SetType(10);
				}
			}
			break;

		//----------------------------
		// �X�e�[�W�I����ʂȂ�
		//----------------------------
		case CApplication::MODE_STAGESELECT:
			pObject = CApplication::GetStage()->GetObjectX();
			targetPos = pObject->GetPosition();
			
			//--------------------------------
			// �����蔻��
			//--------------------------------
			if (CUtility::Collision(pos, posOld, size
				, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
			{// �Փ˔��肪�s��ꂽ�B
				CStageSelect::SetViewMap(true);		//�}�b�v��\��������
				CStageSelect::SetStart(true);		//��ʑJ�ڏo������
			}
			else
			{
				CStageSelect::SetViewMap(false);	//�}�b�v��\�����Ȃ����
				CStageSelect::SetStart(false);		//��ʑJ�ڏo���Ȃ����
			}
			break;

		default:
			break;
		}

		//--------------------------------
		// �A�C�e���Ƃ̓����蔻��
		//--------------------------------
		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
			&& pObject->GetObjType() == CObject::OBJTYPE_ITEM)
		{// �Փ˔��肪�s��ꂽ�B
			if (CInputKeyboard::Trigger(DIK_H))
			{// �A�C�e�����擾����
				Retention((CItemObj*)pObject);
			}
		}

		//--------------------------------
		// ���v�Ƃ̓����蔻��
		//--------------------------------
		pObject = CApplication::GetGame()->GetObjectX();
		targetPos = pObject->GetPosition();

		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
			&& pObject->GetObjType() == CObject::OBJTYPE_CLOCK)
		{// �Փ˔��肪�s��ꂽ�B
			int a = 0;
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
		// �e�ݒ�̕���
		m_pMyItem->SetParent();

		// �����蔻��̐ݒ�
		CCollision_Rectangle3D* pItemCollision = m_pMyItem->GetCollision();
		pItemCollision->SetUseFlag(true);

		m_pMyItem = nullptr;
	}
}
