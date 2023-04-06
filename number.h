//===================================================
//
// ���l�\���p�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"

//================================
// �i���o�[�N���X
//================================
class CNumber : public CObject2D
{
public:
	CNumber();				//�R���X�g���N�^
	~CNumber() override;	//�f�X�g���N�^

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
	void Set(int nDigit);	//���l�̐ݒ�
	void SetScaling(float fWidth, float fHeight);	//�g�k
	void SetEnable(bool bEnable) { m_bDraw = bEnable; }	//�`�悷�邩�ǂ���

	//------------------
	// �Q�b�^�[
	//------------------
	int Get() { return m_nValue; }	//���l�̎擾

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CNumber* Create(D3DXVECTOR3 pos, int nValue);

private:
	//------------------
	// �����o�ϐ�
	//------------------
	int m_nValue;	//���l
	int m_nDigit;	//����
	bool m_bDraw;	//�`��t���O
};

#endif