#pragma once
#include "../../Bullet/Bullet.h"

class Bullet;
class Player;
class C_Player;
class GameScene;

enum class EnemyType {
	Straight,	// 直進
	SineWave,	// 波上
	StopShot,	// 停止し打つ
	Homing		// ホーミング
};

class C_Enemy
{
public:

	C_Enemy() {};
	~C_Enemy() {};

	void Init();
	void Update();
	void Draw();
	void Hit();
	void PlayerHit();
	void SetPos(float x, float y) { m_pos.x = x; m_pos.y = y; };
	void SetTex(KdTexture* Tex); //セッター
	void SetType(EnemyType type) { m_type = type; }
	void SetOwner(GameScene* pOwner) { m_pOwner = pOwner; }
	void SetStopX(float x) { m_stopX = x; }
	void SetTargetPos(float x, float y);
	void SetPlayer(C_Player* p) { m_playerPtr = p; }
	Math::Vector2 GetPos()const { return m_pos; }
	
	//敵が生きているか？
	bool IsAlive() const { return m_alive; }

	bool IsDead() const { return m_dead; }


	//Scene* m_owner;

protected:

	void UpdateMovePattern();
	EnemyType m_type;
	float m_timer = 0.0f;//動き計算用タイマー
	float m_stopX;

	const float m_moveSpeed = 5.0f;
	const float m_radius = 32.0f;
	bool m_alive;
	C_Bullet m_bullet[10];

	bool m_dead;

	KdTexture* m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Vector2 m_startPos; //出現位置を覚える
	Math::Vector2 m_targetPos;
	Math::Matrix m_mat;
	C_Player* m_playerPtr = nullptr;

	GameScene* m_pOwner = nullptr;

};
