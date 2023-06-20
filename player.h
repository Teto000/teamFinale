//=============================================================================
//
// プレイヤークラス(player.h)
// Author : 唐�ｱ結斗
// 概要 : プレイヤー生成を行う
//
//=============================================================================
#ifndef _PLAYER_H_			// このマクロ定義がされてなかったら
#define _PLAYER_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "motion_model3D.h"

//--------------------------------
// 前方宣言
//--------------------------------
class CMove;
class CObjectX;
class CObject2D;
class CItemObj;
class CLine;

//=============================================================================
// プレイヤークラス
// Author : 唐�ｱ結斗
// 概要 : プレイヤー生成を行うクラス
//=============================================================================
class CPlayer : public CMotionModel3D
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CPlayer *Create();			// プレイヤーの生成

	//--------------------------------------------------------------------
	// プレイヤーのアクションの列挙型
	//--------------------------------------------------------------------
	enum ACTION_TYPE
	{
		// 通常
		NEUTRAL_ACTION = 0,		// ニュートラル
		MOVE_ACTION,			// 移動
		ATTACK_ACTION,			// 攻撃
		ATTACK_JUMP,			// ジャンプ
		ATTACK_LANDING,			// 着地 
		MAX_ACTION,				// 最大数
	};

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CPlayer();
	~CPlayer();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;		// 初期化
	void Uninit() override;						// 終了
	void Update() override;						// 更新
	void Draw() override;						// 描画
	void Retention(CItemObj *pItem);			// アイテム保持
	void Drop();								// アイテムの保持解除

	// セッター
	void SetNumber(int nNum) { m_nNumber = nNum; }	// プレイヤー番号の設定
	void SetMiniGame(bool bMiniGame);				// ミニゲーム中かどうかの設定

	// ゲッター
	CItemObj* GetMyItem() { return m_pMyItem; }			// 取得アイテムのゲッター
	int GetParentParts() { return m_nParentParts; }		// 親パーツのゲッター
	bool GetMiniGame() { return m_bMiniGame; }			// ミニゲーム中かどうかの取得

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	D3DXVECTOR3 Move(int nUpKey, int nDownKey
					, int nLeftKey, int nRightKey);		// 移動
	void Rotate();			// 回転
	D3DXVECTOR3 Warp(D3DXVECTOR3 pos);		// ワープ
	void Collision();		// 当たり判定

	/* ↓ オブジェクトごとの当たり判定 ↓ */
	void Coll_Pavilion(D3DXVECTOR3 size, CObjectX* pObject);	// 東屋
	void Coll_Item(D3DXVECTOR3 size, CObjectX* pObject);		// アイテム
	void Coll_Clock(D3DXVECTOR3 size, CObjectX* pObject);		// 時計

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMove *m_pMove;				// 移動情報
	CItemObj *m_pMyItem;		// 所持アイテム
	ACTION_TYPE m_EAction;		// アクションタイプ
	D3DXVECTOR3 m_rotDest;		// 目的の向き
	int m_nNumMotion;			// 現在のモーション番号
	int m_nCntRimit;			// 過去に残れる時間を数える
	int m_nParentParts;			// 親パーツの番号
	int m_nNumber;				// プレイヤー番号
	bool m_bMiniGame;			// ミニゲーム中かどうか

	//--------------------------------------------------------------------
	// 静的メンバ変数
	//--------------------------------------------------------------------
	static bool m_bFuture;		// 未来にいるかどうか
	CLine **m_pLine;			// ラインの情報
	D3DXCOLOR lineCol;			// ラインの色
	bool m_bCrate;				// ビルが建ったか
	static bool m_bWarp;		// ワープする状態かどうか
};

#endif
