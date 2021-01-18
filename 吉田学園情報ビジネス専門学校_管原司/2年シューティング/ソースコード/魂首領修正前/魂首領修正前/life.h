//---------------------------------------------------
//	LIFE
// life.cpp
// Authur:	管原司
//---------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_
#define MAX_LIFE 3
#define LIFE_SIZE_X 30
#define LIFE_SIZE_Y 30
//---------------------------------------------------
//前方宣言
//---------------------------------------------------
class CScene2d;
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CLife : public CScene
{
public:
	CLife(int nPriority = CScene::PRIORITY_TYPE_UI);
	~CLife();
	static CLife * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(int nLife);
	void HitDamage(int Damage);
	void SetLife(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ情報
	CScene2d * m_apScene2D[MAX_LIFE];	//ライフの情報
	D3DXVECTOR3 m_pos;	//位置座標
	int m_nNumLife;	//ライフ数
};
#endif