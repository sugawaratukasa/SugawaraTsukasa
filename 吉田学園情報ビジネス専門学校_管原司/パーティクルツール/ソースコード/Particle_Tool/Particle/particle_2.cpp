//***********************************************************************************
//	particle [particle.cpp]
//	Author : 管原 司
//***********************************************************************************
//***********************************************************************************
// インクルードファイル
//***********************************************************************************
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "particle_2.h"
//***********************************************************************************
// マクロ定義
//***********************************************************************************
#define MIN_SCALE		(0.0f)					// 拡大率の最小値
#define MIN_COL			(0.0f)					// 色の最小値
#define MIN_LIFE		(0)						// ライフ最小値
#define RANDOM_POS_MUT	(10.0f)					// 掛ける値
#define MUT				(2.0f)					// ２倍
#define ROT_MAX			(360)					// 角度最大
#define COLOR_A			(255)					// α値
#define ADD_RAND		(1.0f)					// 疑似乱数用
//***********************************************************************************
// コンストラクタ
//***********************************************************************************
CParticle_2::CParticle_2()
{
	m_pUi			= NULL;
	m_nLife			= INIT_INT;
	m_bAlpha_Blend	= false;
	m_Angle			= INIT_D3DXVECTOR3;
}
//***********************************************************************************
// デストラクタ
//***********************************************************************************
CParticle_2::~CParticle_2()
{
}
//***********************************************************************************
// 生成関数
//***********************************************************************************
CParticle_2 * CParticle_2::Create(CUI *pUi)
{
	// CParticleのポインタ
	CParticle_2 *pParticle = NULL;

	// NULLの場合
	if (pParticle == NULL)
	{
		// メモリ確保
		pParticle = new CParticle_2;

		// NULLでない場合
		if (pParticle != NULL)
		{
			// 代入
			pParticle->m_pUi = pUi;

			// 位置設定
			pParticle->SetPosition(pParticle->m_pUi->GetPos_2());

			// サイズ設定
			pParticle->SetSize(pParticle->m_pUi->GetSize_2());

			// 色設定
			pParticle->SetColor(pParticle->m_pUi->GetColor_2());

			// テクスチャ番号取得
			int nNumTex = pParticle->m_pUi->GetTexNum_2();

			// テクスチャ受け渡し
			pParticle->BindTexture(CManager::GetTexture()->GetTexture(nNumTex));

			// 透過値取得
			int nAlpha = pParticle->m_pUi->GetAlpha_2();

			// 透過値設定
			pParticle->SetAlpha(nAlpha);

			// 初期化
			pParticle->Init();
		}
	}
	// ポインタを返す
	return pParticle;
}
//***********************************************************************************
// 初期化関数
//***********************************************************************************
HRESULT CParticle_2::Init(void)
{
	// 初期化
	CBillboard::Init();

	// 向きをランダムにするか取得
	bool bRotRandom = m_pUi->GetbRotRandom_2();

	// falseの場合
	if (bRotRandom == false)
	{
		// 向き取得
		D3DXVECTOR3 rot = m_pUi->GetRot_2();

		// ラジアン変換
		rot = (D3DXToRadian(rot));

		// 向き設定
		SetRotation(rot);
	}
	// trueの場合
	if (bRotRandom == true)
	{
		// 向き取得
		D3DXVECTOR3 rot = INIT_D3DXVECTOR3;

		// 向きランダム
		rot.z = float(rand() % (int)ROT_MAX);

		// ラジアン変換
		rot = (D3DXToRadian(rot));

		// 向き設定
		SetRotation(rot);
	}

	// サイズランダム
	bool bRandomSize = m_pUi->GetRandomSize_2();

	// trueの場合
	if (bRandomSize == true)
	{
		// サイズ
		D3DXVECTOR3 size = INIT_D3DXVECTOR3;

		// ランダムサイズの最小値
		float fRandom_Min_Size = m_pUi->GetRandom_Min_Size_2();

		// ランダムサイズの最大値
		float fRandom_Max_Size = m_pUi->GetRandom_Max_Size_2();

		// サイズをランダム
		float fRandomSize = float(rand() % (int)fRandom_Max_Size + (int)fRandom_Min_Size);

		// サイズを設定
		size.x = fRandomSize;

		// サイズを設定
		size.y = fRandomSize;

		// サイズ設定
		SetSize(size);
	}

	// サイズランダム
	bool bRandomPos = m_pUi->GetbRandomPos_2();

	// trueの場合
	if (bRandomPos == true)
	{
		// 向き取得
		D3DXVECTOR3 pos = INIT_D3DXVECTOR3;

		// 取得
		D3DXVECTOR3 RandomPos = m_pUi->GetRandom_Pos_2();

		// 位置ランダム
		pos.x = float(rand() % (int)RandomPos.x *RANDOM_POS_MUT * MUT - (int)RandomPos.x *RANDOM_POS_MUT / MUT);

		// 除算
		pos.x = pos.x / RANDOM_POS_MUT;

		// 位置ランダム
		pos.y = float(rand() % (int)RandomPos.y * RANDOM_POS_MUT);

		// 除算
		pos.y = pos.y / RANDOM_POS_MUT;

		// 位置設定
		SetPosition(pos);
	}
	// カラーランダムか
	bool bColorRandom = m_pUi->GetColorRandom_2();

	// falseの場合
	if (bColorRandom == false)
	{
		// 色設定
		SetColor(m_pUi->GetColor_2());
	}
	// trueの場合
	if (bColorRandom == true)
	{
		// 色
		D3DXCOLOR col = INIT_COLOR;

		// 色取得
		int nColor_R = m_pUi->GetColorRandom_R_2();
		int nColor_G = m_pUi->GetColorRandom_G_2();
		int nColor_B = m_pUi->GetColorRandom_B_2();

		// 色ランダム
		nColor_R = (rand() % nColor_R);
		nColor_G = (rand() % nColor_G);
		nColor_B = (rand() % nColor_B);

		col = D3DCOLOR_RGBA(nColor_R, nColor_G, nColor_B, COLOR_A);

		// 色設定
		SetColor(col);
	}
	// ライフ
	bool bLife = m_pUi->GetbLife_2();

	// 角度をランダムに
	float fAngle = m_pUi->GetAngle_2();

	// 角度ランダム
	fAngle = float(rand() % (int)fAngle);

	// 角度取得
	m_Angle.x = fAngle;
	m_Angle.y = fAngle;
	m_Angle.z = fAngle;

	// trueの場合
	if (bLife == true)
	{
		// ライフ取得
		m_nLife = m_pUi->GetLife_2();
	}
	bool bTexRandom = m_pUi->GetbTexRandom_2();

	// trueの場合
	if (bTexRandom == true)
	{
		// テクスチャ最小番号取得
		int nMinTex = m_pUi->GetMinTexRandomNum_2();

		// テクスチャ最大番号取得
		int nMaxTex = m_pUi->GetMaxTexRandomNum_2();

		// 範囲内で乱数に
		int nTexNum = nMinTex + (int)(rand() * (nMaxTex - nMinTex + ADD_RAND) / (ADD_RAND + RAND_MAX));

		// テクスチャ受け渡し
		BindTexture(CManager::GetTexture()->GetTexture(nTexNum));
	}

	// falseの場合
	if (bTexRandom == false)
	{
		// テクスチャ番号取得
		int nNumTex = m_pUi->GetTexNum_2();

		// テクスチャ受け渡し
		BindTexture(CManager::GetTexture()->GetTexture(nNumTex));
	}

	return S_OK;
}
//***********************************************************************************
// 終了関数
//***********************************************************************************
void CParticle_2::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//***********************************************************************************
// 更新関数
//***********************************************************************************
void CParticle_2::Update(void)
{
	// 更新
	CBillboard::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 移動量取得
	D3DXVECTOR3 move = m_pUi->GetMove_2();

	// 拡大率取得
	float fScale = GetScale();

	// 角度加算値取得
	D3DXVECTOR3 AddAngle = m_pUi->GetAddAngle_2();

	// 角度加算
	m_Angle.x += AddAngle.x;
	m_Angle.y += AddAngle.y;
	m_Angle.z += AddAngle.z;

	// アルファブレンドを使用するか取得
	m_bAlpha_Blend = m_pUi->GetUseAlpha_Blend_2();

	// ライフ
	bool bLife = m_pUi->GetbLife_2();

	// ライフを使用する場合
	if (bLife == true)
	{
		// デクリメント
		m_nLife--;

		// ライフが0以下の場合
		if (m_nLife <= MIN_LIFE)
		{
			// 終了
			Uninit();
			return;
		}
	}

	// 拡大率を加算するか取得
	bool bAddScale = m_pUi->GetbAddScale_2();

	// 拡大率加算が使用状態なら
	if (bAddScale == true)
	{
		// 拡大率
		float AddScale = m_pUi->GetScale_2();

		// 拡大率加算
		fScale += AddScale;

		// 拡大率が0.0f以下の場合
		if (fScale <= MIN_SCALE)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// 色減算
	bool bSubColor = m_pUi->GetbSubColor_2();

	// 色減算を使用する場合
	if (bSubColor == true)
	{
		// 色減算値取得
		D3DXCOLOR SubColor = m_pUi->GetSubColor_2();

		// 減算
		col -= SubColor;

		// α値が0.0f以下の場合
		if (col.a <= MIN_COL)
		{
			// 終了
			Uninit();
			return;
		}
	}

	// 拡大率設定
	SetScale(fScale);

	// サイズ設定
	SetSize(size);

	// 色設定
	SetColor(col);

	// 位置更新
	pos.x += cosf(D3DXToRadian(m_Angle.x))*move.x;
	pos.y += sinf(D3DXToRadian(m_Angle.y))*move.y;
	pos.z += sinf(D3DXToRadian(m_Angle.z))*move.z;

	// 位置設定
	SetPosition(pos);
}
//***********************************************************************************
// 描画関数
//***********************************************************************************
void CParticle_2::Draw(void)
{
	// falseの場合
	if (m_bAlpha_Blend == false)
	{
		// 描画
		CBillboard::Draw();
	}

	// trueの場合
	if (m_bAlpha_Blend == true)
	{
		// レンダラー取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// 加算合成の設定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 描画
		CBillboard::Draw();

		// 元に戻す
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
