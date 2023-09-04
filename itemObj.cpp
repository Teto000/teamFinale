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
#include "collision_rectangle3D.h"

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
CItemObj::CItemObj() : m_pParentItem(nullptr),		// �e�I�u�W�F�̏��
m_pChildItem(nullptr),								// �q���I�u�W�F�̏��
m_pParent(nullptr),									// �e�I�u�W�F�N�g�̏��
m_Type(TYPE_NONE),									// �A�C�e���̎��
m_posOffset(D3DXVECTOR3(0.0f,0.0f,0.0f)),			// �ʒu�̍���
m_rotOffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			// �����̍���
{
	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_ITEM);
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

	if (GetParent() == nullptr)
	{// �l�ݏd��
		Stack();
	}
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

void CItemObj::Stack(CItemObj * pTarget)
{
	// �e�̐ݒ�
 	CItemObj *pItem = this;
	int nCntChildItem = 0;

	// �q�A�C�e���̌���
	int nCntItem = 0;
	pItem = pItem->SearchChild(nCntItem);

	if (pItem->GetChildItem() == nullptr)
	{// �e�q�֌W�̐ݒ�
		if (pItem->GetChildItem() != nullptr)
		{
			assert(false);
		}

		pTarget->SetParentItem(pItem);
		pTarget->SetParent(pItem->GetModel());
		pItem->SetChildItem(pTarget);

		// �A�C�e���̓����蔻��̐ݒ�
		pTarget->GetCollision()->SetUseFlag(false);
		D3DXVECTOR3 collisionSize = GetCollision()->GetSize();
		collisionSize.y += pTarget->GetCollision()->GetSize().y;
		GetCollision()->SetSize(collisionSize);
		D3DXVECTOR3 modelSize = pTarget->GetModel()->GetMyMaterial().size;
		pTarget->SetPosOffset(D3DXVECTOR3(0.0f, modelSize.y, 0.0f));
	}
}

//=============================================================================
// �q���̌���
// Author : �������l
// �T�v : �A�C�e������q���̌������s��
//=============================================================================
CItemObj* CItemObj::SearchChild()
{
	// �e�̐ݒ�
	CItemObj *pItem = this;
	CItemObj *pItemNext = nullptr;

	while (1)
	{
		pItemNext = (CItemObj*)pItem->GetChildItem();

		if (pItemNext != nullptr)
		{
			pItem = pItemNext;
		}
		else
		{
			break;
		}
	}

	return pItem;
}

CItemObj * CItemObj::SearchChild(int &count)
{
	int nCntItem = 0;

	// �e�̐ݒ�
	CItemObj *pItem = this;
	CItemObj *pItemNext = nullptr;

	while (1)
	{
		pItemNext = (CItemObj*)pItem->GetChildItem();

		if (pItemNext != nullptr)
		{
			pItem = pItemNext;
			nCntItem++;
		}
		else
		{
			break;
		}
	}

	count = nCntItem;

	return pItem;
}

//=============================================================================
// �e���f���̐ݒ�
// Author : �������l
// �T�v : �e���f���̐ݒ�
//=============================================================================
void CItemObj::SetParent(CModel3D * pParent)
{
	m_pParent = pParent;

	// �����蔻��
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->SetUseFlag(false);
}

//=============================================================================
// �e���f���̐ݒ�
// Author : �������l
// �T�v : �e���f���̐ݒ�
//=============================================================================
void CItemObj::SetParent()
{
	if (m_pParentItem != nullptr)
	{// �e���A�C�e���̏ꍇ
		SetParentItem();
	}

	// �e�̐ݒ�̉���
	m_pParent = nullptr;

	// �����蔻��
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->SetUseFlag(true);
}

//=============================================================================
// �A�C�e���̎�ʂ̐ݒ�
// Author : �������l
// �T�v : �A�C�e���̎�ʂ�ݒ肷��
//=============================================================================
void CItemObj::SetItemType(EItemType type)
{
	m_Type = type;

	// �����蔻��̐ݒ�
	CCollision_Rectangle3D *pCollision = GetCollision();

	switch (m_Type)
	{
	case CItemObj::TYPE_NONE:
		break;

	case CItemObj::TYPE_WOOD:
		SetType(23);
		break;

	case CItemObj::TYPE_STONE:
		SetType(24);
		break;

	case CItemObj::TYPE_METAL:
		SetType(25);
		break;

	default:
		break;
	}

	// �����蔻��̐ݒ�
	pCollision->SetSize(GetModel()->GetMyMaterial().size);

	D3DXVECTOR3 size = pCollision->GetSize();

	pCollision->SetPos(D3DXVECTOR3(0.0f, GetModel()->GetMyMaterial().size.y / 2.0f, 0.0f));
	pCollision->SetUseFlag(false);
}

//=============================================================================
// �ςݏd��
// Author : �������l
// �T�v : ���������A�C�e����ςݏd�˂鏈��
//=============================================================================
void CItemObj::Stack()
{
	// �A�C�e���ǂ����̓����蔻��
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->Collision(CObject::OBJTYPE_ITEM, false);

	// ���������I�u�W�F�N�g�̃��X�g���擾
	std::vector<CObject*> apCollidedObj = pCollision->GetCollidedObj();

	if (apCollidedObj.size() > 0)
	{// ���������I�u�W�F�N�g�Ƃ̏���
		for (int nCntObj = 0; nCntObj < apCollidedObj.size(); nCntObj++)
		{// ���������A�C�e���̐ݒ�
			CItemObj *pTargetItem = (CItemObj*)apCollidedObj.at(nCntObj);

			// �e�̐ݒ�
			CItemObj *pItem = this;

			// �q�A�C�e���̌���
			int nCntItem = 0;
			pItem = pItem->SearchChild(nCntItem);

			if (pItem->GetChildItem() == nullptr)
			{// �e�q�֌W�̐ݒ�
				pTargetItem->SetParentItem(pItem);
				pTargetItem->SetParent(pItem->GetModel());
				pItem->SetChildItem(pTargetItem);

				// �A�C�e���̓����蔻��̐ݒ�
				pTargetItem->GetCollision()->SetUseFlag(false);
				D3DXVECTOR3 collisionSize = GetCollision()->GetSize();
				collisionSize.y += pTargetItem->GetCollision()->GetSize().y;
				GetCollision()->SetSize(collisionSize);
				D3DXVECTOR3 modelSize = pTargetItem->GetModel()->GetMyMaterial().size;
				pTargetItem->SetPosOffset(D3DXVECTOR3(0.0f, modelSize.y, 0.0f));
			}
		}
	}
}
