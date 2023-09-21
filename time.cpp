//===================================================
//
// �^�C�}�[����
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "time.h"
#include "number.h"
#include "game.h"
#include "renderer.h"
#include "ranking.h"
#include "input.h"
#include "input_keyboard.h"
#include "mode.h"
#include "fade.h"
#include "message.h"

//=======================
// �R���X�g���N�^
//=======================
CTime::CTime() : CObject2D(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̈ʒu
	m_nTime = 0;				//����
	m_nCntMove = 0;				//�ړ��܂ł̎���
	m_nFinTime = 0;				//�Q�[���I���܂ł̎���
	m_nCntFream = 0;			//�t���[�����̃J�E���g
	m_neeadleRotX = 0.0f;		//�j�̊p�x
	m_bCntTime = false;			//���Ԃ𐔂�����
	m_pMessage = nullptr;

	for (int i = 0; i < nMaxObj; i++)
	{
		m_pObj[i] = nullptr;
	}
}

//=======================
// �f�X�g���N�^
//=======================
CTime::~CTime()
{

}

//=======================
// ������
//=======================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;			//�ʒu
	m_neeadleRotX = -0.1f;	//�j�̊p�x
	m_nTime = nMaxTime;		//��������

	m_pObj[0] = new CObject2D;
	m_pObj[0]->Init(pos);
	m_pObj[0]->SetSize(180.0f,180.0f);
	m_pObj[0]->SetTexture(CTexture::TEXTURE_CLOCK);

	m_pObj[1] = new CObject2D;
	m_pObj[1]->Init(pos);
	m_pObj[1]->SetSize(180.0f, 140.0f);
	m_pObj[1]->SetTexture(CTexture::TEXTURE_CLOCK_NEEDLE);

	return S_OK;
}

//=======================
// �I��
//=======================
void CTime::Uninit()
{
	/*for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Uninit();
			delete m_pObj[i];
			m_pObj[i] = nullptr;
		}
	}*/
}

//=======================
// �X�V
//=======================
void CTime::Update()
{
	//�X�V
	for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Update();
		}
	}

	if (CInputKeyboard::Trigger(DIK_P))
	{
		m_neeadleRotX -= 0.1f;
	}

	//���v�̐j����]������
	m_pObj[1]->SetVtxCIE_Rot(m_pos,
		m_neeadleRotX,
		180.0f,
		140.0f);

	if (CGame::GetFinish() && CMode::GetMode() == CMode::MODE_GAME)
	{//�Q�[�����I�����Ă���Ȃ�
		m_nFinTime++;

		if (m_nFinTime >= 60)
		{
			//���U���g��ʂɈڍs
			CMode::GetFade()->SetFade(CMode::MODE_RESULT);
		}

		//�^�C����ۑ�
		//CRanking::SetNewTime(m_nTime);
	}
	else if(m_bCntTime && CMode::GetMode() == CMode::MODE_GAME)
	{//���Ԃ𐔂����ԂȂ�
		//�t���[�����𐔂���
		m_nCntFream++;

		//----------------------
		// ���Ԃ̉��Z
		//----------------------
		if (m_nCntFream >= 60)
		{
			if (m_nTime > 0)
			{
				//���Ԃ����炷
				m_nTime--;

				//�j�𓮂���
				//���ԃs�b�^���Ŏ��v�̐j���������悤�ɂ���
				m_neeadleRotX -= (6.2f / nMaxTime);
			}

			//�����̐ݒ�
			m_nCntFream = 0;

			if (m_nTime <= 0)
			{
				CGame::SetFinish(true);

				m_pMessage = CMessage::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, 800.0f, 200.0f);
			}
		}
	}
}

//=======================
// �`��
//=======================
void CTime::Draw()
{
	/*for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Draw();
		}
	}*/
}

//=======================
// ����
// �����F�ʒu
//=======================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pCombo = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pCombo = new CTime;	//����

	if (pCombo != nullptr)
	{//NULL�`�F�b�N
		//������
		pCombo->Init(D3DXVECTOR3(pos));
	}

	return pCombo;
}