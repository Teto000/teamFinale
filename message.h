//===================================================
//
// メッセージヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_	//二重インクルード防止

//-------------------------------
// インクルード
//-------------------------------
#include "object2d.h"

//================================
// メッセージクラス
//================================
class CMessage : public CObject2D
{
public:
	enum MESSAGETYPE
	{
		MESSAGETYPE_NONE = 0,
		MESSAGE_TYPE_FINISH,
		MESSAGE_TYPE_COMPLETE
	};

	CMessage();		//コンストラクタ
	~CMessage();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ変数
	//------------------
	static CMessage* Create(D3DXVECTOR3 pos, MESSAGETYPE m_type);

private:
	MESSAGETYPE m_type;
	int m_nTime;
};

#endif