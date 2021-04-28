//******************************************************************************
// ランキング [ranking.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanfエラー
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "number.h"
#include "../UI/score.h"
#include "ranking.h"
#include "../Mode/result.h"
#include <stdio.h>
//******************************************************************************
// マクロ定義
//******************************************************************************
#define RANKING_SCORE_SIZE	(D3DXVECTOR3(30.0f,30.0f,0.0f))		// スコアのサイズ
#define RANKING_POS			(D3DXVECTOR3(50.0f,100.0f,0.0f))	// ランキングの位置
#define RANKING_SCORE_POS1	(D3DXVECTOR3(0.0f,200.0f,0.0f))		// スコア位置
#define RANKING_SCORE_POS2	(D3DXVECTOR3(0.0f,280.0f,0.0f))		// スコア位置
#define RANKING_SCORE_POS3	(D3DXVECTOR3(0.0f,350.0f,0.0f))		// スコア位置
#define RANKING_SCORE_POS4	(D3DXVECTOR3(0.0f,440.0f,0.0f))		// スコア位置
#define RANKING_SCORE_POS5	(D3DXVECTOR3(0.0f,530.0f,0.0f))		// スコア位置
#define RANKING_MOVE_VALUE	(-1)								// ランキング入れ替え
//******************************************************************************
// コンストラクタ
//******************************************************************************
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	memset(m_apScore, 0, sizeof(m_apScore));
	memset(m_anScore, 0, sizeof(m_anScore));
	m_nPlayerScore = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CRanking::~CRanking()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CRankingクラスのポインタ
	CRanking * pRanking;

	// メモリ確保
	pRanking = new CRanking;

	// 位置座標
	pRanking->m_pos = pos;

	// サイズ代入
	pRanking->m_size = size;

	// 初期化
	pRanking->Init();

	// ポインタを返す
	return pRanking;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CRanking::Init()
{
	// プレイヤーテキスト読み込み
	ReadPlayerFile();

	// プレイヤーのスコア生成
	m_pPlayerScore = CScore::Create(D3DXVECTOR3(m_pos.x + RANKING_POS.x, RANKING_POS.y, m_pos.z), RANKING_SCORE_SIZE);

	// スコア設定
	m_pPlayerScore->SetScore(m_nPlayerScore);

	// ランキングテキスト読み込み
	ReadFile();

	// ランキング設定
	SetRanking(m_nPlayerScore);

	// ランキング読み込み
	ReadFile();

	// スコア生成
	m_apScore[SCORE_1Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS1.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_1Th]->SetScore(m_anScore[SCORE_1Th]);
	m_apScore[SCORE_2Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS2.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_2Th]->SetScore(m_anScore[SCORE_2Th]);
	m_apScore[SCORE_3Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS3.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_3Th]->SetScore(m_anScore[SCORE_3Th]);
	m_apScore[SCORE_4Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS4.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_4Th]->SetScore(m_anScore[SCORE_4Th]);
	m_apScore[SCORE_5Th] = CScore::Create(D3DXVECTOR3(m_pos.x, RANKING_SCORE_POS5.y, m_pos.z), RANKING_SCORE_SIZE);
	m_apScore[SCORE_5Th]->SetScore(m_anScore[SCORE_5Th]);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CRanking::Uninit(void)
{
	// 終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CRanking::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CRanking::Draw(void)
{
}
//******************************************************************************
// ランキングテキスト読み込み関数
//******************************************************************************
void CRanking::ReadFile(void)
{
	FILE * pFile;
	// ファイルの読み込み
	pFile = fopen("ranking.txt", "r");
	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 読み込み
		for (int nCnt = INIT_INT; nCnt < SCORE_MAX; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anScore[nCnt]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}
//******************************************************************************
// プレイヤーのテキスト読み込み関数
//******************************************************************************
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	// ファイルの読み込み
	pFile = fopen("player.txt", "r");

	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 読み込み
		fscanf(pFile, "%d\n", &m_nPlayerScore);
		// ファイルを閉じる
		fclose(pFile);
	}
}
//******************************************************************************
// ランキングテキスト書き込み関数
//******************************************************************************
void CRanking::WriteFile(void)
{
	FILE * pFile;
	// ファイルの書き出し
	pFile = fopen("ranking.txt", "w");
	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 書き込み
		for (int nCnt = INIT_INT; nCnt < SCORE_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anScore[nCnt]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}
//******************************************************************************
// ランキング設定
//******************************************************************************
void CRanking::SetRanking(int nScore)
{
	for (int nCount = INIT_INT; nCount < SCORE_MAX; nCount++)
	{
		// ランキングを更新する場所判定
		if (m_anScore[nCount] == INIT_INT || nScore > m_anScore[nCount])
		{
			// 以降のランキングデータを後ろに移動
			for (int nCntMove = SCORE_MAX + RANKING_MOVE_VALUE; nCntMove > nCount; nCntMove--)
			{
				m_anScore[nCntMove] = m_anScore[nCntMove + RANKING_MOVE_VALUE];
			}
			m_anScore[nCount] = nScore;
			break;
		}
	}
	// ファイル書き込み
	WriteFile();
}
