//===================================================
//
// ステージ選択処理
// Author : Sato Teruto
//
//===================================================

//----------------------------------
// インクルード
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

//==================================
// コンストラクタ
//==================================
CStageSelect::CStageSelect()
{
	m_pCamera = nullptr;	//カメラ
	m_pMeshField = nullptr;	//メッシュフィールド(地面)
	m_pObjectX = nullptr;	//オブジェクトX
	m_pPlayer = nullptr;	//プレイヤー
}

//=================================
// デストラクタ
//=================================
CStageSelect::~CStageSelect()
{
}

//==================================
// 初期化処理
//==================================
HRESULT CStageSelect::Init()
{
	//------------------------
	// カメラの生成
	//------------------------
	m_pCamera = CCamera::Create(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//------------------------
	// 地面の生成
	//------------------------
	m_pMeshField = CMeshField::Create();

	//------------------------
	// プレイヤーの生成
	//------------------------
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

	//------------------------
	// オブジェクトの生成(旗)
	//------------------------
	m_pObjectX = CObjectX::Create();
	m_pObjectX->SetType(1);

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CStageSelect::Uninit()
{
	//-----------------------
	// カメラの終了
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==================================
// 更新処理
//==================================
void CStageSelect::Update()
{
	//-----------------------
	// カメラの更新処理
	//-----------------------
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//ゲーム画面に移行
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);
	}
}