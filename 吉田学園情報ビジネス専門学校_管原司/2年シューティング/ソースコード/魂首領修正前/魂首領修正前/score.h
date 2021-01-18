//---------------------------------------------------
// number
// score.h
// Authur:	管原司
//---------------------------------------------------
#ifndef SCORE_H_
#define SCORE_H_
#define MAX_SCORE 8
#define SCORE_SIZE_X 30
#define SCORE_SIZE_Y 30
class CNumber;
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_TYPE_UI);
	~CScore();
	static CScore * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void) { return m_nScore; }
private:
	CNumber * m_apNumber[MAX_SCORE];	//Scoreの情報
	int m_nScore;	//スコア
};
#endif