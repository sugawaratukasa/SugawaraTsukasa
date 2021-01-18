//---------------------------------------------------
// number
// score.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define MAX_RANKING	5
//---------------------------------------------------
//前方宣言
//---------------------------------------------------
class CScore;
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CRanking : public CScene
{
public:
	CRanking(int nPriority = PRIORITY_TYPE_UI);
	~CRanking();
	static CRanking * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ReadFile(void);
	void ReadPlayerFile(void);
	void WriteFile(void);
	void SetRanking(int nScore);
private:
	CScore * m_apScore[MAX_RANKING];	//ランキング
	CScore * m_pPlayerScore;			//プレイヤースコア
	int m_anScore[MAX_RANKING];			//スコア
	int m_nPlayerScore;					//プレイヤースコア
};
#endif