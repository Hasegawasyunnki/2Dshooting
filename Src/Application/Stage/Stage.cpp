#include "Stage.h"

void Stage::Initialize(KdTexture* tex)
{
	//m_wallL.Initialize(-624.0f, 0.0f, 32.0f, 720.0f);

	//// 右側の壁：中心から右に624ピクセル
	//m_wallR.Initialize(624.0f, 0.0f, 32.0f, 720.0f);

	//m_wallL.SetTex(tex);
	//m_wallR.SetTex(tex);
	m_tex = tex;
}

void Stage::Update()
{
	float scrollSpeed = 1.5f;
	m_bgX1 -= scrollSpeed;

	float totalWidth = 2540.0f;

	if (m_bgX1 <= -totalWidth)
	{
		m_bgX1 += totalWidth; 
	}
}

void Stage::Draw()
{
	Math::Rectangle srcRect = Math::Rectangle(5, 0, 1270, 720);
	float step = 1270.0f;

	Math::Matrix mat0 = Math::Matrix::CreateScale(-1.0f, 1.0f, 1.0f) * Math::Matrix::CreateTranslation(m_bgX1 - step, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat0);
	SHADER.m_spriteShader.DrawTex(m_tex, srcRect, 1.0f);

	Math::Matrix mat1 = Math::Matrix::CreateTranslation(m_bgX1, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat1);
	SHADER.m_spriteShader.DrawTex(m_tex, srcRect, 1.0f);

	Math::Matrix mat2 = Math::Matrix::CreateScale(-1.0f, 1.0f, 1.0f) * Math::Matrix::CreateTranslation(m_bgX1 + step, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat2);
	SHADER.m_spriteShader.DrawTex(m_tex, srcRect, 1.0f);

	Math::Matrix mat3 = Math::Matrix::CreateTranslation(m_bgX1 + (step * 2.0f), 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat3);
	SHADER.m_spriteShader.DrawTex(m_tex, srcRect, 1.0f);

}

void Stage::DrawDebug()
{
	/*if (ImGui::Begin("Debug Window")) {

		ImGui::Text("WallL Left: %ld", m_wallL.GetRect().left);
		ImGui::Text("WallR Left: %ld", m_wallR.GetRect().left);
	}
	ImGui::End();*/
}
