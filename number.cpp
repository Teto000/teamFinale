//===================================================
//
// ���l��\�����鏈��
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "number.h"
#include "application.h"
#include "renderer.h"

//=======================
// �R���X�g���N�^
//=======================
CNumber::CNumber() : CObject2D(1)
{
	m_nValue = 0;		//���l
	m_nDigit = 0;		//����
	m_bDraw = false;	//�`��t���O
}

//=======================
// �f�X�g���N�^
//=======================
CNumber::~CNumber()
{

}

//=======================
// ������
//=======================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_fWidth = 60.0f;
	m_fHeight = 80.0f;

	//�I�u�W�F�N�g�̏�����
	CObject2D::Init(pos);

	//�傫���̐ݒ�
	CObject2D::SetSize(m_fWidth, m_fHeight);

	//�e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);

	return S_OK;
}

//=======================
// �I��
//=======================
void CNumber::Uninit()
{
	//�I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}

//=======================
// �X�V
//=======================
void CNumber::Update()
{
	//�I�u�W�F�N�g�̍X�V
	CObject2D::Update();
}

//=======================
// �`��
//=======================
void CNumber::Draw()
{
	if (!m_bDraw)
	{//�`�悵�Ȃ���ԂȂ�
		return;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�I�u�W�F�N�g�̕`��
	CObject2D::Draw();

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=======================
// ����
// �����F�ʒu�A�l�A����
//=======================
CNumber *CNumber::Create(D3DXVECTOR3 pos, int nValue)
{
	CNumber *pNumber = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pNumber = new CNumber;	//����

	if (pNumber != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pNumber->m_nValue = nValue;

		//������
		pNumber->Init(D3DXVECTOR3(pos));
		pNumber->SetObjType(OBJTYPE_NUMBER);
	}

	return pNumber;
}

//=======================
// ���l�̐ݒ�
// �����F����
//=======================
void CNumber::Set(int nDigit)
{
	CObject2D::SetAnimation((float)nDigit, 10);
}

//=======================
// �g�k
//=======================
void CNumber::SetScaling(float fWidth, float fHeight)
{
	//���ƍ����̐ݒ�
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	CObject2D::SetSize(m_fWidth, m_fHeight);
}