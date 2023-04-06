//===================================================
//
// �T�E���h�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _SOUND_H_
#define _SOUND_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include <xaudio2.h>

//================================
// �T�E���h�N���X�̒�`
//================================
class CSound
{
public:
	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	//*****************************************************************************
	// �T�E���h�t�@�C��
	//*****************************************************************************
	typedef enum
	{
		/* �� BGM �� */
		SOUND_LABEL_TITLE = 0,		//�^�C�g��

		/*�� SE ��*/
		SOUND_LABEL_SE_BUTTOM,		//����

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();	//�R���X�g���N�^
	~CSound();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif // !_SOUND_H_