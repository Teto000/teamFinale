//===================================================
//
// ���b�V���t�B�[���h�̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "meshfield.h"
#include "renderer.h"
#include "texture.h"

//=======================
// �R���X�g���N�^
//=======================
CMeshField::CMeshField() : CMesh(0)
{

}

//=======================
// �f�X�g���N�^
//=======================
CMeshField::~CMeshField()
{

}

//=======================
// ������
//=======================
HRESULT CMeshField::Init(D3DXVECTOR3 pos)
{
	CMesh::Init(pos);

	//�������A���̐ݒ�
	//CMesh::SetMeshSize(8, 400);

	CMesh::SetTexture(CTexture::TEXTURE_GROUND);

	return S_OK;
}

//=======================
// �I��
//=======================
void CMeshField::Uninit()
{
	CMesh::Uninit();
}

//=======================
// �X�V
//=======================
void CMeshField::Update()
{
	CMesh::Update();
}

//=======================
// �`��
//=======================
void CMeshField::Draw()
{
	CMesh::Draw();
}

//=======================
// ����
//=======================
CMeshField *CMeshField::Create()
{
	CMeshField *pMeshField = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMeshField = new CMeshField;	//����

	if (pMeshField != nullptr)
	{//NULL�`�F�b�N
		//������
		{
			D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			pMeshField->Init(D3DXVECTOR3(pos));
		}
		pMeshField->SetObjType(OBJTYPE_MESH);
	}

	return pMeshField;
}