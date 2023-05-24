//===================================================
//
// �w�i�̃w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _BG_H_
#define _BG_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object2D.h"

//--------------------------------
// �w�i�N���X
//--------------------------------
class CBg : public CObject
{
public:
	enum BGTYPE
	{
		BGTYPE_TITLE,		//�^�C�g��
		BGTYPE_RESULT,		//���U���g
		BGTYPE_MAX
	};

	CBg();				//�R���X�g���N�^
	~CBg() override;	//�f�X�g���N�^

	//-------------------
	// �����o�֐�
	//-------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }					//�ʒu�̐ݒ�

	//-------------------
	// �Q�b�^�[
	//-------------------
	D3DXVECTOR3 GetPosition() override  { return m_pos; }							//�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
	float GetWidth() override			{ return m_fWidth; }						//���̎擾
	float GetHeight() override			{ return m_fHeight; }						//�����̎擾

	//-------------------
	// �ÓI�����o�֐�
	//-------------------
	static CBg *Create(D3DXVECTOR3 pos, BGTYPE type);	//����

private:
	//-------------------
	// �����o�ϐ�
	//-------------------
	CObject2D* m_pObject2D;		//�I�u�W�F�N�g2D
	D3DXVECTOR3 m_pos;			//�ʒu
	float m_fWidth;				//��
	float m_fHeight;			//����
	BGTYPE m_type;				//���
};

#endif // !_BG_H_