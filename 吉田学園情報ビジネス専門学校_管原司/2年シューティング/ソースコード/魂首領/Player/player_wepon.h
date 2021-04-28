//******************************************************************************
// 自機の武器 [player_wepon.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_WEPON_H_
#define _PLAYER_WEPON_H_
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CPlayer_Wepon : public CScene2d
{
public:
	// タイプの列挙型
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_RIGHT,
		TYPE_LEFT,
		TYPE_MAX
	}TYPE;

	CPlayer_Wepon(int nPriority = OBJTYPE_PLAYER_WEPON);
	~CPlayer_Wepon();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer_Wepon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Move(void);
	void Shot(void);

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ情報
	TYPE m_Type;								// タイプ
	int m_nCountAnim;						// カウンター
	int m_nPatternAnim;						// パターン

};
#endif