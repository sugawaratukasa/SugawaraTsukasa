//---------------------------------------------------
// number
// number.h
// Authur:	管原司
//---------------------------------------------------
#ifndef NUMBER_H_
#define NUMBER_H_
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define MAX_NUMBER 9
#define NUMBER_SIZE_X 50
#define NUMBER_SIZE_Y 50
class CNumber
{
public:
	CNumber();
	~CNumber();
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber * Create(D3DXVECTOR3 pos, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファ
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	int m_nNumber;	//ナンバー
};
#endif