//---------------------------------------------------
// Player
// player.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PLAYER_SIZE_X 50
#define PLAYER_SIZE_Y 50
#define PLAYER_COLLISION_SIZE_X 5
#define PLAYER_COLLISION_SIZE_Y 5
#define PLAYER_WEPON_SIZE_X 25
#define PLAYER_WEPON_SIZE_Y 25
#define PLAYER_MOVE_Y 8
#define PLAYER_MOVE_X 8
#define PLAYER_BEAM_MOVE_Y 5
#define PLAYER_BEAM_MOVE_X 5
#define RATE_MOVE 0.4f
#define MAX_PLAYER_TEX 3
#define MAX_PLAYER 3
#define DAMAGE_RESPAWN_COUNT 30
#define NODAMAGE_COUNT 50
#define DAMAGE_COUNT 300
#define BOM_LAUNCH_TIME 200
#define MAX_BOM_POSSESION	5
#define PLAYER_LIFE	3
#define PLAYER_CONTINUE	1
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CPlayer : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_MAIN,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_RESPAWN,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;
	CPlayer(int nPriority = PRIORITY_TYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void) { return m_Mainpos; }
	void HitPlayer(void);
	void GetBom(int nBom);
	void GetPowerUp(void);
	void SetContinue(int Continue);
	int GetLevel(void) { return m_Level; }
	int GetPlayerState(void) { return m_nPlayerState; }
	void SavePlayer(void);
	void SetBossBom(bool bBoss);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PLAYER_TEX];	//テクスチャ情報
	CScene2d * m_apScene2D[MAX_PLAYER];						//Playerの情報
	D3DXVECTOR3 m_Mainpos;									//中心
	D3DXVECTOR3 m_WeponRightpos;							//右
	D3DXVECTOR3 m_WeponLeftpos;								//左
	D3DXVECTOR3 m_move;										//移動
	int m_nContinue;									//
	int m_nLife;											//体力
	int m_nCountAnim;										//カウンター
	int m_nCountAnimWepon;									//カウンター
	int m_nPatternAnim;										//パターン
	int m_nPatternAnimWepon;								//右パターン
	int m_AttackCount;										//弾発射のカウント
	int m_nBeamCount;										//ビームの溜め時間
	int m_nDamageCount;										//ダメージカウント
	int m_nRespawnCount;									//リスポーンカウント
	int m_nNoDamageCount;									//無敵時間
	int m_nBomCount;										//ボムの発射カウント
	int m_nBom_possession_count;							//ボムの所持数
	int m_nScore;											//スコア
	int m_nPlayerState;									//プレイヤーのstate
	int m_Level;											//プレイヤーのレベル
	bool m_bMove;											//移動の状態
	bool m_bUseBeam;										//ビームの使用状態
	bool m_bUseBom;											//ボムの使用状態
	bool m_bBoss;											//ボス
	bool m_bContinue;										//コンティニュー
};
#endif