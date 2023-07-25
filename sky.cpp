//===================================================
//
// ���b�V���̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "sky.h"
#include "application.h"
#include "renderer.h"

//=======================
// �R���X�g���N�^
//=======================
CSky::CSky() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʖ@���x�N�g���i�[�p
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	for (int i = 0; i < nMaxVtx; i++)
	{
		m_VtxPos[i] = {};	//���_�̈ʒu
		m_VtxNor[i] = {};	//���_�̖@���x�N�g���i�[�p
	}

	m_nNumVtx = 0;			//���_��
	m_nNumPolygon = 0;		//�|���S����
	m_nNumIndex = 0;		//�C���f�b�N�X��
	m_vertical = 0;			//���������̕�����
	m_fWidth = 0.0f;		//��

	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = nullptr;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
}

//=======================
// �f�X�g���N�^
//=======================
CSky::~CSky()
{

}

//=======================
// ������
//=======================
HRESULT CSky::Init(D3DXVECTOR3 pos)
{
	m_vertical = 20;		//������
	m_fWidth = 10000.0f;	//��

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//----------------------------------
	// ���b�V�����\��������̐ݒ�
	//----------------------------------
	m_nNumVtx = (m_vertical + 1) * (m_vertical + 1);						//���_��
	m_nNumPolygon = m_vertical * m_vertical * 2 + (m_vertical - 1) * 4;		//�|���S����
	m_nNumIndex = (m_vertical + 1) * 2 * m_vertical + (m_vertical - 1) * 2;	//�C���f�b�N�X��

	//----------------------------------
	// ���_�o�b�t�@�̐���
	//----------------------------------
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//----------------------------------
	// �C���f�b�N�X�o�b�t�@�̐���
	//----------------------------------
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pIdxBuff,
								NULL);

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//----------------------------------
	// ���_���̐ݒ�
	//----------------------------------
	float rotDiffZ = (D3DX_PI * 2.0f / (m_vertical - 1));		//Z�����̕����������

	for (int z = 0; z < m_vertical; z++)
	{
		float rotDiffX = (D3DX_PI * 2.0f / (m_vertical - 1));	//X�����̕����������
		float rotZ = rotDiffZ * z;		//Z�̊p�x��ݒ�

		for (int x = 0; x < m_vertical; x++)
		{
			float rotX = rotDiffX * x;	//x�̊p�x��ݒ�

			//���_���W�̐ݒ�
			pVtx[0].pos.x = sinf(rotX) * sinf(rotZ) * m_fWidth;
			pVtx[0].pos.y = cosf(rotX) * m_fWidth;
			pVtx[0].pos.z = sinf(rotX) * cosf(rotZ) * m_fWidth;

			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(sinf(rotX), 0.0f, cosf(rotZ));

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			float fTexX = 1.0f / m_vertical * x;
			float fTexY = 1.0f / m_vertical * z;
			pVtx[0].tex = D3DXVECTOR2(fTexY, -fTexX * 2);

			pVtx++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//----------------------------------
	// �C���f�b�N�X�̐ݒ�
	//----------------------------------
	int nCnt = 0;

	for (int Z = 0; Z < (m_vertical - 1); Z++)
	{
		for (int X = 0; X <= m_vertical; X++)
		{
			//�C���f�b�N�X�o�b�t�@�̐ݒ�
			pIdx[nCnt] = (WORD)(X + Z * m_vertical+m_vertical);
			pIdx[nCnt + 1] = (WORD)(X + Z * m_vertical);

			nCnt += 2;

			//�k�ރ|���S���̒ǉ�
			if (X == (m_vertical - 1))
			{
				pIdx[nCnt] = (WORD)(X + Z * m_vertical);
				pIdx[nCnt + 1] = (WORD)((Z + 2) * m_vertical);

				nCnt += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=======================
// �I��
//=======================
void CSky::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//=======================
// �X�V
//=======================
void CSky::Update()
{

}

//=======================
// �`��
//=======================
void CSky::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//------------------------------------
	// �}�g���b�N�X
	//------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//------------------------------------
	// ���_
	//------------------------------------
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//------------------------------------
	// �e�N�X�`��
	//------------------------------------
	//�e�N�X�`���̎擾
	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_NumTex));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								  0,
								  0,
								  m_nNumVtx,			//���_��
								  0,
								  m_nNumPolygon);		//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);

	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================
// ����
//===========================
CSky* CSky::Create(CTexture::NUM_TEXTURE numTex)
{
	CSky *pSky = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pSky = new CSky;	//����

	if (pSky != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pSky->m_NumTex = numTex;
		
		//������
		pSky->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pSky->SetObjType(OBJTYPE_PLAYER);
	}

	return pSky;
}