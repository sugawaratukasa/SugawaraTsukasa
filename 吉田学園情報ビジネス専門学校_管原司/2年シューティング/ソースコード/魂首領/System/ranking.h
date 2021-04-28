//******************************************************************************
// ランキング [ranking.h]
// Author : 管原　司
//******************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_
//******************************************************************************
// 前方宣言
//******************************************************************************
class CScore;
//******************************************************************************
// クラス
//******************************************************************************
class CRanking : public CScene
{
public:
	typedef enum
	{
		SCORE_NONE = -1,
		SCORE_1Th,
		SCORE_2Th,
		SCORE_3Th,
		SCORE_4Th,
		SCORE_5Th,
		SCORE_MAX,
	}SCORE;
	CRanking(int nPriority = OBJTYPE::OBJTYPE_UI);
	~CRanking();
	static CRanking * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReadFile(void);
	void ReadPlayerFile(void);
	void WriteFile(void);
	void SetRanking(int nScore);
private:
	CScore * m_apScore[SCORE_MAX];		// ランキング
	CScore * m_pPlayerScore;			// プレイヤースコア
	D3DXVECTOR3 m_pos;					// 位置座標
	D3DXVECTOR3 m_size;					// サイズ
	int m_anScore[SCORE_MAX];			// スコア
	int m_nPlayerScore;					// プレイヤースコア
};
#endif