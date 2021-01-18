//=============================================================================
// Ranking
// ranking.cpp
// Author : 管原司
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS	//scanfエラー
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
//コンストラクタ
//---------------------------------------------------------
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(m_apScore, 0, sizeof(m_apScore));
	memset(m_anScore, 0, sizeof(m_anScore));
	m_nPlayerScore = 0;
}
//---------------------------------------------------------
//デストラクタ
//---------------------------------------------------------
CRanking::~CRanking()
{
}
//---------------------------------------------------------
//生成関数
//---------------------------------------------------------
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CRanking * pRanking;
	//メモリ確保
	pRanking = new CRanking;
	//初期化
	pRanking->Init(pos, rot, sizeX, sizeY);
	return pRanking;
}
//---------------------------------------------------------
//初期化関数
//---------------------------------------------------------
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	ReadPlayerFile();
	m_pPlayerScore = CScore::Create(D3DXVECTOR3(pos.x + 50, 100, pos.z), rot, 30, 30);
	m_pPlayerScore->SetScore(m_nPlayerScore);
	ReadFile();
	SetRanking(m_nPlayerScore);
	ReadFile();
		//初期化
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
//終了関数
//---------------------------------------------------------
void CRanking::Uninit(void)
{
	//終了
	Release();
}
//---------------------------------------------------------
//更新関数
//---------------------------------------------------------
void CRanking::Update(void)
{
}
//---------------------------------------------------------
//描画関数
//---------------------------------------------------------
void CRanking::Draw(void)
{
}
//---------------------------------------------------------
//ファイル読み込み関数
//---------------------------------------------------------
void CRanking::ReadFile(void)
{
	FILE * pFile;
	//ファイルの読み込み
	pFile = fopen("ranking.txt", "r");
	//ファイルが空じゃないか
	if (pFile != NULL)
	{
		//読み込み
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anScore[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
//---------------------------------------------------------------
//ファイル読み込み
//---------------------------------------------------------------
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	//ファイルの読み込み
	pFile = fopen("player.txt", "r");
	//ファイルが空じゃないか
	if (pFile != NULL)
	{
		//読み込み
		fscanf(pFile, "%d\n", &m_nPlayerScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}
//---------------------------------------------------------
//ファイル書き込み関数
//---------------------------------------------------------
void CRanking::WriteFile(void)
{
	FILE * pFile;
	//ファイルの書き出し
	pFile = fopen("ranking.txt", "w");
	//ファイルが空じゃないか
	if (pFile != NULL)
	{
		//書き込み
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anScore[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

void CRanking::SetRanking(int nScore)
{
	int nCount;
	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//ランキングを更新する場所判定
		if (m_anScore[nCount] == 0 || nScore > m_anScore[nCount])
		{
			//以降のランキングデータを後ろに移動
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
