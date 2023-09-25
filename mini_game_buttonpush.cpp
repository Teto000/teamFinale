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
#include "game.h"
#include "debug_proc.h"

#include "object2D.h"
#include "input.h"
#include "input_joypad.h"
#include "input_keyboard.h"
#include "fade.h"
#include "game.h"
#include "motion.h"
#include "model3D.h"

#include "itemObj.h"
#include "player.h"
#include "collision_rectangle3D.h"
#include "game_center.h"
#include "utility.h"

//=======================
// コンストラクタ
//=======================
CButtonPushGame::CButtonPushGame()
{
	m_nCount = 0;			//カウント
	m_nCntPlayTime = 0;		//操作出来るまでの時間を数える
	m_bStop = false;		//止まるかどうか
	m_bEdge = false;		//端にたどり着いたかどうか
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
	m_bOnce = false;
	m_nCount = 0;

	//背景用黒ポリゴン
	pObj2D[0] = CBillBoard::Create(D3DXVECTOR3(640.0f,350.0f,0.0f));
	pObj2D[0]->SetSize(150.0f, 70.0f);
	pObj2D[0]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[0]->SetColor(m_col[0]);

	//ゲージ画像
	pObj2D[1] = CBillBoard::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	pObj2D[1]->SetSize(150.0f, 45.0f);
	pObj2D[1]->SetTexture(CTexture::TEXTURE_GAUGE);
	pObj2D[1]->SetColor(m_col[1]);

	//ボタンポリゴン
	pObj2D[2] = CBillBoard::Create(D3DXVECTOR3(750.0f, 350.0f, 0.0f));
	pObj2D[2]->SetSize(5.0f, 40.0f);
	pObj2D[2]->SetTexture(CTexture::TEXTURE_NONE);
	pObj2D[2]->SetColor(m_col[2]);

	return S_OK;
}

//=======================
// 終了
//=======================
void CButtonPushGame::Uninit()
{
	m_nCntPlayTime = 0;
}

//=======================
// 更新
//=======================
void CButtonPushGame::Update()
{
	//オブジェクトがあるなら
	if (pObj2D[0] != nullptr
		&& pObj2D[1] != nullptr)
	{
		CGameCenter *pParent = GetParent();
		CPlayer *pPlayer = pParent->GetPlayer();
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 ObjPos = pObj2D[1]->GetPosition();
		float ObjSize = pObj2D[1]->GetWidth();

		if (!m_bOnce)
		{
			pObj2D[2]->SetPos(PlayerPos);
			m_bOnce = true;
		}

		//操作可能までの時間を数える
		m_nCntPlayTime++;

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
				if (pos.x >= ObjPos.x + ObjSize / 2)
				{
					m_move.x *= -1.0f;
					m_bEdge = true;
				}

				//移動量を設定
				m_move.x += MAX_SPEED;
			}
			else
			{
				if (pos.x <= ObjPos.x - ObjSize / 2)
				{
					m_move.x *= -1.0f;
					m_bEdge = false;
				}

				//移動量を設定
				m_move.x -= MAX_SPEED;
			}

			//移動
			pos += m_move;

			pObj2D[0]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 150.0f, PlayerPos.z));
			pObj2D[1]->SetPos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 150.0f, PlayerPos.z));
			pObj2D[2]->SetPos(D3DXVECTOR3(pos.x, PlayerPos.y + 150.0f, PlayerPos.z));

			GameUpdate();
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
// ミニゲームの更新処理
//=======================
void CButtonPushGame::GameUpdate()
{
	CGameCenter *pParent = GetParent();
	CPlayer *pPlayer = pParent->GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 ObjPos = pObj2D[1]->GetPosition();

	//位置の取得
	D3DXVECTOR3 pos = pObj2D[2]->GetPosition();

#ifdef _DEBUG
	if (CInputKeyboard::Trigger(DIK_SPACE)
		&& m_nCntPlayTime > nMaxPlayTime)
	{//SPACEキーが押された時 & 操作可能時間に達していたら
	 //バーが真ん中の時
		if (pos.x >= ObjPos.x - SUCCESS_RANGE
			&& pos.x <= ObjPos.x + SUCCESS_RANGE)
		{
			//ポリゴンを全削除してnullptr代入
			for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			//プレイヤーをゲーム中状態から解除する
			CGame *pGame = CMode::GetGame();

			//プレイヤーがミニゲームを終了する時
			if (GetGame())
			{
				SetGame(false);
			}
		}
		else
		{
			m_bStop = true;
		}
	}
#endif // _DEBUG
	CInputJoypad *pJoypad = CInput::GetJoypad();

	if (pJoypad->Trigger(CInputJoypad::JOYKEY_B)
		&& m_nCntPlayTime > nMaxPlayTime)
	{//SPACEキーが押された時 & 操作可能時間に達していたら
	 //バーが真ん中の時
		if (pos.x >= ObjPos.x - SUCCESS_RANGE
			&& pos.x <= ObjPos.x + SUCCESS_RANGE)
		{
			//ポリゴンを全削除してnullptr代入
			for (int nCnt = 0; nCnt < MAX_BUTTONPOLYGON; nCnt++)
			{
				pObj2D[nCnt]->Uninit();
				pObj2D[nCnt] = nullptr;
			}

			//プレイヤーをゲーム中状態から解除する
			CGame *pGame = CMode::GetGame();

			//プレイヤーがミニゲームを終了する時
			if (GetGame())
			{
				SetGame(false);
			}
		}
		else
		{
			m_bStop = true;
		}
	}
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