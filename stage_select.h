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
class CScore;		//����
class CSky;			//��

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
	static void SetNumStage(int nNum)	{ m_nNumStage = nNum; }	//���݂̃X�e�[�W�ԍ���ݒ�
	static void SetViewMap(bool bView)	{ m_bViewMap = bView; }	//�}�b�v�\����Ԃ̐ݒ�
	static void SetStart(bool bStart)	{ m_bStart = bStart; }	//�Q�[���J�n��Ԃ̐ݒ�

	//-------------------------
	// �Q�b�^�[
	//-------------------------
	static const int GetMaxStage()		{ return nMaxStage; }			//�X�e�[�W�̍ő吔���擾
	CCamera*	GetCamera()				{ return m_pCamera; }			//�J�������擾
	CObjectX*	GetObjectX(int nNum)	{ return m_pObjectX[nNum]; }	//�I�u�W�F�N�g�̎擾
	CPlayer*	GetPlayer()				{ return m_pPlayer; }			//�v���C���[�̎擾

private:
	//-------------------------
	// �萔
	//-------------------------
	static const int nMaxStage = 2;		//�X�e�[�W�̍ő吔

	//-------------------------
	// �����o�ϐ�
	//-------------------------
	CCamera*	m_pCamera;					//�J����
	CMeshField*	m_pMeshField;				//���b�V���t�B�[���h
	CObjectX*	m_pObjectX[nMaxStage];		//�I�u�W�F�N�g
	CPlayer*	m_pPlayer;					//�v���C���[
	CObject2D*	m_pObject2D;				//�I�u�W�F�N�g2D
	CScore*		m_pNumber;					//����
	CSky*		m_pSky;						//��
	
	//-------------------------
	// �ÓI�����o�ϐ�
	//-------------------------
	static int m_nNumStage;		//���݂̃X�e�[�W�ԍ�
	static bool m_bViewMap;		//�}�b�v��\��������
	static bool m_bStart;		//�Q�[�����J�n������
};

#endif