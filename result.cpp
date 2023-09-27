//===================================================
//
// リザルトの処理
// Author : Sato Teruto
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "result.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "sound.h"
#include "bg.h"
#include "fade.h"
#include "ranking.h"
#include "debug_proc.h"
#include "camera.h"
#include "meshfield.h"

//===========================
// コンストラクタ
//===========================
CResult::CResult()
{
	m_pBg[0] = nullptr;	//背景
	m_pRanking = nullptr;
}

//===========================
// デストラクタ
//===========================
CResult::~CResult()
{
	
}

//===========================
// 初期化
//===========================
HRESULT CResult::Init()
{	
	{	
		//背景の生成
		D3DXVECTOR3 pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		m_pBg[0] = CBg::Create(pos, CBg::BGTYPE_RESULT);
		m_pBg[0]->SetTexture(CTexture::TEXTURE_RESULT);

		m_pBg[1] = CBg::Create(pos, CBg::BGTYPE_RESULT);
		m_pBg[1]->SetTexture(CTexture::TEXTURE_NONE);
		m_pBg[1]->SetSize(800.0f, 650.0f);
		m_pBg[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		m_pBg[2] = CBg::Create(D3DXVECTOR3(pos.x,pos.y - 275.0f,pos.z), CBg::BGTYPE_RESULT);
		m_pBg[2]->SetTexture(CTexture::TEXTURE_RANKING);
		m_pBg[2]->SetSize(500.0f, 300.0f);
	}

	//-------------------------------------
	// スコアが更新されたら値を保存
	//-------------------------------------
	for (int i = 0; i < CApplication::GetMaxStage(); i++)
	{//ステージの最大数分回す
		int nScore = CApplication::GetStageScore(i);	//今回のスコア
		int nMaxScore = CApplication::GetMaxScore(i);	//最大のスコア

		if (nScore >= nMaxScore)
		{//スコアが更新されたら
			//今回のスコアを最大にする
			CApplication::SetMaxScore(i, nScore);
		}

		//今回のスコアの値をリセット
		//CApplication::ResetStageScore(i);
	}

	//BGMの再生
	CSound::PlaySound(CSound::SOUND_LABEL_RESULT);

	//ランキングの生成
	m_pRanking = CRanking::Create();

	return S_OK;
}

//===========================
// 終了
//===========================
void CResult::Uninit()
{
	//BGMの停止
	CSound::StopSound();
}

//===========================
// 更新
//===========================
void CResult::Update()
{
	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	//-----------------------
	// 画面遷移
	//-----------------------
	if (CInputKeyboard::AllTrigger() || joypad->AllTrigger())
	{
		//タイトル画面に移行
		CMode::GetFade()->SetFade(CMode::MODE_TITLE);

		//SEの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);
	}

	CDebugProc::Print("リザルト画面");
}