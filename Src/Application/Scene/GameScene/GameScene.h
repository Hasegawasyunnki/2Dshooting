#pragma once
#include "../BaseScene/BaseScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Stage/Stage.h"
#include "../../Bullet/Bullet.h"
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
	void ResetGame();
	void AddScore(int value);
	int GetScore() const { return m_score; }

	void SpawnBoss();


private:
	Stage m_stage;
	C_Player m_player;
	C_Enemy m_enemy[10];
	int m_enemyNum;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_stageTex;
	KdTexture m_backTex;

	int m_score = 0;

	int m_deadEnemyCount = 0;	//敵死亡数カウント
	bool m_isBossSpawned = false;
	std::vector<C_Enemy*> m_enemyList;
	
	POINT m_mousePos;
};