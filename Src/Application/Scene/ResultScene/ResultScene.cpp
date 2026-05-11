#include "ResultScene.h"
#include "../SceneManager.h"
#include "../../main.h"

void ResultScene::Init()
{
	m_stageTex.Load("Texture/background.png");
	m_stage.Initialize(&m_stageTex);

	m_finalScore = SCENE.GetLastScore();
	m_displayScore = 0;

}

void ResultScene::Update()
{
	m_waitTimer++;

	if (m_displayScore < m_finalScore)
	{
		int addSpeed = (m_finalScore - m_displayScore) / 10 + 1;

		m_displayScore += addSpeed;

		if (m_displayScore > m_finalScore)
		{
			m_displayScore = m_finalScore;
		}
	}

	if (m_waitTimer < 60)return;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SCENE.SetNextScene(SceneManager::Title);
	}
}

void ResultScene::Draw()
{
	m_stage.Draw();

	Math::Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 白文字
	Math::Vector4 yellow = { 1.0f, 1.0f, 0.0f, 1.0f }; // 黄文字（強調用）

	char scoreStr[64];
	sprintf_s(scoreStr, "SCORE: %d", m_displayScore);
	//Math::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawString(-150.0f, 0.0f, scoreStr, color);
	SHADER.m_spriteShader.DrawString(-180.0f, -100.0f, "PUSH ENTER TO TITLE", color);
}

void ResultScene::Release()
{
	m_stageTex.Release();
}
