//---------------------------------------------------
// Player
// player.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define ENEMY_SIZE_X 50
#define ENEMY_SIZE_Y 50
#define ENEMY_BOSS_SIZE_X 800
#define ENEMY_BOSS_SIZE_Y 400
#define ENEMY_BOSS_COLLISION_SIZE_Y 100
#define ENEMY_MOVE_X 8
#define ENEMY_MOVE_Y 8
#define MAX_ENEMY_TEX 3
#define RATE_MOVE 0.4f
#define BOSS_LIFE 4000
#define NORMAL_ENEMY_LIFE 20
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CEnemy : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_NWAY,
		TYPE_TRAKING_NWAY,
		TYPE_TRAKING2,
		TYPE_TRAKING3,
		TYPE_TRAKING4,
		TYPE_CIRCLE,
		TYPE_RIGHT_CIRCLE,
		TYPE_WAVE,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BLUE,
		TEX_TYPE_RED,
		TEX_TYPE_BOSS,
		TEX_TYPE_MAX
	}TEX_TYPE;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CEnemy(int nPriority = PRIORITY_TYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, int nLife, TYPE type, TEX_TYPE tex_type, CScene::OBJTYPE objtype);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, int nLife, TYPE type, TEX_TYPE tex_type, CScene::OBJTYPE objtype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitEnemy(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMY_TEX];	//テクスチャ情報
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動
	int m_nAttackCount;		//攻撃カウント
	int m_nBossAttackCount;	//ボスの攻撃カウント
	TYPE m_Type;			//タイプ
	TEX_TYPE m_TexType;		//テクスチャタイプ
	STATE m_state;			//state
	int m_nLife;			//体力
	int m_nDamageCount;		//ダメージカウント
	int m_nCircleCount;		//円形のカウント
	float m_fAddPosX;		//加算用の変数
};
#endif