//===================================================
//
// タイマー処理
// Author : Sato Teruto
//
//===================================================

//----------------------
// インクルード
//----------------------
#include <string>
#include <vector>
#include <algorithm>
#include "ranking.h"
#include "score.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"

//----------------------
// 静的メンバ変数宣言
//----------------------
int CRanking::m_nScore = 0;	//時間

//=======================
// コンストラクタ
//=======================
CRanking::CRanking() : CObject(1)
{
	m_nRankUpdate = 0;		//更新ランクNo.

	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pScore[i];	//スコア
	}
}

//=======================
// デストラクタ
//=======================
CRanking::~CRanking()
{

}

//=======================
// 初期化
//=======================
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		pos = D3DXVECTOR3(300.0f, 200 + (i * 100.0f), 0.0f);
		m_pScore[i] = CScore::Create(pos);
	}

	Load();		//読み込み
	Ranking();	//並び替え
	Save();		//書き込み

	return S_OK;
}

//=======================
// 終了
//=======================
void CRanking::Uninit()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pScore[i]->Uninit();
	}
}

//=======================
// 更新
//=======================
void CRanking::Update()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pScore[i]->Update();
	}

	//-------------------------------
	// 今回のスコアを赤くする
	//-------------------------------
	if (m_nScore != m_nRankUpdate)
	{//今回のタイムがランキングの数値と同じなら
		if (m_nRankUpdate != -1)
		{//ランキング外じゃなかったら
			//色の変更
			m_pScore[m_nRankUpdate]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

#ifdef _DEBUG
	//ランキングの初期化
	if (CInputKeyboard::Trigger(DIK_1))
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			m_pScore[i]->SetScore(0);
			Save();		//書き込み
		}
	}
#endif // _DEBUG
}

//=======================
// 描画
//=======================
void CRanking::Draw()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pScore[i]->Draw();
	}
}

//=======================
// 生成
// 引数：位置、コンボ数
//=======================
CRanking *CRanking::Create()
{
	CRanking *pRanking = nullptr;

	//----------------------------------
	// 生成と初期化
	//----------------------------------
	pRanking = new CRanking;	//生成

	if (pRanking != nullptr)
	{//NULLチェック
		//初期化
		pRanking->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	return pRanking;
}

//=========================================
// 書き込み
//=========================================
void CRanking::Save()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "w");	//ファイル読み込み
	const int lenLine = 1024;							//1単語の最大数

	if (fp != nullptr)
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			fprintf(fp, "%d\n", m_pScore[i]->GetScore());	//読み込んだ文字ごとに設定する
		}

		fclose(fp);
	}
}

//=========================================
// 読み込み
//=========================================
void CRanking::Load()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "r");	//ファイル読み込み
	const int lenLine = 1024;							//1単語の最大数
	int nScore = 0;										//読み込み用の文字列

	if (fp != nullptr)
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			fscanf(fp, "%d", &nScore);	//読み込んだ文字ごとに設定する
			m_pScore[i]->SetScore(nScore);
		}

		fclose(fp);
	}
}

//=========================================
// ランキングの並び替え
//=========================================
void CRanking::Ranking()
{
	/*m_nRankUpdate = -1;
	if (m_nScore >= m_pScore[0]->GetScore())
	{//比較
		m_pScore[0]->SetScore(m_nScore);

		//昇順に並び変える
		std::vector<int> rank = { m_pScore[0]->GetScore()
								, m_pScore[1]->GetScore()
								, m_pScore[2]->GetScore()
								, m_pScore[3]->GetScore()
								, m_pScore[4]->GetScore() };

		//std::sort(rank.begin(), rank.end());

		//for (int i = 0; i < nMaxRanking; i++)
		//{//並び変えたやつを代入
		//	m_pScore[i]->SetScore(rank[i]);

		//	if (m_nScore == rank[i])
		//	{
		//		m_nRankUpdate = i;
		//	}
		//}
	}*/

	for (int nCnt = 0; nCnt < nMaxRanking; nCnt++)
	{
		int nCopy = 0;

		//条件式が真の場合実行
		if (m_nScore > m_pScore[nCnt]->GetScore())
		{//数値を移す
			nCopy = m_pScore[nCnt]->GetScore();
			m_pScore[nCnt]->SetScore(m_nScore);
			m_nScore = nCopy;
			m_nRankUpdate = nCnt;
		}
	}
}