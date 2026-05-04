#pragma once

// 前方宣言
class BaseScene;

class SceneManager
{
public:

	enum SceneType
	{
		Title,
		Game,
		Result,
	};

	void PreUpdate();
	void Update();
	void Draw();

	// 次のシーンを予約する
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}
	// 現在のシーンを取得する
	SceneType GetCurrentSceneType()const
	{
		return m_currentSceneType;
	}

	void ImGuiUpdate() {
		if (m_currentScene) {
			// 必要に応じて、BaseSceneにも virtual void ImGuiUpdate() = 0; を追加してください
			// m_currentScene->ImGuiUpdate(); 
		}
	}

private:

	
	void Init();
	void Release();
	void ChangeScene(SceneType _sceneType);

	// 変数
	std::shared_ptr<BaseScene> m_currentScene;	//現在のシーンを管理しているポインタ

	SceneType  m_currentSceneType = SceneType::Game;		// 現在のシーンの種類
	SceneType  m_nextSceneType = m_currentSceneType;	// 次のシーンの種類

private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}

};
#define SCENE SceneManager::Instance()
