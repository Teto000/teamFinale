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

#include "object2D.h"
#include "input_keyboard.h"
#include "application.h"
#include "fade.h"
#include "game.h"
#include "number.h"

//=======================
// �R���X�g���N�^
//=======================
CButtonMash::CButtonMash()
{
	//�I�u�W�F�N�g2D�ϐ�
	pObj2D = nullptr;

	//�A�j���[�V�����p�ϐ�
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//�����J�E���g�p�ϐ�
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̈ʒu
	m_fInterval = 40.0f;	//���l�̊Ԋu
	m_nMashCounter = 0;		//�J�E���g��

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//���̌��̐��l
		m_pNumber[i] = nullptr;	//���l
	}
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
	//------------------------------
	//�{�^���|���S���̐ݒ�
	//------------------------------
	pObj2D = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D->SetSize(300.0f, 300.0f);
	pObj2D->SetTexture(CTexture::TEXTURE_BUTTON);
	pObj2D->SetSplitTex(1.0f,1.0f,2.0f,(float)m_nPatternAnim);
	m_pos = pObj2D->GetPosition();

	//------------------------------
	// ���l�̐ݒ�
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3((m_pos.x + 15.0f) + (m_fInterval * i), m_pos.y - 60.0f, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nMashCounter);
		m_pNumber[i]->Set(i);
		m_pNumber[i]->SetSize(40.0f, 60.0f);
	}

	SetNumber();

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
	if (pObj2D != nullptr)
	{
		//�J�E���^�[�����Z
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10�t���[���o��
		 //�e�N�X�`���̃A�j���[�V����
			pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//�p�^�[��No.���X�V����
			m_nPatternAnim++;
		}

		if (CInputKeyboard::Trigger(DIK_J))
		{//J�L�[���������Ƃ���
			//�A�ŃJ�E���g��1���₷
			m_nMashCounter++;
			SetNumber();
		}

		if (m_nMashCounter >= 30)
		{//�A�Ő���30��������
			//�I�u�W�F�N�g�j��
			pObj2D->Uninit();
			pObj2D = nullptr;

			//���l�j��
			for (int i = 0; i < nMaxDigits; i++)
			{
				m_pNumber[i]->Uninit();
			}
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

//=======================
// ���l�̐ݒ�
//=======================
void CButtonMash::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		if (m_pNumber[i] != nullptr)
		{//null����Ȃ��Ȃ�
		 //�������v�Z
			int nDigit = (int)(log10(m_nMashCounter) + 1);

			//�i���o�[�̕`���L���E�����ɂ���
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nMashCounter == 0)
			{//�R���{����0�Ȃ�
			 //�i���o�[�̕`���L���E�����ɂ���
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//pow�Ō������o���B
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//�����Ƃ̒l�����߂�
			m_aPosTexU[i] = (m_nMashCounter % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}
