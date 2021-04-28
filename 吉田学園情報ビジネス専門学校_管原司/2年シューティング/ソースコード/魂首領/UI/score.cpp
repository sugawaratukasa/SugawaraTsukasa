//******************************************************************************
// スコア処理 [score.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../System/number.h"
#include "score.h"
#include <cmath>
//******************************************************************************
// マクロ定義
//******************************************************************************
#define COLOR_VALUE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色の値
#define DIVIDE_VALUE	(10.0f)								// 除算値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pos		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_nScore	= INIT_INT;
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
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
	{
		// 初期化
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * nCnt), m_pos.y, m_pos.z), m_size, COLOR_VALUE);
	}
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CScore::Uninit(void)
{
	// 最大数分繰り返す
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
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
	for (int nCnt = INIT_INT; nCnt < MAX_SCORE; nCnt++)
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
	int integer = INIT_INT;

	// カウント
	int nCntNumber = INIT_INT;

	// 最大数分繰り返す
	for (int nCntDigit = 1; nCntDigit <= MAX_SCORE; nCntDigit++, nCntNumber++)
	{
		// 1の位以下を切り捨てる
		integer = int(m_nScore / std::pow(DIVIDE_VALUE, nCntDigit));
		integer = int(integer * std::pow(DIVIDE_VALUE, nCntDigit));
		// スコアを設定
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(DIVIDE_VALUE, nCntDigit - 1)));
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
