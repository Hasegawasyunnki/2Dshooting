#pragma once

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {}

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:

	KdTexture m_tex;
	KdTexture m_startTex;

	float m_alpha = 1;
	float m_alphaAdd = -0.03f;
};