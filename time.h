//===================================================
//
// タイマーヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _TIME_H_
#define _TIME_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "object2d.h"

//-------------------------------
// 前方宣言
//-------------------------------
class CNumber;	//数値
class CMessage;

//================================
// タイマークラス
//================================
class CTime : CObject2D
{
public:
	CTime();	//コンストラクタ
	~CTime();	//デストラクタ

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
	void SetCntTime(bool bCnt) { m_bCntTime = bCnt; }	//時間を数える状態の設定

	//----------------
	// ゲッター
	//----------------
	D3DXVECTOR3 GetPosition() override { return m_pos; }							//位置の取得
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//位置の取得
	float GetWidth() override { return 0.0f; }										//幅の取得
	float GetHeight() override { return 0.0f; }										//高さの取得
	int GetTime() { return m_nTime; }												//時間の取得

	//------------------
	// 静的メンバ変数
	//------------------
	static CTime* Create(D3DXVECTOR3 pos);

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxTime = 90;	//時間の最大値
	static const int nMaxObj = 2;

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_numberPos;		//数字の位置
	int m_nTime;					//時間
	int m_nCntMove;					//移動までの時間
	int m_nFinTime;					//ゲーム終了までの時間
	int m_nCntFream;				//フレーム数のカウント
	float m_neeadleRotX;			//針の角度
	bool m_bCntTime;				//時間を数える状態
	CMessage* m_pMessage;
	CObject2D* m_pObj[nMaxObj];		//オブジェクト
};

#endif