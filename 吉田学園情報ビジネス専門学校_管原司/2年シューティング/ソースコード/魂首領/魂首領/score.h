//******************************************************************************
// スコア処理 [score.h]
// Author : 管原　司
//******************************************************************************
#ifndef SCORE_H_
#define SCORE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_SCORE	(8)									// スコア最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CNumber;
//******************************************************************************
// クラス
//******************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = OBJTYPE_UI);
	~CScore();
	static CScore * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void) { return m_nScore; }
private:
	CNumber * m_apNumber[MAX_SCORE];	// Scoreの情報
	D3DXVECTOR3 m_pos;					// 位置座標
	D3DXVECTOR3 m_size;					// サイズ
	int m_nScore;						// スコア
};
#endif