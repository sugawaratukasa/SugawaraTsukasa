//******************************************************************************
// ボス左 [boss_left.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOSS_LEFT_H_
#define _BOSS_LEFT_H_
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CBoss_Left : public CScene2d
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

	CBoss_Left(int nPriority = OBJTYPE_BOSS_LEFT);
	~CBoss_Left();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss_Left * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
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