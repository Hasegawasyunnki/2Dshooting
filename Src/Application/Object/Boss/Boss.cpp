#include "../Boss/Boss.h"

C_Boss::C_Boss()
{
	//m_tex->Load("Texture/boss.png");
	/*m_hp = 50;
	SetPos(0.0f, 0.0f);
	m_alive = true;
	m_dead = false;*/
}

void C_Boss::Init()
{
	m_pos = { 1000.0f,0.0f };
	m_alive = false;
	m_hp = 50;
	m_timer = 0.0f;
}

void C_Boss::Update()
{
	if (!m_alive)return;

	m_timer += 0.02f;

	if (m_pos.x > 400.0f) {
		m_pos.x -= 2.0f;
		m_pos.y = sinf(m_timer) * 200.0f;
	}

	//m_pos.y = sinf(m_timer) * 200.0f;

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void C_Boss::Draw()
{
	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 128, 128), 1.0f);
}

void C_Boss::OnDamage(int damage)
{
	m_hp -= damage;

	char buf[256];
	sprintf_s(buf, "Boss HP: %d\n", m_hp);
	OutputDebugStringA(buf);

	if (m_hp <= 0)
	{
		m_alive = false;
	}
}

