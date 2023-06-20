//=============================================================================
//
// プレイヤークラス(player.h)
// Author : 唐﨑結斗
// 概要 : プレイヤー生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <vector>

#include "player.h"
#include "game.h"
#include "stage_select.h"
#include "input_keyboard.h"
#include "camera.h"
#include "utility.h"
#include "motion.h"
#include "objectX.h"
#include "move.h"
#include "itemObj.h"
#include "mini_game_basis.h"
#include "collision_rectangle3D.h"
#include "debug_proc.h"
#include "application.h"
#include "fade.h"
#include "line.h"
#include "game_center.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NOM_SPEED (1.0f)		// 速度
#define MIN_SPEED (0.09f)		// 最低速度
#define MAX_SPEED (10.0f)		// 最高速度
#define NOM_FRICTION (0.1f)		// 摩擦係数

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 3Dモデルを生成する
//=============================================================================
CPlayer * CPlayer::Create()
{
	// オブジェクトインスタンス
	CPlayer *pPlayer = nullptr;

	// メモリの解放
	pPlayer = new CPlayer;

	// メモリの確保ができなかった
	assert(pPlayer != nullptr);

	// 数値の初期化
	pPlayer->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// インスタンスを返す
	return pPlayer;
}

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CPlayer::m_bFuture = false;	// 未来にいるかどうか
bool CPlayer::m_bWarp = false;		// ワープする状態かどうか

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CPlayer::CPlayer()
{
	m_pMove = nullptr;
	m_nCntRimit = 0;		// 過去に残れる時間を数える
	m_nNumber = 0;			// プレイヤー番号
	m_bMiniGame = false;	// ミニゲーム中かどうか
	m_pMyItem = nullptr;	// アイテム所持情報
	m_bCrate = false;		// ビルが建ったかどうか
	m_pLine = nullptr;		// ライン情報
	lineCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);// ラインの色
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	// 親クラスの初期化
	CMotionModel3D::Init(pos);

	if (m_pMove == nullptr)
	{// 移動
		m_pMove = new CMove;
		assert(m_pMove != nullptr);
	}

	// 移動情報の初期化
	m_pMove->SetMoving(NOM_SPEED, MAX_SPEED, MIN_SPEED, NOM_FRICTION);
	m_nParentParts = 3;

	// ラインの生成
	m_pLine = new CLine*[4];

	for (int nCntLine = 0; nCntLine < 4; nCntLine++)
	{
		m_pLine[nCntLine] = CLine::Create();
	}

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CPlayer::Uninit()
{
	if (m_pMove != nullptr)
	{// 終了処理
	 // メモリの解放
		delete m_pMove;
		m_pMove = nullptr;
	}

	// 親クラスの終了
	CMotionModel3D::Uninit();

	// ラインの終了処理
	if (m_pLine != nullptr)
	{
		for (int nCntLine = 0; nCntLine < 4; nCntLine++)
		{
			m_pLine[nCntLine]->Uninit();
			m_pLine[nCntLine] = nullptr;
		}

		delete[] m_pLine;
		m_pLine = nullptr;
	}

	// オブジェクト3Dの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CPlayer::Update()
{
	// モーション情報の取得
	CMotion *pMotion = CMotionModel3D::GetMotion();

	// 位置の取得
	D3DXVECTOR3 pos = GetPos();

	// 過去位置の更新
	SetPosOld(pos);

	//----------------------------
	// 移動
	//----------------------------
	switch (m_nNumber)
	{
	case 0:
		pos += Move(DIK_W, DIK_S, DIK_A, DIK_D);
		break;

	case 1:
		pos += Move(DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT);
		break;

	default:
		break;
	}

	// 位置の設定
	SetPos(pos);

	// 回転
	Rotate();

	// アイテムを所持していたら
	if (m_pMyItem != nullptr)
	{
		const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ラインの設定
		m_pLine[0]->SetLine(D3DXVECTOR3(0.0f,0.0f,0.0f), rot, D3DXVECTOR3(-200.0f, 10.0f, 0.0f), D3DXVECTOR3(-50.0f, 10.0f, 0.0f), lineCol);
		m_pLine[1]->SetLine(D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot, D3DXVECTOR3(-200.0f, 10.0f, -150.0f), D3DXVECTOR3(-50.0f, 10.0f, -150.0f), lineCol);
		m_pLine[2]->SetLine(D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot, D3DXVECTOR3(-200.0f, 10.0f, 0.0f), D3DXVECTOR3(-200.0f, 10.0f, -150.0f), lineCol);
		m_pLine[3]->SetLine(D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot, D3DXVECTOR3(-50.0f, 10.0f, 0.0f), D3DXVECTOR3(-50.0f, 10.0f, -150.0f), lineCol);
	}

	////Playerが一定の位置にいる時
	//if (pos.x > -200.0f
	//	&&pos.x < -50.0f
	//	&&pos.z < 0.0f
	//	&&pos.z > -150.0f)
	//{
	//	if (m_pMyItem != nullptr)
	//	{// アイテムを取得している
	//		if (CInputKeyboard::Trigger(DIK_F)
	//			&& !m_bCrate)
	//		{//アイテムを置くと建物が生成される
	//			CObjectX *m_pObj = CObjectX::Create();
	//			m_pObj->SetType(10);
	//			m_pObj->SetPos(D3DXVECTOR3(-600.0f, 0.0f, 300.0f));
	//			m_bCrate = true;

	//			//リザルト画面に移行
	//			CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
	//		}
	//	}
	//}

	// Playerの位置のデバッグ表示
	CDebugProc::Print("pos：%f,%f,%f", pos.x, pos.y, pos.z);

	//当たり判定
	Collision();

	if (CInputKeyboard::Trigger(DIK_F))
	{// アイテムの保持の解除
		Drop();
	}

	// 当たり判定の取得
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->Collision(CObject::OBJTYPE_NONE, true);

	// 当たったオブジェクトのリストを取得
	std::vector<CObject*> apCollidedObj = pCollision->GetCollidedObj();

	if (apCollidedObj.size() > 0)
	{// 当たったオブジェクトとの処理
		for (int nCntObj = 0; nCntObj < apCollidedObj.size(); nCntObj++)
		{
			CObject *pCollidedObj = apCollidedObj.at(nCntObj);

			if (pCollidedObj->GetObjType() == CObject::OBJTYPE_ITEM
				&& CInputKeyboard::Trigger(DIK_H))
			{// アイテムを保持しておらす、アイテムオブジェクトに触れていた場合取得
				if (m_pMyItem != nullptr)
				{
					m_pMyItem->Stack((CItemObj*)pCollidedObj);
					break;
				}
				else
				{// アイテムを取得する
					Retention((CItemObj*)pCollidedObj);
					break;
				}
			}
			else if (pCollidedObj->GetObjType() == CObject::OBJTYPE_MINIGAME)
			{// ゲームセンターに触れている
				CGameCenter *pGameCenter = (CGameCenter*)pCollidedObj;

				if (CInputKeyboard::Trigger(DIK_SPACE)
					&& !pGameCenter->GetGame())
				{
					pGameCenter->SetPlayer(this);
					pGameCenter->SetGame(true);
				}
			}
		}
	}

	if (pMotion != nullptr
		&& !pMotion->GetMotion())
	{// ニュートラルモーションの設定
		m_EAction = NEUTRAL_ACTION;
		pMotion->SetNumMotion(m_EAction);
	}

	// 親クラスの更新
	CMotionModel3D::Update();
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CPlayer::Draw()
{
	// 親クラスの描画
	CMotionModel3D::Draw();
}

//=============================================================================
// ゲーム中の設定処理
// Author : 梶田大夢
// 概要 : ゲーム中かどうかの設定を行う
//=============================================================================
void CPlayer::SetMiniGame(bool bMiniGame)
{
	m_bMiniGame = bMiniGame;
}

//=============================================================================
// アイテムの取得処理
// Author : 唐﨑結斗
// 概要 : 自分がアイテムを持っていなかったら、アイテムを取得する
//=============================================================================
void CPlayer::Retention(CItemObj * pItem)
{
	// モーション情報の取得
	CMotion *pMotion = CMotionModel3D::GetMotion();

	if (m_pMyItem == nullptr)
	{// アイテムを所持していない
		CModel3D *pParts = (CModel3D*)pMotion->GetParts(m_nParentParts);
		m_pMyItem = pItem;
		m_pMyItem->SetParent(pParts);
	}
}

//=============================================================================
// 移動
// Author : 唐﨑結斗
// 概要 : 移動キーを入力で、指定方向への移動ベクトルを返す
// 引数 : 上下左右キー
//=============================================================================
D3DXVECTOR3 CPlayer::Move(int nUpKey, int nDownKey, int nLeftKey, int nRightKey)
{
	// 変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モーション情報の取得
	CMotion *pMotion = CMotionModel3D::GetMotion();

	if (!m_bMiniGame
		&& (CInputKeyboard::Press(nUpKey)
			|| CInputKeyboard::Press(nLeftKey)
			|| CInputKeyboard::Press(nRightKey)
			|| CInputKeyboard::Press(nDownKey)))
	{// 移動キーが押された
		if (CInputKeyboard::Press(nUpKey))
		{// [W]キーが押された時
			if (CInputKeyboard::Press(nLeftKey))
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * -0.25f;
			}
			else if (CInputKeyboard::Press(nRightKey))
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (CInputKeyboard::Press(nDownKey))
		{// [S]キーが押された時
			if (CInputKeyboard::Press(nLeftKey))
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * -0.75f;
			}
			else if (CInputKeyboard::Press(nRightKey))
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新q
				m_rotDest.y = D3DX_PI;
			}
		}
		else if (CInputKeyboard::Press(nLeftKey))
		{// [A]キーが押された時
		 // 移動方向の更新
			m_rotDest.y = D3DX_PI * -0.5f;
		}
		else if (CInputKeyboard::Press(nRightKey))
		{// [D]キーが押された時
		 // 移動方向の更新
			m_rotDest.y = D3DX_PI * 0.5f;
		}

		//-----------------------------------
		// カメラ情報の取得
		//-----------------------------------
		CCamera* pCamera = nullptr;
		switch (CApplication::GetMode())
		{//モードごとの処理
		 //ゲーム画面なら
		case CApplication::MODE_GAME:
			pCamera = CGame::GetCamera();
			break;

			//ステージ選択画面なら
		case CApplication::MODE_STAGESELECT:
			pCamera = CApplication::GetStage()->GetCamera();
			break;

		default:
			break;
		}

		// 移動方向の算出
		m_rotDest.y += pCamera->GetRot().y;

		// 移動方向の正規化
		m_rotDest.y = CUtility::GetNorRot(m_rotDest.y);

		// 移動量の計算
		move = D3DXVECTOR3(sinf(m_rotDest.y), 0.0f, cosf(m_rotDest.y));

		// 角度の正規化
		m_rotDest.y -= D3DX_PI;

		// 移動方向の正規化
		m_rotDest.y = CUtility::GetNorRot(m_rotDest.y);

		if (pMotion != nullptr
			&& m_EAction == NEUTRAL_ACTION)
		{// 移動
			m_EAction = MOVE_ACTION;
			pMotion->SetNumMotion(m_EAction);
		}
	}

	// 移動情報の計算
 	m_pMove->Moving(move);

	// 移動情報の取得
	D3DXVECTOR3 moveing = m_pMove->GetMove();
	float fLength = m_pMove->GetMoveLength();

	if (fLength <= 0.0f
		&& pMotion != nullptr
		&& m_EAction == MOVE_ACTION)
	{
		m_EAction = NEUTRAL_ACTION;
		pMotion->SetNumMotion(m_EAction);
	}

	// 向きの取得
	D3DXVECTOR3 rot = GetRot();

	// 目的の向きの補正
	if (m_rotDest.y - rot.y >= D3DX_PI)
	{// 移動方向の正規化
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - rot.y <= -D3DX_PI)
	{// 移動方向の正規化
		m_rotDest.y += D3DX_PI * 2;
	}

	return moveing;
}

