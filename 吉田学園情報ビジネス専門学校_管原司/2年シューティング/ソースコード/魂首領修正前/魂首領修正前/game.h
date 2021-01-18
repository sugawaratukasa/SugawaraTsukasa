//=============================================================================
//
// 画面遷移
// game.h
// Author : 管原司
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
// ----------------------------------------------------------------------------
//マクロ
//----------------------------------------------------------------------------7
#define MAX_GAME_WIDTH 960
#define MIN_GAME_WIDTH 320
//----------------------------------------------------------------------------
//前方宣言
//----------------------------------------------------------------------------
class CPlayer;
class CScore;
class CLife;
class CEnemy;
class CBom;
class CShip;
class CBoss;
//---------------------------------------------------------------------------
//クラス
//---------------------------------------------------------------------------
class CGame : public CScene
{
public:
	static CGame * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	CGame(int nPriority = PRIORITY_TYPE_UI);
	~CGame();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore * GetScore(void) { return m_pScore; }
	static CLife * GetLife(void) { return m_pLife; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CBom * GetBomUI(void) { return m_pBom; }
	static CShip * GetShip(void) { return m_pShip; }
	static CBoss * GetBoss(void) { return m_pBoss; }
private:
	static CScore * m_pScore;
	static CLife * m_pLife;
	static CPlayer * m_pPlayer;	//プレイヤー情報
	static CBom * m_pBom;		//ボム
	static CShip * m_pShip;		//船
	static CBoss * m_pBoss;		//ボス
	bool m_bfade;				//フェード
	int m_nCount;				//カウント
	int m_nRespawn_Count;		//Respawnカウント
	int m_nShipSpawnCount;		//船の生成
	bool m_bUseBoss;				//ボス戦か
};
#endif