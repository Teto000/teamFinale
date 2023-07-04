//===================================================
//
// �Q�[���w�b�_�[
// Author : Sato Teruto
//
//====================================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "application.h"

//--------------------------------
// �O���錾
//--------------------------------
class CCamera;		//�J����
class CTime;		//�^�C�}�[
class CSky;			//��
class CMeshField;	//�n��
class CPlayer;		//�v���C���[
class CObjectX;		//�I�u�W�F�N�g

//================================
// �Q�[���N���X�̒�`
//================================
class CGame
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �Q�b�^�[
	//------------------
	static CPlayer* GetPlayer(int nNumber) { return m_pPlayer[nNumber]; }	//�v���C���[�̎擾
	static CObjectX* GetObjectX(int nNum) { return m_pObjectX[nNum]; }		//�I�u�W�F�N�g�̎擾
	static CCamera*	GetCamera() { return m_pCamera; }		//�J�����̎擾
	static const int GetMaxPlayer() { return nMaxPlayer; }	//�v���C���[�̍ő吔���擾
	static const int GetMaxObject() { return nMaxObject; }	//�I�u�W�F�N�g�̍ő吔���擾
	static bool GetFinish() { return m_bFinish; }			//�Q�[���I����Ԃ��擾

private:
	//-------------------
	// �萔
	//-------------------
	static const int nMaxPlayer = 2;	//�v���C���[�̍ő吔
	static const int nMaxObject = 28;	//�I�u�W�F�N�g�̍ő吔

	//-------------------
	// �v���C�x�[�g�֐�
	//-------------------
	void CreateObj();	//�I�u�W�F�N�g�̐���

	//-------------------
	// �ÓI�����o�ϐ�
	//-------------------
	static bool m_bFinish;	//�Q�[���I���t���O

	static CCamera*		m_pCamera;					//�J����
	static CTime*		m_pTime;					//�^�C�}�[
	static CSky*		m_pSky;						//��
	static CMeshField*	m_pMeshField;				//���b�V���t�B�[���h
	static CObjectX*	m_pObjectX[nMaxObject];		//�I�u�W�F�N�g
	static CPlayer*		m_pPlayer[nMaxPlayer];		//�v���C���[
};

#endif