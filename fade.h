//===================================================
//
// �t�F�[�h�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _FADE_H_
#define _FADE_H_	

//-------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "mode.h"
#include "object2d.h"

//================================
// �t�F�[�h�N���X�̒�`
//================================
class CFade
{
public:
	//�t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX
	};

	CFade();	//�R���X�g���N�^
	~CFade();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(CMode::MODE modeNext);
	void Uninit();
	void Update();
	void Draw();
	void SetFade(CMode::MODE modeNext);
	FADE GetFade(void) { return m_fade; };

private:
	//------------------
	// �����o�ϐ�
	//------------------
	FADE	  m_fade;		//�t�F�[�h�̏��
	D3DXCOLOR m_col;		//�|���S��(�t�F�[�h)�̐F
	CMode::MODE m_modeNext;	//���̉��(���[�h)
	CObject2D*m_pObject;	//�t�F�[�h�p�|���S��

};

#endif