//=============================================================================
//
// モデルオブジェクトクラス(model_obj.cpp)
// Author : 唐﨑結斗
// 概要 : モデルオブジェクト生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <stdio.h>

#include "itemObj.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : インスタンスを生成する
//=============================================================================
CItemObj * CItemObj::Create()
{
	// オブジェクトインスタンス
	CItemObj *pItemObj = nullptr;

	// メモリの解放
	pItemObj = new CItemObj;

	// メモリの確保ができなかった
	assert(pItemObj != nullptr);

	// 数値の初期化
	pItemObj->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// インスタンスを返す
	return pItemObj;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CItemObj::CItemObj() : m_pParent(nullptr),			// 親オブジェクトの情報
m_posOffset(D3DXVECTOR3(0.0f,0.0f,0.0f)),			// 位置の差分
m_rotOffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			// 向きの差分
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CItemObj::~CItemObj()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CItemObj::Init(D3DXVECTOR3 pos)
{
	// モデルオブジェクトの初期化
	CObjectX::Init(pos);

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CItemObj::Uninit()
{
	// モデルオブジェクトの終了
	CObjectX::Uninit();

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CItemObj::Update()
{
	// モデルオブジェクトの更新
	CObjectX::Update();
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CItemObj::Draw()
{
	// 情報の取得
	D3DXMATRIX mtxWorld = GetMtx();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();
	CModel3D *pModel = GetModel();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);											// 行列初期化関数

	if (m_pParent != nullptr)
	{// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotOffset.y, m_rotOffset.x, m_rotOffset.z);			// 行列回転関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);												// 行列掛け算関数 

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);					// 行列移動関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);											// 行列掛け算関数

		// 親のワールドマットリックス
		D3DXMATRIX mtxParent = m_pParent->GetMtxWorld();

		// 行列掛け算関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

		// 位置の設定
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &mtxWorld);
		SetPos(pos);
	}
	else
	{// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);			// 行列回転関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// 行列掛け算関数 

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);					// 行列移動関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);					// 行列掛け算関数
	}

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// モデルの描画
	pModel->Draw(mtxWorld);
	SetMtx(mtxWorld);
}
