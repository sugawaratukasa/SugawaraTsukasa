//******************************************************************************
// スコア処理 [score.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// ファイルインクルード
//******************************************************************************
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "number.h"
#include "score.h"
#include <cmath>
//******************************************************************************
// コンストラクタ
//******************************************************************************
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore	= 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CScore::~CScore()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************-
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CScoreクラスのポインタ
	CScore * pScore;

	// メモリ確保
	pScore = new CScore;

	// 位置座標代入
	pScore->m_pos = pos;

	// サイズ代入
	pScore->m_size = size;

	// 初期化
	pScore->Init();

	// ポインタを返す
	return pScore;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CScore::Init()
{
	// 最大数分繰り返す
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// 初期化
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * nCnt), m_pos.y, m_pos.z), m_size);
	}
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CScore::Uninit(void)
{
	// 最大数分繰り返す
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// 終了
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
	//リリース
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CScore::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CScore::Draw(void)
{
	// 最大数分繰り返す
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// 描画
		m_apNumber[nCnt]->Draw();
	}
}
//******************************************************************************
// スコア設定
//******************************************************************************
void CScore::SetScore(int nScore)
{
	// スコア代入
	m_nScore = nScore;
	// 計算用変数
	int integer = 0;
	// カウント
	int nCntNumber = 0;

	// 最大数分繰り返す
	for (int nCntDigit = 1; nCntDigit <= MAX_SCORE; nCntDigit++, nCntNumber++)
	{
		// 1の位以下を切り捨てる
		integer = int(m_nScore / std::pow(10.0f, nCntDigit)); 
		integer = int(integer * std::pow(10.0f, nCntDigit));
		// スコアを設定
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}
//******************************************************************************
// スコア加算
//******************************************************************************
void CScore::AddScore(int nValue)
{
	// スコア加算
	m_nScore += nValue;
	// スコア設定
	SetScore(m_nScore);
}
