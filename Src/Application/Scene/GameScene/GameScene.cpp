#include "GameScene.h"
#include "../../main.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Boss/Boss.h"
	
GameScene::~GameScene()
{
	for (auto enemy : m_enemyList)
	{
		delete enemy;
	}
	m_enemyList.clear();

	Release();
}

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
	m_player.Update();

	m_player.CheckHitBullet(m_enemy, m_enemyNum);
	m_player.CheckHitPlayer(m_enemy, m_enemyNum);

	m_stage.Update();

	Math::Vector2 pPos = m_player.GetPos();

	for (auto enemy : m_enemyList) {
		if (enemy != nullptr) {
			enemy->SetTargetPos(pPos.x, pPos.y);
		}
	}

	//for (auto enemy : m_enemyList) {
	//	enemy->Update();
	//}

	for (int i = 0;i < m_enemyNum;i++)
	{
		m_enemy[i].Update();
	}

	// 敵の倒された数をカウント
	auto it = m_enemyList.begin();
	while (it!=m_enemyList.end()){
		if ((*it)->IsDead()) {
			m_deadEnemyCount++;
			//delete(*it);
			it = m_enemyList.erase(it);
		}
		else {
			(*it)->Update();
			++it;
		}
	}

	//　ボス出現条件
	if (!m_isBossSpawned && m_deadEnemyCount >= 10)
	{
		SpawnBoss();
		m_isBossSpawned = true;
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

	//　スコア仮表示
	char scoreStr[64];
	sprintf_s(scoreStr, "SCORE: %d", m_score);

	Math::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.DrawString(-600.0f,320.0f,scoreStr,color);

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
	m_enemyNum = (rand() % 10) + 3;
	for (int i = 0; i < m_enemyNum;i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetTex(&m_enemyTex);
		m_enemy[i].SetOwner(this);

		float tx = 300.0f + (i * 60.0f)+(rand()%20);
		float ty = -200.0f + ((i % 5) * 100.0f)*(rand()%30-15);
		m_enemy[i].SetTargetPos(tx, ty);

		float customStopX = 400.0f + (i + 50.0f);
		m_enemy[i].SetStopX(customStopX);

		EnemyType randomType = static_cast<EnemyType>(rand() % 3);
		m_enemy[i].SetType(randomType);

		float startX = 800.0f + (i * 250.0f);
		float startY = (float)(rand() % 600 - 300);
		m_enemy[i].SetPos(startX,startY);

		m_enemy[i].Update();
	}
}

void GameScene::AddScore(int value)
{
	m_score += value;

	char buf[256];
	sprintf_s(buf, "Current Score: %d\n", m_score);
	OutputDebugStringA(buf);
}

void GameScene::SpawnBoss()
{
	/*C_Boss* newBoss = new C_Boss();
	m_enemyList.push_back(newBoss);*/
}
