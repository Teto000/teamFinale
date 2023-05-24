//===================================================
//
// �X�J�C�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _SKY_H_
#define _SKY_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"
#include "texture.h"

//================================
// �X�J�C�w�b�_�[�̒�`
//================================
class CSky : public CObject
{
public:
	CSky();				//�R���X�g���N�^
	~CSky() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition()override { return m_pos; }								//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
	float GetWidth() override { return 0; };										//���̎擾
	float GetHeight() override { return 0; };										//�����̎擾

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CSky* Create(CTexture::NUM_TEXTURE numTex);

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxVtx = 512;			//���_�̍ő吔

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_VtxPos[nMaxVtx];	//���_�̈ʒu
	D3DXVECTOR3 m_Normal;			//�ʖ@���x�N�g���i�[�p
	D3DXVECTOR3 m_VtxNor[nMaxVtx];	//���_�̖@���x�N�g���i�[�p
	D3DXVECTOR3 m_rot;				//����
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X

	/* �� ���b�V�����\�������� */
	int m_nNumVtx;			//���_��
	int m_nNumPolygon;		//�|���S����
	int m_nNumIndex;		//�C���f�b�N�X��
	int m_vertical;			//���������̕�����
	float m_fWidth;			//��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::NUM_TEXTURE m_NumTex;		//�e�N�X�`��
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
};

#endif#pragma once
