#pragma once
#include "../../Bullet/Bullet.h"
class GameScene; //前方宣言
class C_Enemy;
class C_Boss;

class C_Player
{
public:

	C_Player() {};
	~C_Player();

	void Init();
	void Update();
	void Draw();
	void CheckHitBullet(C_Enemy* enemyList, int enemyNum);
	void CheckHitPlayer(C_Enemy* enemyList, int enemyNum);
	void CheckHitBoss(C_Boss* pBoss);
	void SetTex(KdTexture* Tex);
	void SetOwner(GameScene* owner) { m_owner = owner; };
	void PlayerHp();
	void LostLife();

	C_Bullet* GetBullet(int index) { return &m_bullet[index]; }
	Math::Vector2 GetPos();

	int GetLife() const { return m_life; }

private:

	GameScene* m_owner;

	static const int m_bulletNum = 100;
	C_Bullet m_bullet[m_bulletNum];
	KdTexture m_bulletTex;

	const float m_moveSpeed = 5.0f;
	int m_life = 3;
	bool m_alive;

	int m_shotTimer = 0;
	std::list<C_Bullet> m_bulletList;

	// 自機の弾管理
	bool   m_isTreeWay		= false;
	float  m_powerUpTimer	= 0.0f;
	float  m_zCoolTimer		= 0.0f;
	const float POWERUP_DURATION = 300.0f;
	const float Z_COOL_TIME = 600.0f;

	float m_animeTimer = 0.0f;
	int   m_animeIndex = 0;

	KdTexture* m_tex;
	Math::Vector2 m_pos; //座標
	Math::Matrix m_mat;
};