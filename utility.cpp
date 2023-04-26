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

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
D3DXVECTOR3 CUtility::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
D3DXVECTOR3 CUtility::m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O�̈ʒu
D3DXVECTOR3 CUtility::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�傫��
D3DXMATRIX  CUtility::m_mtxWorld;	//���[���h�}�g���b�N�X

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
// �����蔻��̏���
// �����F����(�ʒu�A�O�̈ʒu�A�傫���A�}�g���b�N�X)
//=============================================================================
CUtility::COLLISION CUtility::Collision(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize, D3DXMATRIX* targetMtx)
{
	//------------------------------------
	// �s������ɖ߂�
	//------------------------------------
	//���[���h���W�����߂�
	D3DXVECTOR3 worldPos(0.0f, 0.0f, 0.0f);		//���[���h��̍��W
	D3DXVec3TransformCoord(&worldPos, &m_pos, &m_mtxWorld);

	//�t�s������߂�
	D3DXMATRIX invMtxWorld;						//�t�s��̒l������
	D3DXMatrixInverse(&invMtxWorld, NULL, &m_mtxWorld);

	//�t�s����g���ă��[�J�����W�����߂�
	D3DXVECTOR3 localPos(0.0f, 0.0f, 0.0f);		//���[�J����̍��W
	D3DXVec3TransformCoord(&localPos, &worldPos, &invMtxWorld);

	//------------------------------------
	// �����̒[�̐ݒ�
	//------------------------------------
	float fLeft = localPos.x - (m_size.x / 2);		//�����̍��[
	float fRight = localPos.x + (m_size.x / 2);		//�����̉E�[
	float fTop = localPos.y + (m_size.y / 2);		//�����̏�[
	float fBottom = localPos.y - (m_size.y / 2);	//�����̉��[
	float fFront = localPos.z - (m_size.z / 2);		//�����̑O�[
	float fBack = localPos.z + (m_size.z / 2);		//�����̌�[

	//------------------------------------
	// ����̍s������ɖ߂�
	//------------------------------------
	D3DXVec3TransformCoord(&worldPos, &targetPos, targetMtx);
	D3DXMatrixInverse(&invMtxWorld, NULL, targetMtx);
	D3DXVec3TransformCoord(&localPos, &worldPos, &invMtxWorld);

	//------------------------------------
	// ����̒[�̐ݒ�
	//------------------------------------
	float fTargetLeft = localPos.x + targetSize.x;		//����̍��[
	float fTargetRight = localPos.x - targetSize.x;		//����̉E�[
	float fTargetTop = localPos.y + targetSize.y;		//����̏�[
	float fTargetBottom = localPos.y - targetSize.y;	//����̉��[
	float fTargetFront = localPos.z + targetSize.z;		//����̑O�[
	float fTargetBack = localPos.z - targetSize.z;		//����̌�[

	//------------------------------------
	// �����蔻��
	//------------------------------------
	if (fTargetTop >= fTop && fTargetBottom <= fBottom)
	{//�㉺�͈͓̔��Ȃ�
	 //---------------------------------
	 // �O��̓����蔻��
	 //---------------------------------
		if (fTargetLeft >= fLeft && fTargetRight <= fRight)
		{//���E�͈͓̔��Ȃ�
			if (fTargetFront >= fFront && fTargetFront < m_posOld.z - (m_size.z / 2))
			{
				return COLLISION_FRONT;
			}
			else if (fTargetBack <= fBack && fTargetBack > m_posOld.z - (m_size.z / 2))
			{
				return COLLISION_BACK;
			}
		}
		//---------------------------------
		// ���E�̓����蔻��
		//---------------------------------
		if (fTargetFront >= fFront && fTargetBack <= fBack)
		{//�O��͈͓̔��Ȃ�
			if (fTargetLeft >= fLeft && fTargetLeft < m_posOld.x + (m_size.x / 2))
			{
				return COLLISION_LEFT;
			}
			else if (fTargetRight <= fRight && fTargetRight > m_posOld.x - (m_size.x / 2))
			{
				return COLLISION_RIGHT;
			}
		}
	}

	return COLLISION_NONE;
}

