//===================================================
//
// ���[�h�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MODE_H_
#define _MODE_H_	

//-------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>

//--------------------------------
// �O���錾
//--------------------------------
class CGame;		//�Q�[��
class CTitle;		//�^�C�g��
class CResult;		//���U���g
class CStageSelect;	//�X�e�[�W�I��
class CFade;		//�t�F�[�h

//================================
// ���[�h�N���X�̒�`
//================================
class CMode
{
public:
	//----------------------------
	// ���[�h�񋓌^�̒�`
	//----------------------------
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_STAGESELECT,	//�X�e�[�W�I�����
		MODE_FADE,			//�t�F�[�h
		MODE_MAX
	};

	CMode();	//�R���X�g���N�^
	~CMode();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	static HRESULT Init();
	static void Uninit();
	static void Update();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static void SetMode(MODE mode);				//���[�h�̐ݒ�
	static MODE GetMode() { return m_mode; };	//���[�h�̎擾
	static CGame*			GetGame()	{ return m_pGame; }			//�Q�[���̎擾
	static CTitle*			GetTitle()	{ return m_pTitle; }		//�^�C�g���̎擾
	static CStageSelect*	GetStage()	{ return m_pStageSelect; }	//�X�e�[�W�̎擾
	static CFade*			GetFade()	{ return m_pFade; }			//�t�F�[�h�̎擾

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static MODE				m_mode;			//���[�h
	static CGame*			m_pGame;		//�Q�[��
	static CTitle*			m_pTitle;		//�^�C�g��
	static CResult*			m_pResult;		//���U���g
	static CStageSelect*	m_pStageSelect;	//�X�e�[�W�I��
	static CFade*			m_pFade;		//�t�F�[�h
};

#endif