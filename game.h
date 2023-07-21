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
	// セッター
	//------------------
	static void SetFinish(bool fin) { m_bFinish = fin; }	//ゲーム終了状態を設定

	//------------------
	// ゲッター
	//------------------
	static CPlayer* GetPlayer(int nNumber) { return m_pPlayer[nNumber]; }	//プレイヤーの取得
	static CObjectX* GetObjectX(int nNum) { return m_pObjectX[nNum]; }		//オブジェクトの取得
	static CCamera*	GetCamera() { return m_pCamera; }		//カメラの取得
	static const int GetMaxPlayer() { return nMaxPlayer; }	//プレイヤーの最大数を取得
	static const int GetMaxObject() { return nMaxObject; }	//オブジェクトの最大数を取得
	static const float GetPastPosX() { return fPastPosX; }	//過去移動時のX座標の変化量を取得
	static bool GetFinish() { return m_bFinish; }			//ゲーム終了状態を取得

private:
	//-------------------
	// 定数
	//-------------------
	static const int nMaxPlayer = 2;	//プレイヤーの最大数
	static const int nMaxObject = 4;	//オブジェクトの最大数
	static const int nMaxBG = 51;
	static const float fPastPosX;		//過去のX座標

	//-------------------
	// プライベート関数
	//-------------------
	void CreateObj();	//オブジェクトの生成
	void CreateWood();	//背景オブジェクト(木)の生成

	//-------------------
	// 静的メンバ変数
	//-------------------
	static bool m_bFinish;	//ゲーム終了フラグ

	static CCamera*		m_pCamera;					//カメラ
	static CTime*		m_pTime;					//タイマー
	static CSky*		m_pSky;						//空
	static CMeshField*	m_pMeshField;				//メッシュフィールド
	static CObjectX*	m_pObjectX[nMaxObject];		//オブジェクト
	static CObjectX*	m_pObjBG[nMaxBG];			//背景オブジェクト(木)の生成
	static CPlayer*		m_pPlayer[nMaxPlayer];		//プレイヤー
};

#endif