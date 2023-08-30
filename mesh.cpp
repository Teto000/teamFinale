//===================================================
//
// ���b�V���̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include <assert.h>
#include <time.h>
#include "mesh.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "game.h"

//=======================
// �R���X�g���N�^
//=======================
CMesh::CMesh() : CMesh(0)
{
}
CMesh::CMesh(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʖ@���x�N�g���i�[�p
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	for (int i = 0; i < nMaxVtx; i++)
	{
		m_VtxPos[i] = {};	//���_�̈ʒu
		m_VtxNor[i] = {};	//���_�̖@���x�N�g���i�[�p
	}

	m_nNumDivision = 0;		//�|���S���̕�����
	m_nCntVtx = 0;			//���_�̕�����
	m_nNumVtx = 0;			//���_��
	m_nNumPolygon = 0;			//�|���S����
	m_nNumIndex = 0;			//�C���f�b�N�X��
	m_fMaxWidth = 0.0f;		//���b�V���t�B�[���h�̍ő啝
	m_fMeshWidth = 0.0f;	//���b�V���t�B�[���h�̕�
	m_fTexSize = 0.0f;		//�e�N�X�`���̕����T�C�Y

	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = nullptr;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
}

//=======================
// �f�X�g���N�^
//=======================
CMesh::~CMesh()
{
	assert(m_pVtxBuff == nullptr);
	assert(m_pIdxBuff == nullptr);
}

//=======================
// ������
//=======================
HRESULT CMesh::Init(D3DXVECTOR3 pos)
{
	//���������Ƃɂ��������_���Ȓl�𐶐�
	//srand((unsigned int)time(NULL));

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//----------------------------------
	// ���b�V�����\��������̐ݒ�
	//----------------------------------
	m_nNumDivision = 20;				//�|���S���̕�����
	m_nCntVtx = m_nNumDivision + 1;		//���_�̕�����
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//���_��
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//�|���S����
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//�C���f�b�N�X��
	m_fMaxWidth = 5500.0f;								//���b�V���t�B�[���h�̍ő啝
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//���b�V���t�B�[���h�̕�
	m_fTexSize = (5.0f / m_nNumDivision);				//�e�N�X�`���̕����T�C�Y


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
	for (int z = 0; z < m_nCntVtx; z++)
	{
		for (int x = 0; x < m_nCntVtx; x++)
		{
			//���_���W�̐ݒ�
			{
				D3DXVECTOR3 vtxPos(-(m_fMaxWidth / 2) + (m_fMeshWidth * x), 0.0f, (m_fMaxWidth / 2) - (m_fMeshWidth * z));
				pVtx[x + (z * (m_nCntVtx))].pos = vtxPos;
			}

			//�e���_�̖@���̐ݒ�(���x�N�g���̑傫���͕K��1�ɂ���K�v������)
			pVtx[x + (z * (m_nCntVtx))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[x + (z * (m_nCntVtx))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[x + (z * (m_nCntVtx))].tex = D3DXVECTOR2(0.0f + m_fTexSize * x, 0.0f + m_fTexSize * z);
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

	// �C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < m_nNumDivision; nCntZ++)
	{
		for (int nCntX = 0; nCntX < (m_nNumDivision + 1); nCntX++)
		{// �C���f�b�N�X���̐ݒ�
			pIdx[0] = (WORD)((m_nNumDivision + 1) + nCntX + nCntZ * (m_nNumDivision + 1));
			pIdx[1] = (WORD)((m_nNumDivision + 1) + nCntX + nCntZ * (m_nNumDivision + 1) - (m_nNumDivision + 1));

			pIdx += 2;
		}

		if (nCntZ != m_nNumDivision - 1)
		{// �ő吔�ȉ��̎�
		 // �k�ރ|���S���C���f�b�N�X���̐ݒ�
			pIdx[0] = (WORD)((m_nNumDivision + 1) * nCntZ + m_nNumDivision);
			pIdx[1] = (WORD)((m_nNumDivision + 1) * (nCntZ + 2));

			pIdx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//���_�̖@����ݒ�
	SetVtxNor();

	return S_OK;
}

//=======================
// �I��
//=======================
void CMesh::Uninit()
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
void CMesh::Update()
{
	//-------------------------
	// ���b�V���̓����蔻��
	//-------------------------
	CollisionMesh();
}

//=======================
// �`��
//=======================
void CMesh::Draw()
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
								  m_nNumVtx,	//���_��
								  0,
								  m_nNumPolygon);	//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);
}

//==================================
// ���b�V���t�B�[���h�̓����蔻��
//==================================
void CMesh::CollisionMesh()
{
	/*//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	VERTEX_3D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//--------------------------
	// ���_�̈ʒu���擾
	//--------------------------
	for (int nCnt = 0; nCnt < m_nNumIndex; nCnt++)
	{//�C���f�b�N�X������
		m_VtxPos[nCnt] = pVtx[pIdx[nCnt]].pos;
	}

	//--------------------------
	// �F�̏�����
	//--------------------------
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{//���_������
		//�ʏ�̐F�ɂ���
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//------------------------------------
	// �v���C���[������|���S�������߂�
	//------------------------------------
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPosition();

	for (int nNumIdx = 0; nNumIdx < (m_nNumIndex - 2); nNumIdx++)
	{
		//�|���S���̒��_�̈ʒu���擾
		D3DXVECTOR3 P1 = m_VtxPos[nNumIdx + 0];
		D3DXVECTOR3 P2 = m_VtxPos[nNumIdx + 1];
		D3DXVECTOR3 P3 = m_VtxPos[nNumIdx + 2];

		//�k�ރ|���S���̏��O
		if (P1 == P2 || P2 == P3 || P3 == P1)
		{
			nNumIdx++;
			continue;
		}

		//�|���S���̒��_���m�̃x�N�g���̌v�Z
		D3DXVECTOR3 vecA = P2 - P1;
		D3DXVECTOR3 vecB = P3 - P2;
		D3DXVECTOR3 vecC = P1 - P3;

		//�v���C���[�ƒ��_�̃x�N�g���̌v�Z
		D3DXVECTOR3 vec1 = playerPos - P1;
		D3DXVECTOR3 vec2 = playerPos - P2;
		D3DXVECTOR3 vec3 = playerPos - P3;

		//�O�όv�Z�̎��ϐ�
		float a = vecA.x * vec1.z - vecA.z * vec1.x;
		float b = vecB.x * vec2.z - vecB.z * vec2.x;
		float c = vecC.x * vec3.z - vecC.z * vec3.x;

		//�O�όv�Z(2����)
		if ((a * b >= 0) && (b * c >= 0) && (c * a >= 0))
		{//3�̃x�N�g���̓����ɂ���(�O�ς��S��+)�Ȃ�
			//�ԐF�ɂ���
			/*pVtx[pIdx[nNumIdx + 0]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[pIdx[nNumIdx + 1]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[pIdx[nNumIdx + 2]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			//-------------------------
			// �ʖ@���x�N�g�����v�Z
			//-------------------------
			D3DXVECTOR3 V1 = P2 - P1;
			D3DXVECTOR3 V2 = P3 - P2;

			//�O�όv�Z(3����)
			D3DXVec3Cross(&m_Normal, &V1, &V2);

			//�x�N�g���̐��K��
			D3DXVec3Normalize(&m_Normal, &m_Normal);

			//-----------------------------
			// �v���C���[��Y���W�����߂�
			//-----------------------------
			playerPos.y = P1.y - ((playerPos.x - P1.x) * m_Normal.x
						   + (playerPos.z - P1.z) * m_Normal.z)
						   / m_Normal.y;

			//�v���C���[�̈ʒu�̐ݒ�
			CGame::GetPlayer()->SetPosition(playerPos);
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();*/
}

//===========================
// ���_�̖@����ݒ�
//===========================
void CMesh::SetVtxNor()
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//--------------------------
	// ���_�̈ʒu���擾
	//--------------------------
	for (int nCnt = 0; nCnt < m_nNumIndex; nCnt++)
	{//�C���f�b�N�X������
		m_VtxPos[nCnt] = pVtx[pIdx[nCnt]].pos;
		//�e���_�̃x�N�g�����i�[
		m_VtxNor[pIdx[nCnt]] = pVtx[pIdx[nCnt]].nor;
	}

	//-----------------------------
	// ���_�̖@���x�N�g����ݒ�
	//-----------------------------
	for (int nNumIdx = 0; nNumIdx < (m_nNumIndex - 2); nNumIdx++)
	{
		//�|���S���̒��_�̈ʒu���擾
		D3DXVECTOR3 P1 = m_VtxPos[nNumIdx + 0];
		D3DXVECTOR3 P2 = m_VtxPos[nNumIdx + 1];
		D3DXVECTOR3 P3 = m_VtxPos[nNumIdx + 2];

		//�k�ރ|���S���̏��O
		if (P1 == P2 || P2 == P3 || P3 == P1)
		{
			nNumIdx++;
			continue;
		}

		//-------------------------
		// �ʖ@���x�N�g�����v�Z
		//-------------------------
		D3DXVECTOR3 V1 = P2 - P1;
		D3DXVECTOR3 V2 = P3 - P2;

		//�O�όv�Z(3����)
		D3DXVec3Cross(&m_Normal, &V1, &V2);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&m_Normal, &m_Normal);

		//-------------------------
		// �@���̌����𑵂���
		//-------------------------
		if (nNumIdx % 2 != 0)
		{//��Ȃ�
			m_Normal *= -1;
		}

		//-------------------------
		// ���_�x�N�g�����v�Z
		//-------------------------
		//�ʖ@���x�N�g�������Z
		m_VtxNor[pIdx[nNumIdx]] += m_Normal;

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&m_VtxNor[pIdx[nNumIdx]], &m_VtxNor[pIdx[nNumIdx]]);

		//�x�N�g���̐ݒ�
		pVtx[pIdx[nNumIdx]].nor = m_VtxNor[pIdx[nNumIdx]];
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//===========================
// �������ƕ��̐ݒ�
//===========================
void CMesh::SetMeshSize(int nDivision, float fWidth)
{
	m_nNumDivision = nDivision;	//�|���S���̕������̐ݒ�
	m_fMaxWidth = fWidth;		//���b�V���t�B�[���h�̍ő啝�̐ݒ�

	//----------------------------
	// ���b�V���̏��̍Đݒ�
	//----------------------------
	m_nCntVtx = m_nNumDivision + 1;		//���_�̕�����
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//���_��
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//�|���S����
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//�C���f�b�N�X��
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//���b�V���t�B�[���h�̕�
	m_fTexSize = (1.0f / m_nNumDivision);				//�e�N�X�`���̕����T�C�Y
}

//===========================
// �e�N�X�`���̐ݒ�
//===========================
void CMesh::SetTexture(CTexture::NUM_TEXTURE numTex)
{
	m_NumTex = numTex;
}

//===========================
// �ʒu�̎擾
//===========================
D3DXVECTOR3 CMesh::GetPosition()
{
	return m_pos;
}

//===========================
// ���̎擾
//===========================
float CMesh::GetWidth()
{
	return 0.0f;
}

//===========================
// �����̎擾
//===========================
float CMesh::GetHeight()
{
	return 0.0f;
}