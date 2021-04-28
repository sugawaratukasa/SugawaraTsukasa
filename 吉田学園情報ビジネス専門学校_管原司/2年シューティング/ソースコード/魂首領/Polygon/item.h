//******************************************************************************
// アイテム処理 [item.h]
// Author : 管原 司
//******************************************************************************
#ifndef _ITEM_H_
#define _ITEM_H_
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CItem : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BOM,
		TYPE_POWERUP,
		TYPE_MAX
	}TYPE;
	CItem(int nPriority = OBJTYPE_ITEM);
	~CItem();
	static HRESULT Load(void);
	static void Unload(void);
	static CItem * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	bool Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
	void HitPlayer(void);
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];		// テクスチャ
	TYPE m_type;											// タイプ
	D3DXVECTOR3 m_move;										// 移動
	bool m_bMove;											// moveのbool 変数
};
#endif