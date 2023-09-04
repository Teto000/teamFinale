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
#include "collision_rectangle3D.h"

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
CItemObj::CItemObj() : m_pParentItem(nullptr),		// 親オブジェの情報
m_pChildItem(nullptr),								// 子供オブジェの情報
m_pParent(nullptr),									// 親オブジェクトの情報
m_Type(TYPE_NONE),									// アイテムの種別
m_posOffset(D3DXVECTOR3(0.0f,0.0f,0.0f)),			// 位置の差分
m_rotOffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			// 向きの差分
{
	// オブジェクトタイプ
	SetObjType(OBJTYPE_ITEM);
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

	if (GetParent() == nullptr)
	{// 詰み重ね
		Stack();
	}
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

void CItemObj::Stack(CItemObj * pTarget)
{
	// 親の設定
 	CItemObj *pItem = this;
	int nCntChildItem = 0;

	// 子アイテムの検索
	int nCntItem = 0;
	pItem = pItem->SearchChild(nCntItem);

	if (pItem->GetChildItem() == nullptr)
	{// 親子関係の設定
		if (pItem->GetChildItem() != nullptr)
		{
			assert(false);
		}

		pTarget->SetParentItem(pItem);
		pTarget->SetParent(pItem->GetModel());
		pItem->SetChildItem(pTarget);

		// アイテムの当たり判定の設定
		pTarget->GetCollision()->SetUseFlag(false);
		D3DXVECTOR3 collisionSize = GetCollision()->GetSize();
		collisionSize.y += pTarget->GetCollision()->GetSize().y;
		GetCollision()->SetSize(collisionSize);
		D3DXVECTOR3 modelSize = pTarget->GetModel()->GetMyMaterial().size;
		pTarget->SetPosOffset(D3DXVECTOR3(0.0f, modelSize.y, 0.0f));
	}
}

//=============================================================================
// 子供の検索
// Author : 唐﨑結斗
// 概要 : アイテムから子供の検索を行う
//=============================================================================
CItemObj* CItemObj::SearchChild()
{
	// 親の設定
	CItemObj *pItem = this;
	CItemObj *pItemNext = nullptr;

	while (1)
	{
		pItemNext = (CItemObj*)pItem->GetChildItem();

		if (pItemNext != nullptr)
		{
			pItem = pItemNext;
		}
		else
		{
			break;
		}
	}

	return pItem;
}

CItemObj * CItemObj::SearchChild(int &count)
{
	int nCntItem = 0;

	// 親の設定
	CItemObj *pItem = this;
	CItemObj *pItemNext = nullptr;

	while (1)
	{
		pItemNext = (CItemObj*)pItem->GetChildItem();

		if (pItemNext != nullptr)
		{
			pItem = pItemNext;
			nCntItem++;
		}
		else
		{
			break;
		}
	}

	count = nCntItem;

	return pItem;
}

//=============================================================================
// 親モデルの設定
// Author : 唐﨑結斗
// 概要 : 親モデルの設定
//=============================================================================
void CItemObj::SetParent(CModel3D * pParent)
{
	m_pParent = pParent;

	// 当たり判定
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->SetUseFlag(false);
}

//=============================================================================
// 親モデルの設定
// Author : 唐﨑結斗
// 概要 : 親モデルの設定
//=============================================================================
void CItemObj::SetParent()
{
	if (m_pParentItem != nullptr)
	{// 親がアイテムの場合
		SetParentItem();
	}

	// 親の設定の解除
	m_pParent = nullptr;

	// 当たり判定
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->SetUseFlag(true);
}

//=============================================================================
// アイテムの種別の設定
// Author : 唐﨑結斗
// 概要 : アイテムの種別を設定する
//=============================================================================
void CItemObj::SetItemType(EItemType type)
{
	m_Type = type;

	// 当たり判定の設定
	CCollision_Rectangle3D *pCollision = GetCollision();

	switch (m_Type)
	{
	case CItemObj::TYPE_NONE:
		break;

	case CItemObj::TYPE_WOOD:
		SetType(23);
		break;

	case CItemObj::TYPE_STONE:
		SetType(24);
		break;

	case CItemObj::TYPE_METAL:
		SetType(25);
		break;

	default:
		break;
	}

	// 当たり判定の設定
	pCollision->SetSize(GetModel()->GetMyMaterial().size);

	D3DXVECTOR3 size = pCollision->GetSize();

	pCollision->SetPos(D3DXVECTOR3(0.0f, GetModel()->GetMyMaterial().size.y / 2.0f, 0.0f));
	pCollision->SetUseFlag(false);
}

//=============================================================================
// 積み重ね
// Author : 唐﨑結斗
// 概要 : 当たったアイテムを積み重ねる処理
//=============================================================================
void CItemObj::Stack()
{
	// アイテムどうしの当たり判定
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->Collision(CObject::OBJTYPE_ITEM, false);

	// 当たったオブジェクトのリストを取得
	std::vector<CObject*> apCollidedObj = pCollision->GetCollidedObj();

	if (apCollidedObj.size() > 0)
	{// 当たったオブジェクトとの処理
		for (int nCntObj = 0; nCntObj < apCollidedObj.size(); nCntObj++)
		{// 当たったアイテムの設定
			CItemObj *pTargetItem = (CItemObj*)apCollidedObj.at(nCntObj);

			// 親の設定
			CItemObj *pItem = this;

			// 子アイテムの検索
			int nCntItem = 0;
			pItem = pItem->SearchChild(nCntItem);

			if (pItem->GetChildItem() == nullptr)
			{// 親子関係の設定
				pTargetItem->SetParentItem(pItem);
				pTargetItem->SetParent(pItem->GetModel());
				pItem->SetChildItem(pTargetItem);

				// アイテムの当たり判定の設定
				pTargetItem->GetCollision()->SetUseFlag(false);
				D3DXVECTOR3 collisionSize = GetCollision()->GetSize();
				collisionSize.y += pTargetItem->GetCollision()->GetSize().y;
				GetCollision()->SetSize(collisionSize);
				D3DXVECTOR3 modelSize = pTargetItem->GetModel()->GetMyMaterial().size;
				pTargetItem->SetPosOffset(D3DXVECTOR3(0.0f, modelSize.y, 0.0f));
			}
		}
	}
}
