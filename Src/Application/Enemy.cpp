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
	m_pos.x = 700.0f;
	m_pos.y = (float)(rand() % 400 - 200);
	m_move.x = -2.0f;
	m_move.y = 0.0f;
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

	m_pos.x += m_move.x;

	if (m_pos.x < -700.0f)
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

void C_Enemy::PlayerHit()
{
	/*C_Player* m_player = ->GetPos();
	if ()
	{
		float dx = ;
		float dy = ;
		float distSq = (dx * dx) + (dy * dy);

		if (distSq < (30.0f * 30.0f))
		{
			
		}
	};*/
}


void C_Enemy::SetTex(KdTexture* Tex)
{
	m_tex = Tex;
}

Math::Vector2 C_Enemy::GetPos()
{
	return m_pos;
}
