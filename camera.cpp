//===================================================
//
// �J�����̏���
// Author:Teruto Sato
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "camera.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "renderer.h"
#include "game.h"
#include "debug_proc.h"
#include "utility.h"
#include "player.h"

//----------------------
// �ÓI�����o�ϐ��錾
//----------------------
const float CCamera::m_fSpeed = 0.02f;

//===========================
// �R���X�g���N�^
//===========================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//-------------------------
	// �r���[�|�[�g�̏��
	//-------------------------
	m_viewport.X = (DWORD)0.0f;
	m_viewport.Y = (DWORD)0.0f;
	m_viewport.Width = (DWORD)0.0f;
	m_viewport.Height = (DWORD)0.0f;
	m_viewport.MaxZ = (DWORD)0.0f;
	m_viewport.MinZ = (DWORD)0.0f;

	//�J�����̐U��
	m_nQuakeFreamCount = 0;
	m_fQuakeMagnitude = 0.0f;
}

//===========================
// �f�X�g���N�^
//===========================
CCamera::~CCamera()
{

}

//========================
// �J�����̏���������
//========================
void CCamera::Init(void)
{
	//---------------------------------
	// ���_�E�����_�E�������ݒ肷��
	//---------------------------------
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//-------------------------
	// �r���[�|�[�g�̏��
	//-------------------------
	m_viewport.MaxZ = 1.0f;
	m_viewport.MinZ = 0.0f;
}

//========================
// �J�����̏I������
//========================
void CCamera::Uninit(void)
{

}

//========================
// �J�����̍X�V����
//========================
void CCamera::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//��]
	Turn();

	//----------------------------------------
	// ���b�N�I����Ԃ̐؂�ւ�
	//----------------------------------------
	/*// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();

	if (CInputKeyboard::Trigger(DIK_SPACE)
		|| joypad->Trigger(CInputJoypad::JOYKEY_RIGHT_THUMB))
	{
		//���b�N�I����Ԃ�؂�ւ�
		m_bLockOn = !m_bLockOn;
	}

	if (CGame::GetFinish())
	{//�I���t���O�������Ă���Ȃ�
		//���b�N�I��������
		m_bLockOn = false;
	}*/

	//----------------------------------------
	// �s����g�����J��������
	//----------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPosition();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�s��ɉ�]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�s��Ɉړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, playerPos.x, playerPos.y, playerPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���[���h�ϊ��s����g����posV,posR�����߂�
	D3DXVec3TransformCoord(&m_posRDest, &m_posR, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_posVDest, &m_posV, &m_mtxWorld);

	//----------------------------------------
	// ���b�N�I������
	//----------------------------------------
	/*//���b�N�I���ʒu
	D3DXVECTOR3 lockOnPos;
	if (CGame::GetEnemy())
	{//�G��null����Ȃ��Ȃ�
		lockOnPos = CGame::GetEnemy()->GetPosition();
	}

	if (m_bLockOn)
	{//���b�N�I����ԂȂ�
		//�����_�����b�N�I���ʒu�ɐݒ�
		m_posRDest = lockOnPos;
		m_posRDest.y += 100.0f;	//�����_�̍��W����������

		//�v���C���[�ʒu�ƃ��b�N�I���ʒu�Ԃ̃x�N�g�������߂�
		D3DXVECTOR3 vec = lockOnPos - playerPos;

		//���K��
		D3DXVec3Normalize(&vec, &vec);

		//���_�̈ʒu��ݒ�
		{
			float posV_y = m_posVDest.y;				//y���W��ۑ�
			m_posVDest = playerPos + (-vec) * 500.0f;	//���_�̈ʒu��ύX
			m_posVDest.y = posV_y;						//y���W��߂�
		}

		//�J�����̊p�x�����b�N�I����ɍ��킹��
		m_rot.y = atan2f(m_posRDest.x - m_posVDest.x, m_posRDest.z - m_posVDest.z);
	}

	// ���E�̊p�x�̐��K��
	m_rot.y = CUtility::GetNorRot(m_rot.y);

	//����
	m_posRDest += (m_posRDest - m_posRDest) * 0.1f;
	m_posVDest += (m_posVDest - m_posVDest) * 0.1f;*/

	//���_�E�����_�̕\��
	CDebugProc::Print("���_�F%f,%f,%f", m_posVDest.x, m_posVDest.y, m_posVDest.z);
	CDebugProc::Print("�����_�F%f,%f,%f", m_posRDest.x, m_posRDest.y, m_posRDest.z);
	CDebugProc::Print("��]�F%f,%f,%f", m_rot.x, m_rot.y, m_rot.z);
}

