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
#include "ItemMark.h"
#include "score.h"
#include "model3D.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
const float CGame::fPastPosX = 3000.0f;				//�ߋ��ړ�����X���W�̕ω���
bool		CGame::m_bFinish = false;				//�Q�[���I���t���O
CCamera*	CGame::m_pCamera = nullptr;				//�J����
CTime*		CGame::m_pTime = nullptr;				//�^�C�}�[
CSky*		CGame::m_pSky = nullptr;				//��
CMeshField*	CGame::m_pMeshField = nullptr;			//�n��
CMeshField* CGame::m_pMeshField2 = nullptr;			//�n��2
CMeshField* CGame::m_pCityField = nullptr;			//���̃t�B�[���h
CObjectX*	CGame::m_pObjectX[nMaxObject] = {};		//�I�u�W�F�N�g
CObjectX*	CGame::m_pObjBG[nMaxBG];				//�w�i�I�u�W�F�N�g
CPlayer*	CGame::m_pPlayer[nMaxPlayer] = {};		//�v���C���[
CRubble*	CGame::m_pRubble[nMaxRubble] = {};
CScore*		CGame::m_pScore = nullptr;				//�X�R�A
CObject2D*	CGame::m_pObjUI = nullptr;

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
	m_pCamera = CCamera::Create();

	m_pMeshField2 = CMeshField::Create(12.0f, 5500.0f);
	m_pMeshField2->SetPos(D3DXVECTOR3(500.0f, -5.0f, 0.0f));
	m_pMeshField2->SetTexture(CTexture::TEXTURE_GROUND);
	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(12.0f, 1000.0f);
	m_pMeshField->SetTexture(CTexture::TEXTURE_GROUND);

	m_pCityField = CMeshField::Create(12.0f, 2500.0f);
	m_pCityField->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 0.0f));
	m_pCityField->SetTexture(CTexture::TEXTURE_GROUND_DART);

	//��̐���
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//�^�C�}�[�̐���
	m_pTime = CTime::Create(
		D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));
	m_pTime->SetCntTime(true);

	//�X�R�A�̐���
	{
		D3DXVECTOR3 pos(1000.0f, 630.0f, 0.0f);
		m_pScore = CScore::Create(pos);
	}

	//������@�̕\��
	m_pObjUI = new CObject2D(1);

	if (m_pObjUI)
	{
		m_pObjUI->Init(D3DXVECTOR3(200.0f, 600.0f, 0.0f));
		m_pObjUI->SetSize(300.0f, 200.0f);
		m_pObjUI->SetTexture(CTexture::TEXTURE_UI_MANUAL);
	}

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
	//if (!m_bFinish
	//	&& CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	//{
	//	//�Q�[���I���t���O�𗧂Ă�
	//	m_bFinish = true;

	//	//���U���g��ʂɈڍs
	//	CMode::GetFade()->SetFade(CMode::MODE_RESULT);
	//}

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
	int size = 1.25f;
	D3DXVECTOR3 dSize = D3DXVECTOR3(size, size, size);

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(���v)
	//-----------------------------------
	m_pObjectX[0] = CItemObj::Create();
	m_pObjectX[0]->SetType(17);
	m_pObjectX[0]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	m_pObjectX[0]->GetModel()->SetSize(dSize);
	pCollision = m_pObjectX[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(50.0f, 120.0f, 50.0f));

	m_pObjectX[1] = CItemObj::Create();
	m_pObjectX[1]->SetType(17);
	m_pObjectX[1]->SetObjType(CObject::OBJTYPE_CLOCK);
	m_pObjectX[1]->SetPos(D3DXVECTOR3(fPastPosX, 0.0f, 200.0f));
	m_pObjectX[1]->GetModel()->SetSize(dSize);
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
	pGameCenter->SetPos(D3DXVECTOR3(200.0f + fPastPosX, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));

	//��ꂽ����
	m_pRubble[0] = CRubble::Create();
	m_pRubble[0]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
	m_pRubble[0]->SetBuildType(CRubble::TYPE_PAVILION);
	pCollision = m_pRubble[0]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(90.0f, 90.0f, 90.0f));
	m_pRubble[0]->SetRequired(1);
	std::vector<CRubble::REPAIR> repair;
	repair.clear();
	repair.resize(m_pRubble[0]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[0]->SetRepair(repair);

	//�����𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	m_pRubble[0]->SetMark(D3DXVECTOR3(-200.0f, 130.0f, 0.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[2] = CItemObj::Create();
	//m_pObjectX[2]->SetType(19);
	//m_pObjectX[2]->SetObjType(CObject::OBJTYPE_PAVILION_BREAK);
	//m_pObjectX[2]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

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
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));

	//��ꂽ����
	m_pRubble[1] = CRubble::Create();
	m_pRubble[1]->SetPos(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	m_pRubble[1]->SetBuildType(CRubble::TYPE_FOUNTAIN);
	pCollision = m_pRubble[1]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(150.0f, 100.0f, 150.0f));
	m_pRubble[1]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[1]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 4;
	m_pRubble[1]->SetRepair(repair);

	//�����𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	m_pRubble[1]->SetMark(D3DXVECTOR3(200.0f, 130.0f, 200.0f), CTexture::TEXTURE_FUKIDASI4);

	//��ꂽ����
	/*m_pObjectX[3] = CItemObj::Create();
	m_pObjectX[3]->SetType(21);
	m_pObjectX[3]->SetObjType(CObject::OBJTYPE_FOUNTAIN_BREAK);
	m_pObjectX[3]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -100.0f));*/

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(�����)
	//-----------------------------------
	//�Y��Ȋ����
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(26);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f + fPastPosX, 0.0f, 0.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(140.0f, 90.0f, 50.0f));

	//��ꂽ�����
	m_pRubble[2] = CRubble::Create();
	m_pRubble[2]->SetPos(D3DXVECTOR3(200.0f, 0.0f, 0.0f));
	m_pRubble[2]->SetBuildType(CRubble::TYPE_SLIDE);
	pCollision = m_pRubble[2]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 30.0f));
	pCollision->SetSize(D3DXVECTOR3(140.0f, 90.0f, 50.0f));
	m_pRubble[2]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[2]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[2]->SetRepair(repair);

	//�����𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	m_pRubble[2]->SetMark(D3DXVECTOR3(200.0f, 130.0f, 0.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[4] = CItemObj::Create();
	//m_pObjectX[4]->SetType(27);
	//m_pObjectX[4]->SetObjType(CObject::OBJTYPE_SLIDE_BREAK);
	//m_pObjectX[4]->SetPos(D3DXVECTOR3(200.0f, 0.0f, -50.0f));

	//�����𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(�u�����R)
	//-----------------------------------
	//�Y��ȃu�����R
	pGameCenter = CGameCenter::Create();
	pGameCenter->SetType(28);
	pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	pGameCenter->SetPos(D3DXVECTOR3(-200.0f + fPastPosX, 0.0f, 400.0f));
	pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	pGameCenter->GetModel()->SetSize(dSize);
	pCollision = pGameCenter->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(-5.0f, 25.0f, 0.0f));
	pCollision->SetSize(D3DXVECTOR3(165.0f, 90.0f, 130.0f));

	//��ꂽ�u�����R
	m_pRubble[3] = CRubble::Create();
	m_pRubble[3]->SetPos(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));
	m_pRubble[3]->SetBuildType(CRubble::TYPE_SWING);
	pCollision = m_pRubble[3]->GetCollision();
	pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 30.0f));
	pCollision->SetSize(D3DXVECTOR3(165.0f, 90.0f, 130.0f));
	m_pRubble[3]->SetRequired(1);
	repair.clear();
	repair.resize(m_pRubble[3]->GetRequired());
	repair.at(0).type = CItemObj::TYPE_WOOD;
	repair.at(0).nRequired = 1;
	m_pRubble[3]->SetRepair(repair);

	//�u�����R�𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	m_pRubble[3]->SetMark(D3DXVECTOR3(-300.0f, 130.0f, 300.0f), CTexture::TEXTURE_FUKIDASI);

	//m_pObjectX[5] = CItemObj::Create();
	//m_pObjectX[5]->SetType(29);
	//m_pObjectX[5]->SetObjType(CObject::OBJTYPE_SWING_BREAK);
	//m_pObjectX[5]->SetPos(D3DXVECTOR3(-300.0f, 0.0f, 300.0f));

	//�u�����R�𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

	//-----------------------------------
	// �I�u�W�F�N�g�̐���(�V�[�\�[)
	//-----------------------------------
	//�Y��ȃV�[�\�[
	//pGameCenter = CGameCenter::Create();
	//pGameCenter->SetType(30);
	//pGameCenter->SetGameType(CMiniGameBasis::TYPE_BUTTUNPUSH);
	//pGameCenter->SetPos(D3DXVECTOR3(-250.0f + fPastPosX, 0.0f, 200.0f));
	//pGameCenter->SetItemType(CItemObj::TYPE_WOOD);
	//pCollision = pGameCenter->GetCollision();
	//pCollision->SetPos(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	//pCollision->SetSize(D3DXVECTOR3(270.0f, 90.0f, 30.0f));

	////��ꂽ�V�[�\�[
	//m_pRubble[4] = CRubble::Create();
	//m_pRubble[4]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, -250.0f));
	//m_pRubble[4]->SetBuildType(CRubble::TYPE_SEESAW);
	//pCollision = m_pRubble[4]->GetCollision();
	//pCollision->SetPos(D3DXVECTOR3(5.0f, 25.0f, 0.0f));
	//pCollision->SetSize(D3DXVECTOR3(280.0f, 90.0f, 80.0f));
	//m_pRubble[4]->SetRequired(1);
	//repair.clear();
	//repair.resize(m_pRubble[4]->GetRequired());
	//repair.at(0).type = CItemObj::TYPE_WOOD;
	//repair.at(0).nRequired = 1;
	//m_pRubble[4]->SetRepair(repair);

	//m_pObjectX[6] = CItemObj::Create();
	//m_pObjectX[6]->SetType(31);
	//m_pObjectX[6]->SetObjType(CObject::OBJTYPE_SEESAW_BREAK);
	//m_pObjectX[6]->SetPos(D3DXVECTOR3(-200.0f, 0.0f, -250.0f));

	//�V�[�\�[�𒼂��̂ɕK�v�ȃA�C�e���̖ڈ�
	//m_pItemMark[2] = CItemMark::Create(D3DXVECTOR3(-200.0f, 130.0f, 0.0f));
	//m_pItemMark[2]->SetSize(100.0f, 100.0f);
	//m_pItemMark[2]->SetTexture(CTexture::TEXTURE_FUKIDASI);

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
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f, 0.0f, 500.0f - (100.0f * i)));
		}
		else if (i < 25)
		{//�E�̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(550.0f, 0.0f, 500.0f - (100.0f * (i - 13))));
		}
		else if (i < 38)
		{//��̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 26)), 0.0f, 550.0f));
		}
		else if (i < 51)
		{//���̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(22);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + (100.0f * (i - 39)), 0.0f, -550.0f));
		}

		//���������������̐���
		else if (i < 64)
		{//���̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX, 0.0f, 500.0f - (100.0f * (i - 51))));
		}
		else if (i < 77)
		{//�E�̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(550.0f + fPastPosX, 0.0f, 500.0f - (100.0f * (i - 64))));
		}
		else if (i < 90)
		{//��̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX + (100.0f * (i - 77)), 0.0f, 550.0f));
		}
		else if (i < 103)
		{//���̖�
			m_pObjBG[i] = CItemObj::Create();
			m_pObjBG[i]->SetType(32);
			m_pObjBG[i]->SetPos(D3DXVECTOR3(-550.0f + fPastPosX +(100.0f * (i - 90)), 0.0f, -550.0f));
		}
	}
}