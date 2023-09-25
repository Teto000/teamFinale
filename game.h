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
class CItemMark;	//�A�C�e���ڈ�
class CRubble;

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
	// �Z�b�^�[
	//------------------
	static void SetFinish(bool fin) { m_bFinish = fin; }	//�Q�[���I����Ԃ�ݒ�

	//------------------
	// �Q�b�^�[
	//------------------
	static CPlayer* GetPlayer(int nNumber) { return m_pPlayer[nNumber]; }	//�v���C���[�̎擾
	static CObjectX* GetObjectX(int nNum) { return m_pObjectX[nNum]; }		//�I�u�W�F�N�g�̎擾
	static CCamera*	GetCamera() { return m_pCamera; }		//�J�����̎擾
	static const int GetMaxPlayer() { return nMaxPlayer; }	//�v���C���[�̍ő吔���擾
	static const int GetMaxObject() { return nMaxObject; }	//�I�u�W�F�N�g�̍ő吔���擾
	static const float GetPastPosX() { return fPastPosX; }	//�ߋ��ړ�����X���W�̕ω��ʂ��擾
	static bool GetFinish() { return m_bFinish; }			//�Q�[���I����Ԃ��擾

private:
	//-------------------
	// �萔
	//-------------------
	static const int nMaxPlayer = 2;	//�v���C���[�̍ő吔
	static const int nMaxObject = 2;	//�I�u�W�F�N�g�̍ő吔
	static const int nMaxBG = 102;		//�w�i�I�u�W�F�N�g�̍ő吔
	static const int nWood = 13;
	static const int nMaxItemMark = 2;	//�A�C�e���ڈ�̍ő吔
	static const float fPastPosX;		//�ߋ���X���W
	static const int nMaxRubble = 4;

	//-------------------
	// �v���C�x�[�g�֐�
	//-------------------
	void CreateObj();	//�I�u�W�F�N�g�̐���
	void CreateWood();	//�w�i�I�u�W�F�N�g(��)�̐���

	//-------------------
	// �ÓI�����o�ϐ�
	//-------------------
	static bool m_bFinish;	//�Q�[���I���t���O

	static CCamera*		m_pCamera;					//�J����
	static CTime*		m_pTime;					//�^�C�}�[
	static CSky*		m_pSky;						//��
	static CMeshField*	m_pMeshField;				//���b�V���t�B�[���h
	static CMeshField*	m_pMeshField2;				//���b�V���t�B�[���h
	static CMeshField*	m_pCityField;				//���̃t�B�[���h
	static CObjectX*	m_pObjectX[nMaxObject];		//�I�u�W�F�N�g
	static CItemMark*	m_pItemMark[nMaxItemMark];	//�A�C�e���̖ڈ�	
	static CObjectX*	m_pObjBG[nMaxBG];			//�w�i�I�u�W�F�N�g(��)�̐���
	static CPlayer*		m_pPlayer[nMaxPlayer];		//�v���C���[
	static CRubble*		m_pRubble[nMaxRubble];
};

#endif