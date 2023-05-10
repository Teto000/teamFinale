//=============================================================================
//
// プレイヤークラス(player.h)
// Author : 唐�ｱ結斗
// 概要 : プレイヤー生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "player.h"
#include "game.h"
#include "input_keyboard.h"
#include "camera.h"
#include "utility.h"
#include "motion.h"
#include "objectX.h"
#include "move.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NOM_SPEED (1.0f)		// 速度
#define MIN_SPEED (0.09f)		// 最低速度
#define MAX_SPEED (10.0f)		// 最高速度
#define NOM_FRICTION (0.1f)		// 摩擦係数

//=============================================================================
// インスタンス生成
// Author : 唐�ｱ結斗
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
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CPlayer::CPlayer()
{
	m_pMove = nullptr;
	m_nCntRimit = 0;		// 過去に残れる時間を数える
	m_bFuture = false;		//未来にいるかどうか
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
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

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
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
// Author : 唐�ｱ結斗
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

	// 移動
	pos += Move();

	// 位置の設定
	SetPos(pos);

	// 回転
	Rotate();

	// ワープ
	Warp();

	//-----------------------------------
	// オブジェクトとの当たり判定
	//-----------------------------------
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 posOld = GetPosOld();
		D3DXVECTOR3 size(20.0f, 20.0f, 20.0f);

		//オブジェクトの位置を取得
		D3DXVECTOR3 targetPos = CGame::GetObjectX()->GetPosition();

		//当たり判定
		if (CUtility::Collision(pos, posOld, size
			, targetPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f)))
		{// 衝突判定が行われた。

		}

		//位置の更新
		SetPos(pos);
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
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CPlayer::Draw()
{
	// 親クラスの描画
	CMotionModel3D::Draw();
}

//=============================================================================
// 移動
// Author : 唐�ｱ結斗
// 概要 : 移動キーを入力で、指定方向への移動ベクトルを返す
//=============================================================================
D3DXVECTOR3 CPlayer::Move()
{
	// 変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モーション情報の取得
	CMotion *pMotion = CMotionModel3D::GetMotion();

	if ((CInputKeyboard::Press(DIK_W)
		|| CInputKeyboard::Press(DIK_A)
		|| CInputKeyboard::Press(DIK_D)
		|| CInputKeyboard::Press(DIK_S)))
	{// 移動キーが押された
		if (CInputKeyboard::Press(DIK_W))
		{// [W]キーが押された時
			if (CInputKeyboard::Press(DIK_A))
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * -0.25f;
			}
			else if (CInputKeyboard::Press(DIK_D))
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.25f;
			}
			else
			{// 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.0f;
			}
		}
		else if (CInputKeyboard::Press(DIK_S))
		{// [S]キーが押された時
			if (CInputKeyboard::Press(DIK_A))
			{// [A]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * -0.75f;
			}
			else if (CInputKeyboard::Press(DIK_D))
			{// [D]キーが押された時
			 // 移動方向の更新
				m_rotDest.y = D3DX_PI * 0.75f;
			}
			else
			{// 移動方向の更新q
				m_rotDest.y = D3DX_PI;
			}
		}
		else if (CInputKeyboard::Press(DIK_A))
		{// [A]キーが押された時
		 // 移動方向の更新
			m_rotDest.y = D3DX_PI * -0.5f;
		}
		else if (CInputKeyboard::Press(DIK_D))
		{// [D]キーが押された時
		 // 移動方向の更新
			m_rotDest.y = D3DX_PI * 0.5f;
		}

		// カメラ情報の取得
		CCamera *pCamera = CGame::GetCamera(0);

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

		if (m_EAction == NEUTRAL_ACTION)
		{// 移動
			m_EAction = MOVE_ACTION;

			if (pMotion != nullptr)
			{
				pMotion->SetNumMotion(m_EAction);
			}
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
// Author : 唐�ｱ結斗
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
