//******************************************************************************
// ボス右 [boss_right.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOSS_RIGHT_H_
#define _BOSS_RIGHT_H_
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CBoss_Right : public CScene2d
{
public:

	// 状態
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	CBoss_Right(int nPriority = OBJTYPE_BOSS_RIGHT);
	~CBoss_Right();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss_Right * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);

private:
	void State(void);
	void Attack(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ情報
	STATE m_State;							// 状態変数
	int m_nAttackCount;						// 攻撃カウント
	int m_nDamageCount;						// ダメージカウント
	int m_nHalfLife_AttackCount;			// ライフが半分の時の攻撃カウント
};
#endif