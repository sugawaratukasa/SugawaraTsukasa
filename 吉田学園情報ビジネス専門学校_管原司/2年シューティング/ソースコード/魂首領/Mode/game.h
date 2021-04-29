//******************************************************************************
// ゲーム [game.h]
// Author : 管原 司
//******************************************************************************
#ifndef _GAME_H_
#define _GAME_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "mode.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_GAME_WIDTH (960)
#define MIN_GAME_WIDTH (320)
//******************************************************************************
// 前方宣言
//******************************************************************************
class CPlayer;
class CScore;
class CLife;
class CEnemy;
class CBomUI;
class CShip;
class CBoss;

///******************************************************************************
// クラス
//******************************************************************************
class CGame : public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateBoss(void);
	static CScore * GetScore(void) { return m_pScore; }
	static CLife * GetLife(void) { return m_pLife; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CBomUI * GetBomUI(void) { return m_pBom; }
	static CShip * GetShip(void) { return m_pShip; }
	static CBoss * GetBoss(void) { return m_pBoss; }
private:
	void Enemy_Respawn(void);

	static CScore * m_pScore;	// スコア情報
	static CLife * m_pLife;		// ライフ情報
	static CPlayer * m_pPlayer;	// プレイヤー情報
	static CBomUI * m_pBom;		// ボム
	static CShip * m_pShip;		// 船
	static CBoss * m_pBoss;		// ボス

	bool m_bfade;				// フェード
	int m_nCount;				// カウント
	int m_nRespawn_Count;		// Respawnカウント
	int m_nShipSpawnCount;		// 船の生成
	bool m_bUseBoss;			// ボス戦か
};
#endif