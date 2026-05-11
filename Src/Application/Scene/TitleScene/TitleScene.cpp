#include "TitleScene.h"
#include "../../main.h"
#include "../GameScene/GameScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{
	m_tex.Load("Texture/title.png");
	m_startTex.Load("Texture/start.png");

	m_alpha = 1.0f;     // 最初ははっきり見える
	m_alphaAdd = -0.02f; //
}

void TitleScene::Update()
{
	m_alpha += m_alphaAdd;
	if (m_alpha < 0.0f)
	{
		m_alpha = 0.3f;
		m_alphaAdd *= -1;
	}
	else if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SCENE.SetNextScene(SceneManager::SceneType::Game);
	}

}

void TitleScene::Draw()
{

	Math::Matrix identity = Math::Matrix::Identity;
	SHADER.m_spriteShader.SetMatrix(identity);

	// 背景画像を描画（座標などは適宜調整してください）
	Math::Rectangle rc = { 0, 0, 1280, 720 };
	// m_tex（title.png）を描画
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &rc);

	// 文字（start.png）を点滅させて描画
	Math::Rectangle startRc = { 0,0,512,128 };
	Math::Color color = { 1, 1, 1, m_alpha }; // Updateで作っているm_alphaを使う
	SHADER.m_spriteShader.DrawTex(&m_startTex, 0, -200,&startRc, &color);
}

void TitleScene::Release()
{
}
