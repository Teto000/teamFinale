//===================================================
//
// �I�u�W�F�N�gX�̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "objectX.h"
#include "object.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "model3D.h"
#include "utility.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : 3D���f���𐶐�����
//=============================================================================
CObjectX * CObjectX::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CObjectX *pObjectX = nullptr;

	// �������̉��
	pObjectX = new CObjectX;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pObjectX != nullptr);

	// ���l�̏�����
	pObjectX->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �C���X�^���X��Ԃ�
	return pObjectX;
}

//========================
// �R���X�g���N�^
//========================
CObjectX::CObjectX() : CObjectX(0)
{
}

CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//���f��
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̐ݒ�
}

//========================
// �f�X�g���N�^
//========================
CObjectX::~CObjectX()
{

}

//========================
// ������
//========================
HRESULT CObjectX::Init(D3DXVECTOR3 pos)
{
	// �ϐ��̏�����
	m_mtxWorld = {};										// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_nType = -1;											// ���f���̃^�C�v

	// ���f���N���X�̃������m��
	m_pModel = CModel3D::Create();
	assert(m_pModel != nullptr);
	m_pModel->SetModelID(m_nType);

	return S_OK;
}

//========================
// �I��
//========================
void CObjectX::Uninit()
{
	if (m_pModel != nullptr)
	{// �I������
		m_pModel->Uninit();

		// �������̉��
		delete m_pModel;
		m_pModel = nullptr;
	}
}

//========================
// �X�V
//========================
void CObjectX::Update()
{
	// ���f���̍X�V
	m_pModel->Update();
}

//========================
// �`��
//========================
void CObjectX::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	m_pModel->Draw(m_mtxWorld);
}

//===========================
// �ʒu�̐ݒ�
//===========================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===========================
// �����̐ݒ�
//===========================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CObjectX::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CObjectX::GetWidth()
{
	return 0.0f;
}

//===========================
// �����̎擾
//===========================
float CObjectX::GetHeight()
{
	return 0.0f;
}

//=============================================================================
// ���f���̃^�C�v�̐ݒ�
// Author : �������l
// �T�v : ���f���̃^�C�v�̐ݒ�
//=============================================================================
void CObjectX::SetType(const int nType)
{
	// ���f���̃^�C�v
	m_nType = nType;

	// ���f���N���X��ID�ݒ�
	m_pModel->SetModelID(m_nType);
}
