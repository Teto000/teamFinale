//===================================================
//
// �t�F�[�h�̏���
// Author : Sato Teruto
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "fade.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "application.h"
#include "renderer.h"
#include "object2d.h"
#include "camera.h"
#include "game.h"

//===========================
// �R���X�g���N�^
//===========================
CFade::CFade()
{

}

//===========================
// �f�X�g���N�^
//===========================
CFade::~CFade()
{

}

//===========================
// ������
//===========================
HRESULT CFade::Init(CApplication::MODE modeNext)
{
	//�񋓌^�̏�����
	m_fade = FADE_IN;		//�t�F�[�h�C�����
	m_modeNext = modeNext;	//���̉��(���[�h)��ݒ�
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�����|���S��(�s����)�ɂ��Ă���

	m_pObject = new CObject2D(3);

	m_pObject->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	m_pObject->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	m_pObject->SetColor(m_col);

	m_pObject->SetTexture(CTexture::TEXTURE_NONE);	//�e�N�X�`���̐ݒ�

	return S_OK;
}

//===========================
// �I��
//===========================
void CFade::Uninit()
{

}

//===========================
// �X�V
//===========================
void CFade::Update()
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_col.a -= 0.02f;	//�|���S���𓧖��ɂ��Ă���

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;

				if (m_pObject != nullptr)
				{
					m_pObject->Release();
					m_pObject = nullptr;
				}

				m_fade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_col.a += 0.02f;	//�|���S����s�����ɂ��Ă���

			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_fade = FADE_IN;	//�t�F�[�h�C����Ԃ�

				//-----------------------
				// �J�����̊g��
				//-----------------------
				/*CCamera* pCamera[2] = {};

				for (int i = 0; i < 2; i++)
				{
					if (CApplication::GetMode() == CApplication::MODE_GAME)
					{//null����Ȃ��Ȃ�
						pCamera[i] = CGame::GetCamera(i);
						pCamera[i]->SetViewSize(0.0f, 0.0f, 1280.0f, 720.0f);
					}
				}*/

				CApplication::SetMode(m_modeNext);
				m_pObject = new CObject2D(3);

				m_pObject->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

				m_pObject->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

				m_pObject->SetColor(m_col);

				m_pObject->SetTexture(CTexture::TEXTURE_NONE);	//�e�N�X�`���̐ݒ�
			}
		}
	}

	if (m_pObject != nullptr)
	{
		m_pObject->SetColor(m_col);
		m_pObject->Update();		//���ɒu���Ȃ��Ɛ������ꂽ��u���������̂܂܂ɂȂ��Ă��܂�
	}
}

//===========================
// �`��
//===========================
void CFade::Draw()
{
	if (m_pObject != nullptr)
	{
		m_pObject->Draw();
	}
}

//===========================
// �ݒ�
//===========================
void CFade::SetFade(CApplication::MODE modeNext)
{
	if (m_fade != FADE_OUT)
	{
		m_fade = FADE_OUT;		//�t�F�[�h�A�E�g��Ԃ�
		m_modeNext = modeNext;	//���̉�ʂ�ݒ�
		m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}