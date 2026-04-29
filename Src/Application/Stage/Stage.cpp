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
	float scrollSpeed = 2.0f;

	m_bgX1 -= scrollSpeed;
	m_bgX2 -= scrollSpeed;

	if (m_bgX1 <= -1280.0f)
	{
		m_bgX1 = m_bgX2 + 1280.0f;
	}

	if (m_bgX2 <= -1280.0f)
	{
		m_bgX2 = m_bgX1 + 1280.0f;
	}
}

void Stage::Draw()
{
	/*m_wallL.Draw();
	m_wallR.Draw();*/
	Math::Matrix mat1 = Math::Matrix::CreateTranslation(m_bgX1, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat1);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	Math::Matrix mat2 = Math::Matrix::CreateTranslation(m_bgX2, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat2);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

}

void Stage::DrawDebug()
{
	/*if (ImGui::Begin("Debug Window")) {

		ImGui::Text("WallL Left: %ld", m_wallL.GetRect().left);
		ImGui::Text("WallR Left: %ld", m_wallR.GetRect().left);
	}
	ImGui::End();*/
}
