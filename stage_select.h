//===================================================
//
// �X�e�[�W�I���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_	

//----------------------------------
// �C���N���[�h
//----------------------------------
#include <d3dx9.h>

//----------------------------------
// �O���錾
//----------------------------------
class CCamera;		//�J����
class CMeshField;	//���b�V���t�B�[���h(�n��)
class CObjectX;		//�I�u�W�F�N�gX
class CPlayer;		//�v���C���[

//==================================
// �^�C�g���N���X�̒�`
//==================================
class CStageSelect
{
public:
	CStageSelect();		//�R���X�g���N�^
	~CStageSelect();	//�f�X�g���N�^

	//-------------------------
	// �����o�֐�
	//-------------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//-------------------------
	// �Q�b�^�[
	//-------------------------
	CCamera*	GetCamera()		{ return m_pCamera; }	//�J�������擾
	CObjectX*	GetObjectX()	{ return m_pObjectX; }	//�I�u�W�F�N�g�̎擾
	CPlayer*	GetPlayer()		{ return m_pPlayer; }	//�v���C���[�̎擾

private:
	//-------------------------
	// �����o�ϐ�
	//-------------------------
	CCamera*	m_pCamera;		//�J����
	CMeshField*	m_pMeshField;	//���b�V���t�B�[���h
	CObjectX*	m_pObjectX;		//�I�u�W�F�N�g
	CPlayer*	m_pPlayer;		//�v���C���[
};

#endif