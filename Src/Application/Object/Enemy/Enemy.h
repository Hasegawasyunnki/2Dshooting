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
	//Homing		// ホーミング
};

class C_Enemy
{
public:

	C_Enemy() {};
	~C_Enemy() {};

	void Init();
	void Update();
	void Draw();
	void Hit(bool isDefeated);
	//void PlayerHit();
	void SetPos(float x, float y);
	void SetTex(KdTexture* Tex) {m_tex = Tex;}; //セッター
	void SetType(EnemyType type) { m_type = type; }
	void SetOwner(GameScene* pOwner) { m_pOwner = pOwner; }
	void SetStopX(float x) { m_stopX = x; }
	void SetTargetPos(float x, float y);
	void SetPlayer(C_Player* p) { m_playerPtr = p; }
	void Spawn() { m_alive = true; }
	void Shoot();
	Math::Vector2 GetPos()const { return m_pos; }
	
	//敵が生きているか？
	bool IsAlive() const { return m_alive; }

	bool IsDead() const { return m_dead; }
	//Scene* m_owner;

protected:

	void UpdateMovePattern(float speed);
	EnemyType m_type;
	float m_timer = 0.0f;//動き計算用タイマー
	float m_stopX;
	float m_hoverOffset;

	const float m_moveSpeed = 5.0f;
	const float m_radius = 32.0f;
	bool m_alive;
	bool m_dead;
	C_Bullet m_bullet[10];

	int m_shotTimer = 0;
	bool m_hasShot = false;

	KdTexture*			m_tex;
	Math::Vector2		m_pos;
	Math::Vector2		m_move;
	Math::Vector2		m_startPos; //出現位置を覚える
	Math::Vector2		m_targetPos;
	Math::Vector2		m_targetOffset;
	Math::Matrix		m_mat;
	C_Player* m_playerPtr = nullptr;
	GameScene* m_pOwner = nullptr;
};
