//=============================================================================
//
// ���[�V�����L�����N�^�[3D�N���X(model3D.h)
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_model3D.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"
#include "objectX.h"
#include "collision_rectangle3D.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CMotionModel3D * CMotionModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionModel3D *pMotionModel3D = nullptr;

	// �������̉��
	pMotionModel3D = new CMotionModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionModel3D != nullptr);

	// ���l�̏�����
	pMotionModel3D->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �C���X�^���X��Ԃ�
	return pMotionModel3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionModel3D::CMotionModel3D() : CMotionModel3D(0)
{
}
CMotionModel3D::CMotionModel3D(int nPriority) : CObject(nPriority),
m_pMotion(nullptr),											// ���[�V�������
m_pCollision(nullptr),										// �����蔻��
m_mtxWorld(D3DXMATRIX()),									// ���[���h�}�g���b�N�X
m_pos(D3DXVECTOR3()),										// �ʒu
m_posOld(D3DXVECTOR3()),									// �ߋ��ʒu
m_rot(D3DXVECTOR3()),										// ����
m_size(D3DXVECTOR3())										// �傫��
{
	
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionModel3D::~CMotionModel3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionModel3D::Init(D3DXVECTOR3 pos)
{
	// �ϐ��̏�����
	m_pos = pos;											// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �傫��

	// �����蔻��̐���
	m_pCollision = CCollision_Rectangle3D::Create();
	m_pCollision->SetParent(this);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionModel3D::Uninit()
{
	if (m_pCollision != nullptr)
	{// �I������
		m_pCollision->Uninit();

		// �������̉��
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// �I�u�W�F�N�g2D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CMotionModel3D::Update()
{
	if (m_pMotion != nullptr)
	{// ���[�V�����ԍ��̐ݒ�
		m_pMotion->Update();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CMotionModel3D::Draw()
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

	if (m_pMotion != nullptr)
	{// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(m_mtxWorld);
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0);
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s���A�����Ŏw�肳�ꂽ���[�V�����ɐݒ肷��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName, const int nNumMotion)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(nNumMotion);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(nNumMotion);
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CMotionModel3D::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CMotionModel3D::GetWidth()
{
	return 0.0f;
}

//===========================
// �����̎擾
//===========================
float CMotionModel3D::GetHeight()
{
	return 0.0f;
}