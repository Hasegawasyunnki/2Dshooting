#pragma once
#include "../BaseScene/BaseScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Stage/Stage.h"
#include "../../Bullet/Bullet.h"

class GameScene : public BaseScene
{
public:
	GameScene() {}
	~GameScene() { Release(); }

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void CalcMousePos();
	void ResetGame();

private:
	Stage m_stage;
	C_Player m_player;
	C_Enemy m_enemy[10];
	int m_enemyNum;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_stageTex;
	KdTexture m_backTex;

	POINT m_mousePos;
};