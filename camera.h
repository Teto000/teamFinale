//===================================================
//
// カメラヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _CAMERA_H_	//このマクロが定義されてなかったら
#define _CAMERA_H_	//2重インクルード防止のマクロ定義

//--------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>
#include "main.h"

//================================
// カメラクラスの定義
//================================
class CCamera
{
public:
	CCamera();	//コンストラクタ
	~CCamera();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init();
	void Uninit();
	void Update();
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);

	//------------------
	// 静的メンバ関数
	//------------------
	static CCamera* CCamera::Create();

	//------------------
	// セッター
	//------------------
	void ShakeCamera(int fream, float magnitude, D3DXVECTOR3 max);	//カメラの振動情報の設定
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }	//視点の設定
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }	//注視点の設定

	//------------------
	// ゲッター
	//------------------
	D3DXVECTOR3 GetPosV()		{ return m_posV; }		//視点を取得
	D3DXVECTOR3 GetInitPosV()	{ return m_initPosV; }	//視点の初期値を取得
	D3DXVECTOR3 GetPosR()		{ return m_posR; }		//注視点を取得
	D3DXVECTOR3 GetRot()		{ return m_rot; }		//角度を取得
	D3DXMATRIX GetMtxProjection() { return m_mtxProjection; }
	D3DXMATRIX GetMtxView()		{ return m_mtxView; }

private:
	void Turn();	//旋回
	void Follow();	//追従

private:
	//------------------
	// 定数
	//------------------
	static const float m_fSpeed;	//旋回速度

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_posV;			//現在の視点
	D3DXVECTOR3 m_initPosV;		//視点の初期値
	D3DXVECTOR3 m_posR;			//現在の注視点
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_worldPosV;	//ワールド座標(視点)
	D3DXVECTOR3 m_worldPosR;	//ワールド座標(注視点)
	D3DXVECTOR3 m_posVDest;		//目的の視点
	D3DXVECTOR3 m_posRDest;		//目的の注視点
	D3DXVECTOR3 m_rotDest;		//目的の角度
	D3DXVECTOR3 m_vecU;			//上方向ベクトル
	D3DXVECTOR3 m_maxShake;		//揺れの最大値
	D3DXMATRIX  m_mtxWorld;		//ワールドマトリックス
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス

	//カメラの振動
	int m_nQuakeFreamCount;		//揺らすフレーム数
	float m_fQuakeMagnitude;	//揺れの量
};

#endif