//******************************************************************************
// 敵 [enemy.h]
// Author : 管原　司
//******************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CEnemy : public CScene2d
{
public:
	// テクスチャの列挙型
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BLUE,
		TEX_TYPE_RED,
		TEX_TYPE_SHIP_BATTERY,
		TEX_TYPE_MAX
	}TEX_TYPE;
	// 状態の列挙型
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitEnemy(int nDamage);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, TEX_TYPE tex_type, CScene::OBJTYPE objtype);

	STATE GetState(void) { return m_state; }
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	//　テクスチャ情報
	TEX_TYPE m_TexType;										//　テクスチャタイプ
	STATE m_state;											//　state
	int m_nLife;											//　体力
	int m_nDamageCount;										//　ダメージカウント
};
#endif