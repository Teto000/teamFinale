//===================================================
//
// �J�����w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _CAMERA_H_	//���̃}�N������`����ĂȂ�������
#define _CAMERA_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "main.h"

//================================
// �J�����N���X�̒�`
//================================
class CCamera
{
public:
	CCamera();	//�R���X�g���N�^
	~CCamera();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	void Init();
	void Uninit();
	void Update();
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CCamera* CCamera::Create();

	//------------------
	// �Z�b�^�[
	//------------------
	void ShakeCamera(int fream, float magnitude, D3DXVECTOR3 max);	//�J�����̐U�����̐ݒ�
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }	//���_�̐ݒ�
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }	//�����_�̐ݒ�

	//------------------
	// �Q�b�^�[
	//------------------
	D3DXVECTOR3 GetPosV()		{ return m_posV; }		//���_���擾
	D3DXVECTOR3 GetInitPosV()	{ return m_initPosV; }	//���_�̏����l���擾
	D3DXVECTOR3 GetPosR()		{ return m_posR; }		//�����_���擾
	D3DXVECTOR3 GetRot()		{ return m_rot; }		//�p�x���擾
	D3DXMATRIX GetMtxProjection() { return m_mtxProjection; }
	D3DXMATRIX GetMtxView()		{ return m_mtxView; }

private:
	void Turn();	//����
	void Follow();	//�Ǐ]

private:
	//------------------
	// �萔
	//------------------
	static const float m_fSpeed;	//���񑬓x

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_posV;			//���݂̎��_
	D3DXVECTOR3 m_initPosV;		//���_�̏����l
	D3DXVECTOR3 m_posR;			//���݂̒����_
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_worldPosV;	//���[���h���W(���_)
	D3DXVECTOR3 m_worldPosR;	//���[���h���W(�����_)
	D3DXVECTOR3 m_posVDest;		//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;		//�ړI�̒����_
	D3DXVECTOR3 m_rotDest;		//�ړI�̊p�x
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 m_maxShake;		//�h��̍ő�l
	D3DXMATRIX  m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X

	//�J�����̐U��
	int m_nQuakeFreamCount;		//�h�炷�t���[����
	float m_fQuakeMagnitude;	//�h��̗�
};

#endif