#pragma once

#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	KdTexture m_tex;
	KdTexture m_startTex;

	float m_alpha = 1;
	float m_alphaAdd = -0.03f;
};