//===================================================
//
// ステージ選択ヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_	

//----------------------------------
// インクルード
//----------------------------------
#include <d3dx9.h>

//----------------------------------
// 前方宣言
//----------------------------------
class CCamera;		//カメラ
class CMeshField;	//メッシュフィールド(地面)
class CObjectX;		//オブジェクトX
class CPlayer;		//プレイヤー
class CObject2D;	//オブジェクト2D

//==================================
// タイトルクラスの定義
//==================================
class CStageSelect
{
public:
	CStageSelect();		//コンストラクタ
	~CStageSelect();	//デストラクタ

	//-------------------------
	// メンバ関数
	//-------------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//-------------------------
	// セッター
	//-------------------------
	static void SetViewMap(bool bView) { m_bViewMap = bView; }	//マップ表示状態の設定

	//-------------------------
	// ゲッター
	//-------------------------
	CCamera*	GetCamera()		{ return m_pCamera; }	//カメラを取得
	CObjectX*	GetObjectX()	{ return m_pObjectX; }	//オブジェクトの取得
	CPlayer*	GetPlayer()		{ return m_pPlayer; }	//プレイヤーの取得

private:
	//-------------------------
	// メンバ変数
	//-------------------------
	CCamera*	m_pCamera;		//カメラ
	CMeshField*	m_pMeshField;	//メッシュフィールド
	CObjectX*	m_pObjectX;		//オブジェクト
	CPlayer*	m_pPlayer;		//プレイヤー
	CObject2D*	m_pObject2D;	//オブジェクト2D

	//-------------------------
	// 静的メンバ変数
	//-------------------------
	static bool m_bViewMap;		//マップを表示する状態
};

#endif