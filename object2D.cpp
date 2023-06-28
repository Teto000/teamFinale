//===================================
//
// �I�u�W�F�N�g2D�̏���
// Author : Sato Teruto
//
//===================================

//------------------------
// �C���N���[�h
//------------------------
#include <assert.h>
#include "object2D.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "input_keyboard.h"

//------------------------
// �}�N����`
//------------------------
#define	ROT		(0.05f)		//��]�p�x�̑�����
#define	SCAL	(0.01f)		//�g�k�̒l�̑�����

//===========================
// �R���X�g���N�^
//===========================
CObject2D::CObject2D() : CObject2D(0)
{
}

CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
	m_fRot = 0.0f;		//��]�p�x
	m_fScal = 0.0f;		//�傫��
	m_NumTex = CTexture::TEXTURE_NONE;
}

//===========================
// �f�X�g���N�^
//===========================
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//===========================
// ������
//===========================
HRESULT CObject2D::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu
	m_pos = pos;

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//------------------------
	// rhw�̐ݒ�
	//------------------------
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//------------------------
	// �e�N�X�`�����W�̐ݒ�
	//------------------------
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
// �I��
//===========================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//===========================
// �X�V
//===========================
void CObject2D::Update()
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
  	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���W�̐ݒ�
	//------------------------
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, -m_fHeight / 2, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fWidth / 2, m_fHeight / 2, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fWidth / 2, m_fHeight / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �`��
//===========================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_NumTex));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
						   0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
						   2);					//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);
}

//===========================
// ����
//===========================
CObject2D * CObject2D::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g2D�̐���
	CObject2D* pObj2D = nullptr;
	pObj2D = new CObject2D;

	//����������
	pObj2D->Init(pos);

	return pObj2D;
}

//===========================
// �ړ��ʂ̉��Z
//===========================
D3DXVECTOR3 CObject2D::AddMove(D3DXVECTOR3 move)
{
	m_pos += move;

	return m_pos;
}

//===========================
// �傫���̐ݒ�
//===========================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;		//���̐ݒ�
	m_fHeight = fHeight;	//�����̐ݒ�
}

//===========================
// �F�̐ݒ�
//===========================
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_�J���[�̐ݒ�
	//------------------------
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// ���E��ʒ[�̐ݒ�
//===========================
void CObject2D::SetScreenX(float posX, float fLeft, float fRight)
{
	if (posX <= fLeft)
	{
		posX = fLeft;
	}
	else if (posX >= fRight)
	{
		posX = fRight;
	}

	m_pos.x = posX;
}

//===========================
// �㉺��ʒ[�̐ݒ�
//===========================
void CObject2D::SetScreenY(float posY, float fUp, float fDown)
{
	if (posY <= fUp)
	{
		posY = fUp;
	}
	else if (posY >= fDown)
	{
		posY = fDown;
	}

	m_pos.y = posY;
}

//===========================
// ��ʊO�ɏo������
//===========================
bool CObject2D::OutScreen(D3DXVECTOR3 pos)
{
	if (pos.x <= 0.0f || pos.x >= SCREEN_WIDTH)
	{
		return true;
	}
	else if (pos.y <= 0.0f || pos.y >= SCREEN_HEIGHT)
	{
		return true;
	}

	return false;
}

//===========================
// �e�N�X�`�����W�̐ݒ�
//===========================
void CObject2D::SetTexCIE(float left ,float fRight)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(left, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fRight, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// �e�N�X�`���̐ݒ�
//===========================
void CObject2D::SetTexture(CTexture::NUM_TEXTURE numTex)
{
	m_NumTex = numTex;
}

//===========================
// ���_���W�̐ݒ�
//===========================
void CObject2D::SetVtxCIE(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth / 2, fHeight / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth / 2, fHeight / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==================================
// ���_���W�̐ݒ�(��])
//==================================
void CObject2D::SetVtxCIE_Rot(D3DXVECTOR3 pos, float rotX, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;	//�Ίp���̒������Z�o����
	float fAngle = atan2f(fWidth, fHeight);								//�Ίp���̊p�x���Z�o

	//���_���W�̐ݒ�
	pVtx[0].pos.x = pos.x + sinf(rotX + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.y = pos.y + cosf(rotX + (D3DX_PI + fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(rotX + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = pos.y + cosf(rotX + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(rotX - (0 + fAngle)) * fLength;
	pVtx[2].pos.y = pos.y + cosf(rotX - (0 + fAngle)) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(rotX - (0 - fAngle)) * fLength;
	pVtx[3].pos.y = pos.y + cosf(rotX - (0 - fAngle)) * fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// ���_���W�̐ݒ�(�Q�[�W)
//===========================
void CObject2D::SetVtxCIE_Gauge(D3DXVECTOR3 pos, 
	float fLeft,float fRight, float fUp, float fDown)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(fLeft, fUp, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fRight, fUp, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(fLeft, fDown, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fRight, fDown, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================
// ���_���W�̐ݒ�(�X�R�A)
//===========================
void CObject2D::SetVtxCIE_Score(D3DXVECTOR3 pos, float fWidth, float fHeight,float fSpace)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth / 2, -fHeight / 2, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth / 2, fHeight / 2, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth / 2, fHeight / 2, 0.0f);

	pos.x += fSpace;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=========================================
// ���u�����f�B���O�����Z�����ɐݒ�
//=========================================
void CObject2D::SetAddALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//=========================================
// �A�j���[�V�����̐ݒ�
// �����F���l�A�e�N�X�`���̕�����
//=========================================
void CObject2D::SetAnimation(float fNumber, int nPattern)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	float PatternSize = 1.0f / nPattern;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//tex�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fNumber * PatternSize, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fNumber * PatternSize + PatternSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fNumber * PatternSize, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fNumber * PatternSize + PatternSize, 1.0f);

	// ���_���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================================
// �A�j���[�V�����̐ݒ�
// �����F���̕������A���̐��l�A�c�̕������A�c�̐��l
//=====================================================
void CObject2D::SetSplitTex(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY) / Split);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY) / Split);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY + 1) / Split);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY + 1) / Split);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=========================================
// ���u�����f�B���O�����ɖ߂�
//=========================================
void CObject2D::ResAddALPHA()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================
// �~�`�ɓ�����
//===========================
D3DXVECTOR3 CObject2D::MoveCircle(D3DXVECTOR3 CenterPos, float fAngle, float fLength)
{
	//�p�x�̏㑤��0�ɂ���
	float fNewAngle = D3DXToRadian(fAngle) - D3DXToRadian(90);

	//�~�̈ʒu�܂ł̋��������߂�
	float fDistX = (float)(cos(fNewAngle) * fLength);
	float fDistY = (float)(sin(fNewAngle) * fLength);

	//�~�̈ʒu�Ɉړ�����
	m_pos.x = CenterPos.x + fDistX;
	m_pos.y = CenterPos.y + fDistY;

	return m_pos;
}