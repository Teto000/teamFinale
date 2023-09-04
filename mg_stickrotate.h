//===================================================
//
// スティック回転ゲームヘッダー
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MG_STICKROTATE_H_
#define _MG_STICKROTATE_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "mini_game_basis.h"

//-------------------------------
// マクロ定義
//-------------------------------

//-------------------------------
// 前方宣言
//-------------------------------
class CObject2D;

//================================
// ミニゲーム基盤クラス
//================================
class CStickRotate : public CMiniGameBasis
{
public:

	enum SticPos
	{
		STICK_UP = 0,
		STICK_DOWN,
		STICK_LEFT,
		STICK_RIGHT,
		STICK_UPLEFT,
		STICK_UPRIGHT,
		STICK_DOWNLEFT,
		STICK_DOWNRIGHT,
		STICK_MAX
	};

	CStickRotate();				//コンストラクタ
	~CStickRotate() override;	//デストラクタ

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
	static CStickRotate* Create(D3DXVECTOR3 pos);

private:

	//------------------
	// メンバ変数
	//------------------
	CObject2D *pObj2D;			//オブジェクト2D
	D3DXCOLOR m_col;				//カラー
	D3DXVECTOR3 m_PolygonPos;		//ポリゴンの位置
	D3DXVECTOR3 m_pos;				//位置
	SticPos m_stick;
	SticPos m_stickold;

	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
	int m_nStickCount;	//連打数
	bool m_bStick;
};

#endif
