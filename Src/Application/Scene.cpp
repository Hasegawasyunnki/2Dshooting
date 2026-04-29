#include "main.h"
#include "Scene.h"
#include "../Application/Stage/Stage.h"
#include "../Application/Enemy/Enemy.h"



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
	m_stageTex.Load("Texture/background.png");
	//m_wallTex.Load("Texture/wall.png");

	m_player.SetTex(&m_playerTex);
	m_stage.Initialize(&m_stageTex);

	m_player.SetOwner(this);

	//m_stage.Initialize(&m_playerTex);

	ResetGame();
	
	/*m_wallL.Initialize(0, 0, 32, 720);
	m_wallR.Initialize(1248, 0, 32, 720);*/
}

void Scene::Update()
{
	CalcMousePos();
	m_player.Update(m_mousePos);

	m_player.CheckHitBullet(m_enemy, m_enemyNum);
	m_player.CheckHitPlayer(m_enemy, m_enemyNum);

	m_stage.Update();

	//int aliveCount = 0;
	//for (int i = 0; i < m_enemyNum; i++)
	//{
	//	if (m_enemy[i].IsAlive())
	//	{
	//		m_enemy[i].Update();
	//		aliveCount++;
	//	}
	//}

	//if (aliveCount == 0)
	//{
	//	this->ResetGame();
	//}
	for(int i=0;i<m_enemyNum;i++)
	{
		m_enemy[i].Update();
	}
}

void Scene::Draw2D()
{
	m_stage.Draw();

	m_player.Draw();

	for (int i = 0; i < m_enemyNum; i++)
	{
		if (m_enemy[i].IsAlive())
		{
			m_enemy[i].Draw();
		}
	}

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

void Scene::ResetGame()
{
	m_enemyNum = (rand() % 8) + 3;
	for (int i = 0;i < m_enemyNum;i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetTex(&m_enemyTex);

		float startX = 800.0f + (i * 250.0f);
		m_enemy[i].SetPos(startX, (float)(rand() % 600 - 300));

		m_enemy[i].Update();
	}
}

C_Enemy* Scene::GetEnemy()
{
	return m_enemy;
}
