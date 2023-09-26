//===================================================
//
// チュートリアルの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "tutorial.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "mode.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bg.h"

//===========================
// コンストラクタ
//===========================
CTutorial::CTutorial()
{
	m_pBg = nullptr;	//背景
}

//===========================
// デストラクタ
//===========================
CTutorial::~CTutorial()
{

}

//===========================
// 初期化
//===========================
HRESULT CTutorial::Init()
{
	//背景の生成
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_TITLE);
		m_pBg->SetTexture(CTexture::TEXTURE_TUTORIAL);
	}

	return S_OK;
}

//===========================
// 終了
//===========================
void CTutorial::Uninit()
{
	////BGMの停止
	//CSound::StopSound();
}

//===========================
// 更新
//===========================
void CTutorial::Update()
{
	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//ゲーム画面に移行
		CMode::GetFade()->SetFade(CMode::MODE_GAME);

		//SEの再生
		//CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
}