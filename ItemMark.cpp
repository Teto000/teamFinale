//===================================================
//
// �A�C�e���̖ڈ��\�����鏈��
// Author : Sato Teruto
//
//===================================================

//---------------------------
// �C���N���[�h
//---------------------------
#include "ItemMark.h"

//======================================
// �R���X�g���N�^
//======================================
CItemMark::CItemMark()
{
}

//======================================
// �f�X�g���N�^
//======================================
CItemMark::~CItemMark()
{
}

//======================================
// ������
//======================================
HRESULT CItemMark::Init(D3DXVECTOR3 pos)
{
	CBillBoard::Init(pos);

	return S_OK;
}

//======================================
// �I��
//======================================
void CItemMark::Uninit()
{
	CBillBoard::Uninit();
}

//======================================
// �X�V
//======================================
void CItemMark::Update()
{
	CBillBoard::Update();

	//�e�N�X�`���̐؂�ւ�
	ChangeTexture();
}

//======================================
// �`��
//======================================
void CItemMark::Draw()
{
	CBillBoard::Draw();
}

//======================================
// ����
//======================================
CItemMark* CItemMark::Create(D3DXVECTOR3 pos)
{
	CItemMark* pItemMark = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pItemMark = new CItemMark;	//����

	if (pItemMark != nullptr)
	{//NULL�`�F�b�N
		//������
		pItemMark->Init(D3DXVECTOR3(pos));
	}

	return pItemMark;
}

//======================================
// �l�̐ݒ�
//======================================
void CItemMark::SetValue(int nValue)
{
	m_nValue = nValue;
}

//======================================
// �e�N�X�`���̐؂�ւ�
//======================================
void CItemMark::ChangeTexture()
{
	switch (m_nValue)
	{
	case 4:
		SetTexture(CTexture::TEXTURE_FUKIDASI4);
		break;

	case 3:
		SetTexture(CTexture::TEXTURE_FUKIDASI3);
		break;

	case 2:
		SetTexture(CTexture::TEXTURE_FUKIDASI2);
		break;

	case 1:
		SetTexture(CTexture::TEXTURE_FUKIDASI);
		break;

	default:
		break;
	}
}