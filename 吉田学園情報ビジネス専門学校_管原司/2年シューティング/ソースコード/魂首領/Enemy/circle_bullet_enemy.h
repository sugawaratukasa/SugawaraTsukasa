//******************************************************************************
// 円形の弾を出す敵 [circle_bullet_enemy.h]
// Author : 管原　司
//******************************************************************************
#ifndef _CIRCLEL_BULLET_ENEMY_H_
#define _CIRCLEL_BULLET_ENEMY_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CCirecle_Bullet_Enemy : public CEnemy
{
public:
	// ドロップするアイテムの列挙型
	typedef enum
	{
		DROP_ITEM_NONE = -1,
		DROP_ITEM_POWERUP,
		DROP_ITEM_BOM,
		DROP_ITEM_MAX
	}DROP_ITEM;
	CCirecle_Bullet_Enemy(int nPriority = OBJTYPE_ENEMY);
	~CCirecle_Bullet_Enemy();
	static CCirecle_Bullet_Enemy * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, DROP_ITEM drop_item);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);

	DROP_ITEM m_DropItem;	// 落とすアイテム
	int m_nAttackCount;		// 攻撃カウント
};
#endif