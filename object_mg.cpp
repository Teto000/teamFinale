//=============================================================================
//
// �I�u�W�F�ƃ}�l�[�W���[�N���X(object_mg.h)
// Author : �������l
// �T�v : 3D�v���C���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "object_mg.h"
#include "rubble.h"
#include "message.h"
#include "renderer.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CObjectManager * CObjectManager::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CObjectManager *pObjectManager = nullptr;

	// �������̉��
	pObjectManager = new CObjectManager;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pObjectManager != nullptr);

	// ���l�̏�����
	pObjectManager->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �C���X�^���X��Ԃ�
	return pObjectManager;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CObjectManager::CObjectManager() : CObjectManager(0)
{
}

CObjectManager::CObjectManager(int nPriority) : CObject(nPriority),
m_pos(D3DXVECTOR3()),					// �ʒu
m_posOld(D3DXVECTOR3()),				// �ߋ��ʒu
m_nMaxRubble(0),
m_pMessage(0)
{
	
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CObjectManager::~CObjectManager()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CObjectManager::Init(D3DXVECTOR3 pos)
{
	// �p�[�c�̏�����
	m_pRubble.clear();

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CObjectManager::Uninit()
{
	// �I�u�W�F�N�g2D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CObjectManager::Update()
{
	UpdateRubble();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CObjectManager::Draw()
{

}

void CObjectManager::UpdateRubble()
{
	int nCntComplete = 0;

	for (int nCntRubble = 0; nCntRubble < m_nMaxRubble; nCntRubble++)
	{
		if (!m_pRubble.at(nCntRubble)->GetComplete())
		{
			break;
		}

		nCntComplete++;
	}

	if (nCntComplete != m_nMaxRubble)
	{
		return;
	}

	for (int nCntRubble = 0; nCntRubble < m_nMaxRubble; nCntRubble++)
	{
		m_pRubble.at(nCntRubble)->Reset();

		//���b�Z�[�W�̕\��
		m_pMessage = CMessage::Create(
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
			, CMessage::MESSAGE_TYPE_COMPLETE);
	}
}

void CObjectManager::SetRubble(CRubble * pRubble)
{
	m_nMaxRubble++;

	m_pRubble.resize(m_nMaxRubble);

	m_pRubble[m_nMaxRubble - 1] = pRubble;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CObjectManager::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CObjectManager::GetWidth()
{
	return 0.0f;
}

//===========================
// �����̎擾
//===========================
float CObjectManager::GetHeight()
{
	return 0.0f;
}
