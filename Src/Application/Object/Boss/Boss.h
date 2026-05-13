#pragma once
#include "../Enemy/Enemy.h"
class GameScene;

class C_Boss : public C_Enemy
{
public:
	C_Boss() ;
	~C_Boss() {};

	void Init();
	void Update();
	void Draw();

	void Spawn() { m_alive = true;m_hp = 50; }
	bool IsAlive() const { return m_alive; }

	void SetTex(KdTexture* tex)		 { m_tex = tex; }
	void SetPos(float x, float y)	 { m_pos = { x,y }; }
	void SetPlayer(C_Player* p)		 { m_playerPtr = p; }
	void SetOwner(GameScene* pOwner) { m_pOwner = pOwner; }

	void OnDamage(int damage);
	void Shoot();
	int GetHp() const { return m_hp; }

	Math::Vector2 GetPos() const { return m_pos; }

private:

	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	KdTexture* m_tex = nullptr;
	C_Player* m_playerPtr = nullptr;

	int m_hp = 50;
	float m_timer = 0.0f;

	float m_moveTimer = 0.0f;
	int   m_shotTimer = 0;
	bool m_alive = false;
	float m_targetX = 400.0f;
	GameScene* m_pOwner = nullptr;

};
