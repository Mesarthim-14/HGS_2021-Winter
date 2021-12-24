////=============================================================================
////
//// �����L���O�N���X [ranking.cpp]
//// Author : Konishi Yuuto
////
////=============================================================================
//
////=============================================================================
//// �C���N���[�h
////=============================================================================
//#include "ranking.h"
//#include "manager.h"
//#include "renderer.h"
//#include "number_2d.h"
//#include <stdio.h>
//#include "texture.h"
//#include "resource_manager.h"
//
////=============================================================================
//// �}�N����`
////=============================================================================
//#define SAVE_FILENAME "data/Text/Ranking.txt"		// �t�@�C����
//#define RANKING_INTERVAL_X	(70.0f)					// �����̊Ԋu
//#define RANKING_INTERVAL_Y	(100.0f)					// �����̊Ԋu
//
//#define MY_RANKING_INTERVAL_X	(80.0f)				// �����̊Ԋu
//#define MY_RANKING_INTERVAL_Y	(88.0f)				// �����̊Ԋu
//
//#define RANKING_FLASH_NUM	(30)					// �����L���O�_�Ńt���[��
//
////=============================================================================
//// �}�N����`
////=============================================================================
//int CRanking::m_nRanking[MAX_RANKING] = {};
//int CRanking::m_nCurrentNum = -1;
//int CRanking::m_nMyRank = 0;
//
////=============================================================================
//// �����L���O����
////=============================================================================
//CRanking * CRanking::Create(void)
//{
//	// �������m��
//	CRanking *pRanking = new CRanking;
//
//	// ����������
//	pRanking->Init();
//
//	return pRanking;
//}
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CRanking::CRanking()
//{
//	// 0�N���A
//	memset(m_apRanking, 0, sizeof(m_apRanking));
//	memset(m_apMyRanking, 0, sizeof(m_apMyRanking));
//	m_nNumRanking = 0;
//	m_nFlashFlame = 0;
//	m_nSubNumber = 0;
//	m_nSubNum = 0;
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CRanking::~CRanking()
//{
//	m_nCurrentNum = -1;
//	m_nMyRank = 0;
//}
//
////=============================================================================
//// ����������
////=============================================================================
//HRESULT CRanking::Init(void)
//{
//	CTexture *pTexture = GET_TEXTURE_PTR;
//
//	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
//	{
//		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//		{
//			// �����̃������m��
//			m_apRanking[nCntRank][nCount] =
//				CNumber2d::Create(D3DXVECTOR3(RANKING_POS_X - nCount*RANKING_INTERVAL_X,
//									RANKING_POS_Y + nCntRank*RANKING_INTERVAL_Y, 0.0f),
//									D3DXVECTOR3(RANKING_SIZE_X, RANKING_SIZE_Y, 0.0f));
//
//			if (m_apRanking[nCntRank][nCount] != NULL)
//			{
//				int nNum = (m_nRanking[nCntRank] / (int)(pow(10, nCount))) % 10;
//
//				// �����̐ݒ�
//				m_apRanking[nCntRank][nCount]->SetNumber(nNum);
//			}
//
//			// ���݂̔ԍ���������
//			if (nCntRank == m_nCurrentNum)
//			{
//				// �e�N�X�`���̐ݒ�
//				m_apRanking[nCntRank][nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_2_2D));
//			}
//			else
//			{
//				// �e�N�X�`���̐ݒ�
//				m_apRanking[nCntRank][nCount]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_NUMBER_1_2D));
//			}
//		}
//	}
//
//	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//	//{
//	//	// �����̃������m��
//	//	m_apMyRanking[nCount] =
//	//		CNumber2d::Create(D3DXVECTOR3(470.0f - nCount*MY_RANKING_INTERVAL_X, 370.0f, 0.0f),
//	//							D3DXVECTOR3(MY_RANKING_SIZE_X, MY_RANKING_SIZE_Y, 0.0f));
//
//	//	if (m_apMyRanking[nCount] != NULL)
//	//	{
//	//		int nNum = (m_nMyRank / (int)(pow(10, nCount))) % 10;
//
//	//		// �����̐ݒ�
//	//		m_apMyRanking[nCount]->SetNumber(nNum);
//	//	}
//	//}
//
//	// �t�@�C������
//	Save();
//
//	return S_OK;
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void CRanking::Uninit(void)
//{
//	// �t�@�C������
//	Save();
//
//	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
//	{
//		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//		{
//			if (m_apRanking[nCntRank][nCount] != NULL)
//			{
//				// �I������
//				m_apRanking[nCntRank][nCount]->Uninit();
//				//delete m_apRanking[nCntRank][nCount];
//				m_apRanking[nCntRank][nCount] = NULL;
//			}
//		}
//	}
//
//	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//	//{
//	//	if (m_apMyRanking[nCount] != NULL)
//	//	{
//	//		// �����̃������m��
//	//		m_apMyRanking[nCount]->Uninit();
//	//		//delete m_apMyRanking[nCount];
//	//		m_apMyRanking[nCount] = NULL;
//	//	}
//	//}
//
//	// �������̊J������
//	Release();
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void CRanking::Update(void)
//{
//	// �|���S���̓_��
//	FlashPolygon();
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void CRanking::Draw(void)
//{
//	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
//	{
//		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//		{
//			if (m_apRanking[nCntRank][nCount] != NULL)
//			{
//				// �`�揈��
//				m_apRanking[nCntRank][nCount]->Draw();
//			}
//		}
//	}
//	//for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//	//{
//	//	if (m_apMyRanking[nCount] != NULL)
//	//	{
//	//		// �����̃������m��
//	//		m_apMyRanking[nCount]->Draw();
//
//	//	}
//	//}
//}
//
////=============================================================================
//// �t�@�C������
////=============================================================================
//void CRanking::Save(void)
//{
//	FILE *pFile;
//
//	// �t�@�C�����J��
//	pFile = fopen(SAVE_FILENAME, "w");
//
//	// �|�C���^�����������m�F
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			// �̗͂��t�@�C���ɏo��
//			fprintf(pFile, "%d\n", m_nRanking[nCount]);
//
//			// ���s
//			printf("\n");
//
//		}
//		// �t�@�C�������
//		fclose(pFile);
//	}
//	else
//	{	// �J���Ȃ������ꍇ
//		printf("�J���܂���ł���");
//	}
//}
//
////=============================================================================
//// �t�@�C���o��
////=============================================================================
//void CRanking::Load(void)
//{
//	FILE *pFile;
//
//	// �e�L�X�g�t�@�C�����J��
//	pFile = fopen(SAVE_FILENAME, "r");
//
//	// �t�@�C�����J�������̏���
//	if (pFile != NULL)
//	{
//		// �v���C���[���̏�����
//		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//		{
//			// ������
//			m_nRanking[nCount] = 0;
//
//			// �X�R�A���o��
//			fscanf(pFile, "%d\n", &m_nRanking[nCount]);
//		}
//		// �t�@�C�������
//		fclose(pFile);
//	}
//	else
//	{	// �t�@�C�����J���Ȃ��Ƃ�
//		printf("�J���܂���ł���\n");
//	}
//}
//
////=============================================================================
//// �����L���O�փX�R�A����
////=============================================================================
//void CRanking::SetRanking(int nNumber)
//{
//	// �t�@�C���o��
//	Load();
//
//	m_nMyRank = nNumber;
//	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//	{
//		// �����L���O���O������
//		if (m_nRanking[nCount] < nNumber)
//		{
//			for (int nCntRank = MAX_RANKING - 1; nCntRank > nCount; nCntRank--)
//			{
//				int nSort = m_nRanking[nCntRank];
//				m_nRanking[nCntRank] = m_nRanking[nCntRank - 1];
//				m_nRanking[nCntRank - 1] = nSort;
//			}
//			// �����L���O�ŉ��ʂ̏㏑��
//			m_nRanking[nCount] = nNumber;
//
//			// ���݂̔ԍ��擾
//			m_nCurrentNum = nCount;
//			break;
//		}
//	}
//}
//
////=============================================================================
//// �|���S���̐���
////=============================================================================
//void CRanking::FlashPolygon(void)
//{
//	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
//	{
//		for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//		{
//			if (nCntRank == m_nCurrentNum)
//			{
//				if (m_nCurrentNum != -1)
//				{
//					// �t���[�������Z
//					m_nFlashFlame++;
//
//					if (m_nFlashFlame >= RANKING_FLASH_NUM)
//					{
//						m_nFlashFlame = 0;
//
//						if (m_nSubNumber == 0)
//						{
//							// 0�ɂȂ�����؂�ւ�
//							m_nSubNumber = 255;
//						}
//						else if (m_nSubNumber == 255)
//						{
//							// 255�ɂȂ�����؂�ւ�
//							m_nSubNumber = 0;
//						}
//
//						for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
//						{
//							m_apRanking[nCntRank][nCount]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)m_nSubNumber));
//						}
//					}
//				}
//			}
//		}
//	}
//}