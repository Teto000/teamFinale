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
	void SetNumber();	//数値の設定

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxDigits = 2;	//最大桁数

	//------------------
	// メンバ変数
	//------------------
	CObject2D *pObj2D;				//オブジェクト2D
	CNumber* m_pNumber[nMaxDigits];	//数値
	D3DXVECTOR3 m_numberPos;		//数字の位置
	D3DXVECTOR3 m_pos;				//位置
	
	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
	int m_nMashCounter;	//連打数
	int m_aPosTexU[nMaxDigits];	//今の桁の数値
	float m_fInterval;			//数値の間隔
};

#endif