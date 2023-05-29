//===================================================
//
// �I�u�W�F�N�g�̏���
// Author : Sato Teruto
//
//===================================================

//--------------------
// �C���N���[�h
//--------------------
#include "object.h"
#include "object3d.h"

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
CObject* CObject::m_Top[nMaxPriority] = {};		//�ŏ��̃I�u�W�F�N�g
CObject* CObject::m_Current[nMaxPriority] = {};	//�Ō�̃I�u�W�F�N�g

//=============================
// �R���X�g���N�^
//=============================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority;	//�v���C�I���e�B�̔ԍ�
	m_bDeath = false;			//���S�t���O
	m_ObjType = OBJTYPE_NONE;

	//-----------------------------
	// �擪�̃I�u�W�F�N�g��ݒ�
	//-----------------------------
	if (m_Top[m_nPriority] == nullptr)
	{//�擪���Ȃ��Ȃ�
		//�擪�̃I�u�W�F�N�g�ɑ��
		m_Top[m_nPriority] = this;
		m_pPrev = nullptr;
	} 

	//-----------------------------
	// �Ō�̃I�u�W�F�N�g��ݒ�
	//-----------------------------
	if (m_pNext == nullptr)
	{//1��낪null�Ȃ�
		//�Ō�̃I�u�W�F�N�g�ɑ��
		m_pPrev = m_Current[m_nPriority];
		m_Current[m_nPriority] = this;

		if (m_pPrev)
		{
			m_pPrev->m_pNext = this;
		}
	}
}

//=============================
// �f�X�g���N�^
//=============================
CObject::~CObject()
{

}

//=============================
// �S�ĉ��
//=============================
void CObject::ReleaseAll(bool bFinish)
{
	for (int i = 0; i < nMaxPriority; i++)
	{
		if (!m_Top[i])
		{//Top��null�Ȃ�
			continue;
		}

		CObject* pObj = m_Top[i];

		while (pObj)
		{//pObj��null����Ȃ��Ȃ�
			//���̃I�u�W�F�N�g��ۑ�
			CObject* pObjNext = pObj->m_pNext;

			//�I������
			pObj->Uninit();
			pObj->Release();

			//���̃I�u�W�F�N�g�̃A�h���X����
			pObj = pObjNext;
		}

		//-------------------
		// ���S����
		//-------------------
		pObj = m_Top[i];

		while (pObj)
		{
			if (bFinish == true)
			{
				//���̃I�u�W�F�N�g��ۑ�
				CObject* pObjNext = pObj->m_pNext;

				if (pObj->m_bDeath == true)
				{
					//��������
					pObj->Death(pObj);
				}

				//���̃I�u�W�F�N�g�̃A�h���X����
				pObj = pObjNext;
			}
		}
	}
}

//=============================
// �S�čX�V
//=============================
void CObject::UpdateAll()
{
	for (int i = 0; i < nMaxPriority; i++)
	{
		if (!m_Top[i])
		{//Top��null�Ȃ�
			continue;
		}

		CObject* pObj = m_Top[i];

		while (pObj)
		{//pObj��null����Ȃ��Ȃ�
			//���̃I�u�W�F�N�g��ۑ�
			CObject* pObjNext = pObj->m_pNext;

			//�X�V����
			if (pObj->m_bDeath != true)
			{
				pObj->Update();
			}

			//���̃I�u�W�F�N�g�̃A�h���X����
			pObj = pObjNext;
		}

		//-------------------
		// ���S����
		//-------------------
		pObj = m_Top[i];

		while (pObj)
		{
			//���̃I�u�W�F�N�g��ۑ�
			CObject* pObjNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{
				//��������
				pObj->Death(pObj);
			}

			//���̃I�u�W�F�N�g�̃A�h���X����
			pObj = pObjNext;
		}
	}
}

//=============================
// �S�ĕ`��
//=============================
void CObject::DrawAll()
{
	for (int i = 0; i < nMaxPriority; i++)
	{
		if (!m_Top[i])
		{//Top��null�Ȃ�
			continue;
		}

		CObject* pObj = m_Top[i];

		while (pObj)
		{//pObj��null����Ȃ��Ȃ�
			//�`�揈��
			pObj->Draw();

			//���̃I�u�W�F�N�g�̃A�h���X����
			pObj = pObj->m_pNext;
		}
	}
}

//=============================
// �������
//=============================
void CObject::Release()
{
	//���S�t���O�𗧂Ă�
	m_bDeath = true;

	return;
}

//=============================
// ���S����
//=============================
void CObject::Death(CObject* pObj)
{
	//----------------------------------
	// �O��̃I�u�W�F�N�g�̐ڑ�
	//----------------------------------
	if (m_pPrev != nullptr)
	{//1�O��null����Ȃ��Ȃ�
	 //�O��Next�Ɏ�����
		m_pPrev->m_pNext = m_pNext;
	}

	if (m_pNext != nullptr)
	{//1�オnull����Ȃ��Ȃ�
	 //����Prev�ɑO����
		m_pNext->m_pPrev = m_pPrev;
	}

	//----------------------------------
	// �擪�ƍŌ�̃I�u�W�F�N�g��ݒ�
	//----------------------------------
	if (m_pPrev == nullptr)
	{//�������擪�Ȃ�
		//���̃I�u�W�F�N�g��擪�ɂ���
		m_Top[m_nPriority] = m_pNext;
	}

	if (m_pNext == nullptr)
	{//�������Ō�Ȃ�
		//���̃I�u�W�F�N�g���Ō�ɂ���
		m_Current[m_nPriority] = m_pPrev;
	}

	pObj->Uninit();

	delete pObj;
	pObj = nullptr;
}

//=============================
// �����̎擾
//=============================
int CObject::GetNumAll()
{
	return 0;
}

//========================================
// �I�u�W�F�N�g�̎擾
// �����F�ړI�̎�ށA�v���C�I���e�B�ԍ�
//========================================
CObject *CObject::GETObject(EObjType type, int nNum)
{
	CObject* pObj = m_Top[nNum];	//pObj��擪�ɂ���

	while (pObj)
	{//pObj��null����Ȃ��Ȃ�
		//���̃I�u�W�F�N�g�̃A�h���X����
		pObj = pObj->m_pNext;

		if (pObj && pObj->m_ObjType == type)
		{//�I�u�W�F�N�g��null����Ȃ� & �ړI�̎�ނȂ�
			return pObj;
		}
	}

	return nullptr;
}

//=============================
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================
void CObject::SetObjType(EObjType ObjType)
{
	m_ObjType = ObjType;
}

//=============================
// �I�u�W�F�N�g�̎�ނ̎擾
//=============================
CObject::EObjType CObject::GetObjType()
{
	return m_ObjType;
}