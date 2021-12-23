#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[�N���X�w�b�_  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene
{
public:
    //=============================================================================
    // �L�����N�^�[�̏��
    //=============================================================================
    enum STATE
    {
        STATE_NORMAL = 0,
        STATE_MAX
    };

    //=============================================================================
    // �L�����N�^�[�̎��
    //=============================================================================
    enum CHARACTER_TYPE
    {
        CHARACTER_TYPE_NONE = -1,    // �����l
        CHARACTER_TYPE_PLAYER,        // �v���C���[
        CHARACTER_TYPE_MAX            // �ő�l
    };

    CCharacter(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    virtual ~CCharacter();                              // �f�X�g���N�^

    virtual HRESULT Init();             // ����������
    virtual void Uninit();              // �I������
    virtual void Update();              // �X�V����
    virtual void Draw();                // �`�揈��
    void Landing(const float &fHeight); // ���n
    void Fall();                        // ����

    // Get�֐�
    D3DXVECTOR3 GetPos()const                            { return m_pos; }                       // ���݂̍��W���
    D3DXVECTOR3 GetOldPos()const                         { return m_posOld; }                    // �Â����W���
    D3DXVECTOR3 GetRot()const                            { return m_rot; }                       // �p�x���
    D3DXVECTOR3 GetMove()const                           { return m_move; }                      // �ړ��ʂ̏��
    D3DXVECTOR3 GetSize()const                           { return m_size; }                      // �T�C�Y�擾
    CModelAnime *GetModelAnime(const int &nCount)const   { return m_apModelAnime.at(nCount); }   // ���[�V�����̃J�E���g���
    CMotion *GetMotion()const                            { return m_pMotion; }                   // ���[�V�����̃|�C���^���
    int GetStateCounter()const                           { return m_nStateCounter; }             // ��ԃJ�E���^�[�̏��
    int GetPartsNum()const                               { return m_apModelAnime.size(); }       // �p�[�c���擾
    float &GetSpeed()                                    { return m_fSpeed; }                    // �X�s�[�h�̏��
    STATE GetState()const                                { return m_State; }                     // ��Ԏ擾
    CHARACTER_TYPE GetType() const                       { return m_type; }                      // ���
    vector<CModelAnime*> GetModelAnimeVec()const         { return m_apModelAnime; }              // �|�C���^�S�Ă̎擾
    D3DXMATRIX GetMtxWorld()const                        { return m_mtxWorld; }                  // �}�g���N�X���[���h

    void SetPos(const D3DXVECTOR3 &pos)      { m_pos = pos; }            // ���W�̐ݒ�
    void SetLanding(const bool &bLanding)    { m_bLanding = bLanding; }  // ���n
    bool GetLanding()                        { return m_bLanding; }      // ���n����擾

protected:
    void SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �L�����N�^�[�̊�{���
    void ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum);           // ���f���̐���
    void SetShadowRotCalculation();                                         // �e����

    // Set�֐�
    void SetPosOld(const D3DXVECTOR3 &posOld)    { m_posOld = posOld; }      // ���W�̐ݒ�
    void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }          // �ړ��ʂ̐ݒ�
    void SetRot(const D3DXVECTOR3 &rot)          { m_rot = rot; }            // �p�x�̐ݒ�
    void SetSize(const D3DXVECTOR3 &size)        { m_size = size; }          // �T�C�Y�ݒ�
    void SetSpeed(const float &fSpeed)           { m_fSpeed = fSpeed; }      // ���x�̐ݒ�
    void SetState(const STATE &state)            { m_State = state; }        // ��Ԑݒ�
    void SetGravityFlag(const bool &bFlag)       { m_bGravity = bFlag; }     // �d�͂̃t���O
    void SetType(const CHARACTER_TYPE &type)     { m_type = type; }          // ���

private:
    // private�֐�
    void ModelAnimeUpdate();                    // ���f���A�j���[�V����
    void Gravity();                             // �d��
    void SetMotion(const int &nMotionState);    // ���[�V�����̐ݒ�

    // �������z�֐�
    virtual void UpdateState() = 0;             // �L�����N�^�[���

    // �����o�ϐ�
    vector<CModelAnime*> m_apModelAnime;    // ���f���p�[�c�p�|�C���^
    CMotion *m_pMotion;                     // ���[�V�����N���X�̃|�C���^
    D3DXVECTOR3 m_pos;                      // ���W
    D3DXVECTOR3 m_posOld;                   // �Â����W
    D3DXVECTOR3 m_move;                     // �ړ���
    D3DXVECTOR3 m_rot;                      // ���݂̉�]
    D3DXVECTOR3 m_size;                     // �T�C�Y
    D3DXMATRIX m_mtxWorld;                  // ���[���h�}�g���b�N�X
    STATE m_State;                          // ���
    CHARACTER_TYPE m_type;                  // ���
    int m_nStateCounter;                    // ��Ԃ̃J�E���^�[
    int m_nParts;                           // �p�[�c��
    float m_fSpeed;                         // �ړ���
    bool m_bLanding;                        // ���n�t���O
    bool m_bGravity;                        // �d�͂�������t���O
};
#endif
