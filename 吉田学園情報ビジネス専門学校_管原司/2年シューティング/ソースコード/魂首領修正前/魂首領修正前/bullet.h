//---------------------------------------------------
// Bullet
// Bullet.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define BULLET_LEVEL1_SIZE_X 40		//レベル1の弾のサイズX
#define BULLET_LEVEL1_SIZE_Y 40		//レベル1の弾のサイズY
#define BULLET_LEVEL2_SIZE_X 50		//レベル2の弾のサイズX
#define BULLET_LEVEL2_SIZE_Y 50		//レベル2の弾のサイズX
#define BULLET_LEVEL3_SIZE_X 60		//レベル3の弾のサイズX
#define BULLET_LEVEL3_SIZE_Y 60		//レベル3の弾のサイズX
#define ENEMY_BULLET_SIZE_X	30		//敵の弾のサイズX
#define ENEMY_BULLET_SIZE_Y 30		//敵の弾のサイズY
#define BULLET_ENEMY_COLLISION_X 25	
#define BULLET_ENEMY_COLLISION_Y 25
#define BULLET_LEVEL1_BEAM_SIZE_X 40//ビームのサイズX
#define BULLET_LEVEL1_BEAM_SIZE_Y 40//ビームのサイズY
#define BULLET_LEVEL2_BEAM_SIZE_X 50//ビームのサイズX
#define BULLET_LEVEL2_BEAM_SIZE_Y 50//ビームのサイズY
#define BULLET_LEVEL3_BEAM_SIZE_X 60//ビームのサイズX
#define BULLET_LEVEL3_BEAM_SIZE_Y 60//ビームのサイズY
#define BULLET_BOSS_BOM_SIZE_X 100		//ボムのサイズX
#define BULLET_BOSS_BOM_SIZE_Y 100		//ボムのサイズY
#define BULLET_BOM_SIZE_X 800				//ボムサイズ
#define BULLET_BOM_SIZE_Y 800				//ボムサイズ
#define FIFFUSION_BULLET_SIZE_X	100		//拡散サイズX
#define FIFFUSION_BULLET_SIZE_Y	100		//拡散サイズX
#define MAX_BULLET_TEX 6
#define MAX_EFFECT_COUNT 30
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CBullet : public CScene2d
{
public:
	//誰が撃つか
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;
	//弾のパターン
	typedef enum
	{
		PATTERN_TYPE_NONE = -1,
		PATTERN_TYPE_NORMAL,			//通常
		PATTERN_TYPE_BEAM,				//ビーム
		PATTERN_TYPE_BOM,				//ボム
		PATTERN_TYPE_BOSS_BOM,			//ボス戦の時のボム
		PATTERN_TYPE_ENEMY_NORMAL,		//敵の通常
		PATTERN_TYPE_ENEMY_TRAKING,		//狙ってくる
		PATTERN_TYPE_ENEMY_DIFFUSION,	//拡散
		PATTERN_TYPE_ENEMY_WAVE,		//波状
		PATTERN_TYPE_MAX
	}PATTERN_TYPE;
	//テクスチャタイプ
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BEAM,
		TEX_TYPE_BOM,
		TEX_TYPE_ENEMY_NORMAL,
		TEX_TYPE_ENEMY_WAVE,
		TEX_TYPE_MAX
	}TEX_TYPE;
	CBullet(int nPriority = PRIORITY_TYPE_BULLET);
	~CBullet();
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern, TEX_TYPE texType ,OBJTYPE objtype);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern, TEX_TYPE texType , OBJTYPE objtype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetUseBeam(bool bUseBeam);
	static void SetUseBom(bool bUseBom);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEX];	//textureの情報
	D3DXVECTOR3 m_move;			//移動
	D3DXVECTOR3 m_rot;			//向き
	TYPE m_type;				//タイプ
	TEX_TYPE m_textype;			//テクスチャのタイプ
	PATTERN_TYPE m_PatternType;	//弾の種類
	OBJTYPE m_objtype;			//オブジェクトタイプ
	static bool m_bUseBeam;		//ビームの使用状態
	static bool m_bUseBom;		//ボムの使用状態
	int m_nEffectCount;			//エフェクトの生成カウント
	int m_nDifCount;			//拡散弾のカウント
	int m_nAddMove;				//moveの加算
	int m_nBom_Anim_Count;		//アニメーションカウント
	int m_nPattern_Bom_Anim;	//ボムのパターン
	float m_nMinMove;			//moveの減算
	float m_rad;				//弧度
	float m_fAngle;				//角度
	float m_fMoveX;
	float m_fMoveY;	
	bool m_bWavemove;
};
#endif