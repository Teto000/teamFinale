//===================================================
//
// カメラの処理
// Author:Teruto Sato
//
//===================================================

//----------------------
// インクルード
//----------------------
#include <cmath>
#include "camera.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "renderer.h"
#include "game.h"
#include "stage_select.h"
#include "debug_proc.h"
#include "utility.h"
#include "player.h"
#include "mode.h"

//----------------------
// 静的メンバ変数宣言
//----------------------
const float CCamera::m_fSpeed = 0.02f;

//===========================
// コンストラクタ
//===========================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_initPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//視点の初期値
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カメラの振動
	m_nQuakeFreamCount = 0;
	m_fQuakeMagnitude = 0.0f;
}

//===========================
// デストラクタ
//===========================
CCamera::~CCamera()
{

}

//========================
// カメラの初期化処理
//========================
void CCamera::Init(void)
{
	//---------------------------------
	// 視点・注視点・上方向を設定する
	//---------------------------------
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);
	m_initPosV = m_posV;
	m_posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//========================
// カメラの終了処理
//========================
void CCamera::Uninit(void)
{

}

//========================
// カメラの更新処理
//========================
void CCamera::Update(void)
{
	//回転
	//Turn();

	//追従処理
	Follow();

	//視点・注視点の表示
	CDebugProc::Print("視点：%f,%f,%f", m_posVDest.x, m_posVDest.y, m_posVDest.z);
	CDebugProc::Print("注視点：%f,%f,%f", m_posRDest.x, m_posRDest.y, m_posRDest.z);
	CDebugProc::Print("回転：%f,%f,%f", m_rot.x, m_rot.y, m_rot.z);
}

//========================
// カメラの設定処理
//========================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	//--------------------------------
	// カメラ情報の振動
	//--------------------------------
	D3DXVECTOR3 adjustPos(0.0f, 0.0f, 0.0f);

	if (m_nQuakeFreamCount > 0)
	{//揺らすフレーム数が0より大きいなら
		//フレーム数の減少
		m_nQuakeFreamCount--;

		//ランダムな値を設定
		adjustPos.x = m_fQuakeMagnitude * (rand() % (int)m_maxShake.x - ((int)m_maxShake.x / 2.0f));
		adjustPos.y = m_fQuakeMagnitude * (rand() % (int)m_maxShake.y - ((int)m_maxShake.y / 2.0f));
		adjustPos.z = m_fQuakeMagnitude * (rand() % (int)m_maxShake.z - ((int)m_maxShake.z / 2.0f));
	}

	//--------------------------------
	// カメラ情報の設定
	//--------------------------------
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
					   &(m_posVDest + adjustPos),	//視点
					   &(m_posRDest + adjustPos),	//注視点
					   &m_vecU);					//上の向き

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
							   D3DXToRadian(45.0f),	//視野角
							   (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
							   10.0f,		//near
							   100000.0f);	//far

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//--------------------------------
	// フォグ
	//--------------------------------
	//フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//フォグカラーの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//フォグモードの設定
	//範囲指定:D3DFOG_LINEAR , 密度指定:D3DFOG_EXP
	//pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);	//範囲指定
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);	//密度指定

	//----------------------------
	// 範囲指定時の処理
	//----------------------------
	/*float fFogStart = 100;		//開始位置
	float fFogEnd = 1000;		//終了位置
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStart));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEnd));*/

	//----------------------------
	// 密度指定時の処理
	//----------------------------
	float fFogDensity = 0.000f;		//密度(0.001でもかなり真っ白)
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}

//==================================================
// カメラの生成
// 引数 : 左上の座標 X, 左上の座標 Y, 幅, 高さ
//==================================================
CCamera* CCamera::Create()
{
	CCamera* pCamera = nullptr;

	//------------------------------
	// ポリゴンの生成と初期化
	//------------------------------
	pCamera = new CCamera;	//生成

	if (pCamera != nullptr)
	{//NULLチェック

		//初期化
		pCamera->Init();
	}

	return pCamera;
}

