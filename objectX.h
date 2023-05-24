//===================================================
//
// �I�u�W�F�N�gX�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CModel3D;

//================================
// �I�u�W�F�N�gX�N���X�̒�`
//================================
class CObjectX : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CObjectX *Create();			// ���f���̐���

	CObjectX();
	explicit CObjectX(int nPriority);	//�R���X�g���N�^
	virtual ~CObjectX() override;		//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }					//�ʒu�̐ݒ�
	void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }				//
	void SetRot(D3DXVECTOR3 rot);											//�����̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override;										//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return m_posOld; }					//�ʒu�̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }									//�����̃Q�b�^�[
	float GetWidth() override;												//���̎擾
	float GetHeight() override;												//�����̎擾
	void SetType(const int nType);											// �^�C�v�̐ݒ�
	void SetMtx(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }
	D3DXMATRIX GetMtx() { return m_mtxWorld; }
	CModel3D *GetModel() { return m_pModel; }

private:
	//----------------
	// �����o�ϐ�
	//----------------
	CModel3D *m_pModel;					//���f�����
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_posOld;				//�ߋ��ʒu
	D3DXVECTOR3 m_rot;					//����
	int m_nType;						//���f���̃^�C�v
};

#endif