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
	CPlayer* GetPlayer() { return m_pPlayer; }	//�v���C���[�̎擾

	static bool GetFinish() { return m_bFinish; }	  //�Q�[���I����Ԃ��擾
	static CCamera*	GetCamera() { return m_pCamera; } //�J�����̎擾

private:
	//-------------------
	// �����o�ϐ�
	//-------------------
	CPlayer* m_pPlayer;	//�v���C���[

	//-------------------
	// �ÓI�����o�ϐ�
	//-------------------
	static bool m_bFinish;	//�Q�[���I���t���O

	static CCamera*		m_pCamera;		//�J����
	static CTime*		m_pTime;		//�^�C�}�[
	static CSky*		m_pSky;			//��
	static CMeshField*	m_pMeshField;	//���b�V���t�B�[���h
};

#endif