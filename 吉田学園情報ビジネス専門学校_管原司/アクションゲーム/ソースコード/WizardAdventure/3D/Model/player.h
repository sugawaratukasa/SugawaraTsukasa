//******************************************************************************
// プレイヤーの処理 [player.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_PLAYER_PARTS	(15)							// プレイヤーのモデルのパーツの最大数
#define MAX_MATERIAL		(50)							// マテリアルの最大
#define MAX_BLOCK			(3)								// ブロック数の最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CMotion;
class CModel;
class CBlock;
class CStone_Block;
class CParticle_Emitter;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CPlayer :public CScene
{
public:
	// プレイヤーパーツ
	typedef enum
	{
		PARTS_UNDER_BODY = 0,	// 腰
		PARTS_BODY,				// 上体
		PARTS_HEAD,				// 頭
		PARTS_SHOULDER_R,		// 右肩
		PARTS_UP_ARM_R,			// 右上腕
		PARTS_DOWN_ARM_R,		// 右前腕
		PARTS_SHOULDER_L,		// 左肩
		PARTS_UP_ARM_L,			// 左上腕
		PARTS_DOWN_ARM_L,		// 左前腕
		PARTS_THIGTS_R,			// 右太もも
		PARTS_KNEE_R,			// 右膝
		PARTS_FOOT_R,			// 右足
		PARTS_THIGTS_L,			// 左太もも
		PARTS_KNEE_L,			// 左膝
		PARTS_FOOT_L,			// 左足
		PARTS_MAX				// 最大数
	}PLAYER_PARTS;

	// モーション
	typedef enum {
		MOTION_IDLE = 0,// 待機モーション
		MOTION_RUN,		// 歩きモーション
		MOTION_JUMP,	// ジャンプモーション
		MOTION_LANDING,	// 着地モーション
		MOTION_MAX		// 最大数
	}MOTIONSTATE;

	// ブロックを用いての行動の種類
	typedef enum
	{
		BLOCK_ACTIVE_NONE = 0,	// ブロックを用いて行動をしていない状態
		BLOCK_ACTIVE_CREATE,	// ブロック生成時
		BLOCK_ACTIVE_MOVE,		// ブロックを移動させている状態
		BLOCK_ACTIVE_SELECT,	// ブロックを選択している状態
		BLOCK_ACTIVE_SELECTED,	// ブロックを選択した状態
		BLOCK_ACTIVE_MAX		// 最大数
	}BLOCK_ACTIVE;

	// プレイヤーの向き
	typedef enum
	{
		ROT_STATE_RIGHT = 0,// 右を向いている状態
		ROT_STATE_LEFT,		// 左を向いている状態
		ROT_STATE_MAX		// 最大数
	}ROT_STATE;

	// パーティクルエミッター
	enum PARTICLE_EMITTER
	{
		PARTICLE_EMITTER_NONE = -1,		// 最小
		PARTICLE_EMITTER_RIGHT,			// 右
		PARTICLE_EMITTER_LEFT,			// 左
		PARTICLE_EMITTER_MAX			// 最大
	};

	// 放射体の種類
	enum EMITTER_TYPE
	{
		EMITTER_TYPE_NONE = -1,
		EMITTER_TYPE_STAR,
		EMITTER_TYPE_FIRE,
		EMITTER_TYPE_ICE,
		EMITTER_TYPE_MAX
	};

	// 魔法の種類
	enum MAGIC_TYPE
	{
		MAGIC_TYPE_FIREBALL = 0,
		MAGIC_TYPE_ICEBALL,
		MAGIC_TYPE_MAX
	};

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nLife);
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	BLOCK_ACTIVE GetBlockActive(void) { return m_Blcok_Active; }
	D3DXMATRIX GetMtxWorld(PLAYER_PARTS Parts);
	int GetLife(void) { return m_nLife; }
	ROT_STATE GetRotState(void) { return m_Rot_State; }
	MAGIC_TYPE GetMagicType(void) { return m_MagicType; }
private:
	void RightSelectBlock(void);
	void RightBlock(void);
	void RightSelectionBlock(void);

	void LeftSelectBlock(void);
	void LeftBlock(void);
	void LeftSelectionBlock(void);

	void Block_Create(void);
	void Collision(void);
	void Move(void);
	void Magic(void);
	void Emitter_Create(EMITTER_TYPE EmitterType);

	static LPD3DXMESH m_pMesh[PARTS_MAX];							// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[PARTS_MAX];						// マテリアル情報のポインタ
	static DWORD m_nNumMat[PARTS_MAX];								// マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[PARTS_MAX];						// 行列計算用
	static int m_nldxModelParent[PARTS_MAX];						// 親モデルのインデックス
	static char* m_apFileName[PARTS_MAX];							// ファイルの名前
	static char* m_apTextureFileName[PARTS_MAX];					// テクスチャのファイルの名前
	D3DXVECTOR3 m_pos;												// 位置
	D3DXVECTOR3 m_posOld;											// 古い位置
	D3DXVECTOR3 m_RespawnPos;										// リスポーン位置
	D3DXVECTOR3 m_rot;												// 角度
	D3DXVECTOR3 m_size;												// 大きさ
	D3DXVECTOR3 m_move;												// 移動量
	bool m_bAllMotion;												// 全モーションの判定
	CMotion *m_pMotion;												// モーションクラスのポインタ
	CModel *m_pModel[PARTS_MAX];									// モデルクラスのポインタ
	CBlock *m_pBlock;												// 箱のポインタ
	CStone_Block *m_pStoneBlock;									// 石の箱のポインタ
	CParticle_Emitter *m_apParticle_Emitter[PARTICLE_EMITTER_MAX];	// パーティクルエミッターのポインタ
	BLOCK_ACTIVE m_Blcok_Active;									// 箱を用いての移動
	ROT_STATE m_Rot_State;											// 向きの状態
	MAGIC_TYPE m_MagicType;											// 魔法の種類
	EMITTER_TYPE m_Emitter_Type;									// 放射体の種類
	int m_nBlockNum;												// 箱の数
	int m_nBlock_Select_Num;										// 箱の選択する
	int m_nSelect_Save_Num;											// 箱の数を保存する
	int m_nMotion_Count;											// モーションカウント
	int m_nLife;													// 体力
	bool m_bStick;													// スティック判定
	bool m_bRot;													// 向き
	bool m_bJump;													// ジャンプ判定
	bool m_bJumpValue;												// ジャンプ量判定
	bool m_bBlock_Move;												// ブロックの移動判定
	bool m_bMagic;													// モーション判定
	bool m_bParticle_Emitter;										// エミッターの使用判定
	bool m_bCollision;												// オブジェタイプに当たっているか
	bool m_bChange_MagicType;										// 魔法のタイプ変更判定
	bool m_bEnemyCreate;											// 敵生成判定
	bool m_bDash;													// ダッシュ
	bool m_bEnd;													// 終了判定
};
#endif