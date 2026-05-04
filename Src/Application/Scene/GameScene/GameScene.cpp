#include "../../main.h"
#include "GameScene.h"

void GameScene::Init()
{
	m_playerTex.Load("Texture/player.png");
	m_enemyTex.Load("Texture/enemy.png");
	m_stageTex.Load("Texture/background.png");

	m_player.Init();
	m_player.SetTex(&m_playerTex);
	m_player.SetOwner(this);

	m_stage.Initialize(&m_stageTex);
	ResetGame();
}

void GameScene::Update()
{
	CalcMousePos();
	m_player.Update(m_mousePos);

	m_player.CheckHitBullet(m_enemy, m_enemyNum);
	m_player.CheckHitPlayer(m_enemy, m_enemyNum);

	m_stage.Update();

	for (int i = 0;i < m_enemyNum;i++)
	{
		m_enemy[i].Update();
	}
}

void GameScene::Draw()
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

	/*float startX = -600.0f;
	float startY = 320.0f;
	float interval = 40.0f;

	if (m_playerTex.GetSRView() == nullptr)return;

	int lifeCount = m_player.GetLife();

	for (int i = 0;i < lifeCount;i++)
	{
		float x = startX + (i * interval);

		Math::Rectangle rc = { 0,0,64,64 };

		SHADER.m_spriteShader.DrawTex(&m_playerTex, x, startY, &rc);
	}*/

	
}

void GameScene::Release()
{
	m_playerTex.Release();
	m_enemyTex.Release();
}

void GameScene::CalcMousePos()
{
	GetCursorPos(&m_mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	m_mousePos.x -= 640;
	m_mousePos.y -= 360;
	m_mousePos.y *= -1;
}

void GameScene::ResetGame()
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
