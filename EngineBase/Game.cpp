#include "World.h"


class Engine
{
public:
	/**
	 * @brief エンジン初期化処理
	 */
	static void Init()
	{
		//Engine初期化

		//ワールド初期化
		mainWorld.currentLevel = new Level;
		mainWorld.gameInstance = new GameInstance;
	}

	/**
	 * @brief エンジン更新処理
	 */
	static void Tick()
	{
		mainWorld.Input();
		mainWorld.Update(0.016f);
		mainWorld.Render();
	}

	/**
	 * @brief エンジン終了処理
	 */
	static void Exit() {

	}

};

int main() {
	Engine::Init();


	return 0;
}