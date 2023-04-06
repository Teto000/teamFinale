//===================================================
//
// ゲームヘッダー
// Author : Sato Teruto
//
//====================================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>
#include "application.h"

//--------------------------------
// 前方宣言
//--------------------------------
class CCamera;		//カメラ
class CTime;		//タイマー

//================================
// ゲームクラスの定義
//================================
class CGame
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// ゲッター
	//------------------
	static bool GetFinish() { return m_bFinish; }	  //ゲーム終了状態を取得
	static CCamera*	GetCamera() { return m_pCamera; } //カメラの取得

private:
	//-------------------
	// 静的メンバ変数
	//-------------------
	static bool m_bFinish;	//ゲーム終了フラグ

	static CCamera*	m_pCamera;	//カメラ
	static CTime*	m_pTime;	//タイマー
};

#endif