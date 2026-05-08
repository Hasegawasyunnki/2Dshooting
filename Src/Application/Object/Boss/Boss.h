#pragma once
#include "../Enemy/Enemy.h"

class C_Boss : public C_Enemy
{
public:
	C_Boss() ;
	~C_Boss() {};

	void Update();
	void Draw();

private:

	int m_hp;
	int m_attackTimer = 0;
};
