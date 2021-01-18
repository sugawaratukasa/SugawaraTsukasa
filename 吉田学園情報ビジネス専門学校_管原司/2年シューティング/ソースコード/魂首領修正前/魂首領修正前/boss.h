//---------------------------------------------------
// Player
// player.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define MAX_BOSS 3
#define BOSS_MAIN_SIZE_X 150
#define BOSS_MAIN_SIZE_Y 150
#define BOSS_RIGHT_SIZE_X 150
#define BOSS_RIGHT_SIZE_Y 150
#define BOSS_LEFT_SIZE_X 150
#define BOSS_LEFT_SIZE_Y 150
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CBoss : public CScene
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
		STATE_MOVE,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	}STATE;
	CBoss(int nPriority = PRIORITY_TYPE_BOSS);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);
	void SetBoss(int nSetCount);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS];		//テクスチャ情報
	CScene2d * m_apScene2D[MAX_BOSS];						//Bossの情報
	D3DXVECTOR3 m_Mainpos;									//中心
	D3DXVECTOR3 m_Rightpos;							//右
	D3DXVECTOR3 m_Leftpos;								//左
	D3DXVECTOR3 m_move;										//移動
	int m_nLife;											//体力
	int m_nAttackCount;										//攻撃
	int m_nAttackCount2;									//攻撃
	int m_nDamageCount;										//ダメージ
	int m_nSetCount;										//ボスセットカウント
	STATE m_State;											//State
	bool m_bMove;											//move
};
#endif