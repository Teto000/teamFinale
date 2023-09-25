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
	m_pBg[0] = {};	//背景
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
		m_pBg[0] = CBg::Create(pos, CBg::BGTYPE_TITLE);
		m_pBg[0]->SetTexture(CTexture::TEXTURE_TITLE_BG);

		D3DXVECTOR3 LogoPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f);
		m_pBg[1] = CBg::Create(LogoPos, CBg::BGTYPE_TITLE);
		m_pBg[1]->SetTexture(CTexture::TEXTURE_TITLE);
		m_pBg[1]->SetSize(1000.0f, 600.0f);

		D3DXVECTOR3 EnterPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f);
		m_pBg[2] = CBg::Create(EnterPos, CBg::BGTYPE_TITLE);
		m_pBg[2]->SetTexture(CTexture::TEXTURE_PRESSENTER);
		m_pBg[2]->SetSize(300.0f, 300.0f);

		m_bScale = false;
		m_fScale = 500.0f;
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

	// 現在その選択肢が選択されている場合
	if (m_bScale == false)
	{// 文字が拡大している場合
		m_fScale += 5.0f;
		if (m_fScale > 600.0f)
		{// 文字が一定の値まで拡大した場合
			m_bScale = true;	// 文字を縮小させる
		}
	}
	else
	{// 文字が縮小している場合
		m_fScale -= 5.0f;
		if (m_fScale < 400.0f)
		{// 文字が一定の値まで縮小した場合
			m_bScale = false;	// 文字を拡大させる
		}
	}

	m_pBg[2]->SetSize(m_fScale, m_fScale);

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