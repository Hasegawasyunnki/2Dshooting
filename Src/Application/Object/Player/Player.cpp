#include "Player.h"
#include "../Enemy/Enemy.h"

C_Player::~C_Player()
{
	m_bulletTex.Release();
}

void C_Player::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_bulletTex.Load("Texture/bullet.png");
	for (int i = 0; i < m_bulletNum; i++)
	{
		m_bullet[i].Init();
		m_bullet[i].SetTex(&m_bulletTex);
	}
}

void C_Player::Update(POINT mousePos)
{
	if (GetAsyncKeyState('W') & 0x8000)m_pos.y += m_moveSpeed;
	if (GetAsyncKeyState('A') & 0x8000)m_pos.x -= m_moveSpeed;
	if (GetAsyncKeyState('S') & 0x8000)m_pos.y -= m_moveSpeed;
	if (GetAsyncKeyState('D') & 0x8000)m_pos.x += m_moveSpeed;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		for (int i = 0; i < m_bulletNum; i++)
		{
			if (!m_bullet[i].GetAlive())
			{
				const float x = mousePos.x - m_pos.x;
				const float y = mousePos.y - m_pos.y;
				const float radian = atan2(y, x);

				m_bullet[i].Shot(m_pos, radian);
				break;
			}
		}
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix rotation = Math::Matrix::CreateRotationZ(-DirectX::XM_PIDIV2);
	Math::Matrix translation = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = rotation * translation;
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
				enemyList[i].Hit();
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
			enemyList[i].Hit();
		}
	}
}

void C_Player::SetTex(KdTexture* Tex)
{
	m_tex = Tex;
}

Math::Vector2 C_Player::GetPos()
{
	return m_pos;
}
