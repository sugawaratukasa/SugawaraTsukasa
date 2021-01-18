//******************************************************************************
// �����L���O [ranking.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �t�@�C���C���N���[�h
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanf�G���[
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "number.h"
#include "score.h"
#include "ranking.h"
#include "result.h"
#include <stdio.h>
//******************************************************************************
// �}�N����`
//******************************************************************************
#define RANKING_SCORE_SIZE (D3DXVECTOR3(30.0f,30.0f,0.0f))
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(m_apScore, 0, sizeof(m_apScore));
	memset(m_anScore, 0, sizeof(m_anScore));
	m_nPlayerScore = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CRanking::~CRanking()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CRanking�N���X�̃|�C���^
	CRanking * pRanking;

	// �������m��
	pRanking = new CRanking;

	// �ʒu���W
	pRanking->m_pos = pos;

	// �T�C�Y���
	pRanking->m_size = size;

	// ������
	pRanking->Init();

	// �|�C���^��Ԃ�
	return pRanking;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CRanking::Init()
{
	// �v���C���[�e�L�X�g�ǂݍ���
	ReadPlayerFile();

	// �v���C���[�̃X�R�A����
	m_pPlayerScore = CScore::Create(D3DXVECTOR3(m_pos.x + 50, 100, m_pos.z), RANKING_SCORE_SIZE);

	// �X�R�A�ݒ�
	m_pPlayerScore->SetScore(m_nPlayerScore);
	// �����L���O�e�L�X�g�ǂݍ���

	ReadFile();

	// �����L���O�ݒ�
	SetRanking(m_nPlayerScore);

	// �����L���O�ǂݍ���
	ReadFile();

	// �X�R�A����
	m_apScore[0] = CScore::Create(D3DXVECTOR3(m_pos.x, 200, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[0]->SetScore(m_anScore[0]);
	m_apScore[1] = CScore::Create(D3DXVECTOR3(m_pos.x, 280, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[1]->SetScore(m_anScore[1]);
	m_apScore[2] = CScore::Create(D3DXVECTOR3(m_pos.x, 350, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[2]->SetScore(m_anScore[2]);
	m_apScore[3] = CScore::Create(D3DXVECTOR3(m_pos.x, 440, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[3]->SetScore(m_anScore[3]);
	m_apScore[4] = CScore::Create(D3DXVECTOR3(m_pos.x, 530, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[4]->SetScore(m_anScore[4]);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CRanking::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CRanking::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CRanking::Draw(void)
{
}
//******************************************************************************
// �����L���O�e�L�X�g�ǂݍ��݊֐�
//******************************************************************************
void CRanking::ReadFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("ranking.txt", "r");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anScore[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �v���C���[�̃e�L�X�g�ǂݍ��݊֐�
//******************************************************************************
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	// �t�@�C���̓ǂݍ���
	pFile = fopen("player.txt", "r");

	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// �ǂݍ���
		fscanf(pFile, "%d\n", &m_nPlayerScore);
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �����L���O�e�L�X�g�������݊֐�
//******************************************************************************
void CRanking::WriteFile(void)
{
	FILE * pFile;
	// �t�@�C���̏����o��
	pFile = fopen("ranking.txt", "w");
	// �t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		// ��������
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anScore[nCnt]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
//******************************************************************************
// �����L���O�ݒ�
//******************************************************************************
void CRanking::SetRanking(int nScore)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		// �����L���O���X�V����ꏊ����
		if (m_anScore[nCount] == 0 || nScore > m_anScore[nCount])
		{
			// �ȍ~�̃����L���O�f�[�^�����Ɉړ�
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				m_anScore[nCntMove] = m_anScore[nCntMove - 1];
			}
			m_anScore[nCount] = nScore;
			break;
		}
	}
	// �t�@�C����������
	WriteFile();
}
