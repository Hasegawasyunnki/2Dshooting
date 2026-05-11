#pragma once
#include "../BaseScene/BaseScene.h"
#include "../../Stage/Stage.h"
class ResultScene : public BaseScene
{
public:
	ResultScene() {}
	~ResultScene() { Release(); }

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void SetScore(int _score) { m_finalScore = _score; }

private:
	Stage		m_stage;
	KdTexture	m_stageTex;
	KdTexture	m_bgTex;
	KdTexture	m_fontTex;
	int			m_waitTimer = 0;
	int			m_finalScore;
	int			m_displayScore = 0;
};