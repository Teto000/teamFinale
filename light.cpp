//===================================================
//
// ���C�g�̏���
// Author:Teruto Sato
//
//===================================================

//-----------------------
// �C���N���[�h
//-----------------------
#include "light.h"
#include "renderer.h"

//========================
// �R���X�g���N�^
//========================
CLight::CLight()
{
	m_vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���C�g�����̃x�N�g��
}

//========================
// �f�X�g���N�^
//========================
CLight::~CLight()
{

}

//========================
// ������
//========================
void CLight::Init(LPDIRECT3DDEVICE9 pDevice)
{
	//���C�g���N���A����
	ZeroMemory(&m_Light, sizeof(m_Light));

	//--------------------------------------------
	// 1�ڂ̃��C�g
	//--------------------------------------------
	//���C�g�̎�ނ�ݒ�
	m_Light[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�(�F)
	m_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕���������
	m_vecDir = D3DXVECTOR3(0.4f, -0.4f, -0.8f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);
	m_Light[0].Direction = m_vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_Light[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//--------------------------------------------
	// 2�ڂ̃��C�g
	//--------------------------------------------
	//���C�g�̎�ނ�ݒ�
	m_Light[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�(�F)
	m_Light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕���������
	m_vecDir = D3DXVECTOR3(0.4f, 0.8f, -0.4f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);
	m_Light[1].Direction = m_vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &m_Light[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	//--------------------------------------------
	// 3�ڂ̃��C�g
	//--------------------------------------------
	//���C�g�̎�ނ�ݒ�
	m_Light[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�(�F)
	m_Light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕���������
	m_vecDir = D3DXVECTOR3(-0.4f, -0.8f, 0.4f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);
	m_Light[2].Direction = m_vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(2, &m_Light[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
}

//========================
// �I��
//========================
void CLight::Uninit()
{

}

//========================
// �X�V
//========================
void CLight::Update()
{

}

//========================
// ���C�g�����̎擾
//========================
D3DXVECTOR3 CLight::GetVecDir()
{
	return m_vecDir;
}