//========================
// カメラの旋回
//========================
void CCamera::Turn()
{
	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();
	D3DXVECTOR3 stick = joypad->Stick(CInputJoypad::JOYKEY_RIGHT_STICK, 0);

	//スティックを動かす値の設定
	float fMoveValue = 0.5f;

	//------------------
	// 注視点の旋回
	//------------------
	if (CInputKeyboard::Press(DIK_Q) || stick.x <= -fMoveValue)	//左回転
	{//Qキーが押された
		m_rot.y -= m_fSpeed;	//回転量の増加
	}
	else if (CInputKeyboard::Press(DIK_E) || stick.x >= fMoveValue)	//右回転
	{//Eキーが押された
		m_rot.y += m_fSpeed;
	}
	if (CInputKeyboard::Press(DIK_B) || stick.y >= fMoveValue)	//上回転
	{//Bキーが押された
		m_rot.x -= m_fSpeed;
	}
	else if (CInputKeyboard::Press(DIK_Y) || stick.y <= -fMoveValue)	//下回転
	{//Yキーが押された
		m_rot.x += m_fSpeed;
	}

	//-------------------------
	// 上下旋回の上限値追加
	//-------------------------
	if (m_rot.x >= 1.2f)
	{
		m_rot.x = 1.2f;
	}
	else if (m_rot.x <= -0.3f)
	{
		m_rot.x = -0.3f;
	}
}

//========================
// 追従処理
//========================
void CCamera::Follow()
{
	//変数宣言
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);	//追従する位置
	D3DXVECTOR3 pos1(0.0f, 0.0f, 0.0f);		//プレイヤー1の位置
	D3DXVECTOR3 pos2(0.0f, 0.0f, 0.0f);		//プレイヤー2の位置
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);		//プレイヤー間の距離

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//----------------------------------------
	// 行列を使ったカメラ制御
	//----------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	float vecF;

	switch (CMode::GetMode())
	{//モードごとの処理
	case CMode::MODE_GAME:
		//-----------------------------
		// プレイヤー間の中心を見る
		//-----------------------------
		pos1 = CMode::GetGame()->GetPlayer(0)->GetPos();
		pos2 = CMode::GetGame()->GetPlayer(1)->GetPos();

		if (CGame::GetPlayer(0)->GetPast())
		{//プレイヤーが過去にいるなら
			//プレイヤーの位置を整える
			pos1.x -= CGame::GetPastPosX();
			pos2.x -= CGame::GetPastPosX();
		}
		
		//プレイヤー間の距離を求める
		vec = pos1 + pos2;

		//vecF = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.z - pos2.z) * (pos1.z - pos2.z));

		//その中間を見る
		target.x = pos1.x;
		target.z = pos1.z;

		if (CGame::GetPlayer(0)->GetPast() || CGame::GetPlayer(1)->GetPast())
		{//プレイヤーが過去にいるなら
			//追従位置の基準をずらす
			target.x += CGame::GetPastPosX();
		}

		//カメラの高さを調整
		m_posV.y = 50.0f;

		//高さの最低値を設定
		if (m_posV.y <= 300.0f)
		{
			m_posV.y = 300.0f;
		}
		break;

	//ステージ選択画面なら
	case CMode::MODE_STAGESELECT:
		target = CMode::GetStage()->GetPlayer()->GetPosition();
		break;

	default:
		break;
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//行列に回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//行列に移動を反映
	D3DXMatrixTranslation(&mtxTrans, target.x, target.y, target.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//ワールド変換行列を使ってposV,posRを求める
	D3DXVec3TransformCoord(&m_posRDest, &m_posR, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_posVDest, &m_posV, &m_mtxWorld);
}

//========================
// カメラの振動情報の設定
//========================
void CCamera::ShakeCamera(int fream, float magnitude, D3DXVECTOR3 max)
{
	m_nQuakeFreamCount = fream;			//揺らすフレーム数
	m_fQuakeMagnitude = magnitude;		//揺れの量
	m_maxShake = max;					//揺れの大きさの最大値
}