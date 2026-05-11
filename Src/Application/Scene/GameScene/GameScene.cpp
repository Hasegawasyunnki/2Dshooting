#include "GameScene.h"
#include "../../main.h"
#include "../SceneManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Boss/Boss.h"
#include "../../EnemyBullet/EnemyBullet.h"
	
GameScene::~GameScene()
{
	/*for (auto enemy : m_enemyList)
	{
		delete enemy;
	}
	m_enemyList.clear();*/

	Release();
}

void GameScene::Init()
{
	m_playerTex.Load("Texture/player.png");
	m_enemyTex.Load("Texture/enemy.png");
	m_bossTex.Load("Texture/boss.png");
	m_stageTex.Load("Texture/background.png");
	m_bulletTex.Load("Texture/bullet.png");

	for (int i = 0; i < 50; i++) {
		m_enemyBullet[i].Init();
		m_enemyBullet[i].SetTex(&m_bulletTex);
	}

	m_player.Init();
	m_player.SetTex(&m_playerTex);
	m_player.SetOwner(this);

	m_boss.Init();
	m_boss.SetTex(&m_bossTex);
	m_boss.SetPlayer(&m_player);

	m_isBossSpawned = false;
	m_deadEnemyCount = 0;

	m_stage.Initialize(&m_stageTex);
	ResetGame();
}

void GameScene::Update()
{
	//CalcMousePos();
	m_player.Update();
	m_stage.Update();

	if (!m_isBossSpawned)
	{
		for (int i = 0;i < m_enemyNum;i++)
		{
			if (m_enemy[i].IsAlive())
			{
				m_enemy[i].SetTargetPos(m_player.GetPos().x, m_player.GetPos().y);
				m_enemy[i].Update();
			}
		}
	}

	for (int i = 0;i < 50;i++)
	{
		m_enemyBullet[i].Update();

		if (m_enemyBullet[i].IsAlive())
		{
			float dist = Math::Vector2::Distance(m_player.GetPos(), m_enemyBullet[i].GetPos());
			if (dist < 30.0f)
			{
				m_player.LostLife();
				m_enemyBullet[i].Kill();
			}
		}
	}
	
	// 当たり判定
	m_player.CheckHitBullet(m_enemy, m_enemyNum);
	m_player.CheckHitPlayer(m_enemy, m_enemyNum);

	if (m_isBossSpawned && m_boss.IsAlive()) 
	{
		m_player.CheckHitBoss(&m_boss);
	}

	//　ボス出現条件
	if (!m_isBossSpawned && m_deadEnemyCount >= 10)
	{
		SpawnBoss();
		m_isBossSpawned = true;
	}

	if (m_isBossSpawned && m_boss.IsAlive())
	{
		//m_boss.SetTargetPos(m_player.GetPos().x, m_player.GetPos().y);
		m_boss.Update();
	}

	// 雑魚敵が全滅しているか
	int aliveCount = 0;
	for (int i = 0;i < m_enemyNum;i++)
	{
		if (m_enemy[i].IsAlive())
		{
			aliveCount++;
		}
	}

	if (aliveCount <= 0 && !m_isBossSpawned)
	{
		m_currentWave++;
		SpawnWave(m_currentWave);
		return;
	}

	// スコアの動き
	if (m_displayScore < m_score)
	{
		m_displayScore += 2;
		if (m_displayScore > m_score)
		{
			m_displayScore = m_score;
		}
	}
	else if (m_displayScore > m_score)
	{
		m_displayScore -= 2;
		if (m_displayScore < m_score)
		{
			m_displayScore = m_score;
		}
	}

	if (m_isBossSpawned && !m_boss.IsAlive())
	{
		SCENE.SetLastScore(m_score);
		SCENE.SetNextScene(SceneManager::Result);
		return;
	}

	if (m_player.GetLife() <= 0)
	{
		SCENE.SetLastScore(m_score);
		SCENE.SetNextScene(SceneManager::Result);
	}
}

void GameScene::Draw()
{
	m_stage.Draw();

	for (int i = 0; i < 50; i++)
	{
		m_enemyBullet[i].Draw();
	}

	m_player.Draw();
	for (int i = 0; i < m_enemyNum; i++)
	{
		if (m_enemy[i].IsAlive()) m_enemy[i].Draw();
	}

	if (m_isBossSpawned && m_boss.IsAlive())
	{
		m_boss.Draw();
	}

	// --- 2. ライフ画像（アイコン）の描画を先に行う ---
	if (m_playerTex.GetSRView() != nullptr)
	{
		float startX = -600.0f;
		float startY = 300.0f; 
		float interval = 40.0f;
		int lifeCount = m_player.GetLife();

		for (int i = 0; i < lifeCount; i++)
		{
			float x = startX + (i * interval);

			Math::Matrix iconMat = Math::Matrix::CreateScale(0.8f) * Math::Matrix::CreateTranslation(x, startY, 0);

			SHADER.m_spriteShader.SetMatrix(iconMat);
			SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle(0, 0, 64, 64), 1.0f);
		}
	}

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	// スコア表示
	char scoreStr[64];
	sprintf_s(scoreStr, "SCORE: %d", m_displayScore);
	SHADER.m_spriteShader.DrawString(400.0f, 320.0f, scoreStr, { 1, 1, 1, 1 });

	// デバッグ表示
	int debugCount = 0;
	for (int i = 0; i < m_enemyNum; i++) {
		if (m_enemy[i].IsAlive()) debugCount++;
	}
	std::string s = "Alive Enemies: " + std::to_string(debugCount);
	SHADER.m_spriteShader.DrawString(-600.0f, 250.0f, s.c_str(), { 1, 0, 0, 1 });
}

void GameScene::Release()
{
	m_playerTex.Release();
	m_enemyTex.Release();
	m_stageTex.Release();
}

void GameScene::CalcMousePos()
{
	GetCursorPos(&m_mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	m_mousePos.x -= 640;
	m_mousePos.y -= 360;
	m_mousePos.y *= -1;
}

void GameScene::SpawnWave(int waveNum)
{
	m_enemyNum = 10;

	for (int i = 0; i < m_enemyNum; i++)
	{
		m_enemy[i].Init();
		m_enemy[i].SetTex(&m_enemyTex);
		m_enemy[i].SetOwner(this);
		m_enemy[i].SetPlayer(&m_player);

		EnemyType type = static_cast<EnemyType>(rand() % 3);

		m_enemy[i].SetType(type);

		float startX = 800.0f + (i * 60.0f); 
		float startY = (float)(rand() % 601 - 300);

		m_enemy[i].SetPos(startX, startY);
		m_enemy[i].Spawn();
	}
}

void GameScene::SpawnEnemyBullet(Math::Vector2 pos)
{
	for (int i = 0;i < 50;i++)
	{
		if (!m_enemyBullet[i].IsAlive())
		{
			m_enemyBullet[i].Shot(pos);
			break;
		}
	}
}

void GameScene::ResetGame()
{
	m_score = 0;
	m_displayScore = 0;
	m_currentWave = 1;

	SpawnWave(m_currentWave);
}

void GameScene::AddScore(int value)
{
	m_score += value;
	if (m_score < 0)m_score = 0;

	if (value > 0)
	{
		m_deadEnemyCount++;
	}

	char buf[256];
	sprintf_s(buf, "Current Score: %d\n", m_score);
	OutputDebugStringA(buf);
}

void GameScene::SpawnBoss()
{
	m_boss.SetPos(1000.0f, 0.0f);
	m_boss.Spawn();
}
