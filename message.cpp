//===================================================
//
// ���b�Z�[�W��\�����鏈��
// Author : Sato Teruto
//
//===================================================

//----------------------------
// �C���N���[�h
//----------------------------
#include "message.h"

//==========================================
// �R���X�g���N�^
//==========================================
CMessage::CMessage()
{
	m_type = MESSAGETYPE_NONE;
	m_nTime = 0;
}

//==========================================
// �f�X�g���N�^
//==========================================
CMessage::~CMessage()
{
}

//==========================================
// ������
//==========================================
HRESULT CMessage::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);

	switch (m_type)
	{
	case MESSAGE_TYPE_FINISH:
		CObject2D::SetTexture(CTexture::TEXTURE_FINISH);
		SetSize(800.0f, 200.0f);
		break;

	case MESSAGE_TYPE_COMPLETE:
		CObject2D::SetTexture(CTexture::TEXTURE_COMPLETE);
		SetSize(800.0f, 300.0f);
		break;

	default:
		break;
	}

	return S_OK;
}

//==========================================
// �I��
//==========================================
void CMessage::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
// �X�V
//==========================================
void CMessage::Update()
{
	CObject2D::Update();

	m_nTime++;

	if (m_type == MESSAGE_TYPE_COMPLETE && m_nTime >= 60)
	{
		m_nTime = 0;
		Uninit();
	}
}

//==========================================
// �`��
//==========================================
void CMessage::Draw()
{
	CObject2D::Draw();
}

//==========================================
// ����
//==========================================
CMessage * CMessage::Create(D3DXVECTOR3 pos, MESSAGETYPE type)
{
	CMessage *pMessage = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMessage = new CMessage;	//����

	if (pMessage != nullptr)
	{//NULL�`�F�b�N
		//�����̑��
		pMessage->m_type = type;		//���

		//������
		pMessage->Init(D3DXVECTOR3(pos));
	}

	return pMessage;
}
