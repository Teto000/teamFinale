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
#include "object2d.h"

//================================
// ミニゲーム基盤クラス
//================================
class CMiniGameBasis : public CObject2D
{
public:

	enum MiniGameType		//ミニゲームの種類
	{
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

	//------------------
	// ゲッター
	//------------------
	int GetGameType() { return m_nType; }

	//------------------
	// 静的メンバ変数
	//------------------
	static CMiniGameBasis* Create(D3DXVECTOR3 pos, int nType);

private:
	//------------------
	// メンバ変数
	//------------------
	int m_nType;		//ミニゲームの種類
	bool m_bDraw;			//描画フラグ
};

#endif
