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

//=======================
// �R���X�g���N�^
//=======================
CTime::CTime() : CObject(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̈ʒu
	m_nTime = 0;				//����
	m_nCntMove = 0;				//�ړ��܂ł̎���
	m_nFinTime = 0;				//�Q�[���I���܂ł̎���
	m_nCntFream = 0;			//�t���[�����̃J�E���g
	fInterval = 0.0f;			//���l�̊Ԋu
	m_bCntTime = false;			//���Ԃ𐔂�����

	m_pObject = nullptr;

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//���̌��̐��l
		m_pNumber[i] = nullptr;	//���l
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
	m_pos = pos;		//�ʒu
	m_nTime = 5;		//��������
	fInterval = 50.0f;	//���l�̊Ԋu

	m_pObject = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pObject->SetTexture(CTexture::TEXTURE_FINISH);

	//------------------------------
	// ���l�̐ݒ�
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nTime);
		m_pNumber[i]->Set(i);
	}

	SetNumber();

	return S_OK;
}

//=======================
// �I��
//=======================
void CTime::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Uninit();
	}
}

//=======================
// �X�V
//=======================
void CTime::Update()
{
	if (CGame::GetFinish())
	{//�Q�[�����I�����Ă���Ȃ�
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
			SetNumber();
			m_nCntFream = 0;

			if (m_nTime <= 0)
			{
				m_pObject->SetSize(800.0f, 300.0f);
				m_nFinTime++;

				if (m_nFinTime >= 3)
				{
					//���U���g��ʂɈڍs
					//CMode::GetFade()->SetFade(CMode::MODE_RESULT);
				}
			}
		}
	}
}

//=======================
// �`��
//=======================
void CTime::Draw()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Draw();
	}
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

//=======================
// ���l�̐ݒ�
//=======================
void CTime::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		if (m_pNumber[i] != nullptr)
		{//null����Ȃ��Ȃ�
			//�������v�Z
			int nDigit = (int)(log10(m_nTime) + 1);

			//�i���o�[�̕`���L���E�����ɂ���
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nTime == 0)
			{//�R���{����0�Ȃ�
				//�i���o�[�̕`���L���E�����ɂ���
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//pow�Ō������o���B
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//�����Ƃ̒l�����߂�
			m_aPosTexU[i] = (m_nTime % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}

//=======================
// ���Ԃ̐ݒ�
// �����F�ݒ肵�������l
//=======================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

	SetNumber();
}

//=======================
// �`���Ԃ̐ݒ�
// �����F�`���Ԃ�bool
//=======================
void CTime::SetDraw(bool bDraw)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetEnable(bDraw);
	}
}

//=======================
// �F�̐ݒ�
// �����F�ύX��̐F
//=======================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetColor(col);
	}
}