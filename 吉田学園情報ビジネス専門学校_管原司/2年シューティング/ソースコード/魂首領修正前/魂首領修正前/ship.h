//--------------------------------------------------------
//
//	ship
//	ship.h
//	Authur	�ǌ��i
//--------------------------------------------------------

//--------------------------------------------------------
//�}�N����`
//--------------------------------------------------------
#define MAX_SHIP_TEX	3
#define MAX_SHIP	7
#define SHIP_SIZE_X	1000	//ship��x�T�C�Y
#define SHIP_SIZE_Y 1800	//ship��y�T�C�Y
#define SHIP_WEPON_SIZE_X	100	//wepon�T�C�Y
#define SHIP_WEPON_SIZE_Y	200	//wepon�T�C�Y

//--------------------------------------------------------
//�N���X
//--------------------------------------------------------
class CShip : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_SHIP,
		TYPE_WEPON1,
		TYPE_WEPON2,
		TYPE_WEPON3,
		TYPE_WEPON4,
		TYPE_WEPON5,
		TYPE_WEPON6,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_SHIP,
		TEX_TYPE_WEPON1,
		TEX_TYPE_WEPON2,
		TEX_WEPON_MAX
	}TEX_TYPE;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CShip(int nPriority = PRIORITY_TYPE_SHIP);
	~CShip();
	static HRESULT Load(void);
	static void Unload(void);
	static CShip * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitWepon1(int nLife);
	void HitWepon2(int nLife);
	void HitWepon3(int nLife);
	void HitWepon4(int nLife);
	void HitWepon5(int nLife);
	void HitWepon6(int nLife);
	void SetShip(int nShip);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SHIP_TEX];	//�e�N�X�`��
	CScene2d * m_apScene2D[MAX_SHIP];						//Ship�̏��
	//�ʒu���W
	D3DXVECTOR3 m_Ship_pos;									//ship�̈ʒu
	D3DXVECTOR3 m_Wepon1_pos;								//����̈ʒu
	D3DXVECTOR3 m_Wepon2_pos;								//����̈ʒu
	D3DXVECTOR3 m_Wepon3_pos;								//����̈ʒu
	D3DXVECTOR3 m_Wepon4_pos;								//����̈ʒu
	D3DXVECTOR3 m_Wepon5_pos;								//����̈ʒu
	D3DXVECTOR3 m_Wepon6_pos;								//����̈ʒu
	//�������W
	D3DXVECTOR3 m_Wepon1_rot;								//����̌���
	D3DXVECTOR3 m_Wepon2_rot;								//����̌���
	D3DXVECTOR3 m_Wepon3_rot;								//����̌���
	D3DXVECTOR3 m_Wepon4_rot;								//����̌���
	D3DXVECTOR3 m_Wepon5_rot;								//����̌���
	D3DXVECTOR3 m_Wepon6_rot;								//����̌���
	D3DXVECTOR3 m_move;										//�ړ�
	TYPE m_Type;											//�^�C�v
	//�p�x
	float m_fWepon1Angle;									//�p�x
	float m_fWepon2Angle;									//�p�x
	float m_fWepon3Angle;									//�p�x
	float m_fWepon4Angle;									//�p�x
	float m_fWepon5Angle;									//�p�x
	float m_fWepon6Angle;									//�p�x
	float m_fLength;										//����
	int m_nWeponAttackCount;								//�U���J�E���g
	int m_nWepon1_Life;										//Wepon1�̗̑�
	int m_nWepon2_Life;										//Wepon2�̗̑�
	int m_nWepon3_Life;										//Wepon3�̗̑�
	int m_nWepon4_Life;										//Wepon4�̗̑�
	int m_nWepon5_Life;										//Wepon5�̗̑�
	int m_nWepon6_Life;										//Wepon6�̗̑�
	//State
	STATE m_Wepon1State;									//state
	STATE m_Wepon2State;									//state
	STATE m_Wepon3State;									//state
	STATE m_Wepon4State;									//state
	STATE m_Wepon5State;									//state
	STATE m_Wepon6State;									//state

	//�_���[�W�J�E���g
	int m_nWepon1_DamageCount;								//�_���[�W�J�E���g
	int m_nWepon2_DamageCount;								//�_���[�W�J�E���g
	int m_nWepon3_DamageCount;								//�_���[�W�J�E���g
	int m_nWepon4_DamageCount;								//�_���[�W�J�E���g
	int m_nWepon5_DamageCount;								//�_���[�W�J�E���g
	int m_nWepon6_DamageCount;								//�_���[�W�J�E���g

	int m_nShipCount;										//�D�J�E���g
	float m_fAddPosX;										//pos���Z�p�ϐ�
};