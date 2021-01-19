//******************************************************************************
// �~�`�̒e���o���G [circle_bullet_enemy.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CIRCLEL_BULLET_ENEMY_H_
#define _CIRCLEL_BULLET_ENEMY_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "enemy.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define CIRCLE_BULLET_ENEMY_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))	// �T�C�Y
#define CIRCLE_BULLET_ENEMY_LIFE (50)								// ���C�t
//******************************************************************************
// �N���X
//******************************************************************************
class CCirecle_Bullet_Enemy : public CEnemy
{
public:
	// �h���b�v����A�C�e���̗񋓌^
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
	DROP_ITEM m_DropItem;
	int m_nAttackCount;	// �U���J�E���g
};
#endif