//===================================================
//
// �{�^���A�ŏ���
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "mg_buttonmash.h"
#include "application.h"
#include "renderer.h"

#include "input_keyboard.h"
#include "object2D.h"
#include "game.h"

#include "itemObj.h"
#include "player.h"

//=======================
// �R���X�g���N�^
//=======================
CButtonMash::CButtonMash()
{
	
}

//=======================
// �f�X�g���N�^
//=======================
CButtonMash::~CButtonMash()
{

}

//=======================
// ������
//=======================
HRESULT CButtonMash::Init(D3DXVECTOR3 pos)
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J���[�ϐ�
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_col[2] = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f);

	//�w�i�p���|���S��
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(780.0f, 350.0f, 0.0f));
	pObj2D[0]->SetSize(300.0f, 50.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//�{�^���A�ŉ摜
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(300.0f, 300.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_BUTTON);
	pObj2D[1]->SetColor(m_col[1]);
	pObj2D[1]->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

	//���C�t�p�|���S��
	for (int nCnt = 0; nCnt < MAX_LIFEPOLYGON; nCnt++)
	{
		pLife[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
		pLife[nCnt]->SetSize(10.0f, 40.0f);
		pLife[nCnt]->SetTexture(CTexture::TEXTURE_NONE);
		pLife[nCnt]->SetColor(m_col[3]);
	}

	//�A�j���[�V�����p�ϐ�
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//�����J�E���g�p�ϐ�
	m_nMashCounter = -1;		//�J�E���g��

	return S_OK;
}

//=======================
// �I��
//=======================
void CButtonMash::Uninit()
{

}

//=======================
// �X�V
//=======================
void CButtonMash::Update()
{
	if (pObj2D[0] != nullptr
		&&pLife[0] != nullptr)
	{
		//�J�E���^�[�����Z
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10�t���[���o��
			//�e�N�X�`���̃A�j���[�V����
			pObj2D[1]->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//�p�^�[��No.���X�V����
			m_nPatternAnim++;
		}

		if (CInputKeyboard::Trigger(DIK_SPACE))
		{//J�L�[���������Ƃ���
			//�A�ŃJ�E���g��1���₷
			m_nMashCounter++;
		}

		//�A�ł��邽�тɃ|���S���ɐF��t����
		if (m_nMashCounter != -1)
		{
			m_col[2].a = 1.0f;
			pLife[m_nMashCounter]->SetColor(m_col[2]);
			pLife[m_nMashCounter]->SetPos(D3DXVECTOR3(640.0f + (10.0f * m_nMashCounter), 350.0f, 0.0f));
		}

		if (m_nMashCounter >= MAX_LIFEPOLYGON - 1)
		{//�A�Ő������C�t�|���S�����𒴂�����
		 //�I�u�W�F�N�g�j��
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			for (int nCnt = 0; nCnt < MAX_LIFEPOLYGON; nCnt++)
			{
				pLife[nCnt]->Uninit();
				pLife[nCnt] = nullptr;
			}

			//CGame *pGame = CApplication::GetGame();
			//CPlayer *pPlayer[2] = {};
			//CItemObj *pPlayerItem = {};

			//for (int nCnt = 0; nCnt < pGame->GetMaxPlayer(); nCnt++)
			//{
			//	//�v���C���[���̎擾
			//	pPlayer[nCnt] = pGame->GetPlayer(nCnt);

			//	if (pPlayerItem == nullptr)
			//	{// �A�C�e�����擾���Ă��Ȃ�
			//		pPlayerItem = CItemObj::Create();
			//		pPlayerItem->SetType(0);
			//	}

			//	pPlayer[nCnt]->Retention(pPlayerItem);		// �v���C���[�̃A�C�e���̐ݒ�
			//}
		}
	}
}

//=======================
// �`��
//=======================
void CButtonMash::Draw()
{

}

//=======================
// ����
// �����F�ʒu
//=======================
CButtonMash *CButtonMash::Create(D3DXVECTOR3 pos)
{
	CButtonMash *pMashGame = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMashGame = new CButtonMash;	//����

	if (pMashGame != nullptr)
	{//NULL�`�F�b�N

	 //������
		pMashGame->Init(D3DXVECTOR3(pos));
		pMashGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pMashGame;
}
