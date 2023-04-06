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

//================================
// �I�u�W�F�N�gX�N���X�̒�`
//================================
class CObjectX : public CObject
{
public:
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
	void SetPos(D3DXVECTOR3 pos);		//�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);		//�����̐ݒ�
	void SetFireName(LPCTSTR text);		//X�t�@�C���̖��O��ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override;	//�ʒu�̎擾
	float GetWidth() override;			//���̎擾
	float GetHeight() override;			//�����̎擾

private:
	void DrawShadow();

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	LPCTSTR m_name;						//X�t�@�C���̖��O

	/* �� ���f����� �� */
	LPD3DXMESH m_pMesh;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;					//�}�e���A�����̐�
};

#endif