//===================================================
//
// �X�e�B�b�N��]�Q�[���w�b�_�[
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MG_STICKROTATE_H_
#define _MG_STICKROTATE_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "mini_game_basis.h"

//-------------------------------
// �}�N����`
//-------------------------------

//-------------------------------
// �O���錾
//-------------------------------
class CObject2D;

//================================
// �~�j�Q�[����ՃN���X
//================================
class CStickRotate : public CMiniGameBasis
{
public:

	enum SticPos
	{
		STICK_UP = 0,
		STICK_DOWN,
		STICK_LEFT,
		STICK_RIGHT,
		STICK_UPLEFT,
		STICK_UPRIGHT,
		STICK_DOWNLEFT,
		STICK_DOWNRIGHT,
		STICK_MAX
	};

	CStickRotate();				//�R���X�g���N�^
	~CStickRotate() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CStickRotate* Create(D3DXVECTOR3 pos);

private:

	//------------------
	// �����o�ϐ�
	//------------------
	CObject2D *pObj2D;			//�I�u�W�F�N�g2D
	D3DXCOLOR m_col;				//�J���[
	D3DXVECTOR3 m_PolygonPos;		//�|���S���̈ʒu
	D3DXVECTOR3 m_pos;				//�ʒu
	SticPos m_stick;
	SticPos m_stickold;

	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	int m_nStickCount;	//�A�Ő�
	bool m_bStick;
};

#endif
