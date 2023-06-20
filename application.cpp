//===================================================
//
// �A�v���P�[�V�����̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "object3d.h"
#include "texture.h"
#include "sound.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "stage_select.h"
#include "fade.h"
#include "light.h"
#include "debug_proc.h"
#include "camera.h"
#include "model3D.h"
#include "collision.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
/* �� ��ʑJ�� �� */
CTitle*			CApplication::m_pTitle = nullptr;		//�^�C�g��
CGame*			CApplication::m_pGame = nullptr;		//�Q�[��
CResult*		CApplication::m_pResult = nullptr;		//���U���g
CStageSelect*	CApplication::m_pStageSelect = nullptr;	//�X�e�[�W�I��
CFade*			CApplication::m_pFade = nullptr;		//�t�F�[�h
CApplication::MODE	CApplication::m_mode = MODE_MAX;	//�Q�[�����[�h

/* �� ���̑� �� */
CRenderer*		CApplication::m_pRenderer = nullptr;	//�����_���[
CInput*			CApplication::m_pInput = nullptr;		//�C���v�b�g
CTexture*		CApplication::m_pTexture = nullptr;		//�e�N�X�`��
CSound*			CApplication::m_pSound = nullptr;		//�T�E���h
CLight*			CApplication::m_pLight = nullptr;		//���C�g
CDebugProc*		CApplication::m_pDebugproc = nullptr;	//�f�o�b�O�p����

//===========================
// �R���X�g���N�^
//===========================
CApplication::CApplication()
{

}

//===========================
// �f�X�g���N�^
//===========================
CApplication::~CApplication()
{

}

//===========================
// ������
//===========================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�����_��
	srand((unsigned int)time(NULL));

	//----------------------------
	// �����_�����O�̐����Ə�����
	//----------------------------
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//----------------------------
	// �C���v�b�g�̐����Ə�����
	//----------------------------
	m_pInput = new CInput;
	m_pInput->Init(hInstance, hWnd);

	//----------------------------
	// �e�N�X�`���̐���
	//----------------------------
	m_pTexture = new CTexture;
	assert(m_pTexture != nullptr);
	m_pTexture->Init();

	// ���f�����̏�����
	CModel3D::InitModel();

	//----------------------------
	// �T�E���h�̐����Ə�����
	//----------------------------
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//----------------------------
	// ���C�g�̐����Ə�����
	//----------------------------
	m_pLight = new CLight;
	m_pLight->Init(GetRenderer()->GetDevice());

	//----------------------------
	// ���[�h�̐ݒ�
	//----------------------------
	m_pFade = new CFade;
	SetMode(MODE_TITLE);
	m_pFade->Init(MODE_TITLE);

	//----------------------------
	// �f�o�b�O�p�����̐���
	//----------------------------
	m_pDebugproc = new CDebugProc;
	m_pDebugproc->Init();

	return S_OK;
}

//===========================
// �I��
//===========================
void CApplication::Uninit()
{
	//----------------------------
	// �I�u�W�F�N�g�̑S���
	//----------------------------
	CObject::ReleaseAll(true);
	CCollision::ReleaseAll();

	//----------------------------
	//�e�N�X�`���̏I��
	//----------------------------
	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->Uninit();

		// �������̉��
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// ���f�����̏I��
	CModel3D::UninitModel();

	//----------------------------
	// �����_�����O�̏I��
	//----------------------------
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//----------------------------
	// �C���v�b�g�̏I��
	//----------------------------
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//----------------------------
	// �T�E���h�̏I��
	//----------------------------
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//----------------------------
	// ���C�g�̏I��
	//----------------------------
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//----------------------------
	// �^�C�g���̏I��
	//----------------------------
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	//----------------------------
	// �Q�[���̏I��
	//----------------------------
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	//----------------------------
	// ���U���g�̏I��
	//----------------------------
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}

	//----------------------------
	// �X�e�[�W�I���̏I��
	//----------------------------
	if (m_pStageSelect != nullptr)
	{
		m_pStageSelect->Uninit();
		delete m_pStageSelect;
		m_pStageSelect = nullptr;
	}

	//----------------------------
	// �t�F�[�h�̏I��
	//----------------------------
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//----------------------------
	// �f�o�b�O�p�����̏I��
	//----------------------------
	if (m_pDebugproc != nullptr)
	{
		m_pDebugproc->Uninit();
		delete m_pDebugproc;
		m_pDebugproc = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CApplication::Update()
{
	//�C���v�b�g�̍X�V
	m_pInput->Update();	//�ŏ��ɂ��

	//�����_�����O�̍X�V
	m_pRenderer->Update();

	//---------------------------
	// ���[�h���Ƃ̍X�V
	//---------------------------
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case MODE_RESULT:
		m_pResult->Update();
		break;

	case MODE_STAGESELECT:
		m_pStageSelect->Update();
		break;

	default:
		break;
	}

	//�t�F�[�h�̍X�V
	m_pFade->Update();
}

//===========================
// �`��
//===========================
void CApplication::Draw()
{
	//�����_�����O�̕`��
	m_pRenderer->Draw();
}

//===========================
// ���[�h�̐ݒ�
//===========================
void CApplication::SetMode(MODE mode)
{
	//----------------------------
	// ���݂̃��[�h�̏I������
	//----------------------------
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
		break;

	case MODE_RESULT:
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
		break;

	case MODE_STAGESELECT:
		m_pStageSelect->Uninit();
		delete m_pStageSelect;
		m_pStageSelect = nullptr;
		break;

	default:
		break;
	}

	//�I�u�W�F�N�g�̑S���
	CObject::ReleaseAll(true);

	// �����蔻��̏I��
	CCollision::ReleaseAll();

	//���[�h�̐؂�ւ�
	m_mode = mode;

	//----------------------------
	// �V�������[�h�̐���
	//----------------------------
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle = nullptr;
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;

	case MODE_GAME:
		m_pGame = nullptr;
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:
		m_pResult = nullptr;
		m_pResult = new CResult;
		m_pResult->Init();
		break;

	case MODE_STAGESELECT:
		m_pStageSelect = nullptr;
		m_pStageSelect = new CStageSelect;
		m_pStageSelect->Init();
		break;

	default:
		break;
	}
}