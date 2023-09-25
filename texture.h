//=============================================================================
//
// テクスチャ設定処理(texture.h)
// Author : 唐﨑結斗
// 概要 : テクスチャ設定を行う
//
//=============================================================================
#ifndef _TEXTURE_H_		// このマクロ定義がされてなかったら
#define _TEXTURE_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//=============================================================================
// テクスチャクラス
// Author : 唐﨑結斗
// 概要 : テクスチャ設定を行うクラス
//=============================================================================
class CTexture
{
public:
	//*****************************************************************************
	// 定数定義
	//*****************************************************************************
	static const unsigned int MAX_NAME = (0x100);

	struct TEXTURE
	{
		LPDIRECT3DTEXTURE9		pTexture;					// テクスチャ情報
		char					aFileName[MAX_NAME];		// ファイル名
	};

	enum NUM_TEXTURE
	{/* ↓ 使用しない ↓ */
		TEXTURE_NONE = -1,

		/* ↓ タイトル ↓ */
		TEXTURE_TITLE = 0,		//タイトル背景
		TEXTURE_TITLE_BG,
		TEXTURE_PRESSENTER,

		/* ↓ リザルト ↓ */
		TEXTURE_RESULT,			//リザルト背景
		TEXTURE_RANKING,		//ランキングロゴ

		/* ↓ ゲーム ↓ */
		TEXTURE_SKY,			//空
		TEXTURE_GROUND,			//地面
		TEXTURE_FINISH,			//FINISHの文字
		TEXTURE_COMPLETE,		//COMPLETEの文字
		TEXTURE_FUKIDASI,		//吹き出し
		TEXTURE_FUKIDASI2,		//吹き出し(2)
		TEXTURE_FUKIDASI3,		//吹き出し(3)
		TEXTURE_FUKIDASI4,		//吹き出し(4)
		TEXTURE_CLOCK,			//時計盤
		TEXTURE_CLOCK_NEEDLE,	//時計の針
		TEXTURE_SCORE,			//スコア
		TEXTURE_SCORE_50,		//50pt
		TEXTURE_SCORE_300,		//100pt

		/* ↓ その他 ↓ */
		TEXTURE_NUMBER,			//数字

		/* ↓ ミニゲーム ↓ */
		TEXTURE_BUTTON,			//ボタン連打
		TEXTURE_GAUGE,			//ゲージ
		TEXTURE_JOYPAD,			//ジョイパッド
		TEXTURE_ITEM,			//アイテム指示

		/* ↓ ステージセレクト ↓ */
		TEXTURE_STATE1,			//ステージ1の画像
		TEXTURE_STATE2,			//ステージ2の画像

		/* メッシュの*/
		TEXTURE_GRASS,
		TEXTURE_GROUND_DART,
	};

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CTexture();
	~CTexture();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	// 初期化
	void Init(void);

	// 終了
	void Uninit(void);

	// テクスチャのゲッター
	LPDIRECT3DTEXTURE9 GetTexture(const int nNumTex);

	// テクスチャの最大数
	int GetMaxTexture() { return m_nMaxTexture; }

	// テクスチャ情報のゲッター
	TEXTURE *GetTextureData() { return m_pTexture; }

	// ファイルの読み込み
	void LoadFile();

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	TEXTURE		*m_pTexture;		// テクスチャ情報
	int			m_nMaxTexture;		// テクスチャの最大数

};

#endif

