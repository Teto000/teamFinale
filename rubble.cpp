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

#include "rubble.h"
#include "itemObj.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"
#include "collision_rectangle3D.h"
#include "line.h"
#include "ItemMark.h"
#include "game.h"
#include "score.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �C���X�^���X�𐶐�����
//=============================================================================
CRubble * CRubble::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CRubble *pRubble = nullptr;

	// �������̉��
	pRubble = new CRubble;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pRubble != nullptr);

	// ���l�̏�����
	pRubble->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �C���X�^���X��Ԃ�
	return pRubble;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CRubble::CRubble() : m_nRequired(0),		// �C����
m_nCntRequired(0),
m_bComplete(false),
m_pItemMark(nullptr)
{
	// �C���̏�����
	m_repair.clear();

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_BREAK);
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CRubble::~CRubble()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CRubble::Init(D3DXVECTOR3 pos)
{
	// ���f���I�u�W�F�N�g�̏�����
	CObjectX::Init(pos);

	// ���C�����
	m_pLine = new CLine*[4];
	m_lineCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	for (int nCntLine = 0; nCntLine < 4; nCntLine++)
	{
		m_pLine[nCntLine] = CLine::Create();
	}

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CRubble::Uninit()
{
	if (m_pLine != nullptr)
	{
		for (int nCntLine = 0; nCntLine < 4; nCntLine++)
		{
			m_pLine[nCntLine]->Uninit();
			m_pLine[nCntLine] = nullptr;
		}

		delete[] m_pLine;
		m_pLine = nullptr;
	}

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
void CRubble::Update()
{
	// ���f���I�u�W�F�N�g�̍X�V
	CObjectX::Update();

	if (!m_bComplete)
	{
		if (m_nCntRequired == m_nRequired)
		{
			m_bComplete = true;
			Complete();
		}
		else
		{
			// �C�������ɕK�v�Ȏc��A�C�e���ʂ��v�Z
			int nRest = m_repair.at(0).nRequired - m_repair.at(0).nCutRequired;

			// �e�N�X�`���̍X�V
			if (m_pItemMark)
			{
				m_pItemMark->SetValue(nRest);
			}
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CRubble::Draw()
{
	// ���f���I�u�W�F�N�g�̕`��
	CObjectX::Draw();
}

void CRubble::SetBuildType(EBuildType buildType)
{
	m_buildType = buildType;

	switch (m_buildType)
	{
	case CRubble::TYPE_NONE:
		break;

	case CRubble::TYPE_PAVILION:
		SetType(19);
		break;

	case CRubble::TYPE_FOUNTAIN:
		SetType(21);
		break;

	case CRubble::TYPE_SLIDE:
		SetType(27);
		break;

	case CRubble::TYPE_SWING:
		SetType(29);
		break;

	case CRubble::TYPE_SEESAW:
		SetType(31);
		break;

	default:
		assert(false);
		break;
	}
}

void CRubble::Repair(CItemObj *pItem)
{
	CItemObj *pPlayerItem = pItem;

	for (int nCnt = 0; nCnt < m_nRequired; nCnt++)
	{// �A�C�e����ێ����Ă��炷�A�A�C�e���I�u�W�F�N�g�ɐG��Ă����ꍇ�擾 
		if (m_repair.at(nCnt).bCompletion)
		{
			return;
		}

		if (pPlayerItem != nullptr
			&& pPlayerItem->GetItemType() == m_repair.at(nCnt).type)
		{
			CItemObj *pChild = pPlayerItem->SearchChild();

			CItemObj *pParent = (CItemObj*)pChild->GetParentItem();

			if (pParent != nullptr)
			{
				pParent->SetChildItem();
			}

			if (pChild != nullptr)
			{
				pChild->Uninit();
				pChild = nullptr;
			}

			m_repair.at(nCnt).nCutRequired++;

			//�X�R�A�̉��Z(�A�C�e��������)
			CGame::GetScore()->AddScore(5);

			if (m_repair.at(nCnt).nCutRequired == m_repair.at(nCnt).nRequired)
			{
				m_repair.at(nCnt).bCompletion = true;
				m_nCntRequired++;
			}

			break;
		}
	}
}

void CRubble::Complete()
{
	switch (m_buildType)
	{
	case CRubble::TYPE_NONE:
		break;

	case CRubble::TYPE_PAVILION:
		SetType(18);
		break;

	case CRubble::TYPE_FOUNTAIN:
		SetType(20);
		break;

	case CRubble::TYPE_SLIDE:
		SetType(26);
		break;

	case CRubble::TYPE_SWING:
		SetType(28);
		break;

	case CRubble::TYPE_SEESAW:
		SetType(30);
		break;

	default:
		assert(false);
		break;
	}

	//�X�e�[�W�ɃX�R�A�����Z(0�Ԗڂ̃X�e�[�W��100���Z)
	//CApplication::AddStageScore(0, 100);

	//�X�R�A�̉��Z(����������)
	CGame::GetScore()->AddScore(30);

	//�����o���̏���
	if (m_pItemMark)
	{
		m_pItemMark->Uninit();
	}
}

//=============================================================================
// ���C���̐ݒu
// Author : �������l
// �T�v : ���C������`��ɐݒu
//=============================================================================
void CRubble::SetLine()
{
	// �ϐ��錾
	D3DXVECTOR3 pos = GetPosition();
	const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 size = GetCollision()->GetSize();
	const D3DXCOLOR col = m_lineCol;

	// ���C���̐ݒ�
	m_pLine[0]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
	m_pLine[1]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(-size.x, -size.y, size.z), col);
	m_pLine[2]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, -size.z), col);
	m_pLine[3]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
}

//=============================================================================
// �����o���̐ݒu
// Author : Sato Teruto
// �T�v : �A�C�e���𒼂��̂ɕK�v�Ȑ���\��
//=============================================================================
void CRubble::SetMark(D3DXVECTOR3 pos, CTexture::NUM_TEXTURE tex)
{
	m_pItemMark = CItemMark::Create(pos);
	m_pItemMark->SetSize(100.0f, 100.0f);
	m_pItemMark->SetTexture(tex);
}