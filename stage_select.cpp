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
#include "object2D.h"
#include "time.h"

//----------------------------------
// 静的メンバ変数宣言
//----------------------------------
bool CStageSelect::m_bViewMap = false;		//マップを表示する状態
bool CStageSelect::m_bStart = false;		//ゲームを開始する状態

//==================================
// コンストラクタ
//==================================
CStageSelect::CStageSelect()
{
	m_pCamera = nullptr;	//カメラ
	m_pMeshField = nullptr;	//メッシュフィールド(地面)
	m_pObjectX = nullptr;	//オブジェクトX
	m_pPlayer = nullptr;	//プレイヤー
	m_pObject2D = nullptr;	//オブジェクト2D
	m_pNumber = nullptr;	//数字
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

	//------------------------
	// 画像の生成
	//------------------------
	D3DXVECTOR3 pos((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);	//位置
	m_pObject2D = CObject2D::Create(pos);							//生成
	m_pObject2D->SetSize(0.0f, 0.0f);								//大きさ
	m_pObject2D->SetTexture(CTexture::TEXTURE_NONE);				//テクスチャ
	m_pObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));		//色

	//------------------------
	// 数字の生成
	//------------------------
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, 400.0f, 0.0f);
		m_pNumber = CTime::Create(pos);
	}

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

	//-----------------------
	// 画像表示の切り替え
	// 備考::ステージ番号でテクスチャを切り替える
	//-----------------------
	if (m_bViewMap == true)
	{//マップを表示する状態なら
		//画像を拡大する(表示)
		m_pObject2D->SetSize(300.0f, 300.0f);

		//数字を描画する
		m_pNumber->SetDraw(true);
		m_pNumber->SetTime(10);
	}
	else
	{
		//画像を縮小する(非表示)
		m_pObject2D->SetSize(0.0f, 0.0f);

		//数字を描画しない
		m_pNumber->SetDraw(false);
	}

	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (m_bStart &&
		CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{//ゲームを開始する状態 & キーが押されたら
		//ゲーム画面に移行
		CApplication::GetFade()->SetFade(CApplication::MODE_GAME);
	}
}