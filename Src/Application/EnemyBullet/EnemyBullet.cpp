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

	char buf[256];
	sprintf_s(buf, "Bullet Pos:%f\n", m_pos.x);
	/*if (m_pos.x < -700.0f)
	{
		m_alive = false;
	}*/
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void EnemyBullet::Draw()
{
	if (!m_alive) return;
	if (!m_tex || m_tex->GetSRView() == nullptr) return;

	Math::Rectangle srcRect = { 0, 0, 64, 32 };

	Math::Matrix scaleMat = Math::Matrix::CreateScale(1.5f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, -0.1f);
	Math::Matrix drawMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	SHADER.m_spriteShader.SetMatrix(drawMat);
	SHADER.m_spriteShader.DrawTex(m_tex, 0, 0, &srcRect);
}

void EnemyBullet::Shot(const Math::Vector2& pos)
{
	OutputDebugStringA("Enemy Shot Called!\n");

	m_pos = pos;
	m_alive = true;
	m_speed = 10.0f;
}
