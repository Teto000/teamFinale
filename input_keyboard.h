//===================================================
//
// �L�[�{�[�h�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _INPUT_KEYBORD_H_
#define _INPUT_KEYBOARD_H_	

//--------------------------------
// ���C�u�����̃����N 
//--------------------------------
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�Ɏg�p
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v (�L�[�{�[�h)

//--------------------------------
// �C���N���[�h
//--------------------------------
#define DIRECTINPUT_VERSION (0x0800)		//�r���h���̌x���Ώ��p�}�N��
#include <dinput.h>

//--------------------------------
// �}�N����`
//--------------------------------
#define NUM_KEY_MAX		(256)	// �L�[�̍ő吔�i�L�[�{�[�h�j

//================================
// �L�[�{�[�h�N���X�̒�`
//================================
class CInputKeyboard
{
public:
	//--------------------------------------------------
	// �L�[�{�[�h�̍\����
	//--------------------------------------------------
	typedef struct
	{
		LPDIRECTINPUT8			pInput;							// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
		LPDIRECTINPUTDEVICE8	pDevKeyboard;					// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
		BYTE					aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̃v���X���
		BYTE					aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[���
		BYTE					aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X���
	}Keyboard;

	CInputKeyboard();	//�R���X�g���N�^
	~CInputKeyboard();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static bool AllPress(void);		// �S�L�[�v���X����
	static bool Press(int nKey);	// �v���X����
	static bool AllTrigger(void);	// �S�L�[�g���K�[����
	static bool Trigger(int nKey);	// �g���K�[����
	static bool AllRelease(void);	// �S�����[�X����
	static bool Release(int nKey);	// �����[�X����

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static Keyboard m_Keyboard;	//�\����
};

#endif // !_INPUT_KEYBORD_H_