//******************************************************************************
// ライフ処理 [life.h]
// Author : 管原 司
//******************************************************************************
#ifndef _LIFE_H_
#define _LIFE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_LIFE	(3)								// ライフ最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CScene2d;
//******************************************************************************
// クラス
//******************************************************************************
class CLife : public CScene
{
public:
	CLife(int nPriority = OBJTYPE_UI);
	~CLife();
	static HRESULT Load(void);
	static void Unload(void);
	static CLife * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(int nLife);
	void HitDamage(int Damage);
	void SetLife(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ情報
	CScene2d * m_apScene2D[MAX_LIFE];		// ライフの情報
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	int m_nNumLife;							// ライフ数
};
#endif