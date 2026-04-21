#include "Enemy.h"
#include "Player.h"

C_Enemy::C_Enemy()
{
}

C_Enemy::~C_Enemy()
{
}

void C_Enemy::Init()
{
	m_pos.x = (float)(rand() % 600 - 300);
	m_pos.y = 400.0f;
	//m_move.x = m_moveSpeed;
	m_move.y = -2.0f ;
	m_alive = true;

	if (rand() % 2 == 0)
	{
		m_pos.x =(float)((rand() % 220) + 100);
	}
	else 
	{
		m_pos.x = (float)((rand() % 220) - 320);
	}
}

void C_Enemy::Update()
{
	if (!m_alive)return;

	m_pos.y += m_move.y;

	if (m_pos.y < -400.0f)
	{
		m_alive = false;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Enemy::Draw()
{
	if (!m_alive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Enemy::Hit()
{
	m_alive = false;
}


void C_Enemy::SetTex(KdTexture* Tex)
{
	m_tex = Tex;
}

Math::Vector2 C_Enemy::GetPos()
{
	return m_pos;
}
