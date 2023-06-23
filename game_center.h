//=============================================================================
//
// ゲームセンタークラス(game_center.h)
// Author : 唐�ｱ結斗
// 概要 : ゲームセンター生成を行う
//
//=============================================================================
#ifndef _GAME_CENTER_H_			// このマクロ定義がされてなかったら
#define _GAME_CENTER_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "objectX.h"
#include "mini_game_basis.h"

//--------------------------------
// 前方宣言
//--------------------------------
class CPlayer;
class CMiniGameBasis;

//=============================================================================
// ゲームセンタークラス
// Author : 唐�ｱ結斗
// 概要 : ゲームセンター生成を行うクラス
//=============================================================================
class CGameCenter : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CGameCenter *Create();	// ゲームセンターの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CGameCenter();
	~CGameCenter();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;												// 初期化
	void Uninit() override;																// 終了
	void Update() override;																// 更新
	void Draw() override;																// 描画
	void SetPlayer(CPlayer *pPlayer) { m_pPlayer = pPlayer; }							// プレイヤーの設定
	void SetGameType(CMiniGameBasis::MiniGameType type) { m_EMiniGameType = type; }		// ゲームタイプの設定
	void SetGame(bool bGame);															// ゲームのプレイ状況の設定
	CPlayer *GetPlayer() { return m_pPlayer; }
	bool GetGame() { return m_bGame; }

private:
	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CMiniGameBasis::MiniGameType m_EMiniGameType;
	CPlayer* m_pPlayer;
	CMiniGameBasis *m_pMiniGameBasis;
	bool m_bGame;
};

#endif


