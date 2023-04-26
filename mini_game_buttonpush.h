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

//================================
// ミニゲーム基盤クラス
//================================
class CButtonPushGame : public CMiniGameBasis
{
public:

	enum FLASH
	{
		FLASH_NONE = 0,	//フラッシュしていない状態
		FLASH_IN,		//フラッシュ状態
		FLASH_OUT,		//フラッシュアウト状態
		FADE_MAX
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
	CObject2D *pObj2D[2];
	D3DXCOLOR m_col[2];
	FLASH m_flash;			//フラッシュ状態
};

#endif

