//=============================================================================
//
// オブジェとマネージャークラス(object_mg.h)
// Author : 唐﨑結斗
// 概要 : 3Dプレイヤー生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "object_mg.h"
#include "rubble.h"
#include "message.h"
#include "renderer.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CObjectManager * CObjectManager::Create()
{
	// オブジェクトインスタンス
	CObjectManager *pObjectManager = nullptr;

	// メモリの解放
	pObjectManager = new CObjectManager;

	// メモリの確保ができなかった
	assert(pObjectManager != nullptr);

	// 数値の初期化
	pObjectManager->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// インスタンスを返す
	return pObjectManager;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CObjectManager::CObjectManager() : CObjectManager(0)
{
}

CObjectManager::CObjectManager(int nPriority) : CObject(nPriority),
m_pos(D3DXVECTOR3()),					// 位置
m_posOld(D3DXVECTOR3()),				// 過去位置
m_nMaxRubble(0),
m_pMessage(0)
{
	
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CObjectManager::~CObjectManager()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CObjectManager::Init(D3DXVECTOR3 pos)
{
	// パーツの初期化
	m_pRubble.clear();

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CObjectManager::Uninit()
{
	// オブジェクト2Dの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CObjectManager::Update()
{
	UpdateRubble();
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CObjectManager::Draw()
{

}

void CObjectManager::UpdateRubble()
{
	int nCntComplete = 0;

	for (int nCntRubble = 0; nCntRubble < m_nMaxRubble; nCntRubble++)
	{
		if (!m_pRubble.at(nCntRubble)->GetComplete())
		{
			break;
		}

		nCntComplete++;
	}

	if (nCntComplete != m_nMaxRubble)
	{
		return;
	}

	for (int nCntRubble = 0; nCntRubble < m_nMaxRubble; nCntRubble++)
	{
		m_pRubble.at(nCntRubble)->Reset();

		//メッセージの表示
		m_pMessage = CMessage::Create(
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
			, CMessage::MESSAGE_TYPE_COMPLETE);
	}
}

void CObjectManager::SetRubble(CRubble * pRubble)
{
	m_nMaxRubble++;

	m_pRubble.resize(m_nMaxRubble);

	m_pRubble[m_nMaxRubble - 1] = pRubble;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CObjectManager::GetPosition()
{
	return m_pos;
}

//===========================
// 幅の取得
//===========================
float CObjectManager::GetWidth()
{
	return 0.0f;
}

//===========================
// 高さの取得
//===========================
float CObjectManager::GetHeight()
{
	return 0.0f;
}
