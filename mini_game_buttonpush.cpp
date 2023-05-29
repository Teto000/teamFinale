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

#include "object2D.h"
#include "input_keyboard.h"
#include "fade.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

#include "itemObj.h"
#include "player.h"
#include "collision_rectangle3D.h"

//=======================
// �R���X�g���N�^
//=======================
CButtonPushGame::CButtonPushGame()
{

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
	m_nCount = 0;

	//�w�i�p���|���S��
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(1000.0f, 600.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//�Q�[�W�摜
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(900.0f, 250.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_GAUGE);
	pObj2D[1]->SetColor(m_col[1]);

	//�{�^���|���S��
	pObj2D[2] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[2]->SetSize(25.0f, 300.0f);
	pObj2D[2]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[2]->SetColor(m_col[2]);

	return S_OK;
}

//=======================
// �I��
//=======================
void CButtonPushGame::Uninit()
{
	
}

//=======================
// �X�V
//=======================
void CButtonPushGame::Update()
{
	//�I�u�W�F�N�g������Ȃ�
	if (pObj2D[0] != nullptr
		&&pObj2D[1] != nullptr)
	{
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
				if (pos.x >= 1080.0f)
				{
					m_move.x *= -1.0f;
					m_bEdge = true;
				}

				//�ړ��ʂ�ݒ�
				m_move.x += MAX_SPEED;
			}
			else
			{
				if (pos.x <= 200.0f)
				{
					m_move.x *= -1.0f;
					m_bEdge = false;
				}

				//�ړ��ʂ�ݒ�
				m_move.x -= MAX_SPEED;
			}

			//�ړ�
			pos += m_move;
			pObj2D[2]->SetPos(pos);

			if (CInputKeyboard::Trigger(DIK_SPACE))
			{//SPACE�L�[�������ꂽ��
			 //�o�[���^�񒆂̎�
				if (pos.x >= 615.0f
					&& pos.x <= 665.0f)
				{
					//�|���S����S�폜����nullptr���
					for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
					{
						pObj2D[nCnt]->Uninit();
						pObj2D[nCnt] = nullptr;
					}

					//�v���C���[���Q�[������Ԃ����������
					CGame *pGame = CApplication::GetGame();
					CPlayer *pPlayer[2] = {};
					CItemObj *pPlayerItem = {};

					for (int nCnt = 0; nCnt < pGame->GetMaxPlayer(); nCnt++)
					{
						//�v���C���[���̎擾
						pPlayer[nCnt] = pGame->GetPlayer(nCnt);

						if (pPlayerItem == nullptr)
						{// �A�C�e�����擾���Ă��Ȃ�
							pPlayerItem = CItemObj::Create();
							pPlayerItem->SetType(0);

							// �����蔻��̐ݒ�
							CCollision_Rectangle3D *pCollision = pPlayerItem->GetCollision();
							pCollision->SetSize(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
							pCollision->SetPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
							pCollision->SetUseFlag(false);
						}

						//�v���C���[���~�j�Q�[�����I�����鎞
						if (pPlayer[nCnt]->GetMiniGame() == true)
						{
							D3DXVECTOR3 PlayerPos = pPlayer[nCnt]->GetPos();
							pPlayer[nCnt]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 0.5f));
							pPlayer[nCnt]->SetMiniGame(false);	
							pPlayer[nCnt]->Retention(pPlayerItem);		// �v���C���[�̃A�C�e���̐ݒ�
						}
					}
				}
				else
				{
					m_bStop = true;
				}
			}
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