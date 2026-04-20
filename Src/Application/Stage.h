#pragma once
#include "Wall.h"

class Stage {
public:
	void Initialize(KdTexture* tex);
	void Update();
	void Draw();
	void DrawDebug();
	
private:
	Wall m_wallL;
	Wall m_wallR;
};