//=============================================================================
// 回転
// Author : 唐﨑結斗
// 概要 : 目的の向きまで回転する
//=============================================================================
void CPlayer::Rotate()
{
	// 向きの取得
	D3DXVECTOR3 rot = GetRot();
	float fFriction = 0.5f;

	// 向きの更新
	rot.y += (m_rotDest.y - rot.y) * fFriction;

	// 向きの正規化
	rot.y = CUtility::GetNorRot(rot.y);

	// 向きの設定
	SetRot(rot);
}

//=============================================================================
// ワープ
// Author : 佐藤輝翔
// 概要 : 現在の情報(過去・未来)に合わせて指定の位置までワープする
//=============================================================================
D3DXVECTOR3 CPlayer::Warp(D3DXVECTOR3 pos)
{
	//-----------------------------
	// 変数宣言
	//-----------------------------
	CCamera* pCamera = CApplication::GetGame()->GetCamera();
	/*int nTimeRimit = 300;		//過去に残れる時間の限界

	//-----------------------------
	// タイムリミットの処理
	//-----------------------------
	if (!m_bFuture)
	{//過去にいるなら
		//時間を数える
		m_nCntRimit++;

		if (m_nCntRimit >= nTimeRimit)
		{//時間が限界地を超えたら
			//未来に送る
			m_bFuture = true;

			//位置を更新
			pos.x = 0.0f;
			SetPos(pos);

			//カメラの位置の設定
			pCamera->SetPosV(D3DXVECTOR3(0.0f, 200.0f, -400.0f));
			pCamera->SetPosR(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

			//時間を初期化
			m_nCntRimit = 0;
		}
	}*/

	//-----------------------------
	// キーを押したときの処理
	//-----------------------------
	if (!m_bFuture)
	{//未来にいるなら
		pos = D3DXVECTOR3(1000.0f, pos.y, 0.0f);	//プレイヤーの位置を変更

		//カメラの位置の設定
		pCamera->SetPosV(D3DXVECTOR3(1000.0f, 200.0f, -400.0f));
		pCamera->SetPosR(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));
	}
	else
	{//過去にいるなら
		pos = D3DXVECTOR3(0.0f, pos.y, 0.0f);
		pCamera->SetPosV(D3DXVECTOR3(0.0f, 200.0f, -400.0f));
		pCamera->SetPosR(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	}

	m_bFuture = !m_bFuture;		//現在の時代を切り替え

	m_bWarp = true;				//ワープする状態にする

	return pos;
}

