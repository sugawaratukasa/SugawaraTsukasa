//******************************************************************************
// ボス [boss.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOSS_H_
#define _BOSS_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_BOSS		(3)									// ボスの部位数
#define BOSS_LIFE		(4000)								// ボスのライフ
#define BOSS_MAIN_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの中央のサイズ
#define BOSS_RIGHT_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの右のサイズ
#define BOSS_LEFT_SIZE	(D3DXVECTOR3(150.0f,150.0f,0.0f))	// ボスの左のサイズ
//******************************************************************************
// クラス
//******************************************************************************
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
	CBoss(int nPriority = 10);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);
	void SetBoss(int nSetCount);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS];		// テクスチャ情報
	CScene2d * m_apScene2D[MAX_BOSS];						// Bossの情報
	D3DXVECTOR3 m_pos;										// 位置座標
	D3DXVECTOR3 m_size;										// サイズ
	int m_nLife;											// 体力
	int m_nAttackCount;										// 攻撃
	int m_nAttackCount2;									// 攻撃
	int m_nDamageCount;										// ダメージ
	int m_nSetCount;										// ボスセットカウント
	STATE m_State;											// State
	bool m_bMove;											// move
};
#endif