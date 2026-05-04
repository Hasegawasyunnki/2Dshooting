#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

void SceneManager::PreUpdate()
{
	// シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	if (m_currentScene)
	{
		m_currentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (m_currentScene)
	{
		m_currentScene->Draw();
	}
}

void SceneManager::Init()
{
	ChangeScene(SceneType::Game);
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// ①次のシーンを作成し、②シーン管理フラグ更新
	switch (_sceneType)
	{
	case SceneManager::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	}
	if (m_currentScene)
	{
		m_currentScene->Init();
	}
	m_currentSceneType = _sceneType;
}
#define SCENE SceneManager::Instance()