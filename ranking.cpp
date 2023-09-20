//===================================================
//
// �^�C�}�[����
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include <string>
#include <vector>
#include <algorithm>
#include "ranking.h"
#include "score.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "input_keyboard.h"

//----------------------
// �ÓI�����o�ϐ��錾
//----------------------
int CRanking::m_nTime = 0;	//����

//=======================
// �R���X�g���N�^
//=======================
CRanking::CRanking() : CObject(1)
{
	m_nRankUpdate = 0;		//�X�V�����NNo.

	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pTime[i];	//����
	}
}

//=======================
// �f�X�g���N�^
//=======================
CRanking::~CRanking()
{

}

//=======================
// ������
//=======================
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		pos = D3DXVECTOR3(300.0f, 200 + (i * 100.0f), 0.0f);
		m_pTime[i] = CScore::Create(pos);
	}

	Load();		//�ǂݍ���
	Ranking();	//���ёւ�
	Save();		//��������

	return S_OK;
}

//=======================
// �I��
//=======================
void CRanking::Uninit()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pTime[i]->Uninit();
	}
}

//=======================
// �X�V
//=======================
void CRanking::Update()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pTime[i]->Update();
	}

	//-------------------------------
	// ����̃X�R�A��Ԃ�����
	//-------------------------------
	if (m_nTime != m_nRankUpdate)
	{//����̃^�C���������L���O�̐��l�Ɠ����Ȃ�
		if (m_nRankUpdate != -1)
		{//�����L���O�O����Ȃ�������
			//�F�̕ύX
			m_pTime[m_nRankUpdate]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

#ifdef _DEBUG
	//�����L���O�̏�����
	if (CInputKeyboard::Trigger(DIK_1))
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			m_pTime[i]->SetTime(999);
			Save();		//��������
		}
	}
#endif // _DEBUG
}

//=======================
// �`��
//=======================
void CRanking::Draw()
{
	for (int i = 0; i < nMaxRanking; i++)
	{
		m_pTime[i]->Draw();
	}
}

//=======================
// ����
// �����F�ʒu�A�R���{��
//=======================
CRanking *CRanking::Create()
{
	CRanking *pRanking = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pRanking = new CRanking;	//����

	if (pRanking != nullptr)
	{//NULL�`�F�b�N
		//������
		pRanking->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	return pRanking;
}

//=========================================
// ��������
//=========================================
void CRanking::Save()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "w");	//�t�@�C���ǂݍ���
	const int lenLine = 1024;							//1�P��̍ő吔

	if (fp != nullptr)
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			fprintf(fp, "%d\n", m_pTime[i]->GetScore());	//�ǂݍ��񂾕������Ƃɐݒ肷��
		}

		fclose(fp);
	}
}

//=========================================
// �ǂݍ���
//=========================================
void CRanking::Load()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "r");	//�t�@�C���ǂݍ���
	const int lenLine = 1024;							//1�P��̍ő吔
	int nScore = 0;										//�ǂݍ��ݗp�̕�����

	if (fp != nullptr)
	{
		for (int i = 0; i < nMaxRanking; i++)
		{
			fscanf(fp, "%d", &nScore);	//�ǂݍ��񂾕������Ƃɐݒ肷��
			m_pTime[i]->SetTime(nScore);
		}

		fclose(fp);
	}
}

//=========================================
// �����L���O�̕��ёւ�
//=========================================
void CRanking::Ranking()
{
	m_nRankUpdate = -1;
	if (m_nTime <= m_pTime[nMaxRanking - 1]->GetScore())
	{//��r
		m_pTime[nMaxRanking - 1]->SetTime(m_nTime);

		//�����ɕ��ѕς���
		std::vector<int> rank = { m_pTime[0]->GetScore()
								, m_pTime[1]->GetScore()
								, m_pTime[2]->GetScore()
								, m_pTime[3]->GetScore()
								, m_pTime[4]->GetScore() };

		std::sort(rank.begin(), rank.end());

		for (int i = 0; i < nMaxRanking; i++)
		{//���ѕς��������
			m_pTime[i]->SetTime(rank[i]);

			if (m_nTime == rank[i])
			{
				m_nRankUpdate = i;
			}
		}
	}
}