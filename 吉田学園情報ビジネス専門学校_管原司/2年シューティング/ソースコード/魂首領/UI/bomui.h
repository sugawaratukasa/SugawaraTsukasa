//******************************************************************************
// ボムのUI [bomui.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BOM_UI_H_
#define _BOM_UI_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_BOM		(5)								// ボムの最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CScene2d;
//******************************************************************************
// クラス
//******************************************************************************
class CBomUI : public CScene
{
public:
	CBomUI(int nPriority = OBJTYPE_UI);
	~CBomUI();
	static CBomUI * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBomUI(int mBomPossesion);
private:
	// 所持数の列挙型
	typedef enum
	{
		POSESSION_NONE = 0,
		POSESSION_1,
		POSESSION_2,
		POSESSION_3,
		POSESSION_4,
		POSESSION_MAX
	}POSESSION;

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ情報
	CScene2d * m_apScene2D[MAX_BOM];		// ライフの情報
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;
	int m_nBom_Posession;					// ボムの所持数
};
#endif