//===================================================
//
// �����_�����O�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_	//��d�C���N���[�h�h�~

//--------------------
// �C���N���[�h
//--------------------
#include <tchar.h> // _T
#include <d3dx9.h>

//--------------------
// �O���錾
//--------------------
class CCamera;

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("�A���̃t�B�i�[��");
}

// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`���ւ̃|�C���^
}VERTEX_3D;

//==============================
// �����_�����O�N���X�̒�`
//==============================
class CRenderer
{
public:
	CRenderer();	//�R���X�g���N�^
	~CRenderer();	//�f�X�g���N�^

	//-----------------
	// �����o�֐�
	//-----------------
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }

private:
	void DrawFPS();

	//-----------------
	// �����o�ϐ�
	//-----------------
	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Device�I�u�W�F�N�g
	LPD3DXFONT m_pFont;					// �t�H���g
	bool m_bWIRE;

	//-------------------
	// �ÓI�����o�ϐ�
	//-------------------
	static CCamera* m_pCamera; //�J�����N���X
};

#endif // !_RENDERER_H_