//******************************************************************************
// 弾 [bullet.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_LEVEL1_SIZE_X 40		//レベル1の弾のサイズX
#define BULLET_LEVEL1_SIZE_Y 40		//レベル1の弾のサイズY
#define BULLET_LEVEL2_SIZE_X 50		//レベル2の弾のサイズX
#define BULLET_LEVEL2_SIZE_Y 50		//レベル2の弾のサイズX
#define BULLET_LEVEL3_SIZE_X 60		//レベル3の弾のサイズX
#define BULLET_LEVEL3_SIZE_Y 60		//レベル3の弾のサイズX
#define ENEMY_BULLET_SIZE_X	30		//敵の弾のサイズX
#define ENEMY_BULLET_SIZE_Y 30		//敵の弾のサイズY
#define BULLET_ENEMY_COLLISION_X 25	
#define BULLET_ENEMY_COLLISION_Y 25
#define BULLET_LEVEL1_BEAM_SIZE_X 40//ビームのサイズX
#define BULLET_LEVEL1_BEAM_SIZE_Y 40//ビームのサイズY
#define BULLET_LEVEL2_BEAM_SIZE_X 50//ビームのサイズX
#define BULLET_LEVEL2_BEAM_SIZE_Y 50//ビームのサイズY
#define BULLET_LEVEL3_BEAM_SIZE_X 60//ビームのサイズX
#define BULLET_LEVEL3_BEAM_SIZE_Y 60//ビームのサイズY
#define BULLET_BOSS_BOM_SIZE_X 100		//ボムのサイズX
#define BULLET_BOSS_BOM_SIZE_Y 100		//ボムのサイズY
#define BULLET_BOM_SIZE_X 800				//ボムサイズ
#define BULLET_BOM_SIZE_Y 800				//ボムサイズ
#define FIFFUSION_BULLET_SIZE_X	100		//拡散サイズX
#define FIFFUSION_BULLET_SIZE_Y	100		//拡散サイズX
#define MAX_BULLET_TEX 6
#define MAX_EFFECT_COUNT 30
//******************************************************************************
// クラス
//******************************************************************************
class CBullet : public CScene2d
{
public:

	//テクスチャタイプ
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_NORMAL,
		TEX_TYPE_BEAM,
		TEX_TYPE_BOM,
		TEX_TYPE_ENEMY_NORMAL,
		TEX_TYPE_MAX
	}TEX_TYPE;
	CBullet(int nPriority = 10);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	//textureの情報
	D3DXVECTOR3 m_rot;			//向き
	TEX_TYPE m_Textype;			//テクスチャのタイプ
};
#endif