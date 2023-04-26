//===================================================
//
// �~�j�Q�[����Ճw�b�_�[
// Author : Kajita Hiromu
//
//===================================================
#ifndef _MINI_GAME_BASIS_H_
#define _MINI_GAME_BASIS_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"

//================================
// �~�j�Q�[����ՃN���X
//================================
class CMiniGameBasis : public CObject2D
{
public:

	enum MiniGameType		//�~�j�Q�[���̎��
	{
		TYPE_BUTTUNPUSH = 0,
		TYPE_A,
		TYPE_MAX
	};

	CMiniGameBasis();				//�R���X�g���N�^
	~CMiniGameBasis() override;		//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �Z�b�^�[
	//------------------
	void SetScaling(float fWidth, float fHeight);		//�g�k
	void SetEnable(bool bEnable) { m_bDraw = bEnable; }	//�`�悷�邩�ǂ���

	//------------------
	// �Q�b�^�[
	//------------------
	MiniGameType GetGameType() { return m_nType; }

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CMiniGameBasis* Create(D3DXVECTOR3 pos, MiniGameType nType);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	MiniGameType m_nType;	//�~�j�Q�[���̎��
	bool m_bDraw;			//�`��t���O
};

#endif