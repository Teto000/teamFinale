//===================================================
//
// �擾�����X�R�A��\�����鏈��
// Author : Sato Teruto
//
//===================================================

//---------------------------
// �C���N���[�h
//---------------------------
#include <time.h>
#include "get_score.h"

//======================================
// �R���X�g���N�^
//======================================
CGetScore::CGetScore() : CBillBoard(0)
{
	nStopTime = 0;		//�~�܂��Ă鎞��
	nDeleteTime = 0;	//��������
	m_num = NUMBER_NONE;
}

//======================================
// �f�X�g���N�^
//======================================
CGetScore::~CGetScore()
{
}

//======================================
// ������
//======================================
HRESULT CGetScore::Init(D3DXVECTOR3 pos)
{
	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	int nWidth = 200;
	int nRandX = rand() % nWidth - (nWidth / 2);
	int nRandY = rand() % nWidth - (nWidth / 2);
	D3DXVECTOR3 newPos(pos.x + (float)nRandX
		, pos.y + (float)nRandY
		, pos.z);

	CBillBoard::Init(newPos);

	switch (m_num)
	{
	case NUMBER_50:
		CBillBoard::SetTexture(CTexture::TEXTURE_SCORE_50);
		CBillBoard::SetSize(50.0f, 50.0f);
		break;

	case NUMBER_300:
		CBillBoard::SetTexture(CTexture::TEXTURE_SCORE_300);
		CBillBoard::SetSize(60.0f, 60.0f);
		break;

	default:
		break;
	}

	return S_OK;
}

//======================================
// �I��
//======================================
void CGetScore::Uninit()
{
	CBillBoard::Uninit();
}

//======================================
// �X�V
//======================================
void CGetScore::Update()
{
	CBillBoard::Update();

	//----------------------------
	// �㏸���ď����鏈��
	//----------------------------
	nStopTime++;

	if (nStopTime >= 20)
	{
		//�㏸������
		D3DXVECTOR3 pos = CBillBoard::GetPosition();
		pos.y += 2.0f;
		CBillBoard::SetPos(pos);

		nDeleteTime++;

		if (nDeleteTime >= 30)
		{
			nStopTime = 0;
			nDeleteTime = 0;
			Uninit();
		}
	}
}

//======================================
// �`��
//======================================
void CGetScore::Draw()
{
	CBillBoard::Draw();
}

//======================================
// ����
//======================================
CGetScore* CGetScore::Create(NUMBER num, D3DXVECTOR3 pos)
{
	CGetScore* pGetScore = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pGetScore = new CGetScore;	//����

	if (pGetScore != nullptr)
	{//NULL�`�F�b�N
		//������
		pGetScore->m_num = num;
		pGetScore->Init(D3DXVECTOR3(pos));
	}

	return pGetScore;
}