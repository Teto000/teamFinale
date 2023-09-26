//===================================================
//
// メッセージを表示する処理
// Author : Sato Teruto
//
//===================================================

//----------------------------
// インクルード
//----------------------------
#include "message.h"

//==========================================
// コンストラクタ
//==========================================
CMessage::CMessage()
{
	m_type = MESSAGETYPE_NONE;
	m_nTime = 0;
}

//==========================================
// デストラクタ
//==========================================
CMessage::~CMessage()
{
}

//==========================================
// 初期化
//==========================================
HRESULT CMessage::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);

	switch (m_type)
	{
	case MESSAGE_TYPE_FINISH:
		CObject2D::SetTexture(CTexture::TEXTURE_FINISH);
		SetSize(800.0f, 200.0f);
		break;

	case MESSAGE_TYPE_COMPLETE:
		CObject2D::SetTexture(CTexture::TEXTURE_COMPLETE);
		SetSize(800.0f, 300.0f);
		break;

	default:
		break;
	}

	return S_OK;
}

//==========================================
// 終了
//==========================================
void CMessage::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
// 更新
//==========================================
void CMessage::Update()
{
	CObject2D::Update();

	m_nTime++;

	if (m_type == MESSAGE_TYPE_COMPLETE && m_nTime >= 60)
	{
		m_nTime = 0;
		Uninit();
	}
}

//==========================================
// 描画
//==========================================
void CMessage::Draw()
{
	CObject2D::Draw();
}

//==========================================
// 生成
//==========================================
CMessage * CMessage::Create(D3DXVECTOR3 pos, MESSAGETYPE type)
{
	CMessage *pMessage = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pMessage = new CMessage;	//生成

	if (pMessage != nullptr)
	{//NULLチェック
		//引数の代入
		pMessage->m_type = type;		//種類

		//初期化
		pMessage->Init(D3DXVECTOR3(pos));
	}

	return pMessage;
}
