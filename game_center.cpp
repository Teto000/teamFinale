//=============================================================================
//
// �Q�[���Z���^�[�N���X(game_center.h)
// Author : �������l
// �T�v : �Q�[���Z���^�[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "game_center.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"
#include "collision_rectangle3D.h"
#include "player.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �C���X�^���X�𐶐�����
//=============================================================================
CGameCenter * CGameCenter::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CGameCenter *pGameCenter = nullptr;

	// �������̉��
	pGameCenter = new CGameCenter;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pGameCenter != nullptr);

	// ���l�̏�����
	pGameCenter->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �C���X�^���X��Ԃ�
	return pGameCenter;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGameCenter::CGameCenter() : m_EMiniGameType(CMiniGameBasis::TYPE_NULL),
m_pPlayer(nullptr),
m_pMiniGameBasis(nullptr),
m_bGame(false)
{
	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_MINIGAME);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGameCenter::~CGameCenter()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CGameCenter::Init(D3DXVECTOR3 pos)
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
void CGameCenter::Uninit()
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
void CGameCenter::Update()
{
	// ���f���I�u�W�F�N�g�̍X�V
	CObjectX::Update();
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CGameCenter::Draw()
{
	// ���f���I�u�W�F�N�g�̕`��
	CObjectX::Draw();
}

void CGameCenter::SetGame(bool bGame)
{
	m_bGame = bGame;

	if (m_bGame && m_EMiniGameType != CMiniGameBasis::TYPE_NULL)
	{//�Q�[���� & �~�j�Q�[����null����Ȃ��Ȃ�
		m_pMiniGameBasis = CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), m_EMiniGameType);
		m_pMiniGameBasis->SetParent(this);
		m_pMiniGameBasis->SetGame(true);
		m_pMiniGameBasis->SetItemType(m_ItemType);
		m_pMiniGameBasis->SetPlayer(m_pPlayer);

		m_pPlayer->SetUpdate(true);
	}
}
