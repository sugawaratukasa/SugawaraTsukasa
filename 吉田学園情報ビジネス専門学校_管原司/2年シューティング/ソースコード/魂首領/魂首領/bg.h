//******************************************************************************
// 背景 [bg.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BG_H_
#define _BG_H_
//******************************************************************************
// クラス
//******************************************************************************
class CBg : public CScene
{
public:
	// タイプの列挙型
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FARST_BG,
		TYPE_SECOUND_BG,
		TYPE_THIRD_BG,
		TYPE_MAX
	}TYPE;
	CBg(int nPriority = OBJTYPE_BG);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// テクスチャ情報
	CScene2d * m_apScene2D[TYPE_MAX];					// BGの情報
	TYPE m_type;										// タイプ
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_size;									// サイズ
	float m_fSlowMove;									// 遅い
	float m_fmove;										// 移動
};													   
#endif
