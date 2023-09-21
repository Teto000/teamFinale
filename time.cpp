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
	m_neeadleRotX = 0.0f;		//針の角度
	m_bCntTime = false;			//時間を数える状態
	m_pMessage = nullptr;

	for (int i = 0; i < nMaxObj; i++)
	{
		m_pObj[i] = nullptr;
	}
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
	m_pos = pos;			//位置
	m_neeadleRotX = -0.1f;	//針の角度
	m_nTime = nMaxTime;		//初期時間

	m_pObj[0] = new CObject2D;
	m_pObj[0]->Init(pos);
	m_pObj[0]->SetSize(180.0f,180.0f);
	m_pObj[0]->SetTexture(CTexture::TEXTURE_CLOCK);

	m_pObj[1] = new CObject2D;
	m_pObj[1]->Init(pos);
	m_pObj[1]->SetSize(180.0f, 140.0f);
	m_pObj[1]->SetTexture(CTexture::TEXTURE_CLOCK_NEEDLE);

	return S_OK;
}

//=======================
// 終了
//=======================
void CTime::Uninit()
{
	/*for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Uninit();
			delete m_pObj[i];
			m_pObj[i] = nullptr;
		}
	}*/
}

//=======================
// 更新
//=======================
void CTime::Update()
{
	//更新
	for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Update();
		}
	}

	if (CInputKeyboard::Trigger(DIK_P))
	{
		m_neeadleRotX -= 0.1f;
	}

	//時計の針を回転させる
	m_pObj[1]->SetVtxCIE_Rot(m_pos,
		m_neeadleRotX,
		180.0f,
		140.0f);

	if (CGame::GetFinish() && CMode::GetMode() == CMode::MODE_GAME)
	{//ゲームが終了しているなら
		m_nFinTime++;

		if (m_nFinTime >= 60)
		{
			//リザルト画面に移行
			CMode::GetFade()->SetFade(CMode::MODE_RESULT);
		}

		//タイムを保存
		//CRanking::SetNewTime(m_nTime);
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
				//時間を減らす
				m_nTime--;

				//針を動かす
				//時間ピッタリで時計の針が一周するようにする
				m_neeadleRotX -= (6.2f / nMaxTime);
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
	/*for (int i = 0; i < nMaxObj; i++)
	{
		if (m_pObj[i])
		{
			m_pObj[i]->Draw();
		}
	}*/
}

//=======================
// 生成
// 引数：位置
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