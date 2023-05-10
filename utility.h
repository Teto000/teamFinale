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
	//�����߂��ꂽ�ʒu��Ԃ������蔻�菈��
	static D3DXVECTOR3 Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size,
									D3DXVECTOR3 targetPos, D3DXVECTOR3 targetSize);

	//�p�x�̐��K��
	static float GetNorRot(float rot);
};

#endif _UTILITY_H_