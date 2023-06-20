//===================================================
//
// アプリケーションの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
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
// 静的メンバ変数宣言
//------------------------
/* ↓ 画面遷移 ↓ */
CTitle*			CApplication::m_pTitle = nullptr;		//タイトル
CGame*			CApplication::m_pGame = nullptr;		//ゲーム
CResult*		CApplication::m_pResult = nullptr;		//リザルト
CStageSelect*	CApplication::m_pStageSelect = nullptr;	//ステージ選択
CFade*			CApplication::m_pFade = nullptr;		//フェード
CApplication::MODE	CApplication::m_mode = MODE_MAX;	//ゲームモード

/* ↓ その他 ↓ */
CRenderer*		CApplication::m_pRenderer = nullptr;	//レンダラー
CInput*			CApplication::m_pInput = nullptr;		//インプット
CTexture*		CApplication::m_pTexture = nullptr;		//テクスチャ
CSound*			CApplication::m_pSound = nullptr;		//サウンド
CLight*			CApplication::m_pLight = nullptr;		//ライト
CDebugProc*		CApplication::m_pDebugproc = nullptr;	//デバッグ用文字

//===========================
// コンストラクタ
//===========================
CApplication::CApplication()
{

}

//===========================
// デストラクタ
//===========================
CApplication::~CApplication()
{

}

//===========================
// 初期化
//===========================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	//ランダム
	srand((unsigned int)time(NULL));

	//----------------------------
	// レンダリングの生成と初期化
	//----------------------------
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//----------------------------
	// インプットの生成と初期化
	//----------------------------
	m_pInput = new CInput;
	m_pInput->Init(hInstance, hWnd);

	//----------------------------
	// テクスチャの生成
	//----------------------------
	m_pTexture = new CTexture;
	assert(m_pTexture != nullptr);
	m_pTexture->Init();

	// モデル情報の初期化
	CModel3D::InitModel();

	//----------------------------
	// サウンドの生成と初期化
	//----------------------------
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//----------------------------
	// ライトの生成と初期化
	//----------------------------
	m_pLight = new CLight;
	m_pLight->Init(GetRenderer()->GetDevice());

	//----------------------------
	// モードの設定
	//----------------------------
	m_pFade = new CFade;
	SetMode(MODE_TITLE);
	m_pFade->Init(MODE_TITLE);

	//----------------------------
	// デバッグ用文字の生成
	//----------------------------
	m_pDebugproc = new CDebugProc;
	m_pDebugproc->Init();

	return S_OK;
}

//===========================
// 終了
//===========================
void CApplication::Uninit()
{
	//----------------------------
	// オブジェクトの全解放
	//----------------------------
	CObject::ReleaseAll(true);
	CCollision::ReleaseAll();

	//----------------------------
	//テクスチャの終了
	//----------------------------
	if (m_pTexture != nullptr)
	{// 終了処理
		m_pTexture->Uninit();

		// メモリの解放
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// モデル情報の終了
	CModel3D::UninitModel();

	//----------------------------
	// レンダリングの終了
	//----------------------------
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//----------------------------
	// インプットの終了
	//----------------------------
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	//----------------------------
	// サウンドの終了
	//----------------------------
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//----------------------------
	// ライトの終了
	//----------------------------
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//----------------------------
	// タイトルの終了
	//----------------------------
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	//----------------------------
	// ゲームの終了
	//----------------------------
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	//----------------------------
	// リザルトの終了
	//----------------------------
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}

	//----------------------------
	// ステージ選択の終了
	//----------------------------
	if (m_pStageSelect != nullptr)
	{
		m_pStageSelect->Uninit();
		delete m_pStageSelect;
		m_pStageSelect = nullptr;
	}

	//----------------------------
	// フェードの終了
	//----------------------------
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//----------------------------
	// デバッグ用文字の終了
	//----------------------------
	if (m_pDebugproc != nullptr)
	{
		m_pDebugproc->Uninit();
		delete m_pDebugproc;
		m_pDebugproc = nullptr;
	}
}

//===========================
// 更新
//===========================
void CApplication::Update()
{
	//インプットの更新
	m_pInput->Update();	//最初にやる

	//レンダリングの更新
	m_pRenderer->Update();

	//---------------------------
	// モードごとの更新
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

	//フェードの更新
	m_pFade->Update();
}

//===========================
// 描画
//===========================
void CApplication::Draw()
{
	//レンダリングの描画
	m_pRenderer->Draw();
}

//===========================
// モードの設定
//===========================
void CApplication::SetMode(MODE mode)
{
	//----------------------------
	// 現在のモードの終了処理
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

	//オブジェクトの全解放
	CObject::ReleaseAll(true);

	// 当たり判定の終了
	CCollision::ReleaseAll();

	//モードの切り替え
	m_mode = mode;

	//----------------------------
	// 新しいモードの生成
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