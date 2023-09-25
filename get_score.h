//===================================================
//
// スコア取得表示ヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _GET_SCORE_H_
#define _GET_SCORE_H_	//二重インクルード防止

//-------------------------
// インクルード
//-------------------------
#include "billboard.h"

//================================
// アイテム目印クラス
//================================
class CGetScore : public CBillBoard
{
public:
	enum NUMBER
	{
		NUMBER_NONE = 0,
		NUMBER_50,
		NUMBER_300
	};

	CGetScore();			// コンストラクタ
	~CGetScore() override;	// デストラクタ

	//----------------------
	// メンバ関数
	//----------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//----------------------
	// 静的メンバ関数
	//----------------------
	static CGetScore* Create(NUMBER num, D3DXVECTOR3 pos);

private:
	int nStopTime;		//止まってる時間
	int nDeleteTime;	//消す時間
	NUMBER m_num;
};

#endif