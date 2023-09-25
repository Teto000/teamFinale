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
#include "light.h"
#include "debug_proc.h"
#include "camera.h"
#include "model3D.h"
#include "collision.h"
#include "mode.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CRenderer*		CApplication::m_pRenderer = nullptr;	//�����_���[
CInput*			CApplication::m_pInput = nullptr;		//�C���v�b�g
CTexture*		CApplication::m_pTexture = nullptr;		//�e�N�X�`��
CSound*			CApplication::m_pSound = nullptr;		//�T�E���h
CLight*			CApplication::m_pLight = nullptr;		//���C�g
CDebugProc*		CApplication::m_pDebugproc = nullptr;	//�f�o�b�O�p����

/* �� �ϐ��@�� */
int CApplication::m_nStageScore[nMaxStage] = {};		//�X�e�[�W���Ƃ̃X�R�A��ۑ�
int CApplication::m_nMaxScore[nMaxStage] = {};			//�X�R�A�̍ő�l��ۑ�

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
	if (FAILED(m_pRenderer->Init(hWnd, FALSE)))
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
	CMode::Init();

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
	// ���[�h�̏I��
	//----------------------------
	CMode::Uninit();

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

	//���[�h�̍X�V
	CMode::Update();
}

//===========================
// �`��
//===========================
void CApplication::Draw()
{
	//�����_�����O�̕`��
	m_pRenderer->Draw();
}