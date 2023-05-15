//===================================================
//
// 便利なやつの処理
// Author:Teruto Sato
//
//===================================================

//------------------------
// インクルード
//------------------------
#include "utility.h"
#include "application.h"
#include "player.h"
//#include "enemy.h"
#include "game.h"
#include "debug_proc.h"

//=======================================
// コンストラクタ
//=======================================
CUtility::CUtility()
{

}

//=======================================
// デストラクタ
//=======================================
CUtility::~CUtility()
{

}

//=============================================================================
// 押し戻された位置を返す当たり判定処理
// 引数：自分の位置,自分の前の位置,自分の大きさ,相手の位置,相手の大きさ
//==============================================================================
bool CUtility::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
									D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize)
{
	bool bCollision = false;

	//------------------------------------
	// 自分の端の設定
	//------------------------------------
	float fLeft = pos.x - (size.x / 2);		//自分の左端
	float fRight = pos.x + (size.x / 2);	//自分の右端
	float fTop = pos.y + (size.y / 2);		//自分の上端
	float fBottom = pos.y - (size.y / 2);	//自分の下端
	float fFront = pos.z - (size.z / 2);	//自分の前端
	float fBack = pos.z + (size.z / 2);		//自分の後端

	//------------------------------------
	// 相手の端の設定
	//------------------------------------
	float fTargetRight = targetPos.x + targetSize.x;	//相手の右端
	float fTargetLeft = targetPos.x - targetSize.x;		//相手の左端
	float fTargetTop = targetPos.y + targetSize.y;		//相手の上端
	float fTargetBottom = targetPos.y - targetSize.y;	//相手の下端
	float fTargetFront = targetPos.z + targetSize.z;	//相手の前端
	float fTargetBack = targetPos.z - targetSize.z;		//相手の後端

	//------------------------------------
	// 当たり判定
	//------------------------------------
	if (fTargetTop >= fTop && fTargetBottom <= fBottom)
	{//上下の範囲内なら
		//---------------------------------
		// 前後の当たり判定
		//---------------------------------
		if (fTargetRight >= fLeft && fTargetLeft <= fRight)
		{//左右の範囲内なら
			//bCollision = true;
			if (fTargetFront >= fFront && fTargetFront < posOld.z + (size.z / 2))
			{
				pos.z = targetPos.z + targetSize.z + (size.z / 2);
			}
			else if (fTargetBack <= fBack && fTargetBack > posOld.z - (size.z / 2))
			{
				pos.z = targetPos.z - targetSize.z - (size.z / 2);
			}
		}
		//---------------------------------
		// 左右の当たり判定
		//---------------------------------
		if (fTargetFront >= fFront && fTargetBack <= fBack)
		{//前後の範囲内なら
			bCollision = true;

			if (fTargetRight >= fLeft && fTargetRight < posOld.x + (size.x / 2))
			{
				pos.x = targetPos.x + targetSize.x + (size.x / 2);
			}
			else if (fTargetLeft <= fRight && fTargetLeft > posOld.x - (size.x / 2))
			{
				pos.x = targetPos.x - targetSize.x - (size.x / 2);
			}
		}
	}

	return bCollision;
}

//=============================================================================
// 角度の正規化
// 引数：角度
//==============================================================================
float CUtility::GetNorRot(float rot)
{
	float rotData = rot;

	if (rotData > D3DX_PI)
	{//角度が180以上なら
		rotData -= D3DX_PI * 2;
	}
	else if (rotData < -D3DX_PI)
	{//角度が-180以下なら
		rotData += D3DX_PI * 2;
	}

	return rotData;
}