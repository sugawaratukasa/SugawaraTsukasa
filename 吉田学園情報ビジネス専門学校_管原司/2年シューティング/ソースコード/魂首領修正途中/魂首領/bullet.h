//******************************************************************************
// �e [bullet.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define BULLET_LEVEL1_SIZE_X 40		//���x��1�̒e�̃T�C�YX
#define BULLET_LEVEL1_SIZE_Y 40		//���x��1�̒e�̃T�C�YY
#define BULLET_LEVEL2_SIZE_X 50		//���x��2�̒e�̃T�C�YX
#define BULLET_LEVEL2_SIZE_Y 50		//���x��2�̒e�̃T�C�YX
#define BULLET_LEVEL3_SIZE_X 60		//���x��3�̒e�̃T�C�YX
#define BULLET_LEVEL3_SIZE_Y 60		//���x��3�̒e�̃T�C�YX
#define ENEMY_BULLET_SIZE_X	30		//�G�̒e�̃T�C�YX
#define ENEMY_BULLET_SIZE_Y 30		//�G�̒e�̃T�C�YY
#define BULLET_ENEMY_COLLISION_X 25	
#define BULLET_ENEMY_COLLISION_Y 25
#define BULLET_LEVEL1_BEAM_SIZE_X 40//�r�[���̃T�C�YX
#define BULLET_LEVEL1_BEAM_SIZE_Y 40//�r�[���̃T�C�YY
#define BULLET_LEVEL2_BEAM_SIZE_X 50//�r�[���̃T�C�YX
#define BULLET_LEVEL2_BEAM_SIZE_Y 50//�r�[���̃T�C�YY
#define BULLET_LEVEL3_BEAM_SIZE_X 60//�r�[���̃T�C�YX
#define BULLET_LEVEL3_BEAM_SIZE_Y 60//�r�[���̃T�C�YY
#define BULLET_BOSS_BOM_SIZE_X 100		//�{���̃T�C�YX
#define BULLET_BOSS_BOM_SIZE_Y 100		//�{���̃T�C�YY
#define BULLET_BOM_SIZE_X 800				//�{���T�C�Y
#define BULLET_BOM_SIZE_Y 800				//�{���T�C�Y
#define FIFFUSION_BULLET_SIZE_X	100		//�g�U�T�C�YX
#define FIFFUSION_BULLET_SIZE_Y	100		//�g�U�T�C�YX
#define MAX_BULLET_TEX 6
#define MAX_EFFECT_COUNT 30
//******************************************************************************
// �N���X
//******************************************************************************
class CBullet : public CScene2d
{
public:

	//�e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BEAM,
		TEX_TYPE_BOM,
		TEX_TYPE_ENEMY_NORMAL,
		TEX_TYPE_MAX
	}TEX_TYPE;
	CBullet(int nPriority = 10);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	//texture�̏��
	D3DXVECTOR3 m_rot;			//����
	TEX_TYPE m_Textype;			//�e�N�X�`���̃^�C�v
};
#endif