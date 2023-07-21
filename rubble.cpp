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

#include "rubble.h"
#include "itemObj.h"
#include "application.h"
#include "renderer.h"
#include "model3D.h"
#include "collision_rectangle3D.h"
#include "line.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : インスタンスを生成する
//=============================================================================
CRubble * CRubble::Create()
{
	// オブジェクトインスタンス
	CRubble *pRubble = nullptr;

	// メモリの解放
	pRubble = new CRubble;

	// メモリの確保ができなかった
	assert(pRubble != nullptr);

	// 数値の初期化
	pRubble->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// インスタンスを返す
	return pRubble;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CRubble::CRubble() : m_nRequired(0),		// 修理数
m_nCntRequired(0),
m_bComplete(false)
{
	// 修理の初期化
	m_repair.clear();

	// オブジェクトタイプ
	SetObjType(OBJTYPE_BREAK);
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CRubble::~CRubble()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CRubble::Init(D3DXVECTOR3 pos)
{
	// モデルオブジェクトの初期化
	CObjectX::Init(pos);

	// ライン情報
	m_pLine = new CLine*[4];
	m_lineCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	for (int nCntLine = 0; nCntLine < 4; nCntLine++)
	{
		m_pLine[nCntLine] = CLine::Create();
	}

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CRubble::Uninit()
{
	if (m_pLine != nullptr)
	{
		for (int nCntLine = 0; nCntLine < 4; nCntLine++)
		{
			m_pLine[nCntLine]->Uninit();
			m_pLine[nCntLine] = nullptr;
		}

		delete[] m_pLine;
		m_pLine = nullptr;
	}

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
void CRubble::Update()
{
	// モデルオブジェクトの更新
	CObjectX::Update();

	if (!m_bComplete)
	{
		Collision();

		if (m_nCntRequired == m_nRequired)
		{
			m_bComplete = true;
			Complete();
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CRubble::Draw()
{
	// モデルオブジェクトの描画
	CObjectX::Draw();
}

void CRubble::SetBuildType(EBuildType buildType)
{
	m_buildType = buildType;

	switch (m_buildType)
	{
	case CRubble::TYPE_NONE:
		break;

	case CRubble::TYPE_PAVILION:
		SetType(19);
		break;

	case CRubble::TYPE_FOUNTAIN:
		SetType(21);
		break;

	default:
		assert(false);
		break;
	}
}

void CRubble::Collision()
{
	// 当たり判定の取得
	CCollision_Rectangle3D *pCollision = GetCollision();
	pCollision->Collision(CObject::OBJTYPE_ITEM, false);

	// 当たったオブジェクトのリストを取得
	std::vector<CObject*> apCollidedObj = pCollision->GetCollidedObj();

	if (apCollidedObj.size() > 0)
	{// 当たったオブジェクトとの処理
		for (int nCntObj = 0; nCntObj < apCollidedObj.size(); nCntObj++)
		{
			CItemObj *pCollidedObj = (CItemObj*)apCollidedObj.at(nCntObj);

			for (int nCnt = 0; nCnt < m_nRequired; nCnt++)
			{// アイテムを保持しておらす、アイテムオブジェクトに触れていた場合取得 
				if (m_repair.at(nCnt).bCompletion)
				{
					return;
				}

				if (pCollidedObj != nullptr
					&& pCollidedObj->GetItemType() == m_repair.at(nCnt).type)
				{
					CItemObj *pChild = pCollidedObj->SearchChild();

					CItemObj *pParent = (CItemObj*)pChild->GetParentItem();
					
					if (pParent != nullptr)
					{
						pParent->SetChildItem();
					}

					pChild->Uninit();
					pChild = nullptr;

					m_repair.at(nCnt).nCutRequired++;

					if (m_repair.at(nCnt).nCutRequired == m_repair.at(nCnt).nRequired)
					{
						m_repair.at(nCnt).bCompletion = true;
						m_nCntRequired++;
					}

					break;
				}
			}
		}
	}
}

void CRubble::Complete()
{
	switch (m_buildType)
	{
	case CRubble::TYPE_NONE:
		break;

	case CRubble::TYPE_PAVILION:
		SetType(18);
		break;

	case CRubble::TYPE_FOUNTAIN:
		SetType(20);
		break;

	default:
		assert(false);
		break;
	}

	//ステージにスコアを加算(0番目のステージに100加算)
	CApplication::AddStageScore(0, 100);
}

//=============================================================================
// ラインの設置
// Author : 唐﨑結斗
// 概要 : ラインを矩形状に設置
//=============================================================================
void CRubble::SetLine()
{
	// 変数宣言
	D3DXVECTOR3 pos = GetPosition();
	const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 size = GetCollision()->GetSize();
	const D3DXCOLOR col = m_lineCol;

	// ラインの設定
	m_pLine[0]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
	m_pLine[1]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(-size.x, -size.y, size.z), col);
	m_pLine[2]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, -size.z), col);
	m_pLine[3]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, -size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
}