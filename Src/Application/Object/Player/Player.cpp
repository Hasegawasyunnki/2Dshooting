#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../../Scene/GameScene/GameScene.h"

C_Player::~C_Player()
{
	m_bulletTex.Release();
}

void C_Player::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_life = 10;
	m_alive = true;

	m_bulletTex.Load("Texture/bullet.png");
	for (int i = 0; i < m_bulletNum; i++)
	{
		m_bullet[i].Init();
		m_bullet[i].SetTex(&m_bulletTex);
	}
}

void C_Player::Update()
{
	if (m_life <= 0)
	{
		m_life = 0;
		m_alive = false;
		return;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)	m_pos.y += m_moveSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) m_pos.y -= m_moveSpeed;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) m_pos.x -= m_moveSpeed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += m_moveSpeed;

	//　画面外制限
	m_pos.y = std::max(-300.0f, std::min(300.0f, m_pos.y));
	m_pos.x = std::max(-600.0f, std::min(600.0f, m_pos.x));

	Math::Matrix rotation = Math::Matrix::CreateRotationZ(-DirectX::XM_PIDIV2);
	Math::Matrix translation = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = rotation * translation;

	m_shotTimer++;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_shotTimer > 10)
		{
			for (int i = 0; i < m_bulletNum; i++)
			{
				if (!m_bullet[i].GetAlive())
				{
					float tempAngle = 0.0f;

					if (GetAsyncKeyState('R') & 0x8000)
					{
						if (GetAsyncKeyState('W') & 0x8000)tempAngle = 0.785f; // 約 -45度
						else if (GetAsyncKeyState('S') & 0x8000)tempAngle = -0.785f;  // 約 +45度
					}
					else
					{
						tempAngle = 0.0f;
					}
	
					m_bullet[i].Shot(m_pos, tempAngle);

					m_shotTimer = 0;
					break;
					}
				}
			}
		}


	//m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	
	for (int i = 0; i < m_bulletNum; i++)
	{
		m_bullet[i].Update();
	}
}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
	for (int i = 0; i < m_bulletNum; i++)
	{
		m_bullet[i].Draw();
	}
}

//弾の当たり判定
void C_Player::CheckHitBullet(C_Enemy* enemyList, int enemyNum)
{
	for (int b = 0; b < m_bulletNum; b++) {
		if (!m_bullet[b].GetAlive()) continue;
		for (int i = 0; i < enemyNum; i++) {
			if (!enemyList[i].IsAlive()) continue;

			float dx = m_bullet[b].GetPos().x - enemyList[i].GetPos().x;
			float dy = m_bullet[b].GetPos().y - enemyList[i].GetPos().y;
			if ((dx * dx) + (dy * dy) < (30.0f * 30.0f)) {
				enemyList[i].Hit(true);
				m_bullet[b].Hit();
			}
		}
	}
}

//敵と自機の当たり判定
void C_Player::CheckHitPlayer(C_Enemy* enemyList, int enemyNum)
{
	for (int i = 0; i < enemyNum; i++) {
		if (!enemyList[i].IsAlive()) continue;

		float dx = m_pos.x - enemyList[i].GetPos().x;
		float dy = m_pos.y - enemyList[i].GetPos().y;
		if ((dx * dx) + (dy * dy) < (60.0f * 60.0f)) {
			enemyList[i].Hit(false);
		}
	}
}

void C_Player::CheckHitBoss(C_Boss* pBoss)
{
	if (!pBoss || !pBoss->IsAlive())return;

	for (int i = 0;i < m_bulletNum;i++) 
	{
		if (!m_bullet[i].GetAlive())continue;

		float dx = m_bullet[i].GetPos().x - pBoss->GetPos().x;
		float dy = m_bullet[i].GetPos().y - pBoss->GetPos().y;
		float distSq = (dx * dx) + (dy * dy);

		if (distSq < (90.0f*90.0f))
		{
			m_bullet[i].Hit();
			pBoss->OnDamage(1);
			if (m_owner)m_owner->AddScore(10);
		}
	}
}

void C_Player::SetTex(KdTexture* Tex)
{
	m_tex = Tex;
}

void C_Player::PlayerHp()
{
	/*if (m_life <= 0)
	{
		m_life = 0;
		m_alive = false;
	}*/
}

void C_Player::LostLife()
{
	if (m_life > 0)
	{
		m_life--;
	}
}

Math::Vector2 C_Player::GetPos()
{
	return m_pos;
}
