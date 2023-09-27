//===================================================
//
// �J�����̏���
// Author:Teruto Sato
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include <cmath>
#include "camera.h"
#include "input.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "renderer.h"
#include "game.h"
#include "stage_select.h"
#include "debug_proc.h"
#include "utility.h"
#include "player.h"
#include "mode.h"

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
	m_initPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���_�̏����l
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);
	m_initPosV = m_posV;
	m_posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	//��]
	//Turn();

	//�Ǐ]����
	Follow();

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
CCamera* CCamera::Create()
{
	CCamera* pCamera = nullptr;

	//------------------------------
	// �|���S���̐����Ə�����
	//------------------------------
	pCamera = new CCamera;	//����

	if (pCamera != nullptr)
	{//NULL�`�F�b�N

		//������
		pCamera->Init();
	}

	return pCamera;
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
// �Ǐ]����
//========================
void CCamera::Follow()
{
	//�ϐ��錾
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);	//�Ǐ]����ʒu
	D3DXVECTOR3 pos1(0.0f, 0.0f, 0.0f);		//�v���C���[1�̈ʒu
	D3DXVECTOR3 pos2(0.0f, 0.0f, 0.0f);		//�v���C���[2�̈ʒu
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);		//�v���C���[�Ԃ̋���

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//----------------------------------------
	// �s����g�����J��������
	//----------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	float vecF;

	switch (CMode::GetMode())
	{//���[�h���Ƃ̏���
	case CMode::MODE_GAME:
		//-----------------------------
		// �v���C���[�Ԃ̒��S������
		//-----------------------------
		pos1 = CMode::GetGame()->GetPlayer(0)->GetPos();
		pos2 = CMode::GetGame()->GetPlayer(1)->GetPos();

		if (CGame::GetPlayer(0)->GetPast())
		{//�v���C���[���ߋ��ɂ���Ȃ�
			//�v���C���[�̈ʒu�𐮂���
			pos1.x -= CGame::GetPastPosX();
			pos2.x -= CGame::GetPastPosX();
		}
		
		//�v���C���[�Ԃ̋��������߂�
		vec = pos1 + pos2;

		//vecF = sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.z - pos2.z) * (pos1.z - pos2.z));

		//���̒��Ԃ�����
		target.x = pos1.x;
		target.z = pos1.z;

		if (CGame::GetPlayer(0)->GetPast() || CGame::GetPlayer(1)->GetPast())
		{//�v���C���[���ߋ��ɂ���Ȃ�
			//�Ǐ]�ʒu�̊�����炷
			target.x += CGame::GetPastPosX();
		}

		//�J�����̍����𒲐�
		m_posV.y = 50.0f;

		//�����̍Œ�l��ݒ�
		if (m_posV.y <= 300.0f)
		{
			m_posV.y = 300.0f;
		}
		break;

	//�X�e�[�W�I����ʂȂ�
	case CMode::MODE_STAGESELECT:
		target = CMode::GetStage()->GetPlayer()->GetPosition();
		break;

	default:
		break;
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�s��ɉ�]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�s��Ɉړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, target.x, target.y, target.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���[���h�ϊ��s����g����posV,posR�����߂�
	D3DXVec3TransformCoord(&m_posRDest, &m_posR, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_posVDest, &m_posV, &m_mtxWorld);
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