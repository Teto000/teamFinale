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
#include "light.h"
#include "debug_proc.h"
#include "camera.h"
#include "model3D.h"
#include "collision.h"
#include "mode.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CRenderer*		CApplication::m_pRenderer = nullptr;	//レンダラー
CInput*			CApplication::m_pInput = nullptr;		//インプット
CTexture*		CApplication::m_pTexture = nullptr;		//テクスチャ
CSound*			CApplication::m_pSound = nullptr;		//サウンド
CLight*			CApplication::m_pLight = nullptr;		//ライト
CDebugProc*		CApplication::m_pDebugproc = nullptr;	//デバッグ用文字

/* ↓ 変数　↓ */
int CApplication::m_nStageScore[nMaxStage] = {};		//ステージごとのスコアを保存
int CApplication::m_nMaxScore[nMaxStage] = {};			//スコアの最大値を保存

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
	if (FAILED(m_pRenderer->Init(hWnd, FALSE)))
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
	CMode::Init();

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
	// モードの終了
	//----------------------------
	CMode::Uninit();

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

	//モードの更新
	CMode::Update();
}

//===========================
// 描画
//===========================
void CApplication::Draw()
{
	//レンダリングの描画
	m_pRenderer->Draw();
}