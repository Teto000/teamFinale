//===================================================
//
// �f�o�b�O�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include <string>

//================================
// �f�o�b�O�N���X�̒�`
//================================
class CDebugProc
{
public:
	CDebugProc();	//�R���X�g���N�^
	~CDebugProc();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static void Print(const char* pFormat, ...);
	static void Draw();

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxString = 1024;	//������̍ő吔

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static LPD3DXFONT m_pFont;
	static std::string m_Str;
	static int m_nCntData;
};

#endif