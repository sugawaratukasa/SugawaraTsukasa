//******************************************************************************
// ボス [boss.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOSS_H_
#define _BOSS_H_
//******************************************************************************
// クラス
//******************************************************************************
class CBoss : public CScene2d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH_EFFECT,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CBoss(int nPriority = OBJTYPE_BOSS);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitBoss(int nDamage);

	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetState(void) { return m_State; }
	int GetLife(void) { return m_nLife; }
	bool GetHalfLife(void) { return m_bLifeHalf; }

private:
	void Attack(void);
	void State(void);
	void Move(void);
	void Death(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;					// テクスチャ情報
	D3DXVECTOR3 m_CollisionSize;							// 当たり判定サイズ
	D3DXVECTOR3 m_move;										// 移動
	int m_nLife;											// 体力
	int m_nAttackCount;										// 攻撃
	int m_nDamageCount;										// ダメージ
	int m_nSetCount;										// ボスセットカウント
	int m_nDeathCount;										// 死亡処理処理用カウント
	STATE m_State;											// State
	bool m_bMove;											// move
	bool m_bLifeHalf;										// ライフが半分以下になったか
};
#endif