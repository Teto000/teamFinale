//===================================================
//
// ���b�V���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MESH_H_
#define _MESH_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object3d.h"
#include "renderer.h"

//================================
// ���b�V���N���X
//================================
class CMesh : public CObject
{
public:
	CMesh();
	explicit CMesh(int nPriority);	//�R���X�g���N�^
	~CMesh();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CollisionMesh();	//���b�V���t�B�[���h�̓����蔻��

	void SetMeshSize(int nDivision, float fWidth);		//�ő啝�̐ݒ�
	void SetTexture(CTexture::NUM_TEXTURE numTex);		//�e�N�X�`���̐ݒ�

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }					//�ʒu�̐ݒ�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override;													//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f,0.0f,0.0f); }			//�ʒu�̎擾
	float GetWidth() override;															//���̎擾
	float GetHeight() override;															//�����̎擾

private:
	void SetVtxNor(VERTEX_3D* pVtx, WORD* pIdx);	//���_�̖@����ݒ�

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxVtx = 512;	//���_�̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_VtxPos[nMaxVtx];	//���_�̈ʒu
	D3DXVECTOR3 m_Normal;			//�ʖ@���x�N�g���i�[�p
	D3DXVECTOR3 m_VtxNor[nMaxVtx];	//���_�̖@���x�N�g���i�[�p
	D3DXVECTOR3 m_rot;				//����
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X

	/* �� ���b�V�����\�������� */
	int m_nNumDivision ;	//�|���S���̕�����
	int m_nCntVtx ;			//���_�̕�����
	int m_nNumVtx;			//���_��
	int m_nNumPolygon;		//�|���S����
	int m_nNumIndex;		//�C���f�b�N�X��
	float m_fMaxWidth;		//���b�V���t�B�[���h�̍ő啝
	float m_fMeshWidth;		//���b�V���t�B�[���h�̕�
	float m_fTexSize;		//�e�N�X�`���̕����T�C�Y

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::NUM_TEXTURE m_NumTex;		//�e�N�X�`��
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
};

#endif