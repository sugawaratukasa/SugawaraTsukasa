//=============================================================================
//
// ��ʑJ��
// result.h
// Author : �ǌ��i
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
//------------------------------------
//�O���錾
//------------------------------------
class CScene2d;
class CPlayerdata;
//------------------------------------
//�N���X
//------------------------------------
class CResult : public CScene
{
public:
	CResult(int nPriority = PRIORITY_TYPE_UI);
	~CResult();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CResult * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayerdata * GetPlayerData(void) { return m_pPlayerData; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̏��
	static CPlayerdata * m_pPlayerData;
	CScene2d * m_pScene2D;	//Result�̏��
	bool m_bfade;
};
#endif