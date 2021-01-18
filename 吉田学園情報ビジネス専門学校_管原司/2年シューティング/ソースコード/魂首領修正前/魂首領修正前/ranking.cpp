//=============================================================================
// Ranking
// ranking.cpp
// Author : �ǌ��i
//=============================================================================
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
//---------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(m_apScore, 0, sizeof(m_apScore));
	memset(m_anScore, 0, sizeof(m_anScore));
	m_nPlayerScore = 0;
}
//---------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------
CRanking::~CRanking()
{
}
//---------------------------------------------------------
//�����֐�
//---------------------------------------------------------
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CRanking * pRanking;
	//�������m��
	pRanking = new CRanking;
	//������
	pRanking->Init(pos, rot, sizeX, sizeY);
	return pRanking;
}
//---------------------------------------------------------
//�������֐�
//---------------------------------------------------------
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	ReadPlayerFile();
	m_pPlayerScore = CScore::Create(D3DXVECTOR3(pos.x + 50, 100, pos.z), rot, 30, 30);
	m_pPlayerScore->SetScore(m_nPlayerScore);
	ReadFile();
	SetRanking(m_nPlayerScore);
	ReadFile();
		//������
	m_apScore[0] = CScore::Create(D3DXVECTOR3(pos.x, 200, pos.z), rot, sizeX, sizeY);
	m_apScore[0]->SetScore(m_anScore[0]);
	m_apScore[1] = CScore::Create(D3DXVECTOR3(pos.x, 280, pos.z), rot, sizeX, sizeY);
	m_apScore[1]->SetScore(m_anScore[1]);
	m_apScore[2] = CScore::Create(D3DXVECTOR3(pos.x, 350, pos.z), rot, sizeX, sizeY);
	m_apScore[2]->SetScore(m_anScore[2]);
	m_apScore[3] = CScore::Create(D3DXVECTOR3(pos.x, 440, pos.z), rot, sizeX, sizeY);
	m_apScore[3]->SetScore(m_anScore[3]);
	m_apScore[4] = CScore::Create(D3DXVECTOR3(pos.x, 530, pos.z), rot, sizeX, sizeY);
	m_apScore[4]->SetScore(m_anScore[4]);
	return S_OK;
}
//---------------------------------------------------------
//�I���֐�
//---------------------------------------------------------
void CRanking::Uninit(void)
{
	//�I��
	Release();
}
//---------------------------------------------------------
//�X�V�֐�
//---------------------------------------------------------
void CRanking::Update(void)
{
}
//---------------------------------------------------------
//�`��֐�
//---------------------------------------------------------
void CRanking::Draw(void)
{
}
//---------------------------------------------------------
//�t�@�C���ǂݍ��݊֐�
//---------------------------------------------------------
void CRanking::ReadFile(void)
{
	FILE * pFile;
	//�t�@�C���̓ǂݍ���
	pFile = fopen("ranking.txt", "r");
	//�t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		//�ǂݍ���
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anScore[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
//---------------------------------------------------------------
//�t�@�C���ǂݍ���
//---------------------------------------------------------------
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	//�t�@�C���̓ǂݍ���
	pFile = fopen("player.txt", "r");
	//�t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		//�ǂݍ���
		fscanf(pFile, "%d\n", &m_nPlayerScore);
		//�t�@�C�������
		fclose(pFile);
	}
}
//---------------------------------------------------------
//�t�@�C���������݊֐�
//---------------------------------------------------------
void CRanking::WriteFile(void)
{
	FILE * pFile;
	//�t�@�C���̏����o��
	pFile = fopen("ranking.txt", "w");
	//�t�@�C�����󂶂�Ȃ���
	if (pFile != NULL)
	{
		//��������
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anScore[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}

void CRanking::SetRanking(int nScore)
{
	int nCount;
	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//�����L���O���X�V����ꏊ����
		if (m_anScore[nCount] == 0 || nScore > m_anScore[nCount])
		{
			//�ȍ~�̃����L���O�f�[�^�����Ɉړ�
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				m_anScore[nCntMove] = m_anScore[nCntMove - 1];
			}
			m_anScore[nCount] = nScore;
			break;
		}
	}
	WriteFile();
}
