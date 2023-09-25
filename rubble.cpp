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
#include "ItemMark.h"
#include "game.h"
#include "score.h"

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
m_bComplete(false),
m_pItemMark(nullptr)
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
		if (m_nCntRequired == m_nRequired)
		{
			m_bComplete = true;
			Complete();
		}
		else
		{
			// 修正完了に必要な残りアイテム量を計算
			int nRest = m_repair.at(0).nRequired - m_repair.at(0).nCutRequired;

			// テクスチャの更新
			if (m_pItemMark)
			{
				m_pItemMark->SetValue(nRest);
			}
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

	case CRubble::TYPE_SLIDE:
		SetType(27);
		break;

	case CRubble::TYPE_SWING:
		SetType(29);
		break;

	case CRubble::TYPE_SEESAW:
		SetType(31);
		break;

	default:
		assert(false);
		break;
	}
}

void CRubble::Repair(CItemObj *pItem)
{
	CItemObj *pPlayerItem = pItem;

	for (int nCnt = 0; nCnt < m_nRequired; nCnt++)
	{// アイテムを保持しておらす、アイテムオブジェクトに触れていた場合取得 
		if (m_repair.at(nCnt).bCompletion)
		{
			return;
		}

		if (pPlayerItem != nullptr
			&& pPlayerItem->GetItemType() == m_repair.at(nCnt).type)
		{
			CItemObj *pChild = pPlayerItem->SearchChild();

			CItemObj *pParent = (CItemObj*)pChild->GetParentItem();

			if (pParent != nullptr)
			{
				pParent->SetChildItem();
			}

			if (pChild != nullptr)
			{
				pChild->Uninit();
				pChild = nullptr;
			}

			m_repair.at(nCnt).nCutRequired++;

			//スコアの加算(アイテム投入時)
			CGame::GetScore()->AddScore(5);

			if (m_repair.at(nCnt).nCutRequired == m_repair.at(nCnt).nRequired)
			{
				m_repair.at(nCnt).bCompletion = true;
				m_nCntRequired++;
			}

			break;
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

	case CRubble::TYPE_SLIDE:
		SetType(26);
		break;

	case CRubble::TYPE_SWING:
		SetType(28);
		break;

	case CRubble::TYPE_SEESAW:
		SetType(30);
		break;

	default:
		assert(false);
		break;
	}

	//ステージにスコアを加算(0番目のステージに100加算)
	//CApplication::AddStageScore(0, 100);

	//スコアの加算(建物完成時)
	CGame::GetScore()->AddScore(30);

	//吹き出しの消去
	if (m_pItemMark)
	{
		m_pItemMark->Uninit();
	}
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

//=============================================================================
// 吹き出しの設置
// Author : Sato Teruto
// 概要 : アイテムを直すのに必要な数を表示
//=============================================================================
void CRubble::SetMark(D3DXVECTOR3 pos, CTexture::NUM_TEXTURE tex)
{
	m_pItemMark = CItemMark::Create(pos);
	m_pItemMark->SetSize(100.0f, 100.0f);
	m_pItemMark->SetTexture(tex);
}