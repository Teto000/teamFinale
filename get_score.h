//===================================================
//
// �X�R�A�擾�\���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _GET_SCORE_H_
#define _GET_SCORE_H_	//��d�C���N���[�h�h�~

//-------------------------
// �C���N���[�h
//-------------------------
#include "billboard.h"

//================================
// �A�C�e���ڈ�N���X
//================================
class CGetScore : public CBillBoard
{
public:
	enum NUMBER
	{
		NUMBER_NONE = 0,
		NUMBER_50,
		NUMBER_300
	};

	CGetScore();			// �R���X�g���N�^
	~CGetScore() override;	// �f�X�g���N�^

	//----------------------
	// �����o�֐�
	//----------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//----------------------
	// �ÓI�����o�֐�
	//----------------------
	static CGetScore* Create(NUMBER num, D3DXVECTOR3 pos);

private:
	int nStopTime;		//�~�܂��Ă鎞��
	int nDeleteTime;	//��������
	NUMBER m_num;
};

#endif