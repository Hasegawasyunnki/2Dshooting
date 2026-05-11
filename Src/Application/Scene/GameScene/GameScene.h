#pragma once
#include "../BaseScene/BaseScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Stage/Stage.h"
#include "../../Bullet/Bullet.h"
#include "../../Object/Boss/Boss.h"
#include "../../EnemyBullet/EnemyBullet.h"
#include <vector>

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void CalcMousePos();
	void SpawnWave(int waveNum);
	void SpawnEnemyBullet(Math::Vector2 pos);
	void ResetGame();
	void AddScore(int value);
	int GetScore() const { return m_score; }

	void SpawnBoss();
	C_Enemy* GetEnemyPtr(int index) { return &m_enemy[index]; }


private:
	Stage		m_stage;
	C_Player	m_player;
	C_Enemy		m_enemy[30];
	C_Boss		m_boss;
	EnemyBullet  m_enemyBullet[50];
	int			m_enemyNum;
	
	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_bossTex;
	KdTexture m_stageTex;
	KdTexture m_backTex;
	KdTexture   m_bulletTex;

	int m_score = 0;
	int m_displayScore = 0;

	int m_deadEnemyCount = 0;	//敵死亡数カウント
	bool m_isBossSpawned = false;
	int m_maxHomingCount = 2;

	int m_currentWave = 0;
	int m_enemyCountInWave = 0;
	
	POINT m_mousePos;
};