//===================================================
//
// 取得したスコアを表示する処理
// Author : Sato Teruto
//
//===================================================

//---------------------------
// インクルード
//---------------------------
#include <time.h>
#include "get_score.h"

//======================================
// コンストラクタ
//======================================
CGetScore::CGetScore() : CBillBoard(0)
{
	nStopTime = 0;		//止まってる時間
	nDeleteTime = 0;	//消す時間
	m_num = NUMBER_NONE;
}

//======================================
// デストラクタ
//======================================
CGetScore::~CGetScore()
{
}

//======================================
// 初期化
//======================================
HRESULT CGetScore::Init(D3DXVECTOR3 pos)
{
	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	int nWidth = 200;
	int nRandX = rand() % nWidth - (nWidth / 2);
	int nRandY = rand() % nWidth - (nWidth / 2);
	D3DXVECTOR3 newPos(pos.x + (float)nRandX
		, pos.y + (float)nRandY
		, pos.z);

	CBillBoard::Init(newPos);

	switch (m_num)
	{
	case NUMBER_50:
		CBillBoard::SetTexture(CTexture::TEXTURE_SCORE_50);
		CBillBoard::SetSize(50.0f, 50.0f);
		break;

	case NUMBER_300:
		CBillBoard::SetTexture(CTexture::TEXTURE_SCORE_300);
		CBillBoard::SetSize(60.0f, 60.0f);
		break;

	default:
		break;
	}

	return S_OK;
}

//======================================
// 終了
//======================================
void CGetScore::Uninit()
{
	CBillBoard::Uninit();
}

//======================================
// 更新
//======================================
void CGetScore::Update()
{
	CBillBoard::Update();

	//----------------------------
	// 上昇して消える処理
	//----------------------------
	nStopTime++;

	if (nStopTime >= 20)
	{
		//上昇させる
		D3DXVECTOR3 pos = CBillBoard::GetPosition();
		pos.y += 2.0f;
		CBillBoard::SetPos(pos);

		nDeleteTime++;

		if (nDeleteTime >= 30)
		{
			nStopTime = 0;
			nDeleteTime = 0;
			Uninit();
		}
	}
}

//======================================
// 描画
//======================================
void CGetScore::Draw()
{
	CBillBoard::Draw();
}

//======================================
// 生成
//======================================
CGetScore* CGetScore::Create(NUMBER num, D3DXVECTOR3 pos)
{
	CGetScore* pGetScore = nullptr;

	//----------------------------------
	// ポリゴンの生成と初期化
	//----------------------------------
	pGetScore = new CGetScore;	//生成

	if (pGetScore != nullptr)
	{//NULLチェック
		//初期化
		pGetScore->m_num = num;
		pGetScore->Init(D3DXVECTOR3(pos));
	}

	return pGetScore;
}