//===================================================
//
// モードヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _MODE_H_
#define _MODE_H_	

//-------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>

//--------------------------------
// 前方宣言
//--------------------------------
class CGame;		//ゲーム
class CTitle;		//タイトル
class CResult;		//リザルト
class CStageSelect;	//ステージ選択
class CFade;		//フェード

//================================
// モードクラスの定義
//================================
class CMode
{
public:
	//----------------------------
	// モード列挙型の定義
	//----------------------------
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル
		MODE_GAME,			//ゲーム
		MODE_RESULT,		//リザルト
		MODE_STAGESELECT,	//ステージ選択画面
		MODE_FADE,			//フェード
		MODE_MAX
	};

	CMode();	//コンストラクタ
	~CMode();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	static HRESULT Init();
	static void Uninit();
	static void Update();

	//------------------
	// 静的メンバ関数
	//------------------
	static void SetMode(MODE mode);				//モードの設定
	static MODE GetMode() { return m_mode; };	//モードの取得
	static CGame*			GetGame()	{ return m_pGame; }			//ゲームの取得
	static CTitle*			GetTitle()	{ return m_pTitle; }		//タイトルの取得
	static CStageSelect*	GetStage()	{ return m_pStageSelect; }	//ステージの取得
	static CFade*			GetFade()	{ return m_pFade; }			//フェードの取得

private:
	//------------------
	// 静的メンバ変数
	//------------------
	static MODE				m_mode;			//モード
	static CGame*			m_pGame;		//ゲーム
	static CTitle*			m_pTitle;		//タイトル
	static CResult*			m_pResult;		//リザルト
	static CStageSelect*	m_pStageSelect;	//ステージ選択
	static CFade*			m_pFade;		//フェード
};

#endif