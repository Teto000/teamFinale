//===================================================
//
// ボタン連打ゲームヘッダー
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MG_BUTTONMASH_H_
#define _MG_BUTTONMASH_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "mini_game_basis.h"

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_LIFEPOLYGON		(29)	//ライフポリゴン数

//-------------------------------
// 前方宣言
//-------------------------------
class CNumber;	//数値

//================================
// ミニゲーム基盤クラス
//================================
class CButtonMash : public CMiniGameBasis
{
public:

	CButtonMash();				//コンストラクタ
	~CButtonMash() override;	//デストラクタ

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
	static CButtonMash* Create(D3DXVECTOR3 pos);

private:

	//------------------
	// メンバ変数
	//------------------
	CObject2D *pObj2D[2];			//オブジェクト2D
	CObject2D *pLife[29];			//ライフポリゴン
	D3DXCOLOR m_col[3];				//カラー
	D3DXVECTOR3 m_PolygonPos;		//ポリゴンの位置
	D3DXVECTOR3 m_pos;				//位置
	
	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
	int m_nMashCounter;	//連打数
};

#endif