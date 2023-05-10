//===================================================
//
// オブジェクトXの処理
// Author:Teruto Sato
//
//===================================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "objectX.h"
#include "object.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "model3D.h"
#include "utility.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 3Dモデルを生成する
//=============================================================================
CObjectX * CObjectX::Create()
{
	// オブジェクトインスタンス
	CObjectX *pObjectX = nullptr;

	// メモリの解放
	pObjectX = new CObjectX;

	// メモリの確保ができなかった
	assert(pObjectX != nullptr);

	// 数値の初期化
	pObjectX->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// インスタンスを返す
	return pObjectX;
}

//========================
// コンストラクタ
//========================
CObjectX::CObjectX() : CObjectX(0)
{
}

CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//モデル
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置の設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きの設定
}

//========================
// デストラクタ
//========================
CObjectX::~CObjectX()
{

}

//========================
// 初期化
//========================
HRESULT CObjectX::Init(D3DXVECTOR3 pos)
{
	// 変数の初期化
	m_mtxWorld = {};										// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
	m_nType = -1;											// モデルのタイプ

	// モデルクラスのメモリ確保
	m_pModel = CModel3D::Create();
	assert(m_pModel != nullptr);
	m_pModel->SetModelID(m_nType);

	return S_OK;
}

//========================
// 終了
//========================
void CObjectX::Uninit()
{
	if (m_pModel != nullptr)
	{// 終了処理
		m_pModel->Uninit();

		// メモリの解放
		delete m_pModel;
		m_pModel = nullptr;
	}
}

//========================
// 更新
//========================
void CObjectX::Update()
{
	// モデルの更新
	m_pModel->Update();
}

//========================
// 描画
//========================
void CObjectX::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											// 行列初期化関数

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	m_pModel->Draw(m_mtxWorld);
}

//===========================
// 位置の設定
//===========================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===========================
// 向きの設定
//===========================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CObjectX::GetPosition()
{
	return m_pos;
}

//===========================
// 幅の取得
//===========================
float CObjectX::GetWidth()
{
	return 0.0f;
}

//===========================
// 高さの取得
//===========================
float CObjectX::GetHeight()
{
	return 0.0f;
}

//=============================================================================
// モデルのタイプの設定
// Author : 唐﨑結斗
// 概要 : モデルのタイプの設定
//=============================================================================
void CObjectX::SetType(const int nType)
{
	// モデルのタイプ
	m_nType = nType;

	// モデルクラスのID設定
	m_pModel->SetModelID(m_nType);
}
