//---------------------------------------------------
// number
// score.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_RANKING	5
//---------------------------------------------------
//�O���錾
//---------------------------------------------------
class CScore;
//---------------------------------------------------
//�N���X
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
	CScore * m_apScore[MAX_RANKING];	//�����L���O
	CScore * m_pPlayerScore;			//�v���C���[�X�R�A
	int m_anScore[MAX_RANKING];			//�X�R�A
	int m_nPlayerScore;					//�v���C���[�X�R�A
};
#endif