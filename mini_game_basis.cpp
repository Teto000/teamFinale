//===================================================
//
// �~�j�Q�[����Տ���
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "mini_game_basis.h"
#include "application.h"
#include "renderer.h"

#include "mini_game_buttonpush.h"
#include "mg_buttonmash.h"
#include "mg_stickrotate.h"
#include "player.h"

//=======================
// �R���X�g���N�^
//=======================
CMiniGameBasis::CMiniGameBasis() : CObject2D(1)
{
	m_bDraw = false;	//�`��t���O
}

//=======================
// �f�X�g���N�^
//=======================
CMiniGameBasis::~CMiniGameBasis()
{

}

//=======================
// ������
//=======================
HRESULT CMiniGameBasis::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_fWidth = 60.0f;
	m_fHeight = 80.0f;

	//�I�u�W�F�N�g�̏�����
	CObject2D::Init(pos);

	//�傫���̐ݒ�
	CObject2D::SetSize(m_fWidth, m_fHeight);

	//�e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_NONE);

	return S_OK;
}

//=======================
// �I��
//=======================
void CMiniGameBasis::Uninit()
{
	//�I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}

//=======================
// �X�V
//=======================
void CMiniGameBasis::Update()
{
	//�I�u�W�F�N�g�̍X�V
	CObject2D::Update();
}

//=======================
// �`��
//=======================
void CMiniGameBasis::Draw()
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
CMiniGameBasis *CMiniGameBasis::Create(D3DXVECTOR3 pos, MiniGameType nType)
{
	CMiniGameBasis *pGameBasis = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	//�^�C�v���Ƃɐ���������̂����߂�
	switch (nType)
	{
	case TYPE_BUTTUNPUSH:
	{//�{�^���v�b�V���Q�[��
		pGameBasis = new CButtonPushGame;	//����
	}

	break;

	case TYPE_BUTTONMASH:
	{//�{�^���A�ŃQ�[��
		pGameBasis = new CButtonMash;	//����
	}
	break;

	case TYPE_STICKROTATE:
	{//�X�e�B�b�N��]�Q�[��
		pGameBasis = new CStickRotate;	//����
	}
	break;

	default:
	{
	}

	break;

	}

	if (pGameBasis != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
		pGameBasis->m_nType = nType;

		//������
		pGameBasis->Init(D3DXVECTOR3(pos));
		pGameBasis->SetObjType(OBJTYPE_MINIGAME);
	}

	return pGameBasis;
}

//=======================
// �g�k
//=======================
void CMiniGameBasis::SetScaling(float fWidth, float fHeight)
{
	//���ƍ����̐ݒ�
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	CObject2D::SetSize(m_fWidth, m_fHeight);
}