//=============================================================================
// �����߂��ꂽ�ʒu��Ԃ�����
// �����F�ʒu�A�O�̈ʒu�A�傫���A�}�g���b�N�X�A����̎��
//=============================================================================
D3DXVECTOR3 CUtility::GetCollisionPos(D3DXVECTOR3 pos, D3DXVECTOR3 posOld
	, D3DXVECTOR3 size, D3DXMATRIX mtx, CObject::EObjType targetType)
{
	//�����ɑ��
	m_pos = pos;		//�ʒu
	m_posOld = posOld;	//�O�̈ʒu
	m_size = size;		//�傫��
	m_mtxWorld = mtx;	//���[���h�}�g���b�N�X

	//�ϐ��錾
	D3DXVECTOR3 targetPos(0.0f, 0.0f, 0.0f);	//����̈ʒu
	D3DXVECTOR3 targetSize(0.0f, 0.0f, 0.0f);	//����̑傫��
	D3DXMATRIX* targetMtx = nullptr;			//����̃}�g���b�N�X

	//--------------------------
	// ����̏����擾
	//--------------------------
	for (int i = 0; i < CObject::GetMaxPriolity(); i++)
	{//�v���C�I���e�B����
		CObject* pObj;
		pObj = CObject::GETObject(targetType, i);

		if (pObj == nullptr)
		{//null�Ȃ�߂�
			continue;
		}

		//---------------------------
		// �I�u�W�F�N�g�̎�ނ̎擾
		//---------------------------
		CObject::EObjType type = pObj->GetObjType();
		if (type != targetType)
		{//�I�u�W�F�N�g�̎�ނ��ړI�̑��肶��Ȃ��Ȃ�
			continue;
		}

		//-----------------------------
		// ����̎�ނ��Ƃ̏���
		//-----------------------------
		if (targetType == CObject::OBJTYPE_PLAYER)
		{//���肪�v���C���[�Ȃ�
			//�_�E���L���X�g
			CPlayer* pPlayer = (CPlayer*)pObj;

			//���̎擾
			targetPos = pPlayer->GetPosition();
			targetSize = pPlayer->GetSize();
			targetMtx = pPlayer->GetMtxWorld();
		}
		/*else if (targetType == CObject::OBJTYPE_ENEMY)
		{//���肪�G�Ȃ�
			//�_�E���L���X�g
			CEnemy* pEnemy = (CEnemy*)pObj;

			//���̎擾
			targetPos = pEnemy->GetPosition();
			targetSize = pEnemy->GetSize();
			targetMtx = pEnemy->GetmtxWorld();
		}*/

		//--------------------------
		// �����蔻��̏���
		//--------------------------
		CUtility::COLLISION direction = CUtility::Collision(targetPos, targetSize, targetMtx);

		//--------------------------
		// �������������ɉ���������
		//--------------------------
		switch (direction)
		{
		case CUtility::COLLISION_FRONT:
			m_pos.z = targetPos.z + targetSize.z + (size.z / 2);
			break;

		case CUtility::COLLISION_BACK:
			m_pos.z = targetPos.z - targetSize.z - (size.z / 2);
			break;

		case CUtility::COLLISION_LEFT:
			m_pos.x = targetPos.x + targetSize.x + (size.x / 2);
			break;

		case CUtility::COLLISION_RIGHT:
			m_pos.x = targetPos.x - targetSize.x - (size.x / 2);
			break;

		default:
			break;
		}
	}

	return m_pos;
}

//=============================================================================
// ���f���̐�̓����蔻��(��)
// �����F�I�t�Z�b�g���W�A���̒��a�A���[���h�}�g���b�N�X�A����̎��
//==============================================================================
bool CUtility::ColliaionWeapon(D3DXVECTOR3 offset, float fDiameter,
	D3DXMATRIX mtxWorld, CObject::EObjType targetType)
{
	//�ϐ��錾
	D3DXVECTOR3 worldPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 targetPos(0.0f, 0.0f, 0.0f);

	//����܂ł̃I�t�Z�b�g�����Z�����ʒu���擾
	D3DXVec3TransformCoord(&worldPos, &offset, &mtxWorld);

	//�I�t�Z�b�g��Ƀv���C���[���ړ�
	//CGame::GetPlayer()->SetPosition(worldPos);

	//--------------------------------------
	// ���f����𒆐S�Ƃ������̓����蔻��
	//--------------------------------------
	//����̏����擾
	for (int i = 0; i < CObject::GetMaxPriolity(); i++)
	{//�v���C�I���e�B����
		CObject* pObj;
		pObj = CObject::GETObject(targetType, i);

		if (pObj == nullptr)
		{//null�Ȃ�߂�
			continue;
		}

		//---------------------------
		// �I�u�W�F�N�g�̎�ނ̎擾
		//---------------------------
		CObject::EObjType type = pObj->GetObjType();
		if (type != targetType)
		{//�I�u�W�F�N�g�̎�ނ��ړI�̑��肶��Ȃ��Ȃ�
			continue;
		}

		//-----------------------------
		// ����̎�ނ��Ƃ̏���
		//-----------------------------
		if (targetType == CObject::OBJTYPE_PLAYER)
		{//���肪�v���C���[�Ȃ�
			//���̎擾
			targetPos = CApplication::GetGame()->GetPlayer()->GetPosition();
		}
		/*else if (targetType == CObject::OBJTYPE_ENEMY)
		{//���肪�G�Ȃ�
			targetPos = CGame::GetEnemy()->GetPosition();
		}*/

		//2�_�Ԃ̋��������߂�
		D3DXVECTOR3 distance = worldPos - targetPos;

		//�����蔻��								//���͈̔�(���a+���a)
		if (sqrtf(D3DXVec3Dot(&distance, &distance)) < fDiameter)
		{
			return true;
		}
	}

	return false;
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
// �ړ����E�̐ݒ�
// �����F�ʒu
//==============================================================================
D3DXVECTOR3 CUtility::LimitMove(D3DXVECTOR3 pos)
{
	//---------------------
	// �ړ��̌��E�l
	//---------------------
	float fValue = 1800.0f;
	float fLeft = -fValue;
	float fRight = fValue;
	float fFlont = -fValue;
	float fBack = fValue;

	//---------------------
	// X���̌��E
	//---------------------
	if (pos.x <= fLeft)
	{
		pos.x = fLeft;
	}
	else if (pos.x >= fRight)
	{
		pos.x = fRight;
	}

	//---------------------
	// Z���̌��E
	//---------------------
	if (pos.z <= fFlont)
	{
		pos.z = fFlont;
	}
	else if (pos.z >= fBack)
	{
		pos.z = fBack;
	}

	return pos;
}