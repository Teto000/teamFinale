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
#include "fade.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

#include "itemObj.h"
#include "player.h"
#include "collision_rectangle3D.h"

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
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//フラッシュ用カラー変数
	m_col[0] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	m_col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//フラッシュ状態
	m_flash = CLEAR_IN;

	//端までいったかどうか
	m_bEdge = false;
	m_bStop = false;
	m_nCount = 0;

	//背景用黒ポリゴン
	pObj2D[0] = CObject2D::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(1000.0f, 600.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//ゲージ画像
	pObj2D[1] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(900.0f, 250.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_GAUGE);
	pObj2D[1]->SetColor(m_col[1]);

	//ボタンポリゴン
	pObj2D[2] = CObject2D::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[2]->SetSize(25.0f, 300.0f);
	pObj2D[2]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[2]->SetColor(m_col[2]);

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
	//オブジェクトがあるなら
	if (pObj2D[0] != nullptr
		&&pObj2D[1] != nullptr)
	{
		if (!m_bStop)
		{
			//位置の取得
			D3DXVECTOR3 pos = pObj2D[2]->GetPosition();

			//移動量の最大値を設定
			if (m_move.x <= -MAX_SPEED)
			{
				m_move.x = -MAX_SPEED;
			}
			else if (m_move.x >= MAX_SPEED)
			{
				m_move.x = MAX_SPEED;
			}

			//端まで行ったら反射
			if (!m_bEdge)
			{
				if (pos.x >= 1080.0f)
				{
					m_move.x *= -1.0f;
					m_bEdge = true;
				}

				//移動量を設定
				m_move.x += MAX_SPEED;
			}
			else
			{
				if (pos.x <= 200.0f)
				{
					m_move.x *= -1.0f;
					m_bEdge = false;
				}

				//移動量を設定
				m_move.x -= MAX_SPEED;
			}

			//移動
			pos += m_move;
			pObj2D[2]->SetPos(pos);

			if (CInputKeyboard::Trigger(DIK_SPACE))
			{//SPACEキーが押された時
			 //バーが真ん中の時
				if (pos.x >= 615.0f
					&& pos.x <= 665.0f)
				{
					//ポリゴンを全削除してnullptr代入
					for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
					{
						pObj2D[nCnt]->Uninit();
						pObj2D[nCnt] = nullptr;
					}

					//プレイヤーをゲーム中状態から解除する
					CGame *pGame = CApplication::GetGame();
					CPlayer *pPlayer[2] = {};
					CItemObj *pPlayerItem = {};

					for (int nCnt = 0; nCnt < pGame->GetMaxPlayer(); nCnt++)
					{
						//プレイヤー情報の取得
						pPlayer[nCnt] = pGame->GetPlayer(nCnt);

						if (pPlayerItem == nullptr)
						{// アイテムを取得していない
							pPlayerItem = CItemObj::Create();
							pPlayerItem->SetType(0);

							// 当たり判定の設定
							CCollision_Rectangle3D *pCollision = pPlayerItem->GetCollision();
							pCollision->SetSize(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
							pCollision->SetPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
							pCollision->SetUseFlag(false);
						}

						//プレイヤーがミニゲームを終了する時
						if (pPlayer[nCnt]->GetMiniGame() == true)
						{
							D3DXVECTOR3 PlayerPos = pPlayer[nCnt]->GetPos();
							pPlayer[nCnt]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 0.5f));
							pPlayer[nCnt]->SetMiniGame(false);	
							pPlayer[nCnt]->Retention(pPlayerItem);		// プレイヤーのアイテムの設定
						}
					}
				}
				else
				{
					m_bStop = true;
				}
			}
		}
		else if (m_bStop)
		{
			m_nCount++;

			if (m_flash == CLEAR_IN)
			{//透明状態
				m_col[2].a -= 0.5f;	//ポリゴンを透明にしていく

				if (m_col[2].a <= 0.0f)
				{
					m_col[2].a = 0.0f;
					m_flash = CLEAR_OUT;	//透明じゃない状態
				}
			}
			else if (m_flash == CLEAR_OUT)
			{//透明じゃない状態
				m_col[2].a += 0.5f;	//ポリゴンを不透明にしていく

				if (m_col[2].a >= 1.0f)
				{
					m_col[2].a = 1.0f;
					m_flash = CLEAR_IN;	//透明状態に

					pObj2D[2]->SetColor(m_col[2]);
				}
			}

			if (m_nCount >= 30)
			{
				m_col[2].a = 1.0f;
				m_bStop = false;
				m_nCount = 0;
			}

			pObj2D[2]->SetColor(m_col[2]);
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