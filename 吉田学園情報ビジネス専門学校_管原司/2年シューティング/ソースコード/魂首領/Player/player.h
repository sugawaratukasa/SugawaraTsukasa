//******************************************************************************
// 自機 [player.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_
//******************************************************************************
// 前方宣言
//******************************************************************************
class CPlayer_Beam;
class CBom_Beam;
//******************************************************************************
// クラス
//******************************************************************************
class CPlayer : public CScene2d
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

	D3DXVECTOR3 GetCollisionSize(void) { return m_Collision_Size; }
	int GetLevel(void) { return m_nPower; }
	int GetPlayerState(void) { return m_nPlayerState; }
	bool GetUseShot(void) { return m_bUseShot; }
	bool GetUseBeam(void) { return m_bUseBeam; }
	bool GetUseBossBom(void) { return m_bBossBom; }
private:
	void Move(void);
	void Shot(void);
	void PlayerState(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ情報
	D3DXVECTOR3 m_Collision_Size;			// 当たり判定サイズ
	CPlayer_Beam *m_pBeam;					// ビームのポインタ
	CBom_Beam *m_pBomBeam;					// ボムビーム
	int m_nContinue;						// コンティニューカウント
	int m_nLife;							// 体力
	int m_nCountAnim;						// カウンター
	int m_nPatternAnim;						// パターン
	int m_AttackCount;						// 弾発射のカウント
	int m_nBeamCount;						// ビームの溜め時間
	int m_nDamageCount;						// ダメージカウント
	int m_nRespawnCount;					// リスポーンカウント
	int m_nBomCount;						// ボムの発射カウント
	int m_nBom_possession_count;			// ボムの所持数
	int m_nScore;							// スコア
	int m_nPlayerState;						// プレイヤーのstate
	int m_nPower;							// プレイヤーのパワー
	bool m_bMove;							// 移動の状態
	bool m_bUseShot;						// 通常弾を発射したか 
	bool m_bUseBeam;						// ビームの使用状態
	bool m_bUseBom;							// ボムの使用状態
	bool m_bBossBom;						// ボス専用のボムの使用状態	
	bool m_bBoss;							// ボス
	bool m_bBossDeath;						// ボスが死亡したか
	bool m_bContinue;						// コンティニュー
};
#endif