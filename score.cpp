//===================================================
//
// �X�R�A����
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "score.h"
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
CScore::CScore() : CObject(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̈ʒu
	m_nScore = 0;				//����
	fInterval = 0.0f;			//���l�̊Ԋu
	m_pScoreBG = nullptr;

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//���̌��̐��l
		m_pNumber[i] = nullptr;	//���l
	}
}

//=======================
// �f�X�g���N�^
//=======================
CScore::~CScore()
{

}

//=======================
// ������
//=======================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;		//�ʒu
	m_nScore = 0;		//�X�R�A
	fInterval = 50.0f;	//���l�̊Ԋu

	if (CMode::GetGame())
	{
		m_pScoreBG = new CObject2D;
	}

	if (m_pScoreBG)
	{
		m_pScoreBG->Init(D3DXVECTOR3(m_pos.x + 70.0f, m_pos.y + 20.0f, 0.0f));
		m_pScoreBG->SetSize(400.0f, 350.0f);
		m_pScoreBG->SetTexture(CTexture::TEXTURE_SCORE);
	}

	//------------------------------
	// ���l�̐ݒ�
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nScore);
		m_pNumber[i]->Set(i);
	}

	SetNumber();

	return S_OK;
}

//=======================
// �I��
//=======================
void CScore::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Uninit();
	}
}

//=======================
// �X�V
//=======================
void CScore::Update()
{
	if (m_pScoreBG)
	{
		m_pScoreBG->Update();
	}

	if (CGame::GetFinish())
	{//�Q�[�����I�����Ă���Ȃ�
		//���݂̃X�R�A���X�e�[�W�̃X�R�A�ɐݒ�
		CApplication::SetStageScore(0,m_nScore);
	}
}

//=======================
// �`��
//=======================
void CScore::Draw()
{
	if (m_pScoreBG)
	{
		m_pScoreBG->Draw();
	}

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Draw();
	}
}

//=======================
// ����
// �����F�ʒu
//=======================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pScore = new CScore;	//����

	if (pScore != nullptr)
	{//NULL�`�F�b�N
		//������
		pScore->Init(D3DXVECTOR3(pos));
	}

	return pScore;
}

//=======================
// ���l�̐ݒ�
//=======================
void CScore::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		if (m_pNumber[i] != nullptr)
		{//null����Ȃ��Ȃ�
		 //�������v�Z
			int nDigit = (int)(log10(m_nScore) + 1);

			//�i���o�[�̕`���L���E�����ɂ���
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nScore == 0)
			{//�R���{����0�Ȃ�
			 //�i���o�[�̕`���L���E�����ɂ���
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//pow�Ō������o���B
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//�����Ƃ̒l�����߂�
			m_aPosTexU[i] = (m_nScore % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}

//=======================
// �X�R�A�̐ݒ�
// �����F�ݒ肵�������l
//=======================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	SetNumber();
}

//=======================
// �X�R�A�̉��Z
// �����F�ݒ肵�������l
//=======================
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;

	SetNumber();
}

//=======================
// �`���Ԃ̐ݒ�
// �����F�`���Ԃ�bool
//=======================
void CScore::SetDraw(bool bDraw)
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
void CScore::SetColor(D3DXCOLOR col)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetColor(col);
	}
}