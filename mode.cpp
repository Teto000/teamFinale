//===================================================
//
// 画面遷移の処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "mode.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "stage_select.h"
#include "fade.h"
#include "collision.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CTitle*			CMode::m_pTitle = nullptr;			//タイトル
CGame*			CMode::m_pGame = nullptr;			//ゲーム
CTutorial*		CMode::m_pTutorial = nullptr;		//チュートリアル
CResult*		CMode::m_pResult = nullptr;			//リザルト
CStageSelect*	CMode::m_pStageSelect = nullptr;	//ステージ選択
CFade*			CMode::m_pFade = nullptr;			//フェード
CMode::MODE		CMode::m_mode = MODE_MAX;			//ゲームモード

//===========================
// コンストラクタ
//===========================
CMode::CMode()
{
}

//===========================
// デストラクタ
//===========================
CMode::~CMode()
{
}

//===========================
// 初期化
//===========================
HRESULT CMode::Init()
{
	m_pFade = new CFade;
	SetMode(MODE_TITLE);
	m_pFade->Init(MODE_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CMode::Uninit()
{
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
	// チュートリアルの終了
	//----------------------------
	if (m_pTutorial != nullptr)
	{
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = nullptr;
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
}

//===========================
// 更新
//===========================
void CMode::Update()
{
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
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
// モードの設定
//===========================
void CMode::SetMode(MODE mode)
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

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = nullptr;
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

	case MODE_TUTORIAL:
		m_pTutorial = nullptr;
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
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