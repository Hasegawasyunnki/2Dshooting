#pragma once

class EnemyBullet
{
public:
	EnemyBullet() {}
	~EnemyBullet(){}

	void Init();
	void Update();
	void Draw();

	void Shot(const Math::Vector2& pos);

	bool IsAlive() const { return m_alive; }
	const Math::Vector2& GetPos() const { return m_pos; }
	void Kill() { m_alive = false; }
	void SetTex(KdTexture* tex) { m_tex = tex; }

private:
	Math::Vector2	m_pos;
	Math::Matrix	m_mat;
	KdTexture*		m_tex = nullptr;
	bool			m_alive = false;

	float			m_speed = 5.0f;
};