//=============================================================================
// 当たり判定の処理
// 概要 : 当たり判定の処理をまとめた関数
//=============================================================================
void CPlayer::Collision()
{
	//-----------------------------------
	// オブジェクトとの当たり判定
	//-----------------------------------
	{
		//変数宣言
		D3DXVECTOR3 size(20.0f, 20.0f, 20.0f);	//プレイヤーの大きさ
		D3DXVECTOR3 targetPos(0.0f, 0.0f, 0.0f);
		CObjectX *pObject = nullptr;			//オブジェクト

		//--------------------------------
		// オブジェクトの位置を取得
		//--------------------------------
		switch (CApplication::GetMode())
		{//モードごとの処理

		 //----------------------------
		 // ゲーム画面なら
		 //----------------------------
		case CApplication::MODE_GAME:
			for (int i = 0; i < CGame::GetMaxObject(); i++)
			{//オブジェクト数分回す
				//オブジェクトを取得
				pObject = CApplication::GetGame()->GetObjectX(i);

				/* ↓ オブジェクトの種類ごとの当たり判定 ↓ */
				Coll_Pavilion(size, pObject);	//東屋
				Coll_Item(size, pObject);;		//アイテム
				Coll_Clock(size, pObject);		//時計
			}
			break;

			//----------------------------
			// ステージ選択画面なら
			//----------------------------
		case CApplication::MODE_STAGESELECT:
			pObject = CApplication::GetStage()->GetObjectX();
			targetPos = pObject->GetPosition();

			if (pObject != nullptr)
			{
				//--------------------------------
				// 当たり判定
				//--------------------------------
				if (CUtility::Collision(GetPos(), GetPosOld(), size
					, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
				{// 衝突判定が行われた。
					CStageSelect::SetViewMap(true);		//マップを表示する状態
					CStageSelect::SetStart(true);		//画面遷移出来る状態
				}
				else
				{
					CStageSelect::SetViewMap(false);	//マップを表示しない状態
					CStageSelect::SetStart(false);		//画面遷移出来ない状態
				}
			}
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// 東屋との当たり判定
// Author : Sato Teruto
// 概要 : 東屋との当たり判定処理をまとめた関数
//=============================================================================
void  CPlayer::Coll_Pavilion(D3DXVECTOR3 size, CObjectX* pObject)
{
    //相手の位置を取得
    D3DXVECTOR3 targetPos = pObject->GetPosition();

    //--------------------------------
    // 東屋との当たり判定
    //--------------------------------
    if (CUtility::Collision(GetPos(), GetPosOld(), size
        , targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
        && pObject->GetObjType() == CObject::OBJTYPE_PAVILION)
    {// 衝突判定が行われた。
        if (CInputKeyboard::Trigger(DIK_SPACE))
        {
            int randData;
            randData = rand() % 1;

            // ミニゲーム中じゃないなら
            if (!m_bMiniGame)
            {
                //ミニゲームの生成&ミニゲーム中に設定する
                CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), randData);
                m_bMiniGame = true;
            }
        }
    }

    //--------------------------------
    // 壊れた東屋との当たり判定
    //--------------------------------
    if (CUtility::Collision(GetPos(), GetPosOld(), size
        , targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
        && pObject->GetObjType() == CObject::OBJTYPE_PAVILION_BREAK
        && m_pMyItem != nullptr)
    {// 衝突判定が行われた & アイテムを持っているなら
        if (CInputKeyboard::Trigger(DIK_F))
        {//アイテムを置いたら
            //東屋を直す
            pObject->SetType(18);

            //リザルト画面に移行
            CApplication::GetFade()->SetFade(CApplication::MODE_RESULT);
        }
    }
}

//=============================================================================
// アイテムとの当たり判定
// Author : Sato Teruto
// 概要 : アイテムとの当たり判定処理をまとめた関数
//=============================================================================
void  CPlayer::Coll_Item(D3DXVECTOR3 size, CObjectX* pObject)
{
	//相手の位置を取得
	D3DXVECTOR3 targetPos = pObject->GetPosition();

	if (CUtility::Collision(GetPos(), GetPosOld(), size
		, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
		&& pObject->GetObjType() == CObject::OBJTYPE_ITEM)
	{// 衝突判定が行われた。
		if (CInputKeyboard::Trigger(DIK_H))
		{
			if (m_pMyItem != nullptr)
			{
				m_pMyItem->Stack((CItemObj*)pObject);
			}
			else
			{// アイテムを取得する
				Retention((CItemObj*)pObject);
			}
		}
	}
}
		
//=============================================================================
// 時計との当たり判定
// Author : Sato Teruto
// 概要 : 時計との当たり判定処理をまとめた関数
//=============================================================================
void CPlayer::Coll_Clock(D3DXVECTOR3 size, CObjectX* pObject)
{
	//変数宣言
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posOld = GetPosOld();
	D3DXVECTOR3 targetPos = pObject->GetPosition();
	D3DXVECTOR3 newPos(0.0f, 0.0f, 0.0f);

	if (CUtility::Collision(pos, posOld, size
		, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
		&& pObject->GetObjType() == CObject::OBJTYPE_CLOCK)
	{// 衝突判定が行われた。
		if (CInputKeyboard::Trigger(DIK_SPACE) && !m_bWarp)
		{//0キーを押したとき & ワープしない状態なら
			//ワープ
			newPos = Warp(pos);
		}
	}

	//位置の更新
	SetPos(pos);

	if (m_bWarp)
	{//ワープする状態なら
		//位置を更新
		for (int i = 0; i < CGame::GetMaxPlayer(); i++)
		{
			CGame::GetPlayer(i)->SetPos(newPos);
		}

		m_bWarp = false;	//ワープしない状態
	}
}

//=============================================================================
// アイテムの保持解除
// Author : 唐﨑結斗
// 概要 : アイテムの保持を解除する
//=============================================================================
void CPlayer::Drop()
{
	if (m_pMyItem != nullptr)
	{
		// 親設定の放棄
		m_pMyItem->SetParent();

		// 当たり判定の設定
		CCollision_Rectangle3D* pItemCollision = m_pMyItem->GetCollision();
		pItemCollision->SetUseFlag(true);

		m_pMyItem = nullptr;
	}
}
