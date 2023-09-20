//===================================================
//
// タイマー処理
// Author : Sato Teruto
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "score.h"
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
CScore::CScore() : CObject(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//数字の位置
	m_nScore = 0;				//時間
	fInterval = 0.0f;			//数値の間隔

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//今の桁の数値
		m_pNumber[i] = nullptr;	//数値
	}
}

//=======================
// デストラクタ
//=======================
CScore::~CScore()
{

}

//=======================
// 初期化
//=======================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//初期値の設定
	m_pos = pos;		//位置
	m_nScore = 90;		//初期時間
	fInterval = 50.0f;	//数値の間隔

	//------------------------------
	// 数値の設定
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nScore);
		m_pNumber[i]->Set(i);
	}

	SetNumber();

	return S_OK;
}

//=======================
// 終了
//=======================
void CScore::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Uninit();
	}
}

//=======================
// 更新
//=======================
void CScore::Update()
{
	
}

//=======================
// 描画
//=======================
void CScore::Draw()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Draw();
	}
}

//=======================
// 生成
// 引数：位置
//=======================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;

	//----------------------------------
	// 生成と初期化
	//----------------------------------
	pScore = new CScore;	//生成

	if (pScore != nullptr)
	{//NULLチェック
		//初期化
		pScore->Init(D3DXVECTOR3(pos));
	}

	return pScore;
}

//=======================
// 数値の設定
//=======================
void CScore::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//桁数分回す
		if (m_pNumber[i] != nullptr)
		{//nullじゃないなら
		 //桁数を計算
			int nDigit = (int)(log10(m_nScore) + 1);

			//ナンバーの描画を有効・無効にする
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nScore == 0)
			{//コンボ数が0なら
			 //ナンバーの描画を有効・無効にする
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//powで桁数を出す。
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//桁ごとの値を求める
			m_aPosTexU[i] = (m_nScore % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}

//=======================
// 時間の設定
// 引数：設定したい数値
//=======================
void CScore::SetTime(int nTime)
{
	m_nScore = nTime;

	SetNumber();
}

//=======================
// 描画状態の設定
// 引数：描画状態のbool
//=======================
void CScore::SetDraw(bool bDraw)
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
void CScore::SetColor(D3DXCOLOR col)
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->SetColor(col);
	}
}