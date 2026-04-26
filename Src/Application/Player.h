#pragma once
#include "Bullet.h"
class Scene; //ëOï˚êÈåæ
class Bullet;
class C_Enemy;

class C_Player
{
public:

	C_Player();
	 ~C_Player();

	 void Init();
	 void Update(POINT mousePos);
	 void Draw();
	 void CheckHitBullet(C_Enemy* enemyList, int enemyNum);
	 void CheckHitPlayer(C_Enemy* enemyList, int enemyNum);

	 void SetTex(KdTexture* Tex);
	 void SetOwner(Scene*owner);


	 C_Bullet* GetBullet(int index) { return &m_bullet[index]; }

	 Math::Vector2 GetPos();

private:

	Scene* m_owner;


	 static const int m_bulletNum = 100;
	 C_Bullet m_bullet[m_bulletNum];
	 KdTexture m_bulletTex;

	 const float m_moveSpeed = 5.0f;
	 const float playerHp = 100.0f;
	
	 KdTexture* m_tex;
	 Math::Vector2 m_pos; //ç¿ïW
	 Math::Matrix m_mat;
};