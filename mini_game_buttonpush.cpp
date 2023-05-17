//===================================================
//
// ミニゲームボタンプッシュ処理
// Author : Kajita Hiromu
//
//===================================================

//----------------------
// インクルード
//----------------------
#include "mini_game_buttonpush.h"
#include "application.h"
#include "renderer.h"

#include "object2D.h"
#include "input_keyboard.h"
#include "application.h"
#include "fade.h"
#include "game.h"
#include "itemObj.h"
#include "player.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

//=======================
// コンストラクタ
//=======================
CButtonPushGame::CButtonPushGame()
{

}

//=======================
// デストラクタ
//=======================
CButtonPushGame::~CButtonPushGame()
{

}

//=======================
// 初期化
//=======================
HRESULT CButtonPushGame::Init(D3DXVECTOR3 pos)
{
	//フラッシュ用カラー変数
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//フラッシュ状態
	m_flash = FLASH_IN;

	//背景用黒ポリゴン
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(1000.0f, 600.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//ボタンポリゴン
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
	pObj2D[1]->SetSize(300.0f, 100.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[1]->SetColor(m_col[1]);

	return S_OK;
}

//=======================
// 終了
//=======================
void CButtonPushGame::Uninit()
{
	
}

//=======================
// 更新
//=======================
void CButtonPushGame::Update()
{
	if (pObj2D[0] != nullptr
		&&pObj2D[1] != nullptr)
	{//オブジェクトがあるなら
		if (m_flash == FLASH_IN)
		{//フラッシュ状態
			m_col[1].a -= 0.03f;	//ポリゴンを透明にしていく

			if (m_col[1].a <= 0.0f)
			{
				m_col[1].a = 0.0f;
				m_flash = FLASH_OUT;	//フラッシュアウト状態
			}
		}
		else if (m_flash == FLASH_OUT)
		{//フラッシュアウト状態
			m_col[1].a += 0.02f;	//ポリゴンを不透明にしていく

			if (m_col[1].a >= 1.0f)
			{
				m_col[1].a = 1.0f;
				m_flash = FLASH_IN;	//フラッシュ状態に

				pObj2D[1]->SetColor(m_col[1]);
			}
		}

		pObj2D[1]->SetColor(m_col[1]);

		//タイミングよくボタンを押したら
		if (m_col[1].a <= 1.0f
			&& m_col[1].a > 0.90f)
		{
			m_col[1].r = 0.0f;

			if (CInputKeyboard::Trigger(DIK_SPACE))
			{//SPACEキーが押された時
				//ポリゴンを全削除してnullptr代入
				pObj2D[0]->Uninit();
				pObj2D[1]->Uninit();
				pObj2D[0] = nullptr;
				pObj2D[1] = nullptr;

				// プレイヤーの取得
				CPlayer *pPlayer = CGame::GetPlayer();
				CItemObj *pPlayerItem = pPlayer->GetMyItem();

				if (pPlayerItem == nullptr)
				{// アイテムを取得していない
					pPlayerItem = CItemObj::Create();
					pPlayerItem->SetType(0);

					// プレイヤーのアイテムの設定
					pPlayer->Acquisition(pPlayerItem);
				}
			}
		}
		else
		{
			m_col[1].r = 1.0f;
		}
	}
}

//=======================
// 描画
//=======================
void CButtonPushGame::Draw()
{
	
}

//=======================
// 生成
// 引数：位置、値、桁数
//=======================
CButtonPushGame *CButtonPushGame::Create(D3DXVECTOR3 pos)
{
	CButtonPushGame *pPushGame= nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pPushGame = new CButtonPushGame;	//生成

	if (pPushGame != nullptr)
	{//NULLチェック

		//初期化
		pPushGame->Init(D3DXVECTOR3(pos));
		pPushGame->SetObjType(OBJTYPE_MINIGAME);
	}

	return pPushGame;
}