//--------------------------------------------------------
//
//	ship
//	ship.h
//	Authur	管原司
//--------------------------------------------------------

//--------------------------------------------------------
//マクロ定義
//--------------------------------------------------------
#define MAX_SHIP_TEX	3
#define MAX_SHIP	7
#define SHIP_SIZE_X	1000	//shipのxサイズ
#define SHIP_SIZE_Y 1800	//shipのyサイズ
#define SHIP_WEPON_SIZE_X	100	//weponサイズ
#define SHIP_WEPON_SIZE_Y	200	//weponサイズ

//--------------------------------------------------------
//クラス
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
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SHIP_TEX];	//テクスチャ
	CScene2d * m_apScene2D[MAX_SHIP];						//Shipの情報
	//位置座標
	D3DXVECTOR3 m_Ship_pos;									//shipの位置
	D3DXVECTOR3 m_Wepon1_pos;								//武器の位置
	D3DXVECTOR3 m_Wepon2_pos;								//武器の位置
	D3DXVECTOR3 m_Wepon3_pos;								//武器の位置
	D3DXVECTOR3 m_Wepon4_pos;								//武器の位置
	D3DXVECTOR3 m_Wepon5_pos;								//武器の位置
	D3DXVECTOR3 m_Wepon6_pos;								//武器の位置
	//向き座標
	D3DXVECTOR3 m_Wepon1_rot;								//武器の向き
	D3DXVECTOR3 m_Wepon2_rot;								//武器の向き
	D3DXVECTOR3 m_Wepon3_rot;								//武器の向き
	D3DXVECTOR3 m_Wepon4_rot;								//武器の向き
	D3DXVECTOR3 m_Wepon5_rot;								//武器の向き
	D3DXVECTOR3 m_Wepon6_rot;								//武器の向き
	D3DXVECTOR3 m_move;										//移動
	TYPE m_Type;											//タイプ
	//角度
	float m_fWepon1Angle;									//角度
	float m_fWepon2Angle;									//角度
	float m_fWepon3Angle;									//角度
	float m_fWepon4Angle;									//角度
	float m_fWepon5Angle;									//角度
	float m_fWepon6Angle;									//角度
	float m_fLength;										//長さ
	int m_nWeponAttackCount;								//攻撃カウント
	int m_nWepon1_Life;										//Wepon1の体力
	int m_nWepon2_Life;										//Wepon2の体力
	int m_nWepon3_Life;										//Wepon3の体力
	int m_nWepon4_Life;										//Wepon4の体力
	int m_nWepon5_Life;										//Wepon5の体力
	int m_nWepon6_Life;										//Wepon6の体力
	//State
	STATE m_Wepon1State;									//state
	STATE m_Wepon2State;									//state
	STATE m_Wepon3State;									//state
	STATE m_Wepon4State;									//state
	STATE m_Wepon5State;									//state
	STATE m_Wepon6State;									//state

	//ダメージカウント
	int m_nWepon1_DamageCount;								//ダメージカウント
	int m_nWepon2_DamageCount;								//ダメージカウント
	int m_nWepon3_DamageCount;								//ダメージカウント
	int m_nWepon4_DamageCount;								//ダメージカウント
	int m_nWepon5_DamageCount;								//ダメージカウント
	int m_nWepon6_DamageCount;								//ダメージカウント

	int m_nShipCount;										//船カウント
	float m_fAddPosX;										//pos加算用変数
};