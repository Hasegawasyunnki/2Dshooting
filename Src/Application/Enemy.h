#pragma once
#include "Bullet.h"
#include "Player.h"

class C_Enemy
{
public:

	C_Enemy();
	~C_Enemy();

	void Init();
	void Update();
	void Draw();
	void Hit();
	void PlayerHit();

	void SetTex(KdTexture* Tex); //セッター
	Math::Vector2 GetPos();

	//敵が生きているか？
	bool IsAlive() const { return m_alive; }

	Scene* m_owner ;

private:

	const float m_moveSpeed = 5.0f;
	const float m_radius = 32.0f;
	bool m_alive;
	C_Bullet m_bullet[10];

	KdTexture* m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
};
