//===================================================
//
// �W���C�p�b�h�w�b�_�[
// Author: Koduna Hirohito
// Author : Sato Teruto
//
//===================================================
#ifndef _INPUT_JOYPAD_H_
#define _INPUT_JOYPAD_H_	

//--------------------------------
// ���C�u�����̃����N 
//--------------------------------
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�Ɏg�p
#pragma comment(lib,"xinput.lib")		//���͏����ɕK�v�i�W���C�p�b�g�j

//--------------------------------
// �C���N���[�h
//--------------------------------
#define DIRECTINPUT_VERSION (0x0800)		//�r���h���̌x���Ώ��p�}�N��
#include <Xinput.h>		//�W���C�p�b�h�����ɕK�v

//--------------------------------
// �}�N����`
//--------------------------------
#define NUM_KEY_MAX		(256)	// �L�[�̍ő吔�i�L�[�{�[�h�j
#define PLAYER_MAX		(4)		// �v���C���[�̍ő�l��
#define DIRECTION_MAX	(4)		// �����̍ő吔
#define STICK_MAX		(2)		// �X�e�B�b�N�̍ő吔

//================================
// �W���C�p�b�h�N���X�̒�`
//================================
class CInputJoypad
{
public:
	//--------------------------------------------------
	// �W���C�p�b�h�̍\����
	//--------------------------------------------------
	typedef struct
	{
		XINPUT_STATE		JoyKeyState[PLAYER_MAX];						// �W���C�p�b�h�̃v���X���
		XINPUT_STATE		JoyKeyStateTrigger[PLAYER_MAX];					// �W���C�p�b�h�̃g���K�[���
		XINPUT_STATE		JoyKeyStateRelease[PLAYER_MAX];					// �W���C�p�b�h�̃����[�X���
		D3DXVECTOR3			JoyStickPos[PLAYER_MAX];						// �W���C�X�e�B�b�N�̌X��
		XINPUT_VIBRATION	JoyMoter[PLAYER_MAX];							// �W���C�p�b�h�̃��[�^�[
		int					nTime[PLAYER_MAX];								// �U����������
		WORD				nStrength[PLAYER_MAX];							// �U���̋��� (0 - 65535)
		bool				bUseJoyPad[PLAYER_MAX];							// �W���C�p�b�h���g�p���Ă邩
		bool				bStick[PLAYER_MAX][STICK_MAX][DIRECTION_MAX];	// �X�e�B�b�N�̃g���K�[���
		bool				bLean[PLAYER_MAX][STICK_MAX][DIRECTION_MAX];	// �X�e�B�b�N���X�������ǂ���
	}Joypad;

	//--------------------------------------------------
	// �񋓌^���`
	//--------------------------------------------------
	typedef enum
	{
		JOYKEY_UP = 0,				// �\���{�^����
		JOYKEY_DOWN,				// �\���{�^����
		JOYKEY_LEFT,				// �\���{�^����
		JOYKEY_RIGHT,				// �\���{�^���E
		JOYKEY_START,				// �X�^�[�g�{�^��
		JOYKEY_BACK,				// �o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			// ���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			// �E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		// L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		// R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		// L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		// R�Q�g���K�[
		JOYKEY_A,					// A�{�^��
		JOYKEY_B,					// B�{�^��
		JOYKEY_X,					// X�{�^��
		JOYKEY_Y,					// Y�{�^��
		JOYKEY_LEFT_STICK,			// ���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			// �E�X�e�B�b�N
		JOYKEY_MAX,
	}JOYKEY;

	CInputJoypad();		//�R���X�g���N�^
	~CInputJoypad();	//�f�X�g���N�^

	//-----------------------------
	// �����o�֐�
	//-----------------------------
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void UpdateStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer);	// �X�e�B�b�N�̃g���K�[�̍X�V

	//-----------------------------
	// �ÓI�����o�֐�
	//-----------------------------
	bool AllPress(void);											// �W���C�p�b�h�v���X����(�L�[�w��Ȃ�)
	bool Press(JOYKEY Key);											// �W���C�p�b�h�v���X����(�v���C���[�w��Ȃ�)
	bool IdxPress(JOYKEY Key, int nPlayer);							// �W���C�p�b�h�̃v���X����(�v���C���[�w�肠��)
	bool AllTrigger(void);											// �W���C�p�b�h�g���K�[����(�L�[�w��Ȃ�)
	bool Trigger(JOYKEY Key);										// �W���C�p�b�h�g���K�[����(�v���C���[�w��Ȃ�)
	bool IdxTrigger(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃g���K�[����(�v���C���[�w�肠��)
	bool Release(JOYKEY Key);										// �W���C�p�b�h�����[�X����(�v���C���[�w��Ȃ�)
	bool IdxRelease(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃����[�X����(�v���C���[�w�肠��)
	D3DXVECTOR3 Stick(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃X�e�B�b�N����
	int TriggerPedal(JOYKEY Key, int nPlayer);						// �W���C�p�b�h�̃g���K�[�y�_������
	void Vibration(int nTime, WORD nStrength, int nPlayer);			// �W���C�p�b�h�̐U������
	bool IsJoyPadUse(int nPlayer);									// �W���C�p�b�h�̎g�p��
	bool StickTrigger(JOYKEY Stick, JOYKEY Key);					// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w��Ȃ�)
	bool IdxStickTrigger(JOYKEY Stick, JOYKEY Key, int nPlayer);	// �W���C�p�b�h�̃X�e�B�b�N�̃g���K�[����(�v���C���[�w�肠��)

private:
	//-----------------------------
	// �ÓI�����o�ϐ�
	//-----------------------------
	static Joypad m_Joypad;	//�\����
};

#endif // !_INPUT_JOYPAD_H_