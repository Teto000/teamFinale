//===================================================
//
// �A�v���P�[�V�����w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_	

//------------------------------
// �C���N���[�h
//------------------------------
#include <d3dx9.h>

//------------------------------
// �O���錾
//------------------------------
class CRenderer;	//�����_���[
class CInput;		//�C���v�b�g
class CTexture;		//�e�N�X�`��
class CSound;		//�T�E���h
class CLight;		//���C�g
class CDebugProc;	//�f�o�b�O�p����

//================================
// �A�v���P�[�V�����N���X�̒�`
//================================
class CApplication
{
public:
	//--------------------------------
	// �Q�[�����[�h�̗񋓌^�̒�`
	//--------------------------------
	enum GAMEMODE
	{
		GAMEMODE_TIME = 0,
		GAMEMODE_SCORE,
		GAMEMODE_MAX
	};

	CApplication();		//�R���X�g���N�^
	~CApplication();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CRenderer*		GetRenderer()	{ return m_pRenderer; }		//�����_���[�̎擾
	static CInput*			GetInput()		{ return m_pInput; }		//�C���v�b�g�̎擾
	static CTexture*		GetTexture()	{ return m_pTexture; }		//�e�N�X�`���̎擾
	static CSound*			GetSound()		{ return m_pSound; }		//�T�E���h�̎擾
	static CLight*			GetLight()		{ return m_pLight; }		//���C�g�̎擾

	//------------------
	// �Z�b�^�[
	//------------------
	static void AddStageScore(int nNum, int nValue) { m_nStageScore[nNum] += nValue; }	//�X�e�[�W���Ƃ̃X�R�A�����Z
	static void ResetStageScore(int nNum) { m_nStageScore[nNum] = 0; }					//�X�e�[�W�̂��Ƃ̃X�R�A�����Z�b�g
	static void SetMaxScore(int nNum, int nValue) { m_nMaxScore[nNum] = nValue; }		//�X�e�[�W���Ƃ̃X�R�A�̍ő吔��ݒ�

	//------------------
	// �Q�b�^�[
	//------------------
	static const int GetMaxStage() { return nMaxStage; }	//�X�e�[�W�̍ő吔���擾
	static int GetStageScore(int nNum) { return m_nStageScore[nNum]; }	//�X�e�[�W���Ƃ̃X�R�A���擾
	static int GetMaxScore(int nNum) { return m_nMaxScore[nNum]; }		//�X�e�[�W���Ƃ̃X�R�A�̍ő吔���擾

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxStage = 2;		//�X�e�[�W�̍ő吔

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static GAMEMODE			m_gameMode;		//�Q�[�����[�h

	static CRenderer*		m_pRenderer;	//�����_���[
	static CInput*			m_pInput;		//�C���v�b�g
	static CTexture*		m_pTexture;		//�e�N�X�`��
	static CSound*			m_pSound;		//�T�E���h
	static CLight*			m_pLight;		//���C�g
	static CDebugProc*		m_pDebugproc;	//�f�o�b�O�p����

	static int m_nStageScore[nMaxStage];	//�X�e�[�W���Ƃ̃X�R�A��ۑ�
	static int m_nMaxScore[nMaxStage];		//�X�R�A�̍ő�l��ۑ�
};

#endif // !_APPLICATION_H_