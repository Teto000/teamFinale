//===================================================
//
// �֗��Ȃ�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_	//��d�C���N���[�h�h�~

//--------------------------
// �C���N���[�h
//--------------------------
#include "object.h"

//================================
// ���[�e�B���e�B�N���X�̒�`
//================================
class CUtility
{
public:
	//--------------------------
	// �����蔻��̌���
	//--------------------------
	enum COLLISION
	{
		COLLISION_NONE = 0,	//�������Ă��Ȃ�
		COLLISION_FRONT,	//�O���瓖������
		COLLISION_BACK,		//��납��
		COLLISION_LEFT,		//������
		COLLISION_RIGHT,	//�E����
		COLLISION_MAX
	};

	CUtility();		//�R���X�g���N�^
	~CUtility();	//�f�X�g���N�^

	//-----------------------
	// �ÓI�����o�֐�
	//-----------------------
	//�����蔻��̏���
	static COLLISION Collision(D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize, D3DXMATRIX* targetMtx);

	//�����߂��ꂽ�ʒu��Ԃ�����
	static D3DXVECTOR3 GetCollisionPos(D3DXVECTOR3 pos, D3DXVECTOR3 posOld
		, D3DXVECTOR3 size, D3DXMATRIX mtx, CObject::EObjType targetType);

	//���f����̓����蔻��(��)
	static bool ColliaionWeapon(D3DXVECTOR3 offset, float fDiameter,
		D3DXMATRIX mtxWorld, CObject::EObjType type);

	//�p�x�̐��K��
	static float GetNorRot(float rot);

	//�ړ����E�̐ݒ�
	static D3DXVECTOR3 LimitMove(D3DXVECTOR3 pos);

private:
	//-----------------------
	// �ÓI�����o�ϐ�
	//-----------------------
	static D3DXVECTOR3 m_pos;		//�ʒu
	static D3DXVECTOR3 m_posOld;	//�O�̈ʒu
	static D3DXVECTOR3 m_size;		//�傫��
	static D3DXMATRIX  m_mtxWorld;	//���[���h�}�g���b�N�X
};

#endif _UTILITY_H_