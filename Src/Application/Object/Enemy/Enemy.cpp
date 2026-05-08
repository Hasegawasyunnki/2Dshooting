#include "Enemy.h"
#include "../Player/Player.h"
#include "../../Scene/GameScene/GameScene.h"

void C_Enemy::Init()
{
	m_pos.x = 800.0f;
	m_pos.y = (float)(rand() % 600 - 300);
	m_move.x = -3.0f;
	m_move.y = 0.0f;
	m_timer = 0.0f;
	m_stopX = (float)(rand() % 301 + 400);
	m_alive = true;
	
	if (rand() % 2 == 0)
	{
		m_pos.x = (float)((rand() % 220) + 100);
	}
	else
	{
		m_pos.x = (float)((rand() % 220) - 320);
	}
}

void C_Enemy::Update()
{
	if (!m_alive)return;

	UpdateMovePattern();
	
	if (m_pos.x < -800.0f)
	{
		m_pos.x = 800.0f;
		m_pos.y = (float)(rand() % 600 - 300);
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
	if (!m_alive)return;

	if (m_pOwner!=nullptr)
	{
		m_pOwner->AddScore(100);
	}

	m_pos.x = 900.0f;
	m_pos.y = (float)(rand() % 600 - 300);
	m_alive = true;
	m_type = static_cast<EnemyType>(rand() % 3);
	m_timer = 0.0f;
}

void C_Enemy::PlayerHit()
{

}


void C_Enemy::SetTex(KdTexture* Tex)
{
	m_tex = Tex;
}

void C_Enemy::SetTargetPos(float x, float y)
{
	m_targetPos.x = x;
	m_targetPos.y = y;
}

void C_Enemy::UpdateMovePattern()
{
	m_timer += 0.02f;
	switch (m_type)
	{
	case EnemyType::Straight:
		m_pos.x -= 5.0f;
		break;

	case EnemyType::SineWave:
		m_pos.x -= 4.0f;
		m_pos.y += sinf(m_timer * 2.0f) * 3.0f;
		break;

	case EnemyType::StopShot:
		if (m_pos.x > m_targetPos.x)
		{
			m_pos.x -= 7.0f;
		}
		if (abs(m_pos.y - m_targetPos.y) > 5.0f) 
		{
			if (m_pos.y < m_targetPos.y)m_pos.y += 2.0f;
			else m_pos.y = -2.0f;
		}
		break;
		
	case EnemyType::Homing:
	{
		Math::Vector2 target = { m_targetPos.x,m_targetPos.y };
		Math::Vector2 current = { m_pos.x,m_pos.y };
		Math::Vector2 enemyMove = target - current;

		if (enemyMove.LengthSquared() > 0.001f)
		{
			enemyMove.Normalize();
			m_pos.x += enemyMove.x * 3.0f;
			m_pos.y += enemyMove.y * 3.0f;
		}
		break;
	}

	default:
		break;
	}
}
