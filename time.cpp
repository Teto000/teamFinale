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

//=======================
// コンストラクタ
//=======================
CTime::CTime() : CObject(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//数字の位置
	m_nTime = 0;				//時間
	m_nCntMove = 0;				//移動までの時間
	m_nFinTime = 0;				//ゲーム終了までの時間
	m_nCntFream = 0;			//フレーム数のカウント
	fInterval = 0.0f;			//数値の間隔
	m_bCntTime = false;			//時間を数える状態

	m_pObject = nullptr;

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//今の桁の数値
		m_pNumber[i] = nullptr;	//数値
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
	m_pos = pos;		//位置
	m_nTime = 5;		//初期時間
	fInterval = 50.0f;	//数値の間隔

	m_pObject = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pObject->SetTexture(CTexture::TEXTURE_FINISH);

	//------------------------------
	// 数値の設定
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nTime);
		m_pNumber[i]->Set(i);
	}

	SetNumber();

	return S_OK;
}

//=======================
// 終了
//=======================
void CTime::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Uninit();
	}
}

//=======================
// 更新
//=======================
void CTime::Update()
{
	if (CGame::GetFinish())
	{//ゲームが終了しているなら
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
			SetNumber();
			m_nCntFream = 0;

			if (m_nTime <= 0)
			{
				m_pObject->SetSize(800.0f, 300.0f);
				m_nFinTime++;

				if (m_nFinTime >= 3)
				{
					//リザルト画面に移行
					//CMode::GetFade()->SetFade(CMode::MODE_RESULT);
				}
			}
		}
	}
}

//=======================
// 描画
//=======================
void CTime::Draw()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Draw();
	}
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

//=======================
// 数値の設定
//=======================
void CTime::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//桁数分回す
		if (m_pNumber[i] != nullptr)
		{//nullじゃないなら
			//桁数を計算
			int nDigit = (int)(log10(m_nTime) + 1);

			//ナンバーの描画を有効・無効にする
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nTime == 0)
			{//コンボ数が0なら
				//ナンバーの描画を有効・無効にする
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//powで桁数を出す。
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//桁ごとの値を求める
			m_aPosTexU[i] = (m_nTime % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}

//=======================
// 時間の設定
// 引数：設定したい数値
//=======================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

	SetNumber();
}

//=======================
// 描画状態の設定
// 引数：描画状態のbool
//=======================
void CTime::SetDraw(bool bDraw)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetEnable(bDraw);
	}
}

//=======================
// 色の設定
// 引数：変更先の色
//=======================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetColor(col);
	}
}