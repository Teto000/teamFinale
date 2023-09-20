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
	m_bCntTime = false;			//���Ԃ𐔂�����
	m_pMessage = nullptr;
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
	m_pos = pos;		//�ʒu
	m_nTime = 90;		//��������

	CObject2D::Init(pos);
	CObject2D::SetSize(100.0f,100.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_CLOCK);

	return S_OK;
}

//=======================
// �I��
//=======================
void CTime::Uninit()
{
	CObject2D::Uninit();
}

//=======================
// �X�V
//=======================
void CTime::Update()
{
	CObject2D::Update();

	if (CGame::GetFinish() && CMode::GetMode() == CMode::MODE_GAME)
	{//�Q�[�����I�����Ă���Ȃ�
		m_nFinTime++;

		if (m_nFinTime >= 60)
		{
			//���U���g��ʂɈڍs
			CMode::GetFade()->SetFade(CMode::MODE_RESULT);
		}

		//�^�C����ۑ�
		CRanking::SetNewTime(m_nTime);
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
				m_nTime--;
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
	CObject2D::Draw();
}

//=======================
// ����
// �����F�ʒu�A�R���{��
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