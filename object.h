//===================================================
//
// オブジェクトヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_	

//-------------------------------
// インクルード
//-------------------------------
#include <d3dx9.h>

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_OBJECT		(512)	//オブジェクトの最大数

//-------------------------------
// 前方宣言
//-------------------------------
class CCollision;

//================================
// オブジェクトクラス
//================================
class CObject
{
public:
	//------------------------
	// オブジェクトの種類
	//------------------------
	enum EObjType
	{
		OBJTYPE_NONE = -1,	// タイプ無し
		OBJTYPE_FADE = 0,	//フェード
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//エネミー
		OBJTYPE_MESSAGE,	//メッセージ
		OBJTYPE_MESH,		//メッシュ
		OBJTYPE_MESHORBIT,	//軌跡
		OBJTYPE_GAUGE,		//ゲージ
		OBJTYPE_NUMBER,		//数値
		OBJTYPE_STYLESHIFT,	//スタイルシフト
		OBJTYPE_MINIGAME,	//ミニゲーム
		OBJTYPE_ITEM,		//アイテム
		OBJTYPE_CLOCK,		//時計
		OBJTYPE_BREAK,		//壊れたオブジェクト
		OBJTYPE_PAVILION,	//東屋
		OBJTYPE_PAVILION_BREAK,	//壊れ東屋
		OBJTYPE_FOUNTAIN,	//噴水
		OBJTYPE_FOUNTAIN_BREAK,	//壊れ噴水
		OBJTYPE_SLIDE,		//滑り台
		OBJTYPE_SLIDE_BREAK,	//壊れ滑り台
		OBJTYPE_SWING,		//ブランコ
		OBJTYPE_SWING_BREAK,	//壊れブランコ
		OBJTYPE_SEESAW,		//シーソー
		OBJTYPE_SEESAW_BREAK,	//壊れシーソー
		OBJTYPE_MAX,
	};

	explicit CObject(int nPriority);	//コンストラクタ
	virtual ~CObject();					//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void Release();

	//----------------
	// 静的メンバ関数
	//----------------
	static void ReleaseAll(bool bFinish);
	static void UpdateAll();
	static void DrawAll();
	static int GetNumAll();

	static CObject *GETObject(EObjType type, int nNum);
	void SetObjType(EObjType ObjType);	//種類の設定
	EObjType GetObjType();				//種類の取得

	// セッター
	virtual void SetPos(D3DXVECTOR3 pos) = 0;

	//ゲッター
	virtual D3DXVECTOR3 GetPosition() = 0;
	virtual D3DXVECTOR3 GetPosOld() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
	static const int GetMaxPriolity() { return nMaxPriority; }	//プライオリティの最大数を返す

private:
	void Death(CObject* pObj);

protected:
	//--------------------------------------------------------------------
	// 定義
	//--------------------------------------------------------------------
	typedef void (CObject::*UPDATE_FUNC)();

	// セッター
	void SetState(const int nState) { m_nState = nState; }

	//ゲッター
	int GetState() const { return m_nState; }

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxPriority = 4;

	//----------------
	// メンバ変数
	//----------------
	CObject* m_pPrev;			//1つ前のオブジェクト
	CObject* m_pNext;			//1つ後のオブジェクト
	CCollision *m_pCollision;	// 当たり判定
	EObjType m_ObjType;			//オブジェクトの種類
	int m_nState;				// 状態
	bool m_bDeath;				//死亡フラグ

	//----------------
	// 静的メンバ変数
	//----------------
	static CObject* m_Top[nMaxPriority];		//最初のオブジェクト
	static CObject*	m_Current[nMaxPriority];	//最後のオブジェクト
	int m_nPriority;	//プライオリティの番号
};

#endif // !_OBJECT_H_