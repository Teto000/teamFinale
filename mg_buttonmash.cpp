//===================================================
//
// ボタン連打処理
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "mg_buttonmash.h"
#include "application.h"
#include "renderer.h"

#include "object2D.h"
#include "input_keyboard.h"
#include "application.h"
#include "fade.h"
#include "game.h"
#include "number.h"

//=======================
// コンストラクタ
//=======================
CButtonMash::CButtonMash()
{
	//オブジェクト2D変数
	pObj2D = nullptr;

	//アニメーション用変数
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//数字カウント用変数
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//数字の位置
	m_fInterval = 40.0f;	//数値の間隔
	m_nMashCounter = 0;		//カウント数

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//今の桁の数値
		m_pNumber[i] = nullptr;	//数値
	}
}

//=======================
// デストラクタ
//=======================
CButtonMash::~CButtonMash()
{

}

//=======================
// 初期化
//=======================
HRESULT CButtonMash::Init(D3DXVECTOR3 pos)
{
	//------------------------------
	//ボタンポリゴンの設定
	//------------------------------
	pObj2D = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D->SetSize(300.0f, 300.0f);
	pObj2D->SetTexture(CTexture::TEXTURE_BUTTON);
	pObj2D->SetSplitTex(1.0f,1.0f,2.0f,(float)m_nPatternAnim);
	m_pos = pObj2D->GetPosition();

	//------------------------------
	// 数値の設定
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3((m_pos.x + 15.0f) + (m_fInterval * i), m_pos.y - 60.0f, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nMashCounter);
		m_pNumber[i]->Set(i);
		m_pNumber[i]->SetSize(40.0f, 60.0f);
	}

	SetNumber();

	return S_OK;
}

//=======================
// 終了
//=======================
void CButtonMash::Uninit()
{

}

//=======================
// 更新
//=======================
void CButtonMash::Update()
{
	if (pObj2D != nullptr)
	{
		//カウンターを加算
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10フレーム経過
		 //テクスチャのアニメーション
			pObj2D->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//パターンNo.を更新する
			m_nPatternAnim++;
		}

		if (CInputKeyboard::Trigger(DIK_J))
		{//Jキーを押したときに
			//連打カウントを1増やす
			m_nMashCounter++;
			SetNumber();
		}

		if (m_nMashCounter >= 30)
		{//連打数が30超えたら
			//オブジェクト破棄
			pObj2D->Uninit();
			pObj2D = nullptr;

			//数値破棄
			for (int i = 0; i < nMaxDigits; i++)
			{
				m_pNumber[i]->Uninit();
			}
		}
	}
}

//=======================
// 描画
//=======================
void CButtonMash::Draw()
{

}

//=======================
// 生成
// 引数：位置
//=======================
CButtonMash *CButtonMash::Create(D3DXVECTOR3 pos)
{
	CButtonMash *pMashGame = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pMashGame = new CButtonMash;	//生成

	if (pMashGame != nullptr)
	{//NULLチェック

	 //初期化
		pMashGame->Init(D3DXVECTOR3(pos));
		pMashGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pMashGame;
}

//=======================
// 数値の設定
//=======================
void CButtonMash::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//桁数分回す
		if (m_pNumber[i] != nullptr)
		{//nullじゃないなら
		 //桁数を計算
			int nDigit = (int)(log10(m_nMashCounter) + 1);

			//ナンバーの描画を有効・無効にする
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nMashCounter == 0)
			{//コンボ数が0なら
			 //ナンバーの描画を有効・無効にする
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//powで桁数を出す。
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//桁ごとの値を求める
			m_aPosTexU[i] = (m_nMashCounter % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}
