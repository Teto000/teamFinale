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
class CSky;			//空
class CMeshField;	//地面
class CPlayer;		//プレイヤー
class CObjectX;		//オブジェクト

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
	static CPlayer* GetPlayer() { return m_pPlayer; }		//プレイヤーの取得
	
	static CObjectX* GetObjectX() { return m_pObjectX; }	//オブジェクトの取得
	static bool GetFinish() { return m_bFinish; }			//ゲーム終了状態を取得
	static CCamera*	GetCamera() { return m_pCamera; }		//カメラの取得

private:
	//-------------------
	// メンバ変数
	//-------------------

	//-------------------
	// 静的メンバ変数
	//-------------------
	static bool m_bFinish;	//ゲーム終了フラグ

	static CCamera*		m_pCamera;		//カメラ
	static CTime*		m_pTime;		//タイマー
	static CSky*		m_pSky;			//空
	static CMeshField*	m_pMeshField;	//メッシュフィールド
	static CObjectX*	m_pObjectX;		//オブジェクト
	static CPlayer*		m_pPlayer;		//プレイヤー
};

#endif