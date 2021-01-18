//=============================================================================
// score.cpp
// Author : 管原司
//=============================================================================
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
#include <cmath>
//-----------------------------------
//コンストラクタ
//-----------------------------------
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;
}
//-----------------------------------
//デストラクタ
//-----------------------------------
CScore::~CScore()
{
}
//-----------------------------------
//生成
//-----------------------------------
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CScoreクラスのポインタ
	CScore * pScore;
	//メモリ確保
	pScore = new CScore;
	//初期化
	pScore->Init(pos, rot, sizeX, sizeY);
	return pScore;
}
//-----------------------------------
//初期化
//-----------------------------------
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//初期化
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x - (30.0f * nCnt), pos.y, pos.z), sizeX, sizeY);
	}
	return S_OK;
}
//-----------------------------------
//終了
//-----------------------------------
void CScore::Uninit(void)
{
	//終了
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
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
//-----------------------------------
//更新
//-----------------------------------
void CScore::Update(void)
{
}
//-----------------------------------
//描画
//-----------------------------------
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//描画
		m_apNumber[nCnt]->Draw();
	}
}
//-----------------------------------
//セット
//-----------------------------------
void CScore::SetScore(int nScore)
{
	//スコア代入
	m_nScore = nScore;
	//計算用変数
	int integer = 0;
	//カウント
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_SCORE; nCntDigit++, nCntNumber++)
	{
		//1の位以下を切り捨てる
		integer = int(m_nScore / std::pow(10.0f, nCntDigit)); 
		integer = int(integer * std::pow(10.0f, nCntDigit));
		//スコアを設定
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}
//----------------------------------
//スコアの加算
//----------------------------------
void CScore::AddScore(int nValue)
{
	//加算
	m_nScore += nValue;
	//スコアセット
	SetScore(m_nScore);
}
