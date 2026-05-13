#include "Enemy.h"
#include "../Player/Player.h"
#include "../../Scene/GameScene/GameScene.h"

void C_Enemy::Init()
{
	m_pos = { 2000.0f,2000.0f };
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0); 
	m_move.x = -3.0f;
	m_move.y = 0.0f;
	m_timer = 0.0f;
	m_stopX = (float)(rand() % 351 + 100);
	m_hoverOffset = (float)(rand() % 121 - 60);
	m_alive = false;
	m_dead = false;
	
	m_targetOffset.x = (float)(rand() % 201 - 100);
	m_targetOffset.y = (float)(rand() % 201 - 100);

	m_shotTimer = 1000;
	/*if (rand() % 2 == 0)
	{
		m_pos.x = (float)((rand() % 220) + 100);
	}
	else
	{
		m_pos.x = (float)((rand() % 220) - 320);
	}*/
}

void C_Enemy::Update()
{
	if (!m_alive)return;
	float currentSpeed = m_moveSpeed;
	UpdateMovePattern(currentSpeed);

	if (m_pos.x < -800.0f || m_pos.x>1200.0f)
	{
		m_alive = false;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Enemy::Draw()
{
	if (!m_alive)return;

	int offsetX = 0;
	Math::Rectangle srcRect = { 64,64,-64,64 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, 0, 0, &srcRect);
}

void C_Enemy::Hit(bool isDefeated)
{
	if (!m_alive)return;

	// スコア加算
	if (m_pOwner != nullptr && isDefeated)
	{
		m_pOwner->AddScore(100);
	}
	else 
	{
		m_pOwner->AddScore(-50);
	}
	
	// 自機の体力を減らす
	if (!isDefeated && m_playerPtr != nullptr)
	{
		m_playerPtr->LostLife();
	}

	m_pos.x = 900.0f;
	m_pos.y = (float)(rand() % 600 - 300);
	m_alive = false;
	m_type = static_cast<EnemyType>(rand() % 3);
	m_timer = 0.0f;
}

void C_Enemy::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Enemy::SetTargetPos(float x, float y)
{
	m_targetPos.x = x;
	m_targetPos.y = y;
}

void C_Enemy::Shoot()
{
	if (m_pOwner)
	{
		m_pOwner->SpawnEnemyBullet(m_pos);
	}
}

void C_Enemy::UpdateMovePattern(float speed)
{
	m_timer += 0.02f;
	switch (m_type)
	{
	case EnemyType::Straight:
		m_pos.x -= 8.0f;
		break;

	case EnemyType::SineWave:
		m_pos.x -= 6.0f;
		m_pos.y += sinf(m_timer * 2.0f) * 3.0f;

		if (m_pos.y > 280.0f)m_pos.y = 280.0f;
		if (m_pos.y < -280.0f)m_pos.y = -280.0f;
		break;

	case EnemyType::StopShot:

		if (m_pos.x > m_stopX)
		{
			m_pos.x -= 8.0f;
		}
		else
		{
			// 停止後の上下移動などの処理...
			m_shotTimer++;
			int coolTime = 120;

			if (m_shotTimer >= coolTime)
			{
				Shoot();
				m_shotTimer = 0;
			}
		}
		break;
		
	//case EnemyType::Homing:
	//{
	//	//Math::Vector2 target = { m_targetPos.x + m_targetOffset.x,m_targetPos.y + m_targetOffset.y };

	//	/*if (m_pos.x < m_targetPos.x - 100.0f)
	//	{
	//		target.x += 50.0f;
	//	}*/
	//	Math::Vector2 target = m_targetPos += m_targetOffset;

	//	Math::Vector2 current = { m_pos.x,m_pos.y };
	//	Math::Vector2 enemyMove = target - current;

	//	if (enemyMove.LengthSquared() > 1.0f)
	//	{
	//		enemyMove.Normalize();
	//		/*float finalSpeed = speed;
	//		if (target.x > current.x)
	//		{
	//			finalSpeed = speed + 2.0f;
	//		}*/

	//		/*m_pos.x += enemyMove.x * finalSpeed;
	//		m_pos.y += enemyMove.y * finalSpeed;*/
	//		m_pos += enemyMove * speed;
	//	}
	//	break;
	//}

	default:
		break;
	}

	if (m_pOwner != nullptr)
	{
		for (int i = 0; i < 30; i++)
		{
			C_Enemy* other = m_pOwner->GetEnemyPtr(i);
			if (other == nullptr || other == this || !other->IsAlive()) continue;

			float dist = Math::Vector2::Distance(m_pos, other->GetPos());
			if (dist < 50.0f) 
			{
				
				if (m_pos.y > other->GetPos().y) m_pos.y += 2.0f;
				else m_pos.y -= 2.0f;

				if (m_type == EnemyType::StopShot) {
					if (m_pos.x > other->GetPos().x) m_pos.x += 1.0f;
					else m_pos.x -= 1.0f;
				}
			}
		}
	}
	if (m_pos.y > 300.0f) m_pos.y = 300.0f;
	if (m_pos.y < -300.0f) m_pos.y = -300.0f;

}
