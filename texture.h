//=============================================================================
//
// �e�N�X�`���ݒ菈��(texture.h)
// Author : �������l
// �T�v : �e�N�X�`���ݒ���s��
//
//=============================================================================
#ifndef _TEXTURE_H_		// ���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//=============================================================================
// �e�N�X�`���N���X
// Author : �������l
// �T�v : �e�N�X�`���ݒ���s���N���X
//=============================================================================
class CTexture
{
public:
	//*****************************************************************************
	// �萔��`
	//*****************************************************************************
	static const unsigned int MAX_NAME = (0x100);

	struct TEXTURE
	{
		LPDIRECT3DTEXTURE9		pTexture;					// �e�N�X�`�����
		char					aFileName[MAX_NAME];		// �t�@�C����
	};

	enum NUM_TEXTURE
	{/* �� �g�p���Ȃ� �� */
		TEXTURE_NONE = -1,

		/* �� �^�C�g�� �� */
		TEXTURE_TITLE = 0,		//�^�C�g���w�i
		TEXTURE_TITLE_BG,
		TEXTURE_PRESSENTER,

		/* �� ���U���g �� */
		TEXTURE_RESULT,			//���U���g�w�i
		TEXTURE_RANKING,		//�����L���O���S

		/* �� �Q�[�� �� */
		TEXTURE_SKY,			//��
		TEXTURE_GROUND,			//�n��
		TEXTURE_FINISH,			//FINISH�̕���
		TEXTURE_COMPLETE,		//COMPLETE�̕���
		TEXTURE_FUKIDASI,		//�����o��
		TEXTURE_FUKIDASI2,		//�����o��(2)
		TEXTURE_FUKIDASI3,		//�����o��(3)
		TEXTURE_FUKIDASI4,		//�����o��(4)
		TEXTURE_CLOCK,			//���v��
		TEXTURE_CLOCK_NEEDLE,	//���v�̐j
		TEXTURE_SCORE,			//�X�R�A
		TEXTURE_SCORE_50,		//50pt
		TEXTURE_SCORE_300,		//100pt

		/* �� ���̑� �� */
		TEXTURE_NUMBER,			//����

		/* �� �~�j�Q�[�� �� */
		TEXTURE_BUTTON,			//�{�^���A��
		TEXTURE_GAUGE,			//�Q�[�W
		TEXTURE_JOYPAD,			//�W���C�p�b�h
		TEXTURE_ITEM,			//�A�C�e���w��

		/* �� �X�e�[�W�Z���N�g �� */
		TEXTURE_STATE1,			//�X�e�[�W1�̉摜
		TEXTURE_STATE2,			//�X�e�[�W2�̉摜

		/* ���b�V����*/
		TEXTURE_GRASS,
		TEXTURE_GROUND_DART,
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CTexture();
	~CTexture();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	// ������
	void Init(void);

	// �I��
	void Uninit(void);

	// �e�N�X�`���̃Q�b�^�[
	LPDIRECT3DTEXTURE9 GetTexture(const int nNumTex);

	// �e�N�X�`���̍ő吔
	int GetMaxTexture() { return m_nMaxTexture; }

	// �e�N�X�`�����̃Q�b�^�[
	TEXTURE *GetTextureData() { return m_pTexture; }

	// �t�@�C���̓ǂݍ���
	void LoadFile();

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	TEXTURE		*m_pTexture;		// �e�N�X�`�����
	int			m_nMaxTexture;		// �e�N�X�`���̍ő吔

};

#endif

