//===================================================
//
// �w�i�̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "bg.h"
#include "renderer.h"
#include "texture.h"

//========================
// �R���X�g���N�^
//========================
CBg::CBg() : CObject(1)
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//========================
// �f�X�g���N�^
//========================
CBg::~CBg()
{

}

//========================
// ������
//========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;
	m_fWidth = SCREEN_WIDTH;
	m_fHeight = SCREEN_HEIGHT;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);

		//-------------------------
		// ��ނ��Ƃ̏���
		//-------------------------
		switch (m_type)
		{
		//�^�C�g����ʂ̔w�i
		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_TITLE);
			break;

		//���U���g��ʂ̔w�i
		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_RESULT);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
	}

	return S_OK;
}

//========================
// �I��
//========================
void CBg::Uninit()
{

}

//========================
// �X�V
//========================
void CBg::Update()
{
	
}

//========================
// �`��
//========================
void CBg::Draw()
{

}

//========================
// ����
//========================
CBg* CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBg = nullptr;

	//----------------------------------
	// �w�i�̐����Ə�����
	//----------------------------------
	pBg = new CBg;	//����
	pBg->m_pObject2D = new CObject2D(1);

	if (pBg != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pBg->m_type = type;

		//������
		pBg->Init(pos);
	}

	return pBg;
}