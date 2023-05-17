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
#include "application.h"
#include "fade.h"
#include "game.h"
#include "itemObj.h"
#include "player.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

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
	//�t���b�V���p�J���[�ϐ�
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�t���b�V�����
	m_flash = FLASH_IN;

	//�w�i�p���|���S��
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(1000.0f, 600.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//�{�^���|���S��
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
	pObj2D[1]->SetSize(300.0f, 100.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[1]->SetColor(m_col[1]);

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
	if (pObj2D[0] != nullptr
		&&pObj2D[1] != nullptr)
	{//�I�u�W�F�N�g������Ȃ�
		if (m_flash == FLASH_IN)
		{//�t���b�V�����
			m_col[1].a -= 0.03f;	//�|���S���𓧖��ɂ��Ă���

			if (m_col[1].a <= 0.0f)
			{
				m_col[1].a = 0.0f;
				m_flash = FLASH_OUT;	//�t���b�V���A�E�g���
			}
		}
		else if (m_flash == FLASH_OUT)
		{//�t���b�V���A�E�g���
			m_col[1].a += 0.02f;	//�|���S����s�����ɂ��Ă���

			if (m_col[1].a >= 1.0f)
			{
				m_col[1].a = 1.0f;
				m_flash = FLASH_IN;	//�t���b�V����Ԃ�

				pObj2D[1]->SetColor(m_col[1]);
			}
		}

		pObj2D[1]->SetColor(m_col[1]);

		//�^�C�~���O�悭�{�^������������
		if (m_col[1].a <= 1.0f
			&& m_col[1].a > 0.90f)
		{
			m_col[1].r = 0.0f;

			if (CInputKeyboard::Trigger(DIK_SPACE))
			{//SPACE�L�[�������ꂽ��
				//�|���S����S�폜����nullptr���
				pObj2D[0]->Uninit();
				pObj2D[1]->Uninit();
				pObj2D[0] = nullptr;
				pObj2D[1] = nullptr;

				// �v���C���[�̎擾
				CPlayer *pPlayer = CGame::GetPlayer();
				CItemObj *pPlayerItem = pPlayer->GetMyItem();

				if (pPlayerItem == nullptr)
				{// �A�C�e�����擾���Ă��Ȃ�
					pPlayerItem = CItemObj::Create();
					pPlayerItem->SetType(0);

					// �v���C���[�̃A�C�e���̐ݒ�
					pPlayer->Acquisition(pPlayerItem);
				}
			}
		}
		else
		{
			m_col[1].r = 1.0f;
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