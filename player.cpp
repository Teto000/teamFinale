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
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CPlayer::CPlayer()
{
	m_pMove = nullptr;
	m_nCntRimit = 0;		// 過去に残れる時間を数える
	m_nNumber = 0;			// プレイヤー番号
	m_bFuture = false;		// 未来にいるかどうか
	m_bMiniGame = false;	// ミニゲーム中かどうか
	m_pMyItem = nullptr;
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

	// ワープ
	Warp();

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
				Retention((CItemObj*)pCollidedObj);
			}
		}
	}

	//当たり判定
	Collision();

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
void CPlayer::Warp()
{
	//-----------------------------
	// 変数宣言
	//-----------------------------
	D3DXVECTOR3 pos = GetPos();	//位置を取得
	int nTimeRimit = 300;		//過去に残れる時間の限界

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
			pos.y = 0.0f;
			SetPos(pos);

			//時間を初期化
			m_nCntRimit = 0;
		}
	}

	//-----------------------------
	// キーを押したときの処理
	// (オブジェクトに触れた時にする予定)
	//-----------------------------
	if (CInputKeyboard::Trigger(DIK_0))
	{//0キーを押したとき
		//-----------------------------
		// 位置の変更
		//-----------------------------
		if (m_bFuture)
		{//未来にいるなら
			//プレイヤーの位置を変更
			pos.y = 300.0f;
		}
		else
		{//過去にいるなら
			pos.y = 0.0f;
		}

		//位置を更新
		SetPos(pos);

		//現在の時代を切り替え
		m_bFuture = !m_bFuture;
	}
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
		//プレイヤーの位置を取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = GetPosOld();
		D3DXVECTOR3 size(20.0f, 20.0f, 20.0f);
		D3DXVECTOR3 targetPos(0.0f, 0.0f, 0.0f);
		CObjectX *pObject = nullptr;

		//--------------------------------
		// オブジェクトの位置を取得
		//--------------------------------
		switch (CApplication::GetMode())
		{//モードごとの処理

		 //----------------------------
		 // ゲーム画面なら
		 //----------------------------
		case CApplication::MODE_GAME:
			pObject = CApplication::GetGame()->GetObjectX();
			targetPos = pObject->GetPosition();

			//--------------------------------
			// 当たり判定
			//--------------------------------
			if (CUtility::Collision(pos, posOld, size
				, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
			{// 衝突判定が行われた。
				if (!m_bMiniGame)
				{
					//ミニゲームの生成
					CMiniGameBasis::Create(D3DXVECTOR3(640.0f, 320.0f, 0.0f), CMiniGameBasis::TYPE_BUTTUNPUSH);
					m_bMiniGame = true;
				}

				//---------------------------------
				// オブジェクトの見た目を変更する
				//---------------------------------
				if (CInputKeyboard::Trigger(DIK_Z))
				{//Zキーが押されたら
					pObject->SetType(10);
				}
			}
			break;

		//----------------------------
		// ステージ選択画面なら
		//----------------------------
		case CApplication::MODE_STAGESELECT:
			pObject = CApplication::GetStage()->GetObjectX();
			targetPos = pObject->GetPosition();
			
			//--------------------------------
			// 当たり判定
			//--------------------------------
			if (CUtility::Collision(pos, posOld, size
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
			break;

		default:
			break;
		}

		//--------------------------------
		// アイテムとの当たり判定
		//--------------------------------
		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
			&& pObject->GetObjType() == CObject::OBJTYPE_ITEM)
		{// 衝突判定が行われた。
			if (CInputKeyboard::Trigger(DIK_H))
			{// アイテムを取得する
				Retention((CItemObj*)pObject);
			}
		}

		//--------------------------------
		// 時計との当たり判定
		//--------------------------------
		pObject = CApplication::GetGame()->GetObjectX();
		targetPos = pObject->GetPosition();

		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f))
			&& pObject->GetObjType() == CObject::OBJTYPE_CLOCK)
		{// 衝突判定が行われた。
			int a = 0;
		}

		//位置の更新
		SetPos(pos);
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
