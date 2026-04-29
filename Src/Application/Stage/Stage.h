#pragma once
#include "../Wall.h"
class Wall;

class Stage {
public:
	void Initialize(KdTexture* tex);
	void Init();
	void Update();
	void Draw();
	void DrawDebug();

private:
	/*Wall m_wallL;
	Wall m_wallR;*/
	float m_bgX1 = 0.0f;
	float m_bgX2 = 1280.0f;

	KdTexture* m_tex;
};
