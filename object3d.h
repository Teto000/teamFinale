//===================================================
//
// �I�u�W�F�N�g3D�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "main.h"
#include "renderer.h"
#include "texture.h"

//================================
// �I�u�W�F�N�g3D�N���X�̒�`
//================================
class CObject3D : public CObject
{
public:
	CObject3D();
	explicit CObject3D(int nPriority);	//�R���X�g���N�^
	virtual ~CObject3D() override;		//�f�X�g���N�^

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
	void SetPos(D3DXVECTOR3 pos);	//�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col);	//�F�̐ݒ�
	void SetSize(float fWidth, float fHeight, float fDepth);
	void SetVtx(VERTEX_3D* vtx);	//���_���̐ݒ�

	/* ���e�N�X�`���� */
	void SetTexCIE(float left, float fRight);		//�e�N�X�`�����W�̐ݒ�
	void SetTexture(CTexture::NUM_TEXTURE numTex);	//�e�N�X�`���̐ݒ�

	/* ���`�恫 */
	void SetSubALPHA();		//���u�����f�B���O�����Z�����ɐݒ�
	void ResetSubALPHA();	//���u�����f�B���O�����ɖ߂�

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override;	//�ʒu�̎擾
	float GetWidth() override;			//���̎擾
	float GetHeight() override;			//�����̎擾

private:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_Depth;		//���s��
	float m_fRot;		//��]�p�x
	float m_fScal;		//�傫��
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::NUM_TEXTURE m_NumTex;		//�e�N�X�`��
};

#endif // !_OBJECT_H_