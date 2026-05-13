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

	KdTexture m_texBack;	// 背景
	KdTexture m_texLogo;	// タイトルロゴ
	KdTexture m_texStart;	//スタート画面

	Math::Vector2 m_posLogo = { 0,150 };
	Math::Vector2 m_posStart = { 0,-100 };

	float m_alpha = 1;
	float m_alphaAdd = -0.03f;
};