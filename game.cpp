//===================================================
//
// �Q�[���̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include <time.h>
#include "game.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "debug_proc.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "time.h"
#include "sky.h"
#include "meshfield.h"
#include "player.h"
#include "mini_game_basis.h"
#include "objectX.h"
#include "itemObj.h"
#include "collision.h"
#include "collision_rectangle3D.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
bool		CGame::m_bFinish = false;			//�Q�[���I���t���O
CCamera*	CGame::m_pCamera = nullptr;			//�J����
CTime*		CGame::m_pTime = nullptr;			//�^�C�}�[
CSky*		CGame::m_pSky = nullptr;			//��
CMeshField*	CGame::m_pMeshField = nullptr;		//�n��
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};	//�I�u�W�F�N�g
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};	//�v���C���[

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{
	for (int i = 0; i < nMaxObjBG; i++)
	{
		m_pObj[i];
	}
}

//===========================
// �f�X�g���N�^
//===========================
CGame::~CGame()
{

}

//===========================
// ������
//===========================
HRESULT CGame::Init()
{
	//�����l�̐ݒ�
	m_bFinish = false;	//�Q�[�����I�����Ă��Ȃ����

	//------------------------
	// �J�����̐���
	//------------------------
	m_pCamera = CCamera::Create((DWORD)0.0f, (DWORD)0.0f
								, (DWORD)SCREEN_WIDTH
								, (DWORD)SCREEN_HEIGHT);

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create();

	//��̐���
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//�^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));
	m_pTime->SetCntTime(true);

	// �v���C���[�̐ݒ�
	for (int i = 0; i < nMaxPlayer; i++)
	{
		m_pPlayer[i] = CPlayer::Create();
		m_pPlayer[i]->SetMotion("data/MOTION/motion.txt");
		m_pPlayer[i]->SetNumber(i);		//�v���C���[�ԍ��̐ݒ�

		CCollision_Rectangle3D *pCollision = m_pPlayer[i]->GetCollision();
		pCollision->SetSize(D3DXVECTOR3(20.0f, 50.0f, 20.0f));
		pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	}

	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(1);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(���v)
	//-----------------------------------
	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));

	m_pObjectX[2] = CItemObj::Create();
	m_pObjectX[2]->SetType(17);
	m_pObjectX[2]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[2]->SetPos(D3DXVECTOR3(1000.0f, 0.0f, 200.0f));

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(����)
	//-----------------------------------
	m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(18);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_PAVILION);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));

	m_pObjectX[4] = CItemObj::Create();
	m_pObjectX[4]->SetType(19);
	m_pObjectX[4]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	m_pObjectX[4]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(�r��)
	//-----------------------------------
	{
		for (int i = 0; i < 4; i++)
		{
			//�r��*4
			m_pObj[i] = CObjectX::Create();
			m_pObj[i]->SetType(10);
			m_pObj[i]->SetPos(D3DXVECTOR3(-600.0f + (i * 400.0f), 0.0f, 800.0f));
		}
	}

	//BGM�̍Đ�
	//CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// �I��
//===========================
void CGame::Uninit()
{
	//BGM�̒�~
	//CSound::StopSound();

	//---------------------
	// �J�����̏I��
	//---------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//===========================
// �X�V
//===========================
void CGame::Update()
{
	//----------------------------
	// �J�����̍X�V
	//----------------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (!m_bFinish
		&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//�Q�[���I���t���O�𗧂Ă�
		m_bFinish = true;

		//���U���g��ʂɈڍs
		CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
	}

	if (CInputKeyboard::Trigger(DIK_M))
	{//M�L�[����������
		//�~�j�Q�[���̐���
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_STICKROTATE);
	}
}