#include "main.h"
#include "Scene.h"
#include "Stage.h"
#include "Enemy.h"

void Scene::Init()
{
	m_player.Init();
	m_enemy[0].Init();

	m_enemyNum = (rand() % 8) + 3;

	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetTex(&m_enemyTex);

		float areaWidth = 640.0f / m_enemyNum;
		float startX = -320.0f + (areaWidth * i);

		float posX = startX + (float)(rand() % (int)areaWidth);
	}

	m_playerTex.Load("Texture/player.png");
	m_enemyTex.Load("Texture/enemy.png");
	m_wallTex.Load("Texture/wall.png");

	m_player.SetTex(&m_playerTex);
	m_stage.Initialize(&m_wallTex);

	m_player.SetOwner(this);

	m_stage.Initialize(&m_playerTex);

	/*m_wallL.Initialize(0, 0, 32, 720);
	m_wallR.Initialize(1248, 0, 32, 720);*/
}

void Scene::Update()
{
	CalcMousePos();

	m_player.Update(m_mousePos);

	int aliveCount = 0;
	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Update();

		if (m_enemy[i].IsAlive())
		{
			aliveCount++;
		}
	}
	if (aliveCount == 0)
	{
		this->Init();
	}
}

void Scene::Draw2D()
{
	m_player.Draw();

	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Draw();
	}

	m_stage.Draw();
}

void Scene::Release()
{
	m_playerTex.Release();
	m_enemyTex.Release();
}

void Scene::ImGuiUpdate()
{
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		m_stage.DrawDebug();
	}
	ImGui::End();
}

void Scene::CalcMousePos()
{
	GetCursorPos(&m_mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	m_mousePos.x -= 640;
	m_mousePos.y -= 360;
	m_mousePos.y *= -1;
}

C_Enemy* Scene::GetEnemy()
{
	return m_enemy;
}
