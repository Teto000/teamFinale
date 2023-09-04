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
#include "renderer.h"

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
bool CUtility::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
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
	float fTargetRight = targetPos.x + (targetSize.x / 2);	//相手の右端
	float fTargetLeft = targetPos.x - (targetSize.x / 2);	//相手の左端
	float fTargetTop = targetPos.y + (targetSize.y / 2);	//相手の上端
	float fTargetBottom = targetPos.y - (targetSize.y / 2);	//相手の下端
	float fTargetFront = targetPos.z + (targetSize.z / 2);	//相手の前端
	float fTargetBack = targetPos.z - (targetSize.z / 2);	//相手の後端

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
			if (fTargetFront >= fFront && fTargetFront < posOld.z + (size.z / 2))
			{
				pos.z = fTargetFront + (size.z / 2);
			}
			else if (fTargetBack <= fBack && fTargetBack > posOld.z - (size.z / 2))
			{
				pos.z = fTargetBack - (size.z / 2);
			}
		}
		//---------------------------------
		// 左右の当たり判定
		//---------------------------------
		if (fTargetFront >= fFront && fTargetBack <= fBack)
		{//前後の範囲内なら
			if (fTargetRight >= fLeft && fTargetRight < posOld.x + (size.x / 2))
			{
				pos.x = fTargetRight + (size.x / 2);
			}
			else if (fTargetLeft <= fRight && fTargetLeft > posOld.x - (size.x / 2))
			{
				pos.x = fTargetLeft - (size.x / 2);
			}
		}

		//---------------------------------
		// 前後左右の範囲内なら
		//---------------------------------
		if (fTargetRight >= fLeft && fTargetLeft <= fRight
			&& fTargetFront >= fFront && fTargetBack <= fBack)
		{
			//当たっている状態にする
			bCollision = true;
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

//=============================================================================
// スクリーン座標をワールド座標にキャストする
// Author : 唐﨑結斗
// 概要 : 
//=============================================================================
D3DXVECTOR3 CUtility::ScreenCastWorld(const D3DXVECTOR3 &pos,CCamera *pCamera)
{
	// 計算用マトリックス
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// カメラのビューマトリックスの取得
	mtxView = pCamera->GetMtxView();

	// カメラのプロジェクションマトリックスの取得
	mtxPrj = pCamera->GetMtxProjection();

	// マトリックスの乗算
	mtx = mtxTrans * mtxView * mtxPrj;

	// ビューポート行列（スクリーン行列）の作成
	float w = (float)SCREEN_WIDTH / 2.0f;
	float h = (float)SCREEN_HEIGHT / 2.0f;

	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// マトリックスのXYZ
	D3DXVECTOR3 vec = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	D3DXVec3TransformCoord(&vec, &vec, &mtxViewPort);

	return vec;
}

//=============================================================================
// ワールド座標をスクリーン座標にキャストする
// Author : 唐﨑結斗
// 概要 : 
//=============================================================================
D3DXVECTOR3 CUtility::WorldCastScreen(const D3DXVECTOR3 &pos, CCamera *pCamera)
{
	// 計算用ベクトル
	D3DXVECTOR3 vec = pos;

	// 計算用マトリックス
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// カメラのビューマトリックスの取得
	mtxView = pCamera->GetMtxView();

	// カメラのプロジェクションマトリックスの取得
	mtxPrj = pCamera->GetMtxProjection();

	// ビューポート行列（スクリーン行列）の作成
	D3DXMatrixIdentity(&mtxViewPort);
	float w = (float)SCREEN_WIDTH / 2.0f;
	float h = (float)SCREEN_HEIGHT / 2.0f;
	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// 逆行列の算出
	D3DXMatrixInverse(&mtxView, NULL, &mtxView);
	D3DXMatrixInverse(&mtxPrj, NULL, &mtxPrj);
	D3DXMatrixInverse(&mtxViewPort, NULL, &mtxViewPort);

	// 逆変換
	mtx = mtxViewPort * mtxPrj * mtxView;
	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(vec.x, vec.y, vec.z), &mtx);

	return vec;
}