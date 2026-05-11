#include "EnemyBullet.h"

void EnemyBullet::Init()
{
	m_pos = { 0,0 };
	m_alive = false;
	m_mat = Math::Matrix::Identity;
}

void EnemyBullet::Update()
{
	if (!m_alive)return;

	m_pos.x -= m_speed;

	if (m_pos.x < -700.0f)
	{
		m_alive = false;
	}
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void EnemyBullet::Draw()
{
	if (!m_alive)return;
	if (!m_tex)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 32, 32), 1.0f);
}

void EnemyBullet::Shot(const Math::Vector2& pos)
{
	m_pos = pos;
	m_alive = true;
}
