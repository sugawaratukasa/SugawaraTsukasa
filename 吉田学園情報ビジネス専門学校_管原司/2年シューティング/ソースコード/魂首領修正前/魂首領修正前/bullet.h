//---------------------------------------------------
// Bullet
// Bullet.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
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
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CBullet : public CScene2d
{
public:
	//�N������
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;
	//�e�̃p�^�[��
	typedef enum
	{
		PATTERN_TYPE_NONE = -1,
		PATTERN_TYPE_NORMAL,			//�ʏ�
		PATTERN_TYPE_BEAM,				//�r�[��
		PATTERN_TYPE_BOM,				//�{��
		PATTERN_TYPE_BOSS_BOM,			//�{�X��̎��̃{��
		PATTERN_TYPE_ENEMY_NORMAL,		//�G�̒ʏ�
		PATTERN_TYPE_ENEMY_TRAKING,		//�_���Ă���
		PATTERN_TYPE_ENEMY_DIFFUSION,	//�g�U
		PATTERN_TYPE_ENEMY_WAVE,		//�g��
		PATTERN_TYPE_MAX
	}PATTERN_TYPE;
	//�e�N�X�`���^�C�v
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
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEX];	//texture�̏��
	D3DXVECTOR3 m_move;			//�ړ�
	D3DXVECTOR3 m_rot;			//����
	TYPE m_type;				//�^�C�v
	TEX_TYPE m_textype;			//�e�N�X�`���̃^�C�v
	PATTERN_TYPE m_PatternType;	//�e�̎��
	OBJTYPE m_objtype;			//�I�u�W�F�N�g�^�C�v
	static bool m_bUseBeam;		//�r�[���̎g�p���
	static bool m_bUseBom;		//�{���̎g�p���
	int m_nEffectCount;			//�G�t�F�N�g�̐����J�E���g
	int m_nDifCount;			//�g�U�e�̃J�E���g
	int m_nAddMove;				//move�̉��Z
	int m_nBom_Anim_Count;		//�A�j���[�V�����J�E���g
	int m_nPattern_Bom_Anim;	//�{���̃p�^�[��
	float m_nMinMove;			//move�̌��Z
	float m_rad;				//�ʓx
	float m_fAngle;				//�p�x
	float m_fMoveX;
	float m_fMoveY;	
	bool m_bWavemove;
};
#endif