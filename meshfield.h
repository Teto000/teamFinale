//===================================================
//
// ���b�V���t�B�[���h�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "mesh.h"

//================================
// ���b�V���t�B�[���h�N���X
//================================
class CMeshField : public CMesh
{
public:
	CMeshField();	//�R���X�g���N�^
	~CMeshField();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CMeshField* Create(float Division,float MaxWidth);
};

#endif