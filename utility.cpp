//===================================================
//
// �֗��Ȃ�̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "utility.h"
#include "application.h"
#include "player.h"
//#include "enemy.h"
#include "game.h"
#include "debug_proc.h"

//=======================================
// �R���X�g���N�^
//=======================================
CUtility::CUtility()
{

}

//=======================================
// �f�X�g���N�^
//=======================================
CUtility::~CUtility()
{

}

//=============================================================================
// �����߂��ꂽ�ʒu��Ԃ������蔻�菈��
// �����F�����̈ʒu,�����̑O�̈ʒu,�����̑傫��,����̈ʒu,����̑傫��
//==============================================================================
bool CUtility::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
									D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize)
{
	bool bCollision = false;

	//------------------------------------
	// �����̒[�̐ݒ�
	//------------------------------------
	float fLeft = pos.x - (size.x / 2);		//�����̍��[
	float fRight = pos.x + (size.x / 2);	//�����̉E�[
	float fTop = pos.y + (size.y / 2);		//�����̏�[
	float fBottom = pos.y - (size.y / 2);	//�����̉��[
	float fFront = pos.z - (size.z / 2);	//�����̑O�[
	float fBack = pos.z + (size.z / 2);		//�����̌�[

	//------------------------------------
	// ����̒[�̐ݒ�
	//------------------------------------
	float fTargetRight = targetPos.x + targetSize.x;	//����̉E�[
	float fTargetLeft = targetPos.x - targetSize.x;		//����̍��[
	float fTargetTop = targetPos.y + targetSize.y;		//����̏�[
	float fTargetBottom = targetPos.y - targetSize.y;	//����̉��[
	float fTargetFront = targetPos.z + targetSize.z;	//����̑O�[
	float fTargetBack = targetPos.z - targetSize.z;		//����̌�[

	//------------------------------------
	// �����蔻��
	//------------------------------------
	if (fTargetTop >= fTop && fTargetBottom <= fBottom)
	{//�㉺�͈͓̔��Ȃ�
		//---------------------------------
		// �O��̓����蔻��
		//---------------------------------
		if (fTargetRight >= fLeft && fTargetLeft <= fRight)
		{//���E�͈͓̔��Ȃ�
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
		// ���E�̓����蔻��
		//---------------------------------
		if (fTargetFront >= fFront && fTargetBack <= fBack)
		{//�O��͈͓̔��Ȃ�
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
// �p�x�̐��K��
// �����F�p�x
//==============================================================================
float CUtility::GetNorRot(float rot)
{
	float rotData = rot;

	if (rotData > D3DX_PI)
	{//�p�x��180�ȏ�Ȃ�
		rotData -= D3DX_PI * 2;
	}
	else if (rotData < -D3DX_PI)
	{//�p�x��-180�ȉ��Ȃ�
		rotData += D3DX_PI * 2;
	}

	return rotData;
}