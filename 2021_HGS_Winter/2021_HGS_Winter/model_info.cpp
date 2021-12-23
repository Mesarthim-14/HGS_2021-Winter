//=============================================================================
//
// �K�w�\���p�̃��f���N���X���� [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model_info.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"

//=============================================================================
// static�錾������
//=============================================================================
list<CModelInfo*> CModelInfo::m_ModelInfoList[MODEL_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelInfo::CModelInfo(const MODEL_TYPE &type)
{
    //�e�����o�ϐ��̃N���A
    memset(&m_model, 0, sizeof(m_model));
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
    ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
    ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
    m_type = type;

    // ���X�g�֒ǉ�
    m_ModelInfoList[type].push_back(this);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelInfo::~CModelInfo()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModelInfo * CModelInfo::Create(const MODEL_TYPE &type)
{
    //�K�w���f���N���X�̃|�C���^�ϐ�
    CModelInfo *pModelInfo = new CModelInfo(type);

    // nullcheck
    if (pModelInfo)
    {
        //�����������Ăяo��
        pModelInfo->Init();

        return pModelInfo;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelInfo::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModelInfo::Uninit()
{
    int nCount = 0;

    // ���g��
    for (auto &itr = m_ModelInfoList[m_type].begin(); itr != m_ModelInfoList[m_type].end(); ++itr)
    {
        if (*itr == this)
        {
            itr = m_ModelInfoList[m_type].erase(itr);
            break;
        }
    }

    delete this;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelInfo::Draw(const D3DXVECTOR3 &rot)
{
}

//=============================================================================
// ���f���̏��ݒ�
//=============================================================================
void CModelInfo::SetModelStatus(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model)
{
    m_pos = pos;
    m_rot = rot;
    m_model = model;
}

//=============================================================================
// ���[���h�}�g���N�X���W
//=============================================================================
D3DXVECTOR3 CModelInfo::GetMtxPos()
{
    return D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}