#ifndef _MODELANIME_H_
#define _MODELANIME_H_
//=============================================================================
//
// �K�w�\���p�̃��f���N���X [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModelInfo;

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelAnime
{
public:
    CModelAnime();  // �R���X�g���N�^
    ~CModelAnime(); // �f�X�g���N�^

    static CModelAnime *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model);               // ����������
    void Draw(const D3DXVECTOR3 &rot);                                                                      // �`�揈��

    // Set�֐�
    void SetParent(CModelAnime *pParent)            { m_pParent = pParent; }        // �e�̐ݒ�
    void SetPosAnime(const D3DXVECTOR3& posAnime)   { m_posAnime = posAnime; }      // �A�j���[�V�����p�[�c�̍��W
    void SetRotAnime(const D3DXVECTOR3& rotAnime)   { m_rotAnime = rotAnime; }      // �p�[�c�̊p�x
    void SetRotCalculation(const bool &bFlag)       { m_bRotCalculation = bFlag; }  // �p�x�̌v�Z�t���O�̐ݒ�

    // Get���
    CModelAnime* GetParent()const    { return m_pParent; }       // �e���̎擾
    D3DXVECTOR3 GetPosAnime()const   { return m_posAnime; }      // �A�j���[�V�������W���
    D3DXVECTOR3 GetRotAnime()const   { return m_rotAnime; }      // �A�j���[�V�����p�x���
    CModelInfo* GetModelInfo()const  { return m_pModelInfo; }    // ���f���̏��

private:
    // private�֐�
    void CreateInfoPtr();   // ��񐶐�

    // �����o�ϐ�
    CModelInfo *m_pModelInfo;   // ���f�����
    D3DXVECTOR3 m_posAnime;     // �A�j���[�V�����p�̈ʒu
    D3DXVECTOR3 m_rotAnime;     // �A�j���[�V�����p�̌���
    CModelAnime *m_pParent;     // �e���̃|�C���^

    // �e�̐����p
    bool m_bRotCalculation; // �p�x�̌v�Z�t���O
};

#endif 