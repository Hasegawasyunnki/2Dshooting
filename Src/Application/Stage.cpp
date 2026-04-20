#include "Stage.h"

void Stage::Initialize(KdTexture* tex)
{
	m_wallL.Initialize(-624.0f, 0.0f, 32.0f, 720.0f);

	// 右側の壁：中心から右に624ピクセル
	m_wallR.Initialize(624.0f, 0.0f, 32.0f, 720.0f);

	m_wallL.SetTex(tex);
	m_wallR.SetTex(tex);
}

void Stage::Update()
{

}

void Stage::Draw()
{
	m_wallL.Draw();
	m_wallR.Draw();
}

void Stage::DrawDebug()
{
	if (ImGui::Begin("Debug Window")) {
		// これでエラーが出なくなるはずです！
		ImGui::Text("WallL Left: %ld", m_wallL.GetRect().left);
		ImGui::Text("WallR Left: %ld", m_wallR.GetRect().left);
	}
	ImGui::End();
}
