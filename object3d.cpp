//===================================================
//
// �I�u�W�F�N�g3D�̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "object3d.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "input_keyboard.h"
#include "texture.h"

//------------------------
// �}�N����`
//------------------------
#define	ROT		(0.05f)		//��]�p�x�̑�����
#define	SCAL	(0.01f)		//�g�k�̒l�̑�����

//===========================
// �R���X�g���N�^
//===========================
CObject3D::CObject3D() : CObject3D(0)
{
}

CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
	m_Depth = 0.0f;		//���s��
	m_fRot = 0.0f;		//��]�p�x
	m_fScal = 0.0f;		//�傫��
}

//===========================
// �f�X�g���N�^
//===========================
CObject3D::~CObject3D()
{
	assert(m_pVtxBuff == nullptr);
}

//===========================
// ������
//===========================
HRESULT CObject3D::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu
	m_pos = pos;

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, m_Depth / 2);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, m_Depth / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, -m_Depth / 2);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, -m_Depth / 2);

	//-----------------------------------------------------------------
	// �e���_�̖@���̐ݒ�(���x�N�g���̑傫���͕K��1�ɂ���K�v������)
	//-----------------------------------------------------------------
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//------------------------
	// �e�N�X�`�����W�̐ݒ�
	//------------------------
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
// �I��
//===========================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//===========================
// �X�V
//===========================
void CObject3D::Update()
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, m_Depth / 2);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, m_Depth / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, -m_Depth / 2);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, -m_Depth / 2);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �`��
//===========================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//------------------------------------
	// �}�g���b�N�X
	//------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//------------------------------------
	// ���_
	//------------------------------------
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//------------------------------------
	// �e�N�X�`��
	//------------------------------------
	//�e�N�X�`���̎擾
	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_NumTex));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
						   0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
						   2);					//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);
}

//===========================
// �ʒu�̐ݒ�
//===========================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===========================
// �����̐ݒ�
//===========================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//===========================
// �F�̐ݒ�
//===========================
void CObject3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �傫���̐ݒ�
//===========================
void CObject3D::SetSize(float fWidth, float fHeight, float fDepth)
{
	m_fWidth = fWidth;		//���̐ݒ�
	m_fHeight = fHeight;	//�����̐ݒ�
	m_Depth = fDepth;		//���s���̐ݒ�
}

//===========================
// ���_���̐ݒ�
//===========================
void CObject3D::SetVtx(VERTEX_3D* vtx)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = vtx;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �e�N�X�`�����W�̐ݒ�
//===========================
void CObject3D::SetTexCIE(float left, float fRight)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(left, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fRight, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �e�N�X�`���̐ݒ�
//===========================
void CObject3D::SetTexture(CTexture::NUM_TEXTURE numTex)
{
	m_NumTex = numTex;
}

//=========================================
// ���u�����f�B���O�����Z�����ɐݒ�
//=========================================
void CObject3D::SetSubALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//=========================================
// ���u�����f�B���O�����ɖ߂�
//=========================================
void CObject3D::ResetSubALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CObject3D::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CObject3D::GetWidth()
{
	return m_fWidth;
}

//===========================
// �����̎擾
//===========================
float CObject3D::GetHeight()
{
	return m_fHeight;
}