//===================================================
//
// ミニゲーム基盤ヘッダー
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MINI_GAME_BASIS_H_
#define _MINI_GAME_BASIS_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "billboard.h"
#include "itemObj.h"

//-------------------------------
// 前方宣言
//-------------------------------
class CGameCenter;
class CPlayer;

//================================
// ミニゲーム基盤クラス
//================================
class CMiniGameBasis : public CBillBoard
{
public:

	enum MiniGameType		//ミニゲームの種類
	{
		TYPE_NULL = -1,
		TYPE_BUTTUNPUSH = 0,
		TYPE_BUTTONMASH,
		TYPE_STICKROTATE,
		TYPE_MAX
	};

	CMiniGameBasis();				//コンストラクタ
	~CMiniGameBasis() override;		//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// セッター
	//------------------
	void SetScaling(float fWidth, float fHeight);		//拡縮
	void SetEnable(bool bEnable) { m_bDraw = bEnable; }	//描画するかどうか
	void SetParent(CGameCenter *pParent) { m_pParent = pParent; }
	void SetItemType(CItemObj::EItemType type) { m_ItemType = type; }
	void SetGame(bool bGame) { m_bGame = bGame; }
	void SetPlayer(CPlayer *player);

	//------------------
	// ゲッター
	//------------------
	CItemObj::EItemType GetItemType() { return m_ItemType; }
	MiniGameType GetGameType() { return m_nType; }
	CGameCenter *GetParent() { return m_pParent; }
	bool GetGame() { return m_bGame; }
	CPlayer *GetPlayer() { return m_pPlayer; }

	//------------------
	// 静的メンバ変数
	//------------------
	static CMiniGameBasis* Create(D3DXVECTOR3 pos, int nType);

private:
	//------------------
	// メンバ変数
	//------------------
	MiniGameType m_nType;					// ミニゲームの種類
	CGameCenter *m_pParent;					// 親オブジェクト
	CItemObj::EItemType m_ItemType;
	CPlayer *m_pPlayer;						// プレイヤー
	bool m_bDraw;							// 描画フラグ
	bool m_bGame;							// ゲーム中か否か
};

#endif