//========================
// �J�����̐ݒ菈��
//========================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	//--------------------------------
	// �J�������̐U��
	//--------------------------------
	D3DXVECTOR3 adjustPos(0.0f, 0.0f, 0.0f);

	if (m_nQuakeFreamCount > 0)
	{//�h�炷�t���[������0���傫���Ȃ�
		//�t���[�����̌���
		m_nQuakeFreamCount--;

		//�����_���Ȓl��ݒ�
		adjustPos.x = m_fQuakeMagnitude * (rand() % (int)m_maxShake.x - ((int)m_maxShake.x / 2.0f));
		adjustPos.y = m_fQuakeMagnitude * (rand() % (int)m_maxShake.y - ((int)m_maxShake.y / 2.0f));
		adjustPos.z = m_fQuakeMagnitude * (rand() % (int)m_maxShake.z - ((int)m_maxShake.z / 2.0f));
	}

	//--------------------------------
	// �J�������̐ݒ�
	//--------------------------------
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
					   &(m_posVDest + adjustPos),	//���_
					   &(m_posRDest + adjustPos),	//�����_
					   &m_vecU);					//��̌���

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
							   D3DXToRadian(45.0f),	//����p
							   (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��
							   10.0f,		//near
							   100000.0f);	//far

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//--------------------------------
	// �t�H�O
	//--------------------------------
	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//�t�H�O���[�h�̐ݒ�
	//�͈͎w��:D3DFOG_LINEAR , ���x�w��:D3DFOG_EXP
	//pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);	//�͈͎w��
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);	//���x�w��

	//----------------------------
	// �͈͎w�莞�̏���
	//----------------------------
	/*float fFogStart = 100;		//�J�n�ʒu
	float fFogEnd = 1000;		//�I���ʒu
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStart));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEnd));*/

	//----------------------------
	// ���x�w�莞�̏���
	//----------------------------
	float fFogDensity = 0.000f;		//���x(0.001�ł����Ȃ�^����)
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}

//==================================================
// �J�����̐���
// ���� : ����̍��W X, ����̍��W Y, ��, ����
//==================================================
CCamera* CCamera::Create(DWORD X, DWORD Y, DWORD Width, DWORD Height)
{
	CCamera* pCamera = nullptr;

	//------------------------------
	// �|���S���̐����Ə�����
	//------------------------------
	pCamera = new CCamera;	//����

	if (pCamera != nullptr)
	{//NULL�`�F�b�N
	 //�r���[�|�[�g�\���̕ۑ�
		pCamera->m_viewport.X = X;				//�J�n�ʒu(X)
		pCamera->m_viewport.Y = Y;				//�J�n�ʒu(Y)
		pCamera->m_viewport.Width = Width;		//��
		pCamera->m_viewport.Height = Height;	//����

		//������
		pCamera->Init();
	}

	return pCamera;
}

//==================================================
// �r���[�|�[�g�̑傫���ݒ�
// ���� : ��ʍ���̍��WX,Y�A���A����
//==================================================
void CCamera::SetViewSize(DWORD X, DWORD Y, int fWidth, int fHeight)
{
	//��������
	m_viewport.X = X;				//�r���[�|�[�g�̍���X���W
	m_viewport.Y = Y;				//�r���[�|�[�g�̍���Y���W
	m_viewport.Width = fWidth;		//�r���[�|�[�g�̕�
	m_viewport.Height = fHeight;	//�r���[�|�[�g�̍���
}

//========================
// �J�����̐���
//========================
void CCamera::Turn()
{
	// �W���C�p�b�h�ł̑���
	CInputJoypad* joypad = CApplication::GetInput()->GetJoypad();
	D3DXVECTOR3 stick = joypad->Stick(CInputJoypad::JOYKEY_RIGHT_STICK, 0);

	//�X�e�B�b�N�𓮂����l�̐ݒ�
	float fMoveValue = 0.5f;

	//------------------
	// �����_�̐���
	//------------------
	if (CInputKeyboard::Press(DIK_Q) || stick.x <= -fMoveValue)	//����]
	{//Q�L�[�������ꂽ
		m_rot.y -= m_fSpeed;	//��]�ʂ̑���
	}
	else if (CInputKeyboard::Press(DIK_E) || stick.x >= fMoveValue)	//�E��]
	{//E�L�[�������ꂽ
		m_rot.y += m_fSpeed;
	}
	if (CInputKeyboard::Press(DIK_B) || stick.y >= fMoveValue)	//���]
	{//B�L�[�������ꂽ
		m_rot.x -= m_fSpeed;
	}
	else if (CInputKeyboard::Press(DIK_Y) || stick.y <= -fMoveValue)	//����]
	{//Y�L�[�������ꂽ
		m_rot.x += m_fSpeed;
	}

	//-------------------------
	// �㉺����̏���l�ǉ�
	//-------------------------
	if (m_rot.x >= 1.2f)
	{
		m_rot.x = 1.2f;
	}
	else if (m_rot.x <= -0.3f)
	{
		m_rot.x = -0.3f;
	}
}

//========================
// �J�����̐U�����̐ݒ�
//========================
void CCamera::ShakeCamera(int fream, float magnitude, D3DXVECTOR3 max)
{
	m_nQuakeFreamCount = fream;			//�h�炷�t���[����
	m_fQuakeMagnitude = magnitude;		//�h��̗�
	m_maxShake = max;					//�h��̑傫���̍ő�l
}