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
class CObject2D;	//�I�u�W�F�N�g2D
class CTime;		//����

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
	// �Z�b�^�[
	//-------------------------
	static void SetViewMap(bool bView)	{ m_bViewMap = bView; }	//�}�b�v�\����Ԃ̐ݒ�
	static void SetStart(bool bStart)	{ m_bStart = bStart; }	//�Q�[���J�n��Ԃ̐ݒ�

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
	CObject2D*	m_pObject2D;	//�I�u�W�F�N�g2D
	CTime*		m_pNumber;		//����

	//-------------------------
	// �ÓI�����o�ϐ�
	//-------------------------
	static bool m_bViewMap;		//�}�b�v��\��������
	static bool m_bStart;		//�Q�[�����J�n������
};

#endif