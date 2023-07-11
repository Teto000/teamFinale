//===================================================
//
// �X�e�[�W�I������
// Author : Sato Teruto
//
//===================================================

//----------------------------------
// �C���N���[�h
//----------------------------------
#include "stage_select.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "fade.h"
#include "camera.h"
#include "meshfield.h"
#include "objectX.h"
#include "player.h"
#include "object2D.h"
#include "time.h"
#include "sky.h"

//----------------------------------
// �ÓI�����o�ϐ��錾
//----------------------------------
bool CStageSelect::m_bViewMap = false;		//�}�b�v��\��������
bool CStageSelect::m_bStart = false;		//�Q�[�����J�n������

//==================================
// �R���X�g���N�^
//==================================
CStageSelect::CStageSelect()
{
	m_pCamera = nullptr;	//�J����
	m_pMeshField = nullptr;	//���b�V���t�B�[���h(�n��)
	m_pObjectX = nullptr;	//�I�u�W�F�N�gX
	m_pPlayer = nullptr;	//�v���C���[
	m_pObject2D = nullptr;	//�I�u�W�F�N�g2D
	m_pNumber = nullptr;	//����
	m_pSky = nullptr;		//��
}

//=================================
// �f�X�g���N�^
//=================================
CStageSelect::~CStageSelect()
{
}

//==================================
// ����������
//==================================
HRESULT CStageSelect::Init()
{
	//------------------------
	// �J�����̐���
	//------------------------
	m_pCamera = CCamera::Create((DWORD)0.0f, (DWORD)0.0f,
								(DWORD)SCREEN_WIDTH, (DWORD)SCREEN_HEIGHT);

	//------------------------
	// �n�ʂ̐���
	//------------------------
	m_pMeshField = CMeshField::Create();

	//------------------------
	// ��̐���
	//------------------------
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//------------------------
	// �v���C���[�̐���
	//------------------------
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

	//------------------------
	// �I�u�W�F�N�g�̐���(��)
	//------------------------
	m_pObjectX = CObjectX::Create();
	m_pObjectX->SetType(1);

	//------------------------
	// �摜�̐���
	//------------------------
	{
		D3DXVECTOR3 pos((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);	//�ʒu
		m_pObject2D = CObject2D::Create(pos);							//����
		m_pObject2D->SetSize(0.0f, 0.0f);								//�傫��
		m_pObject2D->SetTexture(CTexture::TEXTURE_STATE1);				//�e�N�X�`��
	}

	//------------------------
	// �����̐���
	//------------------------
	{
		D3DXVECTOR3 pos(560.0f, 460.0f, 0.0f);
		m_pNumber = CTime::Create(pos);
	}

	return S_OK;
}

//==================================
// �I������
//==================================
void CStageSelect::Uninit()
{
	//-----------------------
	// �J�����̏I��
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==================================
// �X�V����
//==================================
void CStageSelect::Update()
{
	//-----------------------
	// �J�����̍X�V����
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//-----------------------
	// �摜�\���̐؂�ւ�
	// ���l::�X�e�[�W�ԍ��Ńe�N�X�`����؂�ւ���
	//-----------------------
	if (m_bViewMap == true)
	{//�}�b�v��\�������ԂȂ�
		//�摜���g�傷��(�\��)
		m_pObject2D->SetSize(300.0f, 300.0f);

		//�X�R�A���擾
		int nScore = CApplication::GetMaxScore(0);	//�X�e�[�W�ԍ��ɑΉ������X�R�A�̍ő�l���擾

		//������`�悷��
		m_pNumber->SetDraw(true);
		m_pNumber->SetTime(nScore);
	}
	else
	{
		//�摜���k������(��\��)
		m_pObject2D->SetSize(0.0f, 0.0f);

		//������`�悵�Ȃ�
		m_pNumber->SetDraw(false);
	}

	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (m_bStart &&
		CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{//�Q�[�����J�n������ & �L�[�������ꂽ��
		//�Q�[����ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);
	}
}