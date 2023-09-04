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
#include "renderer.h"

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
bool CUtility::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
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
	float fTargetRight = targetPos.x + (targetSize.x / 2);	//����̉E�[
	float fTargetLeft = targetPos.x - (targetSize.x / 2);	//����̍��[
	float fTargetTop = targetPos.y + (targetSize.y / 2);	//����̏�[
	float fTargetBottom = targetPos.y - (targetSize.y / 2);	//����̉��[
	float fTargetFront = targetPos.z + (targetSize.z / 2);	//����̑O�[
	float fTargetBack = targetPos.z - (targetSize.z / 2);	//����̌�[

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
		// ���E�̓����蔻��
		//---------------------------------
		if (fTargetFront >= fFront && fTargetBack <= fBack)
		{//�O��͈͓̔��Ȃ�
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
		// �O�㍶�E�͈͓̔��Ȃ�
		//---------------------------------
		if (fTargetRight >= fLeft && fTargetLeft <= fRight
			&& fTargetFront >= fFront && fTargetBack <= fBack)
		{
			//�������Ă����Ԃɂ���
			bCollision = true;
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

//=============================================================================
// �X�N���[�����W�����[���h���W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CUtility::ScreenCastWorld(const D3DXVECTOR3 &pos,CCamera *pCamera)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = pCamera->GetMtxProjection();

	// �}�g���b�N�X�̏�Z
	mtx = mtxTrans * mtxView * mtxPrj;

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	float w = (float)SCREEN_WIDTH / 2.0f;
	float h = (float)SCREEN_HEIGHT / 2.0f;

	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �}�g���b�N�X��XYZ
	D3DXVECTOR3 vec = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	D3DXVec3TransformCoord(&vec, &vec, &mtxViewPort);

	return vec;
}

//=============================================================================
// ���[���h���W���X�N���[�����W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CUtility::WorldCastScreen(const D3DXVECTOR3 &pos, CCamera *pCamera)
{
	// �v�Z�p�x�N�g��
	D3DXVECTOR3 vec = pos;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = pCamera->GetMtxProjection();

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	D3DXMatrixIdentity(&mtxViewPort);
	float w = (float)SCREEN_WIDTH / 2.0f;
	float h = (float)SCREEN_HEIGHT / 2.0f;
	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �t�s��̎Z�o
	D3DXMatrixInverse(&mtxView, NULL, &mtxView);
	D3DXMatrixInverse(&mtxPrj, NULL, &mtxPrj);
	D3DXMatrixInverse(&mtxViewPort, NULL, &mtxViewPort);

	// �t�ϊ�
	mtx = mtxViewPort * mtxPrj * mtxView;
	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(vec.x, vec.y, vec.z), &mtx);

	return vec;
}