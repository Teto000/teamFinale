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
/* �� ��ʑJ�� �� */
class CGame;		//�Q�[��
class CTitle;		//�^�C�g��
class CResult;		//���U���g
class CStageSelect;	//�X�e�[�W�I��
class CFade;		//�t�F�[�h

/* �� ���̑� �� */
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
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_STAGESELECT,	//�X�e�[�W�I�����
		MODE_FADE,			//�t�F�[�h
		MODE_MAX
	};

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
	static void SetMode(MODE mode);				//���[�h�̐ݒ�
	static MODE GetMode() { return m_mode; };	//���[�h�̎擾
	static CGame*			GetGame()		{ return m_pGame; }			//�Q�[���̎擾
	static CTitle*			GetTitle()		{ return m_pTitle; }		//�^�C�g���̎擾
	static CStageSelect*	GetStage()		{ return m_pStageSelect; }	//�X�e�[�W�̎擾
	static CFade*			GetFade()		{ return m_pFade; }			//�t�F�[�h�̎擾
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
	static const int nMaxStage = 1;		//�X�e�[�W�̍ő吔

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CGame*			m_pGame;		//�Q�[��
	static CTitle*			m_pTitle;		//�^�C�g��
	static CResult*			m_pResult;		//���U���g
	static CStageSelect*	m_pStageSelect;	//�X�e�[�W�I��
	static CFade*			m_pFade;		//�t�F�[�h
	static MODE				m_mode;			//���[�h
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