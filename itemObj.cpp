//=============================================================================
//
// ���f���I�u�W�F�N�g�N���X(model_obj.cpp)
// Author : �������l
// �T�v : ���f���I�u�W�F�N�g�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "itemObj.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �C���X�^���X�𐶐�����
//=============================================================================
CItemObj * CItemObj::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CItemObj *pItemObj = nullptr;

	// �������̉��
	pItemObj = new CItemObj;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pItemObj != nullptr);

	// ���l�̏�����
	pItemObj->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �C���X�^���X��Ԃ�
	return pItemObj;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CItemObj::CItemObj() : m_pParent(nullptr),			// �e�I�u�W�F�N�g�̏��
m_posOffset(D3DXVECTOR3(0.0f,0.0f,0.0f)),			// �ʒu�̍���
m_rotOffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			// �����̍���
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CItemObj::~CItemObj()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CItemObj::Init(D3DXVECTOR3 pos)
{
	// ���f���I�u�W�F�N�g�̏�����
	CObjectX::Init(pos);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CItemObj::Uninit()
{
	// ���f���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CItemObj::Update()
{
	// ���f���I�u�W�F�N�g�̍X�V
	CObjectX::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CItemObj::Draw()
{
	// ���̎擾
	D3DXMATRIX mtxWorld = GetMtx();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();
	CModel3D *pModel = GetModel();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);											// �s�񏉊����֐�

	if (m_pParent != nullptr)
	{// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotOffset.y, m_rotOffset.x, m_rotOffset.z);			// �s���]�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);												// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);					// �s��ړ��֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);											// �s��|���Z�֐�

		// �e�̃��[���h�}�b�g���b�N�X
		D3DXMATRIX mtxParent = m_pParent->GetMtxWorld();

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

		// �ʒu�̐ݒ�
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &mtxWorld);
		SetPos(pos);
	}
	else
	{// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);					// �s��ړ��֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);					// �s��|���Z�֐�
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���f���̕`��
	pModel->Draw(mtxWorld);
	SetMtx(mtxWorld);
}
