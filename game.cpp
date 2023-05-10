//===================================================
//
// ゲームの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
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

//------------------------
// 静的メンバ変数宣言
//------------------------
bool		CGame::m_bFinish = false;				//ゲーム終了フラグ
CCamera*	CGame::m_pCamera[nMaxCamera] = {};		//カメラ
CTime*		CGame::m_pTime = nullptr;				//タイマー
CSky*		CGame::m_pSky = nullptr;				//空
CMeshField*	CGame::m_pMeshField = nullptr;			//地面

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{
	m_pPlayer = nullptr;	//プレイヤー
}

//===========================
// デストラクタ
//===========================
CGame::~CGame()
{

}

//===========================
// 初期化
//===========================
HRESULT CGame::Init()
{
	//初期値の設定
	m_bFinish = false;	//ゲームが終了していない状態

	//------------------------
	// カメラの生成
	//------------------------
	m_pCamera[0] = CCamera::Create((DWORD)0.0f, (DWORD)0.0f
								, (DWORD)(SCREEN_WIDTH / 2)
								, (DWORD)SCREEN_HEIGHT);

	m_pCamera[1] = CCamera::Create((DWORD)(SCREEN_WIDTH/ 2), (DWORD)0.0f
								, (DWORD)(SCREEN_WIDTH / 2)
								, (DWORD)SCREEN_HEIGHT);

	//メッシュフィールドの生成
	m_pMeshField = CMeshField::Create();

	//空の生成
	m_pSky = CSky::Create(CTexture::TEXTURE_SKY);

	//タイマーの生成
	m_pTime = CTime::Create(D3DXVECTOR3(1088.0f, 592.0f, 0.0f));

	// プレイヤーの設定
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data/MOTION/motion.txt");

	//BGMの再生
	//CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGame::Uninit()
{
	//BGMの停止
	//CSound::StopSound();

	//---------------------
	// カメラの終了
	//---------------------
	for (int i = 0; i < nMaxCamera; i++)
	{
		if (m_pCamera[i] != nullptr)
		{
			m_pCamera[i]->Uninit();
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
	}
}

//===========================
// 更新
//===========================
void CGame::Update()
{
	//----------------------------
	// カメラの更新
	//----------------------------
	for (int i = 0; i < nMaxCamera; i++)
	{
		if (m_pCamera[i] != nullptr)
		{
			m_pCamera[i]->Update();
		}
	}

	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_RETURN) || joypad->AllTrigger())
	{
		//ゲーム終了フラグを立てる
		m_bFinish = true;

		//リザルト画面に移行
		CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);

		//画面サイズを拡大
		for (int i = 0; i < nMaxCamera; i++)
		{
			m_pCamera[i]->SetViewSize(0, 0, 1280, 720);
		}
	}

	if (CInputKeyboard::Trigger(DIK_T))
	{//Tキーを押したら
		//ミニゲームの生成
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTUNPUSH);
	}

	if (CInputKeyboard::Trigger(DIK_L))
	{//Lキーを押したら
		//ミニゲームの生成
		CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTONMASH);
	}
}