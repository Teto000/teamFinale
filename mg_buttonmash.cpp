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

#include "input_keyboard.h"
#include "object2D.h"
#include "game.h"

#include "itemObj.h"
#include "player.h"

//=======================
// コンストラクタ
//=======================
CButtonMash::CButtonMash()
{
	
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
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カラー変数
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_col[2] = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f);

	//背景用黒ポリゴン
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(780.0f, 350.0f, 0.0f));
	pObj2D[0]->SetSize(300.0f, 50.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//ボタン連打画像
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(300.0f, 300.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_BUTTON);
	pObj2D[1]->SetColor(m_col[1]);
	pObj2D[1]->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

	//ライフ用ポリゴン
	for (int nCnt = 0; nCnt < MAX_LIFEPOLYGON; nCnt++)
	{
		pLife[nCnt] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
		pLife[nCnt]->SetSize(10.0f, 40.0f);
		pLife[nCnt]->SetTexture(CTexture::TEXTURE_NONE);
		pLife[nCnt]->SetColor(m_col[3]);
	}

	//アニメーション用変数
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//数字カウント用変数
	m_nMashCounter = -1;		//カウント数

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
	if (pObj2D[0] != nullptr
		&&pLife[0] != nullptr)
	{
		//カウンターを加算
		m_nCounterAnim++;

		if ((m_nCounterAnim % 10) == 0)
		{//10フレーム経過
			//テクスチャのアニメーション
			pObj2D[1]->SetSplitTex(1.0f, 1.0f, 2.0f, (float)m_nPatternAnim);

			//パターンNo.を更新する
			m_nPatternAnim++;
		}

		if (CInputKeyboard::Trigger(DIK_SPACE))
		{//Jキーを押したときに
			//連打カウントを1増やす
			m_nMashCounter++;
		}

		//連打するたびにポリゴンに色を付ける
		if (m_nMashCounter != -1)
		{
			m_col[2].a = 1.0f;
			pLife[m_nMashCounter]->SetColor(m_col[2]);
			pLife[m_nMashCounter]->SetPos(D3DXVECTOR3(640.0f + (10.0f * m_nMashCounter), 350.0f, 0.0f));
		}

		if (m_nMashCounter >= MAX_LIFEPOLYGON - 1)
		{//連打数がライフポリゴン数を超えたら
		 //オブジェクト破棄
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			for (int nCnt = 0; nCnt < MAX_LIFEPOLYGON; nCnt++)
			{
				pLife[nCnt]->Uninit();
				pLife[nCnt] = nullptr;
			}

			//CGame *pGame = CApplication::GetGame();
			//CPlayer *pPlayer[2] = {};
			//CItemObj *pPlayerItem = {};

			//for (int nCnt = 0; nCnt < pGame->GetMaxPlayer(); nCnt++)
			//{
			//	//プレイヤー情報の取得
			//	pPlayer[nCnt] = pGame->GetPlayer(nCnt);

			//	if (pPlayerItem == nullptr)
			//	{// アイテムを取得していない
			//		pPlayerItem = CItemObj::Create();
			//		pPlayerItem->SetType(0);
			//	}

			//	pPlayer[nCnt]->Retention(pPlayerItem);		// プレイヤーのアイテムの設定
			//}
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
