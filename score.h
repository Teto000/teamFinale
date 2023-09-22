//===================================================
//
// スコアヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _SCORE_H_
#define _SCORE_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "object.h"

//-------------------------------
// 前方宣言
//-------------------------------
class CNumber;	//数値
class CMessage;

//================================
// スコアクラス
//================================
class CScore : CObject
{
public:
	CScore();	//コンストラクタ
	~CScore();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	//----------------
	// セッター
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }		//位置の設定
	void SetScore(int nScore);		//スコアの設定
	void AddScore(int nScore);		//スコアの加算
	void SetColor(D3DXCOLOR col);	//色の設定
	void SetDraw(bool bDraw);		//描画状態の設定

	//----------------
	// ゲッター
	//----------------
	D3DXVECTOR3 GetPosition() override { return m_pos; }							//位置の取得
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//位置の取得
	float GetWidth() override { return 0.0f; }										//幅の取得
	float GetHeight() override { return 0.0f; }										//高さの取得
	int GetScore() { return m_nScore; }												//時間の取得

	//------------------
	// 静的メンバ変数
	//------------------
	static CScore* Create(D3DXVECTOR3 pos);

private:
	void SetNumber();			//数値の設定

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxDigits = 3;	//最大桁数

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_numberPos;		//数字の位置
	int m_nScore;					//スコア
	int m_aPosTexU[nMaxDigits];		//今の桁の数値
	float fInterval;				//数値の間隔
	CNumber* m_pNumber[nMaxDigits];	//数値
};

#endif