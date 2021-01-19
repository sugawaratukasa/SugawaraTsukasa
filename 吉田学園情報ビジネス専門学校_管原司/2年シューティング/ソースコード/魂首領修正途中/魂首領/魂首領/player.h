//******************************************************************************
// 自機 [player.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define PLAYER_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define PLAYER_WEPON_SIZE		(D3DXVECTOR3(25.0f,25.0f,0.0f))
#define PLAYER_MOVE				(D3DXVECTOR3(8.0f,8.0f,0.0f))
#define PLAYER_BEAM_MOVE		(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(5.0f,5.0f,0.0f))
#define RATE_MOVE				(0.4f)
#define MAX_PLAYER_TEX			(3)
#define MAX_PLAYER				(3)
#define DAMAGE_RESPAWN_COUNT	(30)
#define NODAMAGE_COUNT			(50)
#define DAMAGE_COUNT			(300)
#define BOM_LAUNCH_TIME			(200)
#define MAX_BOM_POSSESION		(5)
#define PLAYER_LIFE				(3)
#define PLAYER_CONTINUE			(1)
//******************************************************************************
// クラス
//******************************************************************************
class CPlayer : public CScene
{
public:
	// タイプの列挙型
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_MAIN,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;
	// 状態用の列挙型
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_RESPAWN,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	// Level用の列挙型
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;

	CPlayer(int nPriority = OBJTYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitPlayer(void);
	void GetBom(int nBom);
	void GetPowerUp(void);
	void SetContinue(int Continue);
	void SavePlayer(void);
	void SetBossBom(bool bBoss);

	D3DXVECTOR3 GetPosition(void) { return m_MainPos; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_Collision_Size; }
	int GetLevel(void) { return m_Level; }
	int GetPlayerState(void) { return m_nPlayerState; }
	
private:
	void Move(void);
	void Shot(void);
	void PlayerState(void);

	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];		// テクスチャ情報
	CScene2d * m_apScene2D[TYPE_MAX];						// Playerの情報
	D3DXVECTOR3 m_MainPos;									// 中心
	D3DXVECTOR3 m_RightPos;									// 右
	D3DXVECTOR3 m_LeftPos;									// 左
	D3DXVECTOR3 m_Size;										// サイズ
	D3DXVECTOR3 m_Collision_Size;								// 当たり判定サイズ
	int m_nContinue;										// コンティニューカウント
	int m_nLife;											// 体力
	int m_nCountAnim;										// カウンター
	int m_nCountAnimWepon;									// カウンター
	int m_nPatternAnim;										// パターン
	int m_nPatternAnimWepon;								// 右パターン
	int m_AttackCount;										// 弾発射のカウント
	int m_nBeamCount;										// ビームの溜め時間
	int m_nDamageCount;										// ダメージカウント
	int m_nRespawnCount;									// リスポーンカウント
	int m_nNoDamageCount;									// 無敵時間
	int m_nBomCount;										// ボムの発射カウント
	int m_nBom_possession_count;							// ボムの所持数
	int m_nScore;											// スコア
	int m_nPlayerState;										// プレイヤーのstate
	int m_Level;											// プレイヤーのレベル
	bool m_bMove;											// 移動の状態
	bool m_bUseBeam;										// ビームの使用状態
	bool m_bUseBom;											// ボムの使用状態
	bool m_bBoss;											// ボス
	bool m_bContinue;										// コンティニュー
};
#endif