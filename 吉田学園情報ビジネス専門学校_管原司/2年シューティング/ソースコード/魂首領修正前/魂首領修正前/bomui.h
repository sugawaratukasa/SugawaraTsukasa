//---------------------------------------------------
//	bomui
// bom.h
// Authur:	管原司
//---------------------------------------------------

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#ifndef _BOM_H_
#define _BOM_H_
#define MAX_BOM 5
#define BOM_SIZE_X 40
#define BOM_SIZE_Y 40
//---------------------------------------------------
//前方宣言
//---------------------------------------------------
class CScene2d;
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CBom : public CScene
{
public:
	CBom(int nPriority = CScene::PRIORITY_TYPE_UI);
	~CBom();
	static CBom * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBomUI(int mBomPossesion);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ情報
	CScene2d * m_apScene2D[MAX_BOM];		//ライフの情報
	D3DXVECTOR3 m_pos;		//位置座標
	int m_nBom_Posession;	//ボムの所持数
};
#endif