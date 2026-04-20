#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Stage.h"

class Scene
{
private:

	Stage m_stage;

	C_Player m_player;  //クラスの変数
	C_Enemy m_enemy[10];   //クラスの変数

	int m_enemyNum;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_wallTex;

	POINT m_mousePos;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	void CalcMousePos();

	C_Enemy* GetEnemy();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
