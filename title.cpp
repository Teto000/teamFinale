//===================================================
//
// タイトルの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "title.h"
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
CTitle::CTitle()
{
	m_pBg = nullptr;	//背景
}

//===========================
// デストラクタ
//===========================
CTitle::~CTitle()
{

}

//===========================
// 初期化
//===========================
HRESULT CTitle::Init()
{
	//背景の生成
	{
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg = CBg::Create(pos, CBg::BGTYPE_TITLE);
		m_pBg->SetTexture(CTexture::TEXTURE_TITLE);
	}

	//BGMの再生
	//CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CTitle::Uninit()
{
	////BGMの停止
	//CSound::StopSound();
}

//===========================
// 更新
//===========================
void CTitle::Update()
{
	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//ゲーム画面に移行
		CMode::GetFade()->SetFade(CMode::MODE_STAGESELECT);

		//SEの再生
		//CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}
}