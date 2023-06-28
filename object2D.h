//=====================================
//
// �I�u�W�F�N�g2D�w�b�_�[
// Author : Sato Teruto
//
//=====================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "texture.h"

//--------------------------------
// �I�u�W�F�N�g2D�N���X�̒�`
//--------------------------------
class CObject2D : public CObject
{
public:
	CObject2D();
	explicit CObject2D(int nPriority);	//�R���X�g���N�^
	virtual ~CObject2D() override;		//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	virtual HRESULT Init(D3DXVECTOR3 pos) override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	
	static CObject2D *Create(D3DXVECTOR3 pos);		//����
	D3DXVECTOR3 AddMove(D3DXVECTOR3 move);			//�ړ��ʂ̉��Z

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }					//�ʒu�̐ݒ�
	void SetSize(float fWidth, float fHeight);				//�傫���̐ݒ�
	void SetColor(D3DXCOLOR col);							//�F�̐ݒ�
	void SetScreenX(float posX, float fLeft, float fRight);	//���E��ʒ[�̐ݒ�
	void SetScreenY(float posY, float fUp, float fDown);	//�㉺��ʒ[�̐ݒ�
	void SetAnimation(float fNumber, int nPattern);			//�A�j���[�V�����̐ݒ�
	void SetSplitTex(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY);	//�A�j���[�V�����̐ݒ�

	bool OutScreen(D3DXVECTOR3 pos);	//��ʊO�ɏo������
	D3DXVECTOR3 MoveCircle(D3DXVECTOR3 CenterPos, float fAngle, float fLength);	//�ʒu���~�`�ɓ�����

	/* ���e�N�X�`���� */
	void SetTexCIE(float left, float fRight);		//�e�N�X�`�����W�̐ݒ�
	void SetTexture(CTexture::NUM_TEXTURE numTex);	//�e�N�X�`���̐ݒ�

	/* �����_���W�� */
	void SetVtxCIE(D3DXVECTOR3 pos, float fWidth, float fHeight);						//���_���W�̐ݒ�
	void SetVtxCIE_Rot(D3DXVECTOR3 pos, float rotX, float fWidth, float fHeight);		//���_���W�̐ݒ�(��])
	void SetVtxCIE_Gauge(D3DXVECTOR3 pos, float fWidth1,
						float fWidth2, float fHeight1, float fHeight2);					//���_���W�̐ݒ�(�Q�[�W)
	void SetVtxCIE_Score(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace);	//���_���W�̐ݒ�(�X�R�A)

	/* ���`�恫 */
	void SetAddALPHA();		//���u�����f�B���O�����Z�����ɐݒ�
	void ResAddALPHA();		//���u�����f�B���O�����ɖ߂�
	
	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override	{ return m_pos; }							//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override	{ return D3DXVECTOR3(0.0f,0.0f,0.0f); }		//�ʒu�̎擾
	D3DXVECTOR3 GetTargetPos()		    { return m_TargetPos; }						//����̈ʒu�̎擾
	float GetWidth() override			{ return m_fWidth; }						//���̎擾
	float GetHeight() override			{return m_fHeight; }						//�����̎擾

protected:
	//----------------
	// �����o�ϐ�
	//----------------
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_TargetPos;	//����̈ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	float m_fWidth;				//��
	float m_fHeight;			//����
	float m_fRot;				//��]�p�x
	float m_fScal;				//�傫��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::NUM_TEXTURE m_NumTex;		//�e�N�X�`��
};

#endif // !_OBJECT_H_