//===================================================
//
// タイマー処理
// Author : Sato Teruto
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "time.h"
#include "number.h"
#include "game.h"
#include "renderer.h"
#include "ranking.h"
#include "input.h"
#include "input_keyboard.h"
#include "mode.h"
#include "fade.h"
#include "message.h"

//=======================
// コンストラクタ
//=======================
CTime::CTime() : CObject2D(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//数字の位置
	m_nTime = 0;				//時間
	m_nCntMove = 0;				//移動までの時間
	m_nFinTime = 0;				//ゲーム終了までの時間
	m_nCntFream = 0;			//フレーム数のカウント
	m_bCntTime = false;			//時間を数える状態
	m_pMessage = nullptr;
}

//=======================
// デストラクタ
//=======================
CTime::~CTime()
{

}

//=======================
// 初期化
//=======================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	//初期値の設定
	m_pos = pos;		//位置
	m_nTime = 90;		//初期時間

	CObject2D::Init(pos);
	CObject2D::SetSize(100.0f,100.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_CLOCK);

	return S_OK;
}

//=======================
// 終了
//=======================
void CTime::Uninit()
{
	CObject2D::Uninit();
}

//=======================
// 更新
//=======================
void CTime::Update()
{
	CObject2D::Update();

	if (CGame::GetFinish() && CMode::GetMode() == CMode::MODE_GAME)
	{//ゲームが終了しているなら
		m_nFinTime++;

		if (m_nFinTime >= 60)
		{
			//リザルト画面に移行
			CMode::GetFade()->SetFade(CMode::MODE_RESULT);
		}

		//タイムを保存
		CRanking::SetNewTime(m_nTime);
	}
	else if(m_bCntTime && CMode::GetMode() == CMode::MODE_GAME)
	{//時間を数える状態なら
		//フレーム数を数える
		m_nCntFream++;

		//----------------------
		// 時間の加算
		//----------------------
		if (m_nCntFream >= 60)
		{
			if (m_nTime > 0)
			{
				m_nTime--;
			}

			//数字の設定
			m_nCntFream = 0;

			if (m_nTime <= 0)
			{
				CGame::SetFinish(true);

				m_pMessage = CMessage::Create(
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, 800.0f, 200.0f);
			}
		}
	}
}

//=======================
// 描画
//=======================
void CTime::Draw()
{
	CObject2D::Draw();
}

//=======================
// 生成
// 引数：位置、コンボ数
//=======================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pCombo = nullptr;

	//----------------------------------
	// 生成と初期化
	//----------------------------------
	pCombo = new CTime;	//生成

	if (pCombo != nullptr)
	{//NULLチェック
		//初期化
		pCombo->Init(D3DXVECTOR3(pos));
	}

	return pCombo;
}