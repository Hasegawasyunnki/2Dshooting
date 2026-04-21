#include "Wall.h"

void Wall::Initialize(float x, float y, float width, float height)
{
	m_pos.x = x;
	m_pos.y = y;
	m_width = width;
	m_height = height;

	m_rect.left = (long)(x - width / 2);
	m_rect.right = (long)(x + width / 2);
	m_rect.top = (long)(y + height / 2);
	m_rect.bottom = (long)(y - height/2);
}

void Wall::Draw()
{
	if (!m_tex)return;

	float texW = (float)m_tex->GetInfo().Width;
	float texH = (float)m_tex->GetInfo().Height;

	Math::Matrix m_mat = Math::Matrix::CreateScale(m_width/texW, m_height/texH, 1.0f)
		*Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);

	SHADER.m_spriteShader.SetMatrix(m_mat);

	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, (int)texW, (int)texH));
	
	//SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, (int)m_width, (int)m_height));
}

void Wall::Hit()
{
}


