//===================================================
//
// �C���v�b�g�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _INPUT_H_
#define _INPUT_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "main.h"

//--------------------------------
// �O���錾
//--------------------------------
class CInputKeyboard;	//�L�[�{�[�h
class CInputJoypad;		//�W���C�p�b�h

//--------------------------------
// �}�N����`
//--------------------------------
#define NUM_KEY_MAX		(256)	// �L�[�̍ő吔�i�L�[�{�[�h�j

//================================
// �C���v�b�g�N���X�̒�`
//================================
class CInput
{
public:
	CInput();	//�R���X�g���N�^
	~CInput();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//���͏����S���̏�����
	void Uninit(void);								//���͏����S���̏I������
	void Update(void);								//���͏����S���̍X�V����

	static CInputJoypad* GetJoypad() { return m_pInputJoypad; }

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CInputKeyboard *m_pInputKeybord;	//�L�[�{�[�h
	static CInputJoypad *m_pInputJoypad;	//�W���C�p�b�h
};

#endif // !_INPUT_H_