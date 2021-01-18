//---------------------------------------------------
// BG
// bg.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _BG_H_
#define _BG_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define MAX_BG 3
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FARST_BG,
		TYPE_SECOUND_BG,
		TYPE_THIRD_BG,
		TYPE_MAX
	}TYPE;
	CBg(int nPriority = PRIORITY_TYPE_BG);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];	//テクスチャ情報
	CScene2d * m_apScene2D[MAX_BG];	//BGの情報
	TYPE m_type;				//タイプ
	D3DXVECTOR3 m_Farstpos;		//位置
	D3DXVECTOR3 m_Secoundpos;	//位置
	D3DXVECTOR3 m_Thirdpos;		//位置
	D3DXVECTOR3 m_move;			//移動
	float m_texsizeX;			//テクスチャX
	float m_texsizeY;			//テクスチャY
	float m_fFastMove;			//速い
	float m_fSlowMove;			//遅い
	float m_fmove;				//移動
};
#endif
