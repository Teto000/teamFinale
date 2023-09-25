//===================================================
//
// �~�j�Q�[���{�^���v�b�V������
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "mini_game_buttonpush.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "debug_proc.h"

#include "object2D.h"
#include "input.h"
#include "input_joypad.h"
#include "input_keyboard.h"
#include "fade.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

#include "itemObj.h"
#include "player.h"
#include "collision_rectangle3D.h"
#include "game_center.h"
#include "utility.h"

//=======================
// �R���X�g���N�^
//=======================
CButtonPushGame::CButtonPushGame()
{
	m_nCount = 0;			//�J�E���g
	m_nCntPlayTime = 0;		//����o����܂ł̎��Ԃ𐔂���
	m_bStop = false;		//�~�܂邩�ǂ���
	m_bEdge = false;		//�[�ɂ��ǂ蒅�������ǂ���
}

//=======================
// �f�X�g���N�^
//=======================
CButtonPushGame::~CButtonPushGame()
{

}

//=======================
// ������
//=======================
HRESULT CButtonPushGame::Init(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�t���b�V���p�J���[�ϐ�
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�t���b�V�����
	m_flash = CLEAR_IN;

	//�[�܂ł��������ǂ���
	m_bEdge = false;
	m_bStop = false;
	m_bOnce = false;
	m_nCount = 0;

	//�w�i�p���|���S��
	pObj2D[0] = CBillBoard::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(150.0f, 70.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//�Q�[�W�摜
	pObj2D[1] = CBillBoard::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(150.0f, 45.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_GAUGE);
	pObj2D[1]->SetColor(m_col[1]);

	//�{�^���|���S��
	pObj2D[2] = CBillBoard::Create(D3DXVECTOR3(750.0f, 350.0f, 0.0f));
	pObj2D[2]->SetSize(5.0f, 40.0f);
	pObj2D[2]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[2]->SetColor(m_col[2]);

	return S_OK;
}

//=======================
// �I��
//=======================
void CButtonPushGame::Uninit()
{
	m_nCntPlayTime = 0;
}

//=======================
// �X�V
//=======================
void CButtonPushGame::Update()
{
	//�I�u�W�F�N�g������Ȃ�
	if (pObj2D[0] != nullptr
		&& pObj2D[1] != nullptr)
	{
		CGameCenter *pParent = GetParent();
		CPlayer *pPlayer = pParent->GetPlayer();
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 ObjPos = pObj2D[1]->GetPosition();
		float ObjSize = pObj2D[1]->GetWidth();

		if (!m_bOnce)
		{
			pObj2D[2]->SetPos(PlayerPos);
			m_bOnce = true;
		}

		//����\�܂ł̎��Ԃ𐔂���
		m_nCntPlayTime++;

		if (!m_bStop)
		{
			//�ʒu�̎擾
			D3DXVECTOR3 pos = pObj2D[2]->GetPosition();

			//�ړ��ʂ̍ő�l��ݒ�
			if (m_move.x <= -MAX_SPEED)
			{
				m_move.x = -MAX_SPEED;
			}
			else if (m_move.x >= MAX_SPEED)
			{
				m_move.x = MAX_SPEED;
			}

			//�[�܂ōs�����甽��
			if (!m_bEdge)
			{
				if (pos.x >= ObjPos.x + ObjSize / 2)
				{
					m_move.x *= -1.0f;
					m_bEdge = true;
				}

				//�ړ��ʂ�ݒ�
				m_move.x += MAX_SPEED;
			}
			else
			{
				if (pos.x <= ObjPos.x - ObjSize / 2)
				{
					m_move.x *= -1.0f;
					m_bEdge = false;
				}

				//�ړ��ʂ�ݒ�
				m_move.x -= MAX_SPEED;
			}

			//�ړ�
			pos += m_move;

			pObj2D[0]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 150.0f, PlayerPos.z));
			pObj2D[1]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 150.0f, PlayerPos.z));
			pObj2D[2]->SetPos(D3DXVECTOR3(pos.x, PlayerPos.y + 150.0f, PlayerPos.z));

			GameUpdate();
		}
		else if (m_bStop)
		{
			m_nCount++;

			if (m_flash == CLEAR_IN)
			{//�������
				m_col[2].a -= 0.5f;	//�|���S���𓧖��ɂ��Ă���

				if (m_col[2].a <= 0.0f)
				{
					m_col[2].a = 0.0f;
					m_flash = CLEAR_OUT;	//��������Ȃ����
				}
			}
			else if (m_flash == CLEAR_OUT)
			{//��������Ȃ����
				m_col[2].a += 0.5f;	//�|���S����s�����ɂ��Ă���

				if (m_col[2].a >= 1.0f)
				{
					m_col[2].a = 1.0f;
					m_flash = CLEAR_IN;	//������Ԃ�

					pObj2D[2]->SetColor(m_col[2]);
				}
			}

			if (m_nCount >= 30)
			{
				m_col[2].a = 1.0f;
				m_bStop = false;
				m_nCount = 0;
			}

			pObj2D[2]->SetColor(m_col[2]);
		}
	}
}

//=======================
// �`��
//=======================
void CButtonPushGame::Draw()
{
	
}

//=======================
// �~�j�Q�[���̍X�V����
//=======================
void CButtonPushGame::GameUpdate()
{
	CGameCenter *pParent = GetParent();
	CPlayer *pPlayer = pParent->GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 ObjPos = pObj2D[1]->GetPosition();

	//�ʒu�̎擾
	D3DXVECTOR3 pos = pObj2D[2]->GetPosition();

#ifdef _DEBUG
	if (CInputKeyboard::Trigger(DIK_SPACE)
		&& m_nCntPlayTime > nMaxPlayTime)
	{//SPACE�L�[�������ꂽ�� & ����\���ԂɒB���Ă�����
	 //�o�[���^�񒆂̎�
		if (pos.x >= ObjPos.x - SUCCESS_RANGE
			&& pos.x <= ObjPos.x + SUCCESS_RANGE)
		{
			//�|���S����S�폜����nullptr���
			for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			//�v���C���[���Q�[������Ԃ����������
			CGame *pGame = CMode::GetGame();

			//�v���C���[���~�j�Q�[�����I�����鎞
			if (GetGame())
			{
				SetGame(false);
			}
		}
		else
		{
			m_bStop = true;
		}
	}
#endif // _DEBUG
	CInputJoypad *pJoypad = CInput::GetJoypad();

	if (pJoypad->Trigger(CInputJoypad::JOYKEY_B)
		&& m_nCntPlayTime > nMaxPlayTime)
	{//SPACE�L�[�������ꂽ�� & ����\���ԂɒB���Ă�����
	 //�o�[���^�񒆂̎�
		if (pos.x >= ObjPos.x - SUCCESS_RANGE
			&& pos.x <= ObjPos.x + SUCCESS_RANGE)
		{
			//�|���S����S�폜����nullptr���
			for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			//�v���C���[���Q�[������Ԃ����������
			CGame *pGame = CMode::GetGame();

			//�v���C���[���~�j�Q�[�����I�����鎞
			if (GetGame())
			{
				SetGame(false);
			}
		}
		else
		{
			m_bStop = true;
		}
	}
}

//=======================
// ����
// �����F�ʒu�A�l�A����
//=======================
CButtonPushGame *CButtonPushGame::Create(D3DXVECTOR3 pos)
{
	CButtonPushGame *pPushGame= nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pPushGame = new CButtonPushGame;	//����

	if (pPushGame != nullptr)
	{//NULL�`�F�b�N

		//������
		pPushGame->Init(D3DXVECTOR3(pos));
		pPushGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pPushGame;
}