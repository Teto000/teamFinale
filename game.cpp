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
#include "game_center.h"
#include "rubble.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CGame::fPastPosX = 2000.0f;			//�ߋ��ړ�����X���W�̕ω���
bool		CGame::m_bFinish = false;			//�Q�[���I���t���O
CCamera*	CGame::m_pCamera = nullptr;			//�J����
CTime*		CGame::m_pTime = nullptr;			//�^�C�}�[
CSky*		CGame::m_pSky = nullptr;			//��
CMeshField*	CGame::m_pMeshField = nullptr;		//�n��
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};	//�I�u�W�F�N�g
CObjectX*	CGame::m_pObjBG[nMaxBG];
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};	//�v���C���[

//===========================
// �R���X�g���N�^
//===========================
CGame::CGame()
{

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
	// �ϐ��錾
	CCollision_Rectangle3D *pCollision = nullptr;

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

		pCollision = m_pPlayer[i]->GetCollision();
		pCollision->SetSize(D3DXVECTOR3(20.0f, 50.0f, 20.0f));
		pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	}

	//�I�u�W�F�N�g�̐����֐�
	CreateObj();

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

#ifdef _DEBUG
	//-----------------------
	// ��ʑJ��
	//-----------------------
	if (!m_bFinish
		&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//�Q�[���I���t���O�𗧂Ă�
		m_bFinish = true;

		//���U���g��ʂɈڍs
		CMode::GetFade()->SetFade(CMode::MODE_RESULT);
	}

	if (CInputKeyboard::Trigger(DIK_L))
	{//L�L�[����������
	 //�~�j�Q�[���̐���
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTONMASH);
	}

	if (CInputKeyboard::Trigger(DIK_M))
	{//M�L�[����������
	 //�~�j�Q�[���̐���
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_STICKROTATE);
	}
#endif // DEBUG
}

//===========================
// �I�u�W�F�N�g�̐����֐�
//===========================
void CGame::CreateObj()
{
	// �ϐ��錾
	CCollision_Rectangle3D *pCollision = nullptr;

	/*m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(1);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));*/

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(���v)
	//-----------------------------------
	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(17);
	m_pObjectX[0]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	pCollision = m_pObjectX[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 200.0f));
	pCollision = m_pObjectX[1]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	//-----------------------------------
	// �Q�[���Z���^�[�̐ݒ�
	//-----------------------------------
	CGameCenter* pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(1);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(����)
	//-----------------------------------
	//�Y��ȓ���
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(18);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));

	//��ꂽ����
	m_pObjectX[2] = CItemObj::Create();
	m_pObjectX[2]->SetType(19);
	m_pObjectX[2]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	m_pObjectX[2]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	/*pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(19);
	pGameCenter->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_NULL);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));*/

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(����)
	//-----------------------------------
	//�Y��ȕ���
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(20);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTONMASH);
	pGameCenter->SetPos(D3DXVECTOR3(200.0f + fPastPosX, 0.0f, 400.0f));
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));

	CRubble *pRubble = CRubble::Create();
	pRubble->SetPos(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	pRubble->SetBuildType(CRubble::TYPE_FOUNTAIN);
	pCollision = pRubble->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));
	pRubble->SetRequired(1);
	std::vector<CRubble::REPAIR> repair;
	repair.clear();
	repair.resize(pRubble->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 4;
	pRubble->SetRepair(repair);

	//��ꂽ����
	m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(21);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_FOUNTAIN_BREAK);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -100.0f));

	//�؂̐���
	CreateWood();
}

//================================
// �w�i�I�u�W�F�N�g(��)�̐���
//================================
void CGame::CreateWood()
{
	for (int i = 0; i < nMaxBG; i++)
	{
		if (i < 12)
		{//���̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-450.0f, 0.0f, 500.0f - (100.0f * i)));
		}
		else if (i < 25)
		{//�E�̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(450.0f, 0.0f, 500.0f - (100.0f * (i - 13))));
		}
		else if (i < 38)
		{//��̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 26)), 0.0f, 450.0f));
		}
		else if (i < 51)
		{//���̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 39)), 0.0f, -450.0f));
		}
	}
}