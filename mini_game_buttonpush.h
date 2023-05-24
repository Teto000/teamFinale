//===================================================
//
// ボタンプッシュゲームヘッダー
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MINI_GAME_BUTTONPUSH_H_
#define _MINI_GAME_BUTTONPUSH_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "mini_game_basis.h"

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_SPEED			(3.0f)	//速度
#define MAX_BUTTONPOLYGON	(3)		//ポリゴンの数

//================================
// ミニゲーム基盤クラス
//================================
class CButtonPushGame : public CMiniGameBasis
{
public:

	enum CLEAR
	{
		CLEAR_NONE = 0,	//透明に入っていない状態
		CLEAR_IN,		//透明状態
		CLEAR_OUT,		//透明じゃない状態
		CLEAR_MAX
	};

	CButtonPushGame();				//コンストラクタ
	~CButtonPushGame() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ変数
	//------------------
	static CButtonPushGame* Create(D3DXVECTOR3 pos);

private:
	//------------------
	// メンバ変数
	//------------------
	CObject2D *pObj2D[MAX_OBJECT];
	D3DXCOLOR m_col[MAX_OBJECT];
	D3DXVECTOR3 m_move;		//移動
	CLEAR m_flash;			//フラッシュ状態
	int m_nCount;			//カウント
	bool m_bStop;			//止まるかどうか
	bool m_bEdge;			//端にたどり着いたかどうか
};